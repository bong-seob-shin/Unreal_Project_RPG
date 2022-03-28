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
	FORCEINLINE void SetObjectPool(class AAdamObjectPool* InObjectPool) { m_ObjectPool = InObjectPool; } // 자신을 관리하는 오브젝트 풀의 레퍼런스 초기화 위한 함수
	void ReturnSelf(); // 자신을 관리하는 오브젝트 풀에 스스로를 반환하고 비활성화 하는 함수
	void SetActive(bool bIsActive); // 자신을 활성/비활성화 하는 함수
	FORCEINLINE bool getIsActive() { return m_bIsActive; } // 해당 오브젝트의 활성화 여부 반환 함수
public:	
	// 화살 메쉬
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Bow_ArrowMesh;

private:
	// 오브젝트 풀링 위한 변수들
	bool m_bIsActive; // 해당 오브젝트의 활성화 여부
	class AAdamObjectPool* m_ObjectPool; // 해당 오브젝트 관리하는 오브젝트 풀의 레퍼런스
};
