// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kallari.generated.h"

UCLASS()
class PROJECTRPG_API AKallari : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKallari();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DashStart();
	void DashEnd();
	void Evade();
	bool Attack(bool IsAttack);
	void AttackEnd();
	void OnSkill1(bool OnOff);
private:
	void Skill1();
	void Dash(float DeltaTime);
	void AttackStartComboState();
	void AttackCheck();

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	UDecalComponent* ShadowDecal;

	UPROPERTY()
	class UKallariAnimInstance* AnimInstance;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float fAttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float fAttackRadius;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bCanNextCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsComboInputOn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 iCurrentCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 iMaxCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = KallariMove, Meta = (AllowPrivateAccess = true))
	float fWalkSpeed;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = KallariMove, Meta = (AllowPrivateAccess = true))
	float fDashSpeed;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = KallariMove, Meta = (AllowPrivateAccess = true))
	float fJumpForce;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = KallariMove, Meta = (AllowPrivateAccess = true))
	bool bIsDash;

	const float fSpeedIncreaseRate = 1000.0f;



};
