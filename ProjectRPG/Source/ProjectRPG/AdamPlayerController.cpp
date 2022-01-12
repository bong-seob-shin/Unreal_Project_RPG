// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamPlayerController.h"
#include "AdamPlayerCameraManager.h"
#include "AdamAnimInstance.h"
#include "AdamCharacter.h"


AAdamPlayerController::AAdamPlayerController()
{
	PlayerCameraManagerClass = AAdamPlayerCameraManager::StaticClass();
	bIsAttacking = false;
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
	//ACharacter* const MyCharacter = GetCharacter();
	if (MyCharacter && NewAxisValue != 0.0f)
	{
		MyCharacter->AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), NewAxisValue);
	}


}

void AAdamPlayerController::MoveLR(float NewAxisValue)
{
	//ACharacter* const MyCharacter = GetCharacter();
	if (MyCharacter && NewAxisValue != 0.0f)
	{
		MyCharacter->AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), NewAxisValue);
	}
}

void AAdamPlayerController::Jump()
{
	//ACharacter* const MyCharacter = GetCharacter();
	if (MyCharacter)
	{
		MyCharacter->Jump();
	}
}

void AAdamPlayerController::StopJumping()
{
	//ACharacter* const MyCharacter = GetCharacter();
	if (MyCharacter)
	{
		MyCharacter->StopJumping();
	}
}

void AAdamPlayerController::LookUp(float NewAxisValue)
{
	//ACharacter* const MyCharacter = GetCharacter();
	if (MyCharacter)
	{
		MyCharacter->AddControllerPitchInput(NewAxisValue);
	}
	
}

void AAdamPlayerController::Turn(float NewAxisValue)
{
	//ACharacter* const MyCharacter = GetCharacter();
	if (MyCharacter)
	{
		MyCharacter->AddControllerYawInput(NewAxisValue);
	}
}

void AAdamPlayerController::Sprint()
{
	//ACharacter* const MyCharacter = GetCharacter();
	if (MyCharacter)
	{
		MyCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
}

void AAdamPlayerController::StopSprinting()
{
	//ACharacter* const MyCharacter = GetCharacter();
	if (MyCharacter)
	{
		MyCharacter->GetCharacterMovement()->MaxWalkSpeed = 450.0f;
	}
}

void AAdamPlayerController::Attack()
{
	if (bIsAttacking)
	{
		if (FMath::IsWithinInclusive<int32>(MyCharacter->CurrentCombo, 1, MyCharacter->MaxCombo))
		{
			if (MyCharacter->bCanNextCombo)
				MyCharacter->bIsComboInputOn = true;
		}
	}
	else
	{
		if (MyCharacter->CurrentCombo == 0) {
			MyCharacter->AttackStartComboState();
			MyCharacter->AdamAnim->PlayAttackMontage();
			MyCharacter->AdamAnim->JumpToAttackMontageSection(MyCharacter->CurrentCombo);
			bIsAttacking = true;
		}
	}
}


