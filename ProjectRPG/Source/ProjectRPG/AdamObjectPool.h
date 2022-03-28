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
	class AAdamArrow* GetPooledObject(); // ������Ʈ Ǯ���� �����ϴ� ������Ʈ�� �ϳ� ��ȯ�ϴ� �Լ�
	void Expand(); // ������Ʈ Ǯ�� ��ȯ ������ ��ü�� �� �̻� ���� ��� ������Ʈ Ǯ�� Ȯ��(��ü �ø�)�ϴ� �Լ�
	void ReturnObject(class AAdamArrow* ReturnObject); // ������Ʈ Ǯ�� ��ȯ�� ��ü�� ������Ʈ Ǯ�� �߰��ϴ� �Լ�
public:
	TSubclassOf<class AAdamArrow> PooledObjectSubClass; // ������ ������Ʈ Ŭ����
	int32 PoolSize = 0; // ������Ʈ Ǯ �⺻ ũ��
	int32 ExpandSize = 10; // ������Ʈ Ǯ Ȯ�� ũ��
private:
	TArray<class AAdamArrow*> Pool; // ������Ʈ Ǯ

};
