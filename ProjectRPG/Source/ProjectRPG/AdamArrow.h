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
	// ������Ÿ�� �ӵ��� �߻� �������� �ʱ�ȭ ��Ű�� �Լ�
	void ShootInDirection(const FVector& ShootDirection);
public:
	FORCEINLINE void SetObjectPool(class AAdamObjectPool* InObjectPool) { m_ObjectPool = InObjectPool; } // �ڽ��� �����ϴ� ������Ʈ Ǯ�� ���۷��� �ʱ�ȭ ���� �Լ�
	void ReturnSelf(); // �ڽ��� �����ϴ� ������Ʈ Ǯ�� �����θ� ��ȯ�ϰ� ��Ȱ��ȭ �ϴ� �Լ�
	void SetActive(bool bIsActive); // �ڽ��� Ȱ��/��Ȱ��ȭ �ϴ� �Լ�
	void OnActivated(const FVector& ShootDir); // Ȱ��ȭ �Ǿ��� �� �Լ�
	FORCEINLINE bool getIsActive() { return m_bIsActive; } // �ش� ������Ʈ�� Ȱ��ȭ ���� ��ȯ �Լ�

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	FORCEINLINE void setDamageByPlayerLevel(float dmg) { DmgByPlayerLv = dmg; }
	FORCEINLINE float getDamageByPlayerLevel() { return DmgByPlayerLv; }

public:	
	// ȭ�� �޽�
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Bow_ArrowMesh;
protected:
	// �浹 �ڽ�
	UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadOnly, meta =(AllowPrivateAccess = "true"))
	class UBoxComponent* ArrowColBox;
	
	// ������Ÿ�� ������Ʈ
	UPROPERTY(Category = Movement, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* Movement; 
private:
	// ������Ʈ Ǯ�� ���� ������
	bool m_bIsActive; // �ش� ������Ʈ�� Ȱ��ȭ ����
	class AAdamObjectPool* m_ObjectPool; // �ش� ������Ʈ �����ϴ� ������Ʈ Ǯ�� ���۷���
	FTimerHandle ArrowTimerHandle; // �浹 �� ������Ʈ Ǯ�� ��ȯ ���� Ÿ�̸� �ڵ�
	float returnInterval; // ��ü�� �浹�ϰ� ������Ʈ Ǯ�� ��ȯ�ɶ� ���� �ð�

	static float DmgByPlayerLv;
};
