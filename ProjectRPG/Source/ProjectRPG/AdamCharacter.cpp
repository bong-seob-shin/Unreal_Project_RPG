// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamCharacter.h"
#include "AdamAnimInstance.h"
#include "AdamPlayerController.h"
#include "AdamWeaponSword.h"
#include "DrawDebugHelpers.h"

// Sets default values
AAdamCharacter::AAdamCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

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

	// Į ���� ������
	bIsAttacking = false;
	MaxCombo = 5; 
	AttackRange = 200.0f;
	AttackRadius = 50.0f;

	AttackEndComboState();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("AdamCharacter"));
	

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_ADAM(TEXT("/Game/PalaceWorld/Resources/Adam_Adventurer/Meshes/Character/SK_AdamAdventurer.SK_AdamAdventurer"));
	if (SK_ADAM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_ADAM.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ADAM_ANIM(TEXT("/Game/PalaceWorld/Blueprints/Animations/AdamAnimBP.AdamAnimBP_C"));
	if (ADAM_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ADAM_ANIM.Class);
	}

	

}

// Called when the game starts or when spawned
void AAdamCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// ���� ���Ͽ� ���� ����
	FName WeaponSocket(TEXT("WeaponHandMount_rSocket")); // ���� ���� ����
	auto CurWeapon = GetWorld()->SpawnActor<AAdamWeaponSword>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (nullptr != CurWeapon) {
		if (GetMesh()->DoesSocketExist(WeaponSocket))
		{
			CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		}
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

	// Į ���� �浹 ó�� ��������Ʈ
	AdamAnim->OnAttackHitCheck.AddUObject(this, &AAdamCharacter::AttackCheck);
}
void AAdamCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

float AAdamCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) //������ TakeDamage �������̵��� ���Ͱ� ���� �������� ó���ϴ� ����
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(PalaceWorld, Warning, TEXT("Actor: %s / Took Dmg: %f"), *GetName(), FinalDamage);
	if (FinalDamage > 0.0f) // ���⿡ ���߿� hp �ڵ� ���� ����
	{
		AdamAnim->SetDeadAnim();
		SetActorEnableCollision(false);
	}
	return FinalDamage;
}


// Called to bind functionality to input
void AAdamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAdamCharacter::Attack()
{
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
			AdamAnim->PlayAttackMontage();
			AdamAnim->JumpToAttackMontageSection(CurrentCombo);
			bIsAttacking = true;
		}
	}
}

void AAdamCharacter::Sprint()
{
	if (GetVelocity().Size() != 0.0f) {
		GetCharacterMovement()->MaxAcceleration = 521.f;
		//GetCharacterMovement()->BrakingDecelerationWalking = 521.f;
		GetCharacterMovement()->MaxWalkSpeed = fWalkSpeed * 2;
		AdamAnim->SetSprintAnim(true);
	}
}

void AAdamCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = fWalkSpeed;
	AdamAnim->SetSprintAnim(false);

	
	GetCharacterMovement()->MaxAcceleration = fAcceleration;


}

void AAdamCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (bIsAttacking) {
		if (CurrentCombo > 0) {
			bIsAttacking = false;
			AttackEndComboState();
		}
	}
	
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
			HitResult.Actor->TakeDamage(50.0f, DamageEvent, GetController(), this); // ������ ���̵� ����, ������ ����, ���� ��� ���� ������(��Ʈ�ѷ�), ������ ���� ���� ����� ����(��)
		}
	}

}
