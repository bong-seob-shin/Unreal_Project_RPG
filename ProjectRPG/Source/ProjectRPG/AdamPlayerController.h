// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "EngineMinimal.h"
#include "PalaceWorld.h"
#include "GameFramework/PlayerController.h"
#include "AdamPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRPG_API AAdamPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAdamPlayerController();
public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;

protected:
	virtual void BeginPlay() override; 
	virtual void SetupInputComponent() override;

private:
	void MoveFB(float NewAxisValue);
	void MoveLR(float NewAxisValue);
	void Jump();
	void StopJumping();
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);
	void Sprint();
	void StopSprinting();
	void Attack(); // 기본공격. 나중에 무기 따라 다르게

	
private:
	class AAdamCharacter* MyCharacter;
public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsAttacking;

};
