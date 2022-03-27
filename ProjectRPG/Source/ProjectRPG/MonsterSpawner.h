// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawner.generated.h"

UCLASS()
class PROJECTRPG_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY()
	class AGrux* Spawn_Grux;

	UPROPERTY(EditAnywhere, Category = "Location")
	FVector SpawnerLocation;

	UPROPERTY(VisibleAnywhere, Category = "Capsule")
	class USceneComponent* Body;

	UFUNCTION()
	void SpawnGrux();

	FTimerHandle SpawnTimerHandle;

};
