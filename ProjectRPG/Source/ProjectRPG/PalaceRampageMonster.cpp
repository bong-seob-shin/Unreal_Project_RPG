// Fill out your copyright notice in the Description page of Project Settings.


#include "PalaceRampageMonster.h"
#include "AdamCharacterStatComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AdamCharacterWidget.h"
#include "AdamCharacterStatComponent.h"
#include "RampageAnimInstance.h"
#include "MonsterAIController.h"

// Sets default values
APalaceRampageMonster::APalaceRampageMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsAttacking = false;
	CharacterStat = CreateDefaultSubobject<UAdamCharacterStatComponent>(TEXT("CHARACTERSTAT"));
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	
	HPBarWidget->SetupAttachment(GetMesh());

	// �޽� ����
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -80.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetCapsuleComponent()->SetCapsuleHalfHeight(100.0f,false);
	GetCapsuleComponent()->SetCapsuleRadius(60.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_RAMPAGE(TEXT("/Game/PalaceWorld/Resources/ParagonRampage/Characters/Heroes/Rampage/Meshes/Rampage.Rampage"));
	if (SK_RAMPAGE.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_RAMPAGE.Object);
	}
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> RAMPAGE_ANIM(TEXT("/Game/PalaceWorld/Blueprints/Animations/Monster/RampageAnimBP.RampageAnimBP_C"));
	if (RAMPAGE_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(RAMPAGE_ANIM.Class);
	}
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	// ü�¹� UI
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 230.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/PalaceWorld/Blueprints/UI/UI_HPBar.UI_HPBar_C"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}
	
	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void APalaceRampageMonster::BeginPlay()
{
	Super::BeginPlay();
	// ĳ���� HPBar widget �ʱ�ȭ
	auto CharacterWidget = Cast<UAdamCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	if (nullptr != CharacterWidget)
	{
		CharacterWidget->BindCharacterStat(CharacterStat);
	}
}

// Called every frame
void APalaceRampageMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APalaceRampageMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APalaceRampageMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	RampageAnim = Cast<URampageAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == RampageAnim)
	{
		UE_LOG(PalaceWorld, Error, TEXT("Animinstance Nullptr"));
		return;
	}
	RampageAnim->OnMontageEnded.AddDynamic(this, &APalaceRampageMonster::OnAttackMontageEnded);
	// ���� �浹 ó�� ��������Ʈ
	RampageAnim->OnAttackHitCheck.AddUObject(this, &APalaceRampageMonster::AttackCheck);

	CharacterStat->OnHPIsZero.AddLambda([this]()-> void {
		RampageAnim->SetDeadAnim();
		SetActorEnableCollision(false);
		});
}

float APalaceRampageMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	CharacterStat->SetDamage(FinalDamage);
	return FinalDamage;
}

void APalaceRampageMonster::Attack()
{
	if (!bIsAttacking)
	{
		RampageAnim->PlayRandAttackMontage();
		bIsAttacking = true;	
	}
}

void APalaceRampageMonster::AttackCheck()
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
//#if ENABLE_DRAW_DEBUG
//	FVector TraceVec = GetActorForwardVector() * AttackRange;
//	FVector Center = GetActorLocation() + TraceVec * 0.5f;
//	float HalfHeight = AttackRange * 0.5f + AttackRadius;
//	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
//	FColor DrawColor = bResult ? FColor::Green : FColor::Red; // ���� ������ �߻��ϸ� ���, �ƴϸ� ������
//	float DebugLifeTime = 5.0f;
//	DrawDebugCapsule(GetWorld(),
//		Center,
//		HalfHeight,
//		AttackRadius,
//		CapsuleRot,
//		DrawColor,
//		false,
//		DebugLifeTime);
//#endif

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			UE_LOG(PalaceWorld, Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(CharacterStat->GetAttack()/*���߿� ���� �������� �����ؾߵ�*/, DamageEvent, GetController(), this); // ������ ���̵� ����, ������ ����, ���� ��� ���� ������(��Ʈ�ѷ�), ������ ���� ���� ����� ����(��)
		}
	}

}

void APalaceRampageMonster::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (bIsAttacking) {
		bIsAttacking = false;
		RampageAnim->SetRandAtkAnimIdx();
		OnAttackEnd.Broadcast();
	}
}

