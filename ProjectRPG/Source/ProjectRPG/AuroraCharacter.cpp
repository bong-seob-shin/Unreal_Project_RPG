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

// Called to bind functionality to input
void AAuroraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AAuroraCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AAuroraCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AAuroraCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AAuroraCharacter::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AAuroraCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AAuroraCharacter::StopJumping);
	PlayerInputComponent->BindAction(TEXT("Sprint"),IE_Pressed, this, &AAuroraCharacter::BeginSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"),IE_Released, this, &AAuroraCharacter::EndSprint);
	PlayerInputComponent->BindAction(TEXT("Dodge"), IE_Pressed, this, &AAuroraCharacter::BeginDodge);
	PlayerInputComponent->BindAction(TEXT("Dodge"), IE_Released, this, &AAuroraCharacter::EndDodge);
}

void AAuroraCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value * CurrentSpeed);
	}
}

void AAuroraCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
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

void AAuroraCharacter::BeginSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
}

void AAuroraCharacter::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}

void AAuroraCharacter::BeginDodge()
{
	Crouch();
}

void AAuroraCharacter::EndDodge()
{
	UnCrouch();
}

