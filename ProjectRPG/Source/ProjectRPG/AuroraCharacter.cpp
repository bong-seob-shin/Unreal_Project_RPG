// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AAuroraCharacter::AAuroraCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add SpringArm Component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->bUsePawnControlRotation = true;

	// Add Camera Component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/IceLandWorld/ParagonAurora/Characters/Heroes/Aurora/Meshes/Aurora.Aurora'"));
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
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

// Called to bind functionality to input
void AAuroraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AAuroraCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AAuroraCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AAuroraCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AAuroraCharacter::LookUp);

	PlayerInputComponent->BindAction(TEXT("Run"),EInputEvent::IE_Pressed, this, &AAuroraCharacter::PressedRun);
	PlayerInputComponent->BindAction(TEXT("Run"),EInputEvent::IE_Released, this, &AAuroraCharacter::ReleasedRun);
}

void AAuroraCharacter::MoveForward(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value * CurrentSpeed);
	}
}

void AAuroraCharacter::MoveRight(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value * CurrentSpeed);
	}
}

void AAuroraCharacter::Turn(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		AddControllerYawInput(Value);
	}
}

void AAuroraCharacter::LookUp(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		AddControllerPitchInput(Value);
	}
}

void AAuroraCharacter::PressedRun()
{
	//MovementComponent->MaxSpeed = 100.0f;
	CurrentSpeed = 500.0f;
}

void AAuroraCharacter::ReleasedRun()
{
	//MovementComponent->MaxSpeed = 20.0f;
	CurrentSpeed = 1.0f;
}

