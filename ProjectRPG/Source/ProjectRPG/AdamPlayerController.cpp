// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamPlayerController.h"

void AAdamPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents(); // ���� �÷��̾� ��Ʈ�ѷ��� �����Ǵ� ����
}
void AAdamPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void AAdamPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameOnly InputMode;  // UI �����ϰ� ���ӿ��� �Է� ����
	SetInputMode(InputMode);
}

void AAdamPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAxis(TEXT("MoveFB"), this, &AAdamPlayerController::MoveFB);
	InputComponent->BindAxis(TEXT("MoveLR"), this, &AAdamPlayerController::MoveLR);

	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AAdamPlayerController::Jump);
	InputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AAdamPlayerController::StopJumping);

	InputComponent->BindAxis(TEXT("LookUp"),this, &AAdamPlayerController::LookUp);
	InputComponent->BindAxis(TEXT("Turn"), this, &AAdamPlayerController::Turn);
}

void AAdamPlayerController::MoveFB(float NewAxisValue)
{
	ACharacter* const MyCharacter = GetCharacter();
	if (MyCharacter && NewAxisValue != 0.0f)
	{
		MyCharacter->AddMovementInput(MyCharacter->GetActorForwardVector(), NewAxisValue);
	}

}

void AAdamPlayerController::MoveLR(float NewAxisValue)
{
	ACharacter* const MyCharacter = GetCharacter();
	if (MyCharacter && NewAxisValue != 0.0f)
	{
		MyCharacter->AddMovementInput(MyCharacter->GetActorRightVector(), NewAxisValue);
	}
}

void AAdamPlayerController::Jump()
{
	ACharacter* const MyCharacter = GetCharacter();
	if (MyCharacter)
	{
		MyCharacter->Jump();
	}
}

void AAdamPlayerController::StopJumping()
{
	ACharacter* const MyCharacter = GetCharacter();
	if (MyCharacter)
	{
		MyCharacter->StopJumping();
	}
}

void AAdamPlayerController::LookUp(float NewAxisValue)
{
	ACharacter* const MyCharacter = GetCharacter();
	if (MyCharacter)
	{
		MyCharacter->AddControllerPitchInput(NewAxisValue);
	}
	
}

void AAdamPlayerController::Turn(float NewAxisValue)
{
	ACharacter* const MyCharacter = GetCharacter();
	if (MyCharacter)
	{
		MyCharacter->AddControllerYawInput(NewAxisValue);
	}
}
