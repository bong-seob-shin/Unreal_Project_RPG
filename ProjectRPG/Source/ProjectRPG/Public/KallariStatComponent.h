// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KallariStatComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHPIsZero);
DECLARE_MULTICAST_DELEGATE(FOnHPChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTRPG_API UKallariStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKallariStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

public:
	void SetNewLevel(int32 NewLevel);
	void SetDamage(float NewDamage);
	void SetHP(float NewHP);

	float GetAttack();
	float GetHpRatio();

	FOnHPIsZero OnHPIsZero;
	FOnHPChanged OnHPChanged;

private:
	void HPRecovery();
private:
	struct FKallariData* CurrentStatData = nullptr;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAcess = true))
	int32 Level;

	UPROPERTY(Transient, VisibleInstanceOnly, Meta = (AllowPrivateAcess = true))
	float CurrentHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Meta = (AllowPrivateAcess = true))
	float Recovery_HP_Amount;

	FTimerHandle HpRecoveryTimerHandle;

};
