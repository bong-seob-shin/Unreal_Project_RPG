// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamCharacter.h"
#include "AdamAnimInstance.h"
#include "AdamPlayerController.h"
#include "AdamCharacterStatComponent.h"
#include "AdamWeaponSword.h"
#include "AdamWeaponShield.h"
#include "AdamWeaponBow.h"
#include "AdamArrow.h"
#include "AdamObjectPool.h"
#include "PalaceGameMode.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "AdamCharacterWidget.h"


// ĳ���� �����Ʈ ���� �⺻����
constexpr float fWalkSpeed = 300.f;
constexpr float fAcceleration = 2048.f;
constexpr float fDeceleration = 521.f;

// Sets default values
AAdamCharacter::AAdamCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	CharacterStat = CreateDefaultSubobject<UAdamCharacterStatComponent>(TEXT("CHARACTERSTAT"));
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	HPBarWidget->SetupAttachment(GetMesh());

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -95.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 600.0f;
	//SpringArm->SetRelativeRotation(FRotator(-40.0f, 0.0f, 0.0f));
	SpringArm->SetRelativeRotation(FRotator(FRotator::ZeroRotator));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	SpringArm->bEnableCameraLag = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; // ���� ��Ʈ�� ȸ���� ���� ���ư���
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ȸ�� �ӵ�? 720
	GetCharacterMovement()->JumpZVelocity = 600.0f; // ���� ���� ����
	GetCharacterMovement()->MaxWalkSpeed = fWalkSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = fDeceleration;

	// ü�¹� UI
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 230.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/PalaceWorld/Blueprints/UI/UI_HPBar.UI_HPBar_C"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}

	// ���� Ÿ�� ����Ʈ : Į,����
	CurWeaponType = EWeaponType::E_SWORDSHIELD;
	bIsAttacking = false; // ���� ���� ���������� ����
	// Į ���� ������
	MaxCombo = 5; 
	AttackRange = 200.0f;
	AttackRadius = 50.0f;
	bIsDead = false;

	AttackEndComboState();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("AdamCharacter"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_ADAM(TEXT("/Game/PalaceWorld/Resources/Adam_Adventurer/Meshes/Character/SK_AdamAdventurer.SK_AdamAdventurer"));
	if (SK_ADAM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_ADAM.Object);
	}

	// � ���� ����ƽ �޽��� ����
	FName BowBackSocket(TEXT("weaponMount_back_lSocket")); 
	FName QuiverBackSocket(TEXT("weaponMount_back_rSocket"));
	FName ScabbardBackSocket(TEXT("weaponMount_back_rScabbard"));
	FName SwordBackSocket(TEXT("weaponMount_back_rSword"));
	FName ShieldBackSocket(TEXT("ShieldMount_backSocket"));

	if (GetMesh()->DoesSocketExist(BowBackSocket))
	{
		Bow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOW"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOW(TEXT("/Game/PalaceWorld/Resources/Adam_Adventurer/Meshes/SM_Adam_Bow.SM_Adam_Bow"));
		if (SM_BOW.Succeeded())
		{
			Bow->SetStaticMesh(SM_BOW.Object);

		}
		Bow->SetupAttachment(GetMesh(), BowBackSocket);
	}

	if (GetMesh()->DoesSocketExist(QuiverBackSocket))
	{
		Quiver = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("QUIVER"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_QUIVER(TEXT("/Game/PalaceWorld/Resources/Adam_Adventurer/Meshes/SM_Adam_Quiver.SM_Adam_Quiver"));
		if (SM_QUIVER.Succeeded())
		{
			Quiver->SetStaticMesh(SM_QUIVER.Object);

		}
		Quiver->SetupAttachment(GetMesh(), QuiverBackSocket);
	}

	if (GetMesh()->DoesSocketExist(ScabbardBackSocket))
	{
		Scabbard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SCABBARD"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SCABBARD(TEXT("/Game/PalaceWorld/Resources/Adam_Adventurer/Meshes/SM_Adam_Scabbard.SM_Adam_Scabbard"));
		if (SM_SCABBARD.Succeeded())
		{
			Scabbard->SetStaticMesh(SM_SCABBARD.Object);

		}
		Scabbard->SetupAttachment(GetMesh(), ScabbardBackSocket);
	}
	
	if (GetMesh()->DoesSocketExist(SwordBackSocket))
	{
		Sword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SWORD"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SWORD(TEXT("/Game/PalaceWorld/Resources/Adam_Adventurer/Meshes/SM_Adam_Sword.SM_Adam_Sword"));
		if (SM_SWORD.Succeeded())
		{
			Sword->SetStaticMesh(SM_SWORD.Object);

		}
		Sword->SetupAttachment(GetMesh(), SwordBackSocket);
	}
	
	if (GetMesh()->DoesSocketExist(ShieldBackSocket))
	{
		Shield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SHIELD"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SHIELD(TEXT("/Game/PalaceWorld/Resources/Adam_Adventurer/Meshes/SM_Adam_Shield.SM_Adam_Shield"));
		if (SM_SHIELD.Succeeded())
		{
			Shield->SetStaticMesh(SM_SHIELD.Object);

		}
		Shield->SetupAttachment(GetMesh(), ShieldBackSocket);
	}
	

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ADAM_ANIM(TEXT("/Game/PalaceWorld/Blueprints/Animations/AdamAnimBP.AdamAnimBP_C"));
	if (ADAM_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ADAM_ANIM.Class);
	}

	
	// �⺻ ���� �ҵ�ؽǵ� -> ��� �Ⱥ��̰�
	Sword->SetVisibility(false);
	Shield->SetVisibility(false);
	
}

// Called when the game starts or when spawned
void AAdamCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ȭ�� ������Ʈ Ǯ �ʱ�ȭ
	ArrowPool = CastChecked<APalaceGameMode>(GetWorld()->GetAuthGameMode())->GetObjectPool();
	
	//Bow_Arrow = ArrowPool->GetPooledObject();
	//Bow_Arrow->SetObjectPool(ArrowPool);
	
	//if (CurWeaponType == EWeaponType::E_SWORDSHIELD) {
		// ���� ���Ͽ� ���� ����
		FName WeaponSocket(TEXT("WeaponHandMount_rSocket")); // ���� ���� ����
		Weapon_Sword = GetWorld()->SpawnActor<AAdamWeaponSword>(FVector::ZeroVector, FRotator::ZeroRotator);
		if (nullptr != Weapon_Sword) {
			if (GetMesh()->DoesSocketExist(WeaponSocket))
			{
				Weapon_Sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
			}
		}
		FName ShieldSocket(TEXT("ShieldMountSocket")); // ���� ����
		Weapon_Shield = GetWorld()->SpawnActor<AAdamWeaponShield>(FVector::ZeroVector, FRotator::ZeroRotator);
		if (nullptr != Weapon_Shield) {
			if (GetMesh()->DoesSocketExist(ShieldSocket))
			{
				Weapon_Shield->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, ShieldSocket);
			}
		}
	//}
		FName BowSocket(TEXT("WeaponHandMount_lSocket")); // Ȱ ����
		Weapon_Bow = GetWorld()->SpawnActor<AAdamWeaponBow>(FVector::ZeroVector, FRotator::ZeroRotator);
		if (nullptr != Weapon_Bow) {
			if (GetMesh()->DoesSocketExist(BowSocket))
			{
				Weapon_Bow->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, BowSocket); // Default Visibility = false
			}
		}

		// ĳ���� HPBar widget �ʱ�ȭ
		auto CharacterWidget = Cast<UAdamCharacterWidget>(HPBarWidget->GetUserWidgetObject());
		if (nullptr != CharacterWidget)
		{
			CharacterWidget->BindCharacterStat(CharacterStat);
		}
}

// Called every frame
void AAdamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAdamCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AdamAnim = Cast<UAdamAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AdamAnim)
	{
		UE_LOG(PalaceWorld, Error, TEXT("Animinstance Nullptr"));
		return;
	}
	AdamAnim->OnMontageEnded.AddDynamic(this, &AAdamCharacter::OnAttackMontageEnded);
	AdamAnim->OnNextAttackCheck.AddLambda([this]()->void {
		bCanNextCombo = false;

		if (bIsComboInputOn)
		{
			AttackStartComboState();
			AdamAnim->JumpToAttackMontageSection(CurrentCombo);

		}
	});

	// ĳ���� hp-������ ó���� ĳ���� ���� ���� ������Ʈ���� �ϵ��� ���ε�
	CharacterStat->OnHPIsZero.AddLambda([this]()-> void {
		UE_LOG(PalaceWorld, Warning, TEXT("OnHPIsZero"));
		bIsDead = true;
		GetController()->DisableInput(Cast<AAdamPlayerController>(GetController()));
		AdamAnim->SetDeadAnim();
		SetActorEnableCollision(false);
		});
	
	

	// Į ���� �浹 ó�� ��������Ʈ
	AdamAnim->OnAttackHitCheck.AddUObject(this, &AAdamCharacter::AttackCheck);

	// ���� ��ȯ ó�� ��������Ʈ
	AdamAnim->OnSwordTookOutCheck.AddUObject(this, &AAdamCharacter::SwordTookOutCheck);
	AdamAnim->OnBowTookOutCheck.AddUObject(this, &AAdamCharacter::BowTookOutCheck);
	
	// Ȱ �⺻���� ��������Ʈ
	AdamAnim->OnBowPickArrowCheck.AddUObject(this, &AAdamCharacter::BowAttackPickArrowCheck);
	AdamAnim->OnBowShootArrowCheck.AddUObject(this, &AAdamCharacter::BowAttackShootArrowCheck);


}
void AAdamCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

float AAdamCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) //������ TakeDamage �������̵��� ���Ͱ� ���� �������� ó���ϴ� ����
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	//UE_LOG(PalaceWorld, Warning, TEXT("Actor: %s / Took Dmg: %f"), *GetName(), FinalDamage);
	
	CharacterStat->SetDamage(FinalDamage);
	return FinalDamage;
}


// Called to bind functionality to input
void AAdamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAdamCharacter::MoveFB(float NewAxisValue)
{
	if (!bIsAttacking && !(AdamAnim->GetbUsingShield()) && !(AdamAnim->GetbAimingArrow()))
		AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), NewAxisValue);
}

void AAdamCharacter::MoveLR(float NewAxisValue)
{
	if (!bIsAttacking && !(AdamAnim->GetbUsingShield()) && !(AdamAnim->GetbAimingArrow()))
		AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), NewAxisValue);
}

void AAdamCharacter::Attack()
{
	if (AdamAnim->GetbIsSprinting())
		StopSprinting();
	switch (CurWeaponType) {
	case EWeaponType::E_SWORDSHIELD :
		if (bIsAttacking)
		{
			if (FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo))
			{
				if (bCanNextCombo)
					bIsComboInputOn = true;
			}
		}
		else
		{
			if (CurrentCombo == 0) {
				AttackStartComboState();
				AdamAnim->PlayAttackMontage(CurWeaponType);
				AdamAnim->JumpToAttackMontageSection(CurrentCombo);
				bIsAttacking = true;
			}
		}
		break;
	case EWeaponType::E_BOW:
		if (!bIsAttacking) 
		{
			bIsAttacking = true;
			Bow_Arrow = ArrowPool->GetPooledObject();
			if (0.0f == Bow_Arrow->getDamageByPlayerLevel())
				Bow_Arrow->setDamageByPlayerLevel(CharacterStat->GetAttack());
			UE_LOG(PalaceWorld, Warning, TEXT("bIsAttacking is %d"), bIsAttacking);
			//Bow_Arrow->SetObjectPool(ArrowPool);
			AdamAnim->PlayAttackMontage(CurWeaponType);
		}
		break;
	}
	
}

void AAdamCharacter::Sprint()
{
	if (!bIsAttacking && !(AdamAnim->GetbUsingShield()))
	{
		if (GetVelocity().Size() != 0.0f) {
			GetCharacterMovement()->MaxAcceleration = 521.f;
			//GetCharacterMovement()->BrakingDecelerationWalking = 521.f;
			GetCharacterMovement()->MaxWalkSpeed = fWalkSpeed * 2;
			AdamAnim->SetSprintAnim(true);
		}
	}
}

void AAdamCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = fWalkSpeed;
	AdamAnim->SetSprintAnim(false);

	
	GetCharacterMovement()->MaxAcceleration = fAcceleration;


}

void AAdamCharacter::UseWeaponAbility()
{
	if (!bIsAttacking) {
		if (AdamAnim->GetbIsSprinting())
			StopSprinting();
		if (CurWeaponType == EWeaponType::E_SWORDSHIELD) // ���и���
		{	
			AdamAnim->SetUsingShieldAnim(true);
		}
		else if (CurWeaponType == EWeaponType::E_BOW)
		{
			AdamAnim->SetAimingArrowAnim(true);
		}
	}
}

void AAdamCharacter::StopWeaponAbility()
{
	if (CurWeaponType == EWeaponType::E_SWORDSHIELD) // ���и���
	{
		AdamAnim->SetUsingShieldAnim(false);
	}
	else if (CurWeaponType == EWeaponType::E_BOW)
	{
		AdamAnim->SetAimingArrowAnim(false);
	}
}

void AAdamCharacter::SwordAndShieldMode()
{
	if (CurWeaponType == EWeaponType::E_SWORDSHIELD)
		return;
	AdamAnim->PlayChangeWeaponMontage(EWeaponType::E_SWORDSHIELD);
	AdamAnim->SetChangingWeapon(true);
	CurWeaponType = EWeaponType::E_SWORDSHIELD;
}

void AAdamCharacter::BowMode()
{
	if (CurWeaponType == EWeaponType::E_BOW)
		return;
	AdamAnim->PlayChangeWeaponMontage(EWeaponType::E_BOW);
	AdamAnim->SetChangingWeapon(true);
	//UE_LOG(PalaceWorld, Warning, TEXT("bIsChangingWeapon = %d"), AdamAnim->GetbIsChangingWeapon());
	CurWeaponType = EWeaponType::E_BOW;
}

//void AAdamCharacter::LoadStaticMeshInConstructor(UStaticMeshComponent* SMComponent, FName SocketName, FName ComponentName, UStaticMesh* mesh)
//{
//	if (GetMesh()->DoesSocketExist(SocketName))
//	{
//		SMComponent = CreateDefaultSubobject<UStaticMeshComponent>(ComponentName);
//		
//		SMComponent->SetStaticMesh(mesh);
//		
//		SMComponent->SetupAttachment(GetMesh(), SocketName);
//	}
//}

void AAdamCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (bIsAttacking) {
		if (CurWeaponType == EWeaponType::E_SWORDSHIELD) {
			if (CurrentCombo > 0) {
				bIsAttacking = false;
				AttackEndComboState();
			}
		}
		else if (CurWeaponType == EWeaponType::E_BOW)
		{
			bIsAttacking = false;
		}
	}
	if (AdamAnim->GetbIsChangingWeapon())
	{
		AdamAnim->SetChangingWeapon(false);
	}
	
}

void AAdamCharacter::SwordTookOutCheck() // ��������Ʈ �Լ�
{
	Bow->SetVisibility(true);
	Sword->SetVisibility(false);
	Shield->SetVisibility(false);
	Weapon_Bow->Weapon_BowMesh->SetVisibility(false);
	Weapon_Sword->Weapon_SwordMesh->SetVisibility(true);
	Weapon_Shield->Weapon_ShieldMesh->SetVisibility(true);
}

void AAdamCharacter::BowTookOutCheck()
{
	Bow->SetVisibility(false);
	Sword->SetVisibility(true);
	Shield->SetVisibility(true);
	Weapon_Bow->Weapon_BowMesh->SetVisibility(true);
	Weapon_Sword->Weapon_SwordMesh->SetVisibility(false);
	Weapon_Shield->Weapon_ShieldMesh->SetVisibility(false);
}

void AAdamCharacter::AttackStartComboState()
{
	bCanNextCombo = true;
	bIsComboInputOn = false;
	if (FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1))
	{
		CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
	}

}

void AAdamCharacter::AttackEndComboState()
{
	bIsComboInputOn = false;
	bCanNextCombo = false;
	CurrentCombo = 0;
}

void AAdamCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.0f, //Ž�� ���� ��ġ: ���� �ü��������� 200cm ������ ��
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.0f), // Ž���� ����� ���� : ������ 50cm ��
		Params);

	// �ݸ��� ����� �����
#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red; // ���� ������ �߻��ϸ� ���, �ƴϸ� ������
	float DebugLifeTime = 5.0f;
	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
#endif

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			UE_LOG(PalaceWorld, Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(CharacterStat->GetAttack()/*���߿� ���� �������� �����ؾߵ�*/, DamageEvent, GetController(), this); // ������ ������ ����, ������ ����, ���� ��� ���� ������(��Ʈ�ѷ�), ������ ���� ���� ����� ����(��)
		}
	}

}

void AAdamCharacter::BowAttackPickArrowCheck()
{
	FName ArrowSocket(TEXT("ArrowSocket")); // ȭ�� ����
	if (nullptr != ArrowPool) {
		if (GetMesh()->DoesSocketExist(ArrowSocket))
		{
			Bow_Arrow->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, ArrowSocket);	
			Bow_Arrow->SetActive(true);
		}
	}

	
}

void AAdamCharacter::BowAttackShootArrowCheck()
{
	Bow_Arrow->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	FVector LaunchDir = GetCapsuleComponent()->GetForwardVector();
	Bow_Arrow->OnActivated(LaunchDir);
	UE_LOG(PalaceWorld, Warning, TEXT("%s is On Activated"), *Bow_Arrow->GetName());
}
