// Fill out your copyright notice in the Description page of Project Settings.


#include "PolarWorldGameInstance.h"

UPolarWorldGameInstance::UPolarWorldGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Kallari(TEXT("DataTable'/Game/PolarWorld/GameDatas/KallariData.KallariData'"));

	if(DT_Kallari.Succeeded())
		KallariTable = DT_Kallari.Object;
}

FKallariData* UPolarWorldGameInstance::GetKallariData(int32 Level)
{
	return KallariTable->FindRow<FKallariData>(*FString::FromInt(Level), TEXT(""));
}

void UPolarWorldGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("DropExp of Level 20 : %d"), GetKallariData(20)->DropExp);
}
