// Fill out your copyright notice in the Description page of Project Settings.


#include "Kallari.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
AKallari::AKallari()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	


	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));//Camera Default Setting

	

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

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("SkeletalMesh'/Game/PolarWorld/ParagonKallari/Characters/Heroes/Kallari/Skins/Rogue/Meshes/Kallari_Rogue.Kallari_Rogue'"));

	if (SkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

}

// Called when the game starts or when spawned
void AKallari::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKallari::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




