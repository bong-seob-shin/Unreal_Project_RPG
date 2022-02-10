// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "EngineMinimal.h"
#include "PalaceWorld.h"
#include "GameFramework/Character.h"
#include "AdamCharacter.generated.h"




UCLASS()
class PROJECTRPG_API AAdamCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAdamCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override; // �θ� AActor�� ������ ���� ������ �����Ǿ� �־� superŰ����� �θ� Ŭ���� ���� ���� ����

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// �� �� ���� ����ƽ�޽���
	UPROPERTY(VisibleAnywhere, Category = Weapon_Back)
	UStaticMeshComponent* Bow;
	UPROPERTY(VisibleAnywhere, Category = Weapon_Back)
	UStaticMeshComponent* Quiver; // ȭ����
	UPROPERTY(VisibleAnywhere, Category = Weapon_Back)
	UStaticMeshComponent* Scabbard; // Į��
	UPROPERTY(VisibleAnywhere, Category = Weapon_Back)
	UStaticMeshComponent* Sword; // Į���� ���� Į
	UPROPERTY(VisibleAnywhere, Category = Weapon_Back)
	UStaticMeshComponent* Shield; // Į���� ���� Į

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	// �����¿� �̵�
	void MoveFB(float NewAxisValue);
	void MoveLR(float NewAxisValue);
	void Attack(); // �⺻����. ���߿� ���� ���� �ٸ���
	// shiftŰ-�޸���
	void Sprint(); 
	void StopSprinting();
	void UseWeaponAbility(); // ���� Ư�����. ���� ���� �ٸ���
	void StopWeaponAbility();
	// ����Ű : ���� ��ȯ
	void SwordAndShieldMode();
	void BowMode();

private:
	//void LoadStaticMeshInConstructor(UStaticMeshComponent* SMComponent,FName SocketName, FName ComponentName, UStaticMesh* mesh);

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// Į ���� �޺�
	void AttackStartComboState();
	void AttackEndComboState();
	// Į ���� Ž��
	void AttackCheck();
	

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) // ���� ���� Ÿ��
	EWeaponType CurWeaponType;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsAttacking;

	// Į ���� �޺� ������
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bCanNextCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsComboInputOn;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	// Į ���� �浹ó��: ĸ�� ����� �����
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRange;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRadius;

	UPROPERTY()
	class UAdamAnimInstance* AdamAnim;

	

	// ĳ���� �����Ʈ ���� �⺻����
	const float fWalkSpeed = 300.f;
	const float fAcceleration = 2048.f;
	const float fDeceleration = 521.f;

	
};
