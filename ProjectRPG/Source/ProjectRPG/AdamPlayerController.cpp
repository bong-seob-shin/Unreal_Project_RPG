// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamPlayerController.h"
#include "AdamPlayerCameraManager.h"

DECLARE_LOG_CATEGORY_EXTERN(PalaceWorld, Log, All);
DEFINE_LOG_CATEGORY(PalaceWorld);

AAdamPlayerController::AAdamPlayerController()
{
	PlayerCameraManagerClass = AAdamPlayerCameraManager::StaticClass();
}


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
	//PlayerCameraManager->ViewPitchMax = 0.0f;
	//PlayerCameraManager->ViewPitchMin = -70.0f;

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
		// ī�޶� ������ �� �� ����������� �̵��ϸ� �������°� ������
		//float PlayerStdAngle = 360.0f - GetControlRotation().Pitch; // �÷��̾� ��Ʈ�� �����̼��� pitch ���� ī�޶� ���� ���� ViewPitchMin �� �񱳿� ����
		//float PostivePitchLimit = -1.0f * PlayerCameraManager->ViewPitchMin;

		////UE_LOG(PalaceWorld, Warning, TEXT("Pitch : %f, Manager: %f"), PlayerStdAngle, PostivePitchLimit);

		//if (PostivePitchLimit - PlayerStdAngle > 20.0f)
		//{
		//	//UE_LOG(PalaceWorld, Warning, TEXT("fixed : %f"), PostivePitchLimit - PlayerStdAngle);
		//	FixedFwdVec = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X);
		//	//MyCharacter->AddMovementInput(MyCharacter->GetActorForwardVector(), NewAxisValue);
		//	
		//}
		//MyCharacter->AddMovementInput(FixedFwdVec, NewAxisValue);
		
		MyCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
	}


}

void AAdamPlayerController::MoveLR(float NewAxisValue)
{
	ACharacter* const MyCharacter = GetCharacter();
	if (MyCharacter && NewAxisValue != 0.0f)
	{
		MyCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
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
