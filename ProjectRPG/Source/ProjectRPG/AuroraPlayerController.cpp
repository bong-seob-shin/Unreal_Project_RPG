// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraPlayerController.h"
#include "AuroraPlayerCameraManager.h"
#include "AuroraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AAuroraPlayerController::AAuroraPlayerController()
{
	PlayerCameraManagerClass = AAuroraPlayerCameraManager::StaticClass();
}

void AAuroraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MoveForward"), this, &AAuroraPlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AAuroraPlayerController::MoveRight);
	InputComponent->BindAxis(TEXT("Turn"), this, &AAuroraPlayerController::Turn);
	InputComponent->BindAxis(TEXT("LookUp"), this, &AAuroraPlayerController::LookUp);

	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AAuroraPlayerController::Jump);
	InputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AAuroraPlayerController::StopJumping);
	InputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &AAuroraPlayerController::BeginRun);
	InputComponent->BindAction(TEXT("Run"), IE_Released, this, &AAuroraPlayerController::EndRun);
}

void AAuroraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	APawn* const aPawn = GetPawn();
	AAuroraCharacter* AuroraCharacter = Cast<AAuroraCharacter>(aPawn);
	if (AuroraCharacter)
	{
		AuroraCharacter->GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	}
}

void AAuroraPlayerController::MoveForward(float Value)
{
	APawn* const aPawn = GetPawn();
	if (aPawn && (Value != 0.0f))
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		aPawn->AddMovementInput(Direction, Value);
	}
}

void AAuroraPlayerController::MoveRight(float Value)
{
	APawn* const aPawn = GetPawn();
	if (aPawn && (Value != 0.0f))
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		aPawn->AddMovementInput(Direction, Value);
	}
}

void AAuroraPlayerController::Turn(float Value)
{
	APawn* const aPawn = GetPawn();
	if (aPawn && (Value != 0.0f))
	{
		aPawn->AddControllerYawInput(Value);
	}
}

void AAuroraPlayerController::LookUp(float Value)
{
	APawn* const aPawn = GetPawn();
	if (aPawn && (Value != 0.0f))
	{
		aPawn->AddControllerPitchInput(Value);
	}
}

void AAuroraPlayerController::Jump()
{
	APawn* const aPawn = GetPawn();
	AAuroraCharacter* AuroraCharacter = Cast<AAuroraCharacter>(aPawn);
	if (AuroraCharacter)
	{
		AuroraCharacter->Jump();
	}
}

void AAuroraPlayerController::StopJumping()
{
	APawn* const aPawn = GetPawn();
	AAuroraCharacter* AuroraCharacter = Cast<AAuroraCharacter>(aPawn);
	if (AuroraCharacter)
	{
		AuroraCharacter->StopJumping();
	}
}

void AAuroraPlayerController::BeginRun()
{
	APawn* const aPawn = GetPawn();
	AAuroraCharacter* AuroraCharacter = Cast<AAuroraCharacter>(aPawn);
	if(AuroraCharacter)
	{
		AuroraCharacter->GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	}
}

void AAuroraPlayerController::EndRun()
{
	APawn* const aPawn = GetPawn();
	AAuroraCharacter* AuroraCharacter = Cast<AAuroraCharacter>(aPawn);
	if (AuroraCharacter)
	{
		AuroraCharacter->GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	}
}
