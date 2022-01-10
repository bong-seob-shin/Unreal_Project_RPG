// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UAuroraAnimInstance::UAuroraAnimInstance()
{
	IsJumping = false;
}

void UAuroraAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	APawn* Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Character = Cast<ACharacter>(Pawn);
	}
}

void UAuroraAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (Character)
	{
		MoveSpeed = Character->GetVelocity().Size();
		Direction = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
		
		IsJumping = Character->GetCharacterMovement()->IsFalling();
	}
}