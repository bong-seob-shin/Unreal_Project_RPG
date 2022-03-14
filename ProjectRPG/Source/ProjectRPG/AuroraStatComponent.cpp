// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraStatComponent.h"
#include "AuroraGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UAuroraStatComponent::UAuroraStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	
	Level = 1;
}


// Called when the game starts
void UAuroraStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UAuroraStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}


// Called every frame
void UAuroraStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAuroraStatComponent::SetNewLevel(int32 NewLevel)
{
	auto AuroraInstance = Cast<UAuroraGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (AuroraInstance != nullptr)
	{
		CurrentStatData = AuroraInstance->GetAuroraCharacterData(NewLevel);
		if (CurrentStatData != nullptr)
		{
			Level = NewLevel;
			CurrentHP = CurrentStatData->MaxHp;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Level %d data doesn't exsist"), NewLevel);
		}
	}
}

void UAuroraStatComponent::SetDamage(float NewDamage)
{
	if(CurrentStatData != nullptr)
	{
		CurrentHP = FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHp);
		if (CurrentHP <= 0.0f)
		{
			OnHpIsZero.Broadcast();
		}
		
	}
}

float UAuroraStatComponent::GetAttack()
{
	if (CurrentStatData == nullptr)
		return 0.0f;
	return CurrentStatData->Attack;
}

