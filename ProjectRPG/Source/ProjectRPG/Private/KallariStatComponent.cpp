// Fill out your copyright notice in the Description page of Project Settings.

#include "KallariStatComponent.h"
#include "PolarWorldGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UKallariStatComponent::UKallariStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...
	Level = 1;
	Recovery_HP_Amount = 5.0f;
}


// Called when the game starts
void UKallariStatComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(HpRecoveryTimerHandle, this, &UKallariStatComponent::HPRecovery, 10.0f, true, 0.0f);

	// ...
}

void UKallariStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);

}

void UKallariStatComponent::SetNewLevel(int32 NewLevel)
{
	auto PolarWorldGameInstance = Cast<UPolarWorldGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (PolarWorldGameInstance != nullptr)
	{
		CurrentStatData = PolarWorldGameInstance->GetKallariData(NewLevel);
		if (CurrentStatData != nullptr)
		{
			Level = NewLevel;
			SetHP(CurrentStatData->MaxHp);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Level %d data doesn't exsist"), NewLevel);
		}
	}
}

void UKallariStatComponent::SetDamage(float NewDamage)
{
	if (CurrentStatData == nullptr)
		return;

	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHp));
	if (CurrentHP <= KINDA_SMALL_NUMBER)
	{
		OnHPIsZero.Broadcast();
	}
	

}

void UKallariStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();

	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}

}

float UKallariStatComponent::GetAttack()
{
	if (CurrentStatData == nullptr)
		return 0.0f;

	return CurrentStatData->Attack;
}

float UKallariStatComponent::GetHpRatio()
{
	if(CurrentStatData == nullptr)
		return 0.0f;

	return (CurrentStatData->MaxHp < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHp);
}

void UKallariStatComponent::HPRecovery()
{
	if (CurrentStatData == nullptr)
		return;

	CurrentHP = CurrentHP + Recovery_HP_Amount;

	if (CurrentHP >= CurrentStatData->MaxHp)
	{
		CurrentHP = CurrentStatData->MaxHp;
	}
	OnHPChanged.Broadcast();
}

