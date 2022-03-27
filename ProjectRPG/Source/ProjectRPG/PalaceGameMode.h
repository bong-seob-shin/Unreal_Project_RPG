// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PalaceGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRPG_API APalaceGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	APalaceGameMode();
	class AAdamObjectPool* GetActorPool();
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<AAdamObjectPool> ActorPoolClass;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	AAdamObjectPool* ActorPool;
};
