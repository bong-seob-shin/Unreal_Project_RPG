// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "AuroraAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Classes//Particles//ParticleSystem.h"

// Sets default values
AAuroraCharacter::AAuroraCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add SpringArm Component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->bUsePawnControlRotation = true;

	// Add Camera Component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	// Load SkeletalMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/IceLandWorld/ParagonAurora/Characters/Heroes/Aurora/Meshes/Aurora.Aurora'"));
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	// Load Animation Blueprint
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> ABP(TEXT("AnimBlueprint'/Game/IceLandWorld/ABP_AruroraAnim.ABP_AruroraAnim_C'"));
	if (ABP.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ABP.Class);
	}

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bIgnoreBaseRotation = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));

	AttackMeleeRange = 100.0f;
	AttackMeleeRadius = 50.0f;




	static ConstructorHelpers::FObjectFinder<UParticleSystem> AttackMelee_Particle(TEXT("ParticleSystem'/Game/IceLandWorld/ParagonAurora/FX/Particles/Abilities/Primary/FX/P_Aurora_Melee_SucessfulImpact.P_Aurora_Melee_SucessfulImpact'"));
	if (AttackMelee_Particle.Succeeded())
	{
		AttackHitParticle = AttackMelee_Particle.Object;
	}
}

// Called when the game starts or when spawned
void AAuroraCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuroraCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AuroraAnimInstance = Cast<UAuroraAnimInstance>(GetMesh()->GetAnimInstance());
	if (AuroraAnimInstance)
	{
		AuroraAnimInstance->OnAttackMeleeHitCheck.AddUObject(this, &AAuroraCharacter::AttackMeleeCheck);
	}
}

// Called every frame
void AAuroraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AAuroraCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// hp > 0 => hit
	// hp = 0 => dead

	if (FinalDamage)
	{
		AuroraAnimInstance->SetDeadAnimation();
		SetActorEnableCollision(false);
	}
	return FinalDamage;
}

void AAuroraCharacter::AttackMeleeCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation()+GetActorForwardVector() * AttackMeleeRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackMeleeRadius),
		Params);

#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector() * AttackMeleeRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackMeleeRange * 0.5f + AttackMeleeRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(), 
		Center, 
		HalfHeight,
		AttackMeleeRadius, 
		CapsuleRot, 
		DrawColor, 
		false, 
		DebugLifeTime);

#endif

	if (bResult && HitResult.Actor.IsValid())
	{
		FDamageEvent DamageEvent;
		HitResult.Actor->TakeDamage(50.0f, DamageEvent, GetController(), this);
	}
}

void AAuroraCharacter::HitFX()
{
	FName WeaponSocket(TEXT("Sword_Tip"));
	FVector SwordTipVec;
	if (GetMesh()->DoesSocketExist(WeaponSocket))
	{
		SwordTipVec = GetMesh()->GetSocketLocation(WeaponSocket);
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AttackHitParticle, SwordTipVec);
}
