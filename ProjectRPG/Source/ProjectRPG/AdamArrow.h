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
	FORCEINLINE void SetObjectPool(class AAdamObjectPool* InObjectPool) { m_ObjectPool = InObjectPool; } // �ڽ��� �����ϴ� ������Ʈ Ǯ�� ���۷��� �ʱ�ȭ ���� �Լ�
	void ReturnSelf(); // �ڽ��� �����ϴ� ������Ʈ Ǯ�� �����θ� ��ȯ�ϰ� ��Ȱ��ȭ �ϴ� �Լ�
	void SetActive(bool bIsActive); // �ڽ��� Ȱ��/��Ȱ��ȭ �ϴ� �Լ�
	FORCEINLINE bool getIsActive() { return m_bIsActive; } // �ش� ������Ʈ�� Ȱ��ȭ ���� ��ȯ �Լ�
public:	
	// ȭ�� �޽�
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Bow_ArrowMesh;

private:
	// ������Ʈ Ǯ�� ���� ������
	bool m_bIsActive; // �ش� ������Ʈ�� Ȱ��ȭ ����
	class AAdamObjectPool* m_ObjectPool; // �ش� ������Ʈ �����ϴ� ������Ʈ Ǯ�� ���۷���
};
