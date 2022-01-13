// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamPlayerController.h"
#include "AdamPlayerCameraManager.h"
#include "AdamCharacter.h"


AAdamPlayerController::AAdamPlayerController()
{
	PlayerCameraManagerClass = AAdamPlayerCameraManager::StaticClass();
	
}


void AAdamPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents(); // 폰과 플레이어 컨트롤러가 생성되는 시점 확인 가능

}
void AAdamPlayerController::OnPossess(APawn* aPawn) 
{
	Super::OnPossess(aPawn); // 빙의를 진행하는 시점 
	MyCharacter = Cast<AAdamCharacter>(GetCharacter());
	
	
}

void AAdamPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameOnly InputMode;  // UI 배제하고 게임에만 입력 전달
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

	InputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AAdamPlayerController::Sprint);
	InputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AAdamPlayerController::StopSprinting);

	InputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &AAdamPlayerController::Attack);


}

void AAdamPlayerController::MoveFB(float NewAxisValue)
{
	if (MyCharacter && NewAxisValue != 0.0f)
	{
		MyCharacter->AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), NewAxisValue);
	}


}

void AAdamPlayerController::MoveLR(float NewAxisValue)
{
	if (MyCharacter && NewAxisValue != 0.0f)
	{
		MyCharacter->AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), NewAxisValue);
	}
}

void AAdamPlayerController::Jump()
{
	if (MyCharacter)
	{
		MyCharacter->Jump();
	}
}

void AAdamPlayerController::StopJumping()
{
	if (MyCharacter)
	{
		MyCharacter->StopJumping();
	}
}

void AAdamPlayerController::LookUp(float NewAxisValue)
{
	if (MyCharacter)
	{
		MyCharacter->AddControllerPitchInput(NewAxisValue);
	}
	
}

void AAdamPlayerController::Turn(float NewAxisValue)
{
	if (MyCharacter)
	{
		MyCharacter->AddControllerYawInput(NewAxisValue);
	}
}

void AAdamPlayerController::Sprint()
{
	if (MyCharacter)
	{
		MyCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
}

void AAdamPlayerController::StopSprinting()
{
	if (MyCharacter)
	{
		MyCharacter->GetCharacterMovement()->MaxWalkSpeed = 450.0f;
	}
}

void AAdamPlayerController::Attack()
{
	if (MyCharacter)
	{
		MyCharacter->Attack();
	}
}




