// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraGameInstance.h"

UAuroraGameInstance::UAuroraGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DATA_AURORA(TEXT("DataTable'/Game/Data/AuroraStatTable.AuroraStatTable'"));

	AuroraCharacterTable = DATA_AURORA.Object;
}

void UAuroraGameInstance::Init()
{
	Super::Init();
}

FAuroraCharacterData* UAuroraGameInstance::GetAuroraCharacterData(int32 Level)
{
	return AuroraCharacterTable->FindRow<FAuroraCharacterData>(*FString::FromInt(Level), TEXT(""));
}
