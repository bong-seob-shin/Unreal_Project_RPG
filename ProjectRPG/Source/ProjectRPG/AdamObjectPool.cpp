// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamObjectPool.h"
#include "AdamArrow.h"

// Sets default values
AAdamObjectPool::AAdamObjectPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAdamObjectPool::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAdamObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AAdamArrow* AAdamObjectPool::GetPooledObject()
{
	if (pool.Num() == 0)
		Expand();
	return pool.Pop();
}

void AAdamObjectPool::Expand()
{
	for (int i = 0; i < ExpandSize; ++i)
	{
		AAdamArrow* PoolableActor = GetWorld()->SpawnActor<AAdamArrow>(PooledObjectSubClass, FVector().ZeroVector, FRotator().ZeroRotator);
		PoolableActor->SetActive(false);
		pool.Push(PoolableActor);
	}
	PoolSize += ExpandSize;
}

void AAdamObjectPool::ReturnObject(AAdamArrow* ReturnObject)
{
	pool.Push(ReturnObject);
}

