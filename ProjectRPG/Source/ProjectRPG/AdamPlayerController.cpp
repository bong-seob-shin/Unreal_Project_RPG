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
	Super::PostInitializeComponents(); // 폰과 플레이어 컨트롤러가 생성되는 시점
}
void AAdamPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void AAdamPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameOnly InputMode;  // UI 배제하고 게임에만 입력 전달
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
		// 카메라 위에서 볼 때 진행방향으로 이동하면 느려지는거 수정중
		//float PlayerStdAngle = 360.0f - GetControlRotation().Pitch; // 플레이어 컨트롤 로테이션의 pitch 값과 카메라 각도 제한 ViewPitchMin 값 비교용 변수
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
