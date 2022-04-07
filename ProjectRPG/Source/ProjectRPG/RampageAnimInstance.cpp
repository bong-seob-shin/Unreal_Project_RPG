// Fill out your copyright notice in the Description page of Project Settings.


#include "RampageAnimInstance.h"

URampageAnimInstance::URampageAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	CurrentPawnDir = 0.0f;
}


void URampageAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
		return;

	if (!bIsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		CurrentPawnDir = CalculateDirection(Pawn->GetVelocity(), FRotator(0.0f, Pawn->GetControlRotation().Yaw, 0.0f)); // pawn의 진행방향 구하는 코드
	}
}
