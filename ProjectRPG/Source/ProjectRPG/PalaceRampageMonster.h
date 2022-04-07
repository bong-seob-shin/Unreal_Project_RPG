// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "GameFramework/Character.h"
#include "PalaceRampageMonster.generated.h"

UCLASS()
class PROJECTRPG_API APalaceRampageMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APalaceRampageMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Ä³¸¯ÅÍ ½ºÅÈ
	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UAdamCharacterStatComponent* CharacterStat;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;
};
