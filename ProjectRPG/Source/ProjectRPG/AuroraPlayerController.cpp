// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraPlayerController.h"
#include "AuroraPlayerCameraManager.h"
#include "AuroraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AuroraAnimInstance.h"

AAuroraPlayerController::AAuroraPlayerController()
{
	PlayerCameraManagerClass = AAuroraPlayerCameraManager::StaticClass();

	IsAttackingMelee = false;

	MaxCombo = 4;
	AttackMeleeEndComboState();
}

void AAuroraPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AAuroraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MoveForward"), this, &AAuroraPlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AAuroraPlayerController::MoveRight);
	InputComponent->BindAxis(TEXT("Turn"), this, &AAuroraPlayerController::Turn);
	InputComponent->BindAxis(TEXT("LookUp"), this, &AAuroraPlayerController::LookUp);

	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AAuroraPlayerController::Jump);
	InputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &AAuroraPlayerController::BeginRun);
	InputComponent->BindAction(TEXT("Run"), IE_Released, this, &AAuroraPlayerController::EndRun);
	InputComponent->BindAction(TEXT("Shield"), IE_Pressed, this, &AAuroraPlayerController::BeginShield);
	InputComponent->BindAction(TEXT("Shield"), IE_Released, this, &AAuroraPlayerController::EndShield);

	InputComponent->BindAction(TEXT("AttackMelee"), IE_Pressed, this, &AAuroraPlayerController::AttackMelee);
	InputComponent->BindAction(TEXT("FirstAbility"), IE_Pressed, this, &AAuroraPlayerController::FirstAbility);
	InputComponent->BindAction(TEXT("SecondAbility"), IE_Pressed, this, &AAuroraPlayerController::SecondAbility);
	InputComponent->BindAction(TEXT("ThirdAbility"), IE_Pressed, this, &AAuroraPlayerController::ThirdAbility);
}

void AAuroraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	APawn* const aPawn = GetPawn();
	AAuroraCharacter* AuroraCharacter = Cast<AAuroraCharacter>(aPawn);
	if (AuroraCharacter == nullptr) return;
	
	AuroraCharacter->GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	AuroraAnimInstance = Cast<UAuroraAnimInstance>(AuroraCharacter->GetMesh()->GetAnimInstance());
	AuroraAnimInstance->OnMontageEnded.AddDynamic(this, &AAuroraPlayerController::OnAttackMeleeMontageEnded);

	AuroraAnimInstance->OnNextAttackMeleeCheck.AddLambda([this]()-> void {
		canNextCombo = false;

		if (IsComboInputOn)
		{
			AttackMeleeStartComboState();
			AuroraAnimInstance->JumpToAttackMeleeMontageSection(CurrentCombo);
		}
	});
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

void AAuroraPlayerController::BeginShield()
{
	AuroraAnimInstance->SetBeginShieldAnimation();
}

void AAuroraPlayerController::EndShield()
{
	AuroraAnimInstance->SetEndShieldAnimation();
}


void AAuroraPlayerController::AttackMelee()
{
	if (IsAttackingMelee)
	{
		if (canNextCombo)
		{
			IsComboInputOn = true;
		}
	}
	else
	{
		AttackMeleeStartComboState();
		AuroraAnimInstance->PlayAttackMeleeMontage();
		AuroraAnimInstance->JumpToAttackMeleeMontageSection(CurrentCombo);
		IsAttackingMelee = true;
	}
}

void AAuroraPlayerController::FirstAbility()
{
}

void AAuroraPlayerController::SecondAbility()
{
}

void AAuroraPlayerController::ThirdAbility()
{
}

void AAuroraPlayerController::OnAttackMeleeMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttackingMelee = false;
	AttackMeleeEndComboState();	
}

void AAuroraPlayerController::AttackMeleeStartComboState()
{
	canNextCombo = true;
	IsComboInputOn = false;
	CurrentCombo++;
}

void AAuroraPlayerController::AttackMeleeEndComboState()
{
	IsComboInputOn = false;
	canNextCombo = false;
	CurrentCombo = 0;
}
