// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	static ConstructorHelpers::FClassFinder<UAnimInstance> ABP(TEXT("AnimBlueprint'/Game/IceLandWorld/ABP_AruroraAnim.ABP_AruroraAnim_C'"));
	if (ABP.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ABP.Class);
	}

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bIgnoreBaseRotation = true;
}

// Called when the game starts or when spawned
void AAuroraCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAuroraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
