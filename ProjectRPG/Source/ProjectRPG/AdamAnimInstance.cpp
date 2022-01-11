// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamAnimInstance.h"


UAdamAnimInstance::UAdamAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
}


void UAdamAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		CurrentPawnDir = CalculateDirection(Pawn->GetVelocity(), Pawn->GetControlRotation());
	}

}