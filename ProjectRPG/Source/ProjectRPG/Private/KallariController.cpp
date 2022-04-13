// Fill out your copyright notice in the Description page of Project Settings.


#include "KallariController.h"
#include "KallariPlayerCameraManager.h"
#include "Kallari.h"


constexpr float Skill1_CoolDown_Time = 10.0f;

constexpr float Evade_CoolDown_Time = 3.0f;

AKallariController::AKallariController()
{
	PlayerCameraManagerClass = AKallariPlayerCameraManager::StaticClass();
	Evade_CoolDown_Calc_Sec = -Evade_CoolDown_Time; // first use
	Skill1_CoolDown_Calc_Sec = -Skill1_CoolDown_Time; // first use

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

void AKallariController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	MyCharacter = Cast<AKallari>(aPawn);
}

void AKallariController::OnUnPossess()
{
	Super::OnUnPossess();
	MyCharacter = nullptr;
}

void AKallariController::Updown(float Value)
{
	if (bIsAttacking) return;
	if (MyCharacter == nullptr || MyCharacter->GetIsDead() || MyCharacter->GetIsEvading())	return;

	MyCharacter->AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::X), Value);

	
}

void AKallariController::LeftRight(float Value)
{
	if (bIsAttacking) return;
	if (MyCharacter == nullptr || MyCharacter->GetIsDead() || MyCharacter->GetIsEvading())	return;

	MyCharacter->AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::Y), Value);
	
}

void AKallariController::Horizontal(float Value)
{
	if (MyCharacter == nullptr || MyCharacter->GetIsDead())	return;

	MyCharacter->AddControllerYawInput(Value);
}

void AKallariController::Vertical(float Value)
{
	if (MyCharacter == nullptr || MyCharacter->GetIsDead())	return;

	MyCharacter->AddControllerPitchInput(Value);	
}

void AKallariController::DashStart()
{
	if (bIsUsingSkill) return;
	if (MyCharacter == nullptr) return;

	MyCharacter->DashStart();

}

void AKallariController::DashEnd()
{
	if (MyCharacter == nullptr) return;

	MyCharacter->DashEnd();

}

void AKallariController::Jump()
{
	if (bIsUsingSkill) return;
	if (MyCharacter == nullptr) return;

	MyCharacter->Jump();

}

void AKallariController::Attack()
{
	if (bIsUsingSkill) return;
	if (MyCharacter == nullptr) return;

	bIsAttacking = MyCharacter->Attack(bIsAttacking);
}

void AKallariController::Evade()
{
	if (GetWorld()->GetTimeSeconds() - Evade_CoolDown_Calc_Sec < Evade_CoolDown_Time)
		return;
	Evade_CoolDown_Calc_Sec = GetWorld()->GetTimeSeconds();

	if (bIsUsingSkill) return;
	if (MyCharacter == nullptr) return;

	MyCharacter->Evade();

}

void AKallariController::OnSkill1()
{
	if (GetWorld()->GetTimeSeconds() - Skill1_CoolDown_Calc_Sec < Skill1_CoolDown_Time)
		return;

	Skill1_CoolDown_Calc_Sec = GetWorld()->GetTimeSeconds();

	if (MyCharacter == nullptr) return;

	MyCharacter->OnSkill1();

}


void AKallariController::OnAttackMontageEnded(UAnimMontage* Montage, bool blnterrupted)
{
	bIsAttacking = false;
	
	if (MyCharacter == nullptr) return;

	MyCharacter->AttackEnd();
}
