// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraAnimNotify.h"
#include "AuroraCharacter.h"
#include "AuroraAnimInstance.h"

void UAuroraAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	UAuroraAnimInstance* AnimInstance = Cast<UAuroraAnimInstance>(MeshComp->GetOwner());
	
	//AnimInstance->AnimNotify_FirstAbilityEnd();
}

FString UAuroraAnimNotify::GetNotifyName_Implementation() const
{
	return L"FirstAbilityEnd";
}
