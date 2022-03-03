
// Fill out your copyright notice in the Description page of Project Settings.


#include "GruxAnimInstance.h"

UGruxAnimInstance::UGruxAnimInstance()
{

}

void UGruxAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (!IsValid(Pawn)) return;

	fCurrentSpeed = Pawn->GetVelocity().Size();
}
