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
	InputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AKallariController::Attack);
	InputComponent->BindAction(TEXT("Dash"), EInputEvent::IE_Pressed, this, &AKallariController::DashStart);
	InputComponent->BindAction(TEXT("Evade"), EInputEvent::IE_Pressed, this, &AKallariController::Evade);
	InputComponent->BindAction(TEXT("Skill1"), EInputEvent::IE_Pressed, this, &AKallariController::OnSkill1);

	InputComponent->BindAction(TEXT("Dash"), EInputEvent::IE_Released, this, &AKallariController::DashEnd);


	InputComponent->BindAxis(TEXT("UpDown"), this, &AKallariController::Updown);
	InputComponent->BindAxis(TEXT("LeftRight"), this, &AKallariController::LeftRight);
	InputComponent->BindAxis(TEXT("Horizontal"), this, &AKallariController::Horizontal);
	InputComponent->BindAxis(TEXT("Vertical"), this, &AKallariController::Vertical);
}

void AKallariController::Updown(float Value)
{
	if (bIsAttacking) return;

	APawn* const MyPawn = GetPawn();
	MyPawn->AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::X), Value);

	
}

void AKallariController::LeftRight(float Value)
{
	if (bIsAttacking) return;

	APawn* const MyPawn = GetPawn();
	MyPawn->AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::Y), Value);
	
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

void AKallariController::DashStart()
{
	if (bIsUsingSkill) return;

	APawn* const MyPawn = GetPawn();
	AKallari* MyCharacter = Cast<AKallari>(MyPawn);


	if (MyCharacter != nullptr)
	{
		MyCharacter->DashStart();
	}
}

void AKallariController::DashEnd()
{
	APawn* const MyPawn = GetPawn();
	AKallari* MyCharacter = Cast<AKallari>(MyPawn);

	if (MyCharacter != nullptr)
	{
		MyCharacter->DashEnd();
	}
}

void AKallariController::Jump()
{

	if (bIsUsingSkill) return;

	APawn* const MyPawn = GetPawn();
	AKallari* MyCharacter = Cast<AKallari>(MyPawn);

	if (MyCharacter != nullptr)
	{
		MyCharacter->Jump();
	}
}

void AKallariController::Attack()
{
	if (bIsUsingSkill) return;

	APawn* const MyPawn = GetPawn();
	AKallari* MyCharacter = Cast<AKallari>(MyPawn);

	if (MyCharacter != nullptr)
	{
		bIsAttacking = MyCharacter->Attack(bIsAttacking);
	}

}

void AKallariController::Evade()
{
	if (bIsUsingSkill) return;

	APawn* const MyPawn = GetPawn();
	AKallari* MyCharacter = Cast<AKallari>(MyPawn);

	if (MyCharacter != nullptr)
	{
		MyCharacter->Evade();
	}

}

void AKallariController::OnSkill1()
{
	bIsUsingSkill = !bIsUsingSkill;

	APawn* const MyPawn = GetPawn();
	AKallari* MyCharacter = Cast<AKallari>(MyPawn);

	if (MyCharacter != nullptr)
	{
		MyCharacter->OnSkill1(bIsUsingSkill);
	}
}


void AKallariController::OnAttackMontageEnded(UAnimMontage* Montage, bool blnterrupted)
{
	bIsAttacking = false;
	APawn* const MyPawn = GetPawn();
	AKallari* MyCharacter = Cast<AKallari>(MyPawn);
	
	if (MyCharacter != nullptr)
	{
		MyCharacter->AttackEnd();
	}
}
