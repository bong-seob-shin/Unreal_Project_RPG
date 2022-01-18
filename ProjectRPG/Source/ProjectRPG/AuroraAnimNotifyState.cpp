// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraAnimNotifyState.h"
#include "AuroraCharacter.h"

void UAuroraAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AAuroraCharacter* Player = Cast<AAuroraCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->HitFX();
		}
	}
}

void UAuroraAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
