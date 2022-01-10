// Fill out your copyright notice in the Description page of Project Settings.


#include "KallariController.h"
#include "KallariPlayerCameraManager.h"
#include "Kallari.h"

AKallariController::AKallariController()
{
	PlayerCameraManagerClass = AKallariPlayerCameraManager::StaticClass();


}

void AKallariController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AKallariController::Jump);

	InputComponent->BindAxis(TEXT("UpDown"), this, &AKallariController::Updown);
	InputComponent->BindAxis(TEXT("LeftRight"), this, &AKallariController::LeftRight);
	InputComponent->BindAxis(TEXT("Horizontal"), this, &AKallariController::Horizontal);
	InputComponent->BindAxis(TEXT("Vertical"), this, &AKallariController::Vertical);
}

void AKallariController::Updown(float Value)
{
	APawn* const MyPawn = GetPawn();
	MyPawn->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), Value);

}

void AKallariController::LeftRight(float Value)
{
	APawn* const MyPawn = GetPawn();
	MyPawn->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), Value);
}

void AKallariController::Horizontal(float Value)
{
	APawn* const MyPawn = GetPawn();
	MyPawn->AddControllerYawInput(Value);
}

void AKallariController::Vertical(float Value)
{
	APawn* const MyPawn = GetPawn();
	MyPawn->AddControllerPitchInput(Value);
	
}

void AKallariController::Jump()
{
	APawn* const MyPawn = GetPawn();
	AKallari* MyCharacter = Cast<AKallari>(MyPawn);

	if (MyCharacter != nullptr)
	{
		MyCharacter->Jump();
	}
}
