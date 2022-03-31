// Fill out your copyright notice in the Description page of Project Settings.


#include "Grux.h"
#include "GruxAIController.h"
#include "GruxAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AGrux::AGrux()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	//Mesh Setting
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("SkeletalMesh'/Game/PolarWorld/ParagonGrux/Characters/Heroes/Grux/Meshes/Grux.Grux'"));
	
	if (SkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	//AIController Setting
	AIControllerClass = AGruxAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//Animation Setting
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UGruxAnimInstance> GruxAnim(TEXT("AnimBlueprint'/Game/PolarWorld/BP_PolarWorld/ABP_Grux.ABP_Grux_C'"));
	if (GruxAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(GruxAnim.Class);
	}

	//Smooth Movement Setting
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	//Collsion Setting
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));

	//Stat Setting
	fAttackRange = 70.0f;
	fAttackRadius = 50.0f;
	fMaxHP = 30.0f;
	fCurrentHP = fMaxHP;
	fAttackDamage = 5.0f;

}

// Called when the game starts or when spawned
void AGrux::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrux::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AGrux::Attack()
{
	auto AnimInstance = Cast<UGruxAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->PlayAttackAnim();
	AttackCheck();
}

void AGrux::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * fAttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(fAttackRadius),
		Params
	);


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

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(fAttackDamage, DamageEvent, GetController(), this);
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());
		}
	}
}

void AGrux::Dead()
{
	UE_LOG(LogTemp, Warning, TEXT("DEAD!!"));
	Destroy();
}

float AGrux::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	fCurrentHP -= Damage;

	if (fCurrentHP <= KINDA_SMALL_NUMBER)
	{
		auto AnimInstance = Cast<UGruxAnimInstance>(GetMesh()->GetAnimInstance());
		AnimInstance->SetIsDead(true);
		SetActorEnableCollision(false);
		GetWorldTimerManager().SetTimer(DieTimerHandle, this, &AGrux::Dead, 10.0f, false, 5.0f);
		UnPossessed();
	}
	return Damage;
}


