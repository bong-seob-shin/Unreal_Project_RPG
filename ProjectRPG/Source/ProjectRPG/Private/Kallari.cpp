// Fill out your copyright notice in the Description page of Project Settings.


#include "Kallari.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "KallariAnimInstance.h"
#include "KallariController.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"
#include "KallariStatComponent.h"
#include "Components/DecalComponent.h"
#include "Components/WidgetComponent.h"
#include "KallariWidget.h"


constexpr float SpeedIncreaseRate = 1000.0f;
constexpr float Skill_1_duration =  5.0f; 

// Sets default values
AKallari::AKallari()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ComponentSetting
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	ShadowDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	CharacterStat = CreateDefaultSubobject<UKallariStatComponent>(TEXT("CHARACTERSTAT"));
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	ShadowDecal->SetupAttachment(GetCapsuleComponent());
	HPBarWidget->SetupAttachment(GetMesh());

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));//mesh loacte CapsuleCollider

	//SpringArm and Camera Setting
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	//Mesh Setting
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("SkeletalMesh'/Game/PolarWorld/ParagonKallari/Characters/Heroes/Kallari/Skins/Rogue/Meshes/Kallari_Rogue.Kallari_Rogue'"));

	if (SkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	//Decal Setting
	static ConstructorHelpers::FObjectFinder<UMaterial> SkillDecalMaterial(TEXT("Material'/Game/PolarWorld/Materials/M_SkillDecal.M_SkillDecal'"));

	if (SkillDecalMaterial.Succeeded())
	{
		ShadowDecal->SetDecalMaterial(SkillDecalMaterial.Object);
	}
	ShadowDecal->DecalSize = FVector(100.0f, 100.f, 100.f);
	ShadowDecal->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(-90.f,0.0f,0.f));
	ShadowDecal->SetVisibility(false);

	//Animation Setting
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> KallariAnim(TEXT("AnimBlueprint'/Game/PolarWorld/BP_PolarWorld/ABP_Kallari.ABP_Kallari_C'"));
	if (KallariAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(KallariAnim.Class);
	}

	//HPBar Setting
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("WidgetBlueprint'/Game/PolarWorld/UI/WBP_HPBar.WBP_HPBar_C'"));

	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}


	//Collision Setting
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Kallari"));

	//Stat Setting
	iMaxCombo = 5;
	fWalkSpeed = 400.0f; 
	fDashSpeed = fWalkSpeed * 2.0f;
	fJumpForce = 500.0f;//default 420
	GetCharacterMovement()->JumpZVelocity = fJumpForce;
	GetCharacterMovement()->MaxWalkSpeed = fWalkSpeed;
	fAttackRange = 200.0f;
	fAttackRadius = 50.0f;
}

// Called when the game starts or when spawned
void AKallari::BeginPlay()
{
	Super::BeginPlay();

	auto CharacterWidget = Cast<UKallariWidget>(HPBarWidget->GetUserWidgetObject());

	if (CharacterWidget != nullptr)
		CharacterWidget->BindCharacterStat(CharacterStat);

}

void AKallari::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto TempAnimInstance = Cast<UKallariAnimInstance>(GetMesh()->GetAnimInstance());

	if (TempAnimInstance != nullptr)
	{
		AnimInstance = TempAnimInstance;
		auto TempController = Cast<AKallariController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if(TempController != nullptr)
			AnimInstance->OnMontageEnded.AddDynamic(TempController, &AKallariController::OnAttackMontageEnded);

		AnimInstance->OnNextAttackCheck.AddLambda([this]()->void {
			bCanNextCombo = false;

			if (bIsComboInputOn)
			{
				AttackStartComboState();
				AnimInstance->JumpToAttackMontageSection(iCurrentCombo);
			}
		});

		AnimInstance->OnAttackHitCheck.AddUObject(this, &AKallari::AttackCheck);
		AnimInstance->OnSkill1.AddUObject(this, &AKallari::Skill1_Start);
	}

	//Character Dead , Character Stat Component -> Character  Delegate OnHpIsZero
	CharacterStat->OnHPIsZero.AddLambda([this]()-> void {
		AnimInstance->SetIsDead(true);
		SetActorEnableCollision(false);
		bIsDead = true;
	});

}

// Called every frame
void AKallari::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Dash(DeltaTime);
}

float AKallari::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CharacterStat->SetDamage(Damage);

	return Damage;
}

void AKallari::DashStart()
{
	bIsDash = true;
}

void AKallari::Dash(float DeltaTime)
{
	if (bIsDash && GetCharacterMovement()->MaxWalkSpeed <= fDashSpeed)
	{
		GetCharacterMovement()->MaxWalkSpeed += SpeedIncreaseRate * DeltaTime;
	}
	else if (!bIsDash && GetCharacterMovement()->MaxWalkSpeed >= fWalkSpeed)
	{
		GetCharacterMovement()->MaxWalkSpeed -= SpeedIncreaseRate * DeltaTime;
	}
}

void AKallari::DashEnd()
{
	bIsDash = false;
}

void AKallari::Evade()
{
	if (!GetMovementComponent()->IsFalling()) {
		AnimInstance->SetIsEvading(true);
		AnimInstance->StopAllMontages(0.1f);
		GetCharacterMovement()->SetMovementMode(MOVE_Falling);
		FVector Direction = (-GetCapsuleComponent()->GetForwardVector()) + FVector::UpVector;
		GetMovementComponent()->Velocity = Direction * fJumpForce;
	}
}

bool AKallari::Attack(bool IsAttack)
{
	if (!AnimInstance->GetIsEvading()) {
		if (IsAttack) {
			if (bCanNextCombo)
			{
				bIsComboInputOn = true;
			}
		}
		else {
			AttackStartComboState();
			AnimInstance->PlayAttackMontage();
			AnimInstance->JumpToAttackMontageSection(iCurrentCombo);
		}
		return true;
	}
	return false;
}




void AKallari::AttackStartComboState()
{
	bCanNextCombo = true;
	bIsComboInputOn = false;
	iCurrentCombo++;
}

void AKallari::AttackCheck()
{

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * fAttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(fAttackRadius),
		Params
	);

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * fAttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = fAttackRange * 0.5f + fAttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		fAttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);

#endif


	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(CharacterStat->GetAttack(), DamageEvent, GetController(), this);
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());
		}
	}
}

void AKallari::AttackEnd()
{
	bCanNextCombo = false;
	bIsComboInputOn = false;
	iCurrentCombo = 0;
}

void AKallari::OnSkill1()
{
	AnimInstance->SetIsSkill_1_Playing(!AnimInstance->GetIsSkill_1_Playing());
}

bool AKallari::GetIsDead()
{
	return bIsDead;
}

void AKallari::Skill1_Start()
{
	if (AnimInstance->GetIsSkill_1_Playing())
	{
		SetCanBeDamaged(false); // can't be damaged
		GetMesh()->SetVisibility(false);
		ShadowDecal->SetVisibility(true);
		GetWorldTimerManager().SetTimer(Skill_1_TimerHandle, this, &AKallari::OnSkill1, 5.0f, false, Skill_1_duration);
	}
	else 
	{
		SetCanBeDamaged(true);// can be damaged
		GetMesh()->SetVisibility(true);
		ShadowDecal->SetVisibility(false);
	}
}







