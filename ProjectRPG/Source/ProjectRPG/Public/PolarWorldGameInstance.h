// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "PolarWorldGameInstance.generated.h"


USTRUCT(BlueprintType)
struct FKallariData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FKallariData() : Level(1), MaxHp(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp;
};

/**
 * 
 */
UCLASS()
class PROJECTRPG_API UPolarWorldGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPolarWorldGameInstance();

	FKallariData* GetKallariData(int32 Level);
	virtual void Init() override;

private:
	UPROPERTY()
	class UDataTable* KallariTable;
};
