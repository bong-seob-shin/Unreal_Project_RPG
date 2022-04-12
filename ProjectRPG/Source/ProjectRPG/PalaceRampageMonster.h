// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "GameFramework/Character.h"
#include "PalaceRampageMonster.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate); // ���� �½�ũ���� ���� ���� ����Ǹ� �˸� ���� �� �ֵ��� ��������Ʈ

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
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// ĳ���� ����
	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UAdamCharacterStatComponent* CharacterStat;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	void Attack();
	FOnAttackEndDelegate OnAttackEnd;
	void AttackCheck();
	void Die();
private:
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsAttacking;

	UPROPERTY()
	class URampageAnimInstance* RampageAnim;

	FTimerHandle destroyTimerHandle; // ��ü �Ҹ� ���� Ÿ�̸� �ڵ�
	float destroyInterval; // ��ü �Ҹ�� �� ���� �ð�
};
