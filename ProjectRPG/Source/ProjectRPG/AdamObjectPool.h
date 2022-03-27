// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "GameFramework/Actor.h"
#include "AdamObjectPool.generated.h"

UCLASS()
class PROJECTRPG_API AAdamObjectPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAdamObjectPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	class AAdamArrow* GetPooledObject();
	void Expand();
	void ReturnObject(class AAdamArrow* ReturnObject);
public:
	TSubclassOf<class AAdamArrow> PooledObjectSubClass;
	int32 PoolSize = 0;
	int32 ExpandSize = 10;
private:
	TArray<class AAdamArrow*> pool;

};
