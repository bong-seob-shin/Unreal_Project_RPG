// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "Components/ActorComponent.h"
#include "AdamCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelgate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangeDelgate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTRPG_API UAdamCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UAdamCharacterStatComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:
	void SetNewLevel(int32 NewLevel);
	void SetDamage(float NewDamage);
	void SetHP(float NewHP);
	float GetAttack();
	float GetHPRatio();

	FOnHPIsZeroDelgate OnHPIsZero;
	FOnHPChangeDelgate OnHPChanged;
private:
	struct FAdamCharacterData* CurrentStatData = nullptr;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;

	// ���� ���۶� ���� ����Ǵ� ���� �����ϴ°� �ǹ̰� �����Ƿ� Transient Ű����� ����ȭ���� ����
	UPROPERTY(Transient,VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentHP;
};
