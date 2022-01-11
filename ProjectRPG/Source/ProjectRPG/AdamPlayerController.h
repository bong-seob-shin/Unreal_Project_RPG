// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
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

private:
	FVector FixedFwdVec; // 컨트롤 로테이션 pitch가 제한각도와 가까워 졌을 때 그 방향으로 진행되어 느려지는 플레이어 이동 방지를 위한 벡터
};
