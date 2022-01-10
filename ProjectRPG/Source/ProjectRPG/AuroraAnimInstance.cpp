// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraAnimInstance.h"

void UAuroraAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		MoveSpeed = Pawn->GetVelocity().Size();
		Direction = CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
	}
}