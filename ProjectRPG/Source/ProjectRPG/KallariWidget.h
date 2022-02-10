// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KallariWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRPG_API UKallariWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class UKallariStatComponent* NewCharacterStat);
	void UpdateHPWidget();
private:
	TWeakObjectPtr<class UKallariStatComponent> CurrentCharacterStat;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HPBar;
};
