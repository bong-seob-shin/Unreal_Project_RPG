// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "GameFramework/Actor.h"
#include "AdamArrow.generated.h"

UCLASS()
class PROJECTRPG_API AAdamArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAdamArrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	FORCEINLINE void SetObjectPool(class UAdamObjectPool* InObjectPool) { m_ObjectPool = InObjectPool; }
	void ReturnSelf();
	void SetActive(bool bIsActive);
	FORCEINLINE bool getIsActive() { return m_bIsActive; }
public:	
	// 화살 메쉬
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Bow_ArrowMesh;

private:
	// 오브젝트 풀링 위한 변수들
	bool m_bIsActive;
	class AAdamObjectPool* m_ObjectPool;
};
