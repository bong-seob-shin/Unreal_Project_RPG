// Fill out your copyright notice in the Description page of Project Settings.


#include "KallariWidget.h"
#include "KallariStatComponent.h"
#include "Components/ProgressBar.h"

void UKallariWidget::BindCharacterStat(UKallariStatComponent* NewCharacterStat)
{
	if (NewCharacterStat == nullptr)
		return;

	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChanged.AddUObject(this, &UKallariWidget::UpdateHPWidget);
}

void UKallariWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Update HP Widget"));

		PB_HPBar->SetPercent(CurrentCharacterStat->GetHpRatio());
	}

}
