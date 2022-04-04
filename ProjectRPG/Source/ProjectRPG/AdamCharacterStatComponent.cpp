// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamCharacterStatComponent.h"
#include "PalaceGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
UAdamCharacterStatComponent::UAdamCharacterStatComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
}

// Called when the game starts or when spawned
void UAdamCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UAdamCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}

void UAdamCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto AdamGameInstance = Cast<UPalaceGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (nullptr != AdamGameInstance)
	{
		CurrentStatData = AdamGameInstance->GetAdamCharacterData(NewLevel);
		if (nullptr != CurrentStatData)
		{
			Level = NewLevel;
			CurrentHP = CurrentStatData->MaxHP;
		}
		else
		{
			UE_LOG(PalaceWorld,Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
		}
	}
}


