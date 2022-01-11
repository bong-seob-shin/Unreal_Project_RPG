// Fill out your copyright notice in the Description page of Project Settings.


#include "Kallari.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "KallariAnimInstance.h"
#include "KallariController.h"
// Sets default values
AKallari::AKallari()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ComponentSetting
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));//Camera Default Setting

	//SpringArm and Camera Setting
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	//Mesh Setting
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("SkeletalMesh'/Game/PolarWorld/ParagonKallari/Characters/Heroes/Kallari/Skins/Rogue/Meshes/Kallari_Rogue.Kallari_Rogue'"));

	if (SkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	//Animation Setting
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> KallariAnim(TEXT("AnimBlueprint'/Game/PolarWorld/BP_PolarWorld/ABP_Kallari.ABP_Kallari_C'"));
	if (KallariAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(KallariAnim.Class);
	}

	//Set ComboSystem
	iMaxCombo = 5;
	
}

// Called when the game starts or when spawned
void AKallari::BeginPlay()
{
	Super::BeginPlay();
	

}

void AKallari::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto TempAnimInstance = Cast<UKallariAnimInstance>(GetMesh()->GetAnimInstance());

	if (TempAnimInstance != nullptr)
	{
		AnimInstance = TempAnimInstance;
		auto TempController = Cast<AKallariController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if(TempController != nullptr)
			AnimInstance->OnMontageEnded.AddDynamic(TempController, &AKallariController::OnAttackMontageEnded);

		AnimInstance->OnNextAttackCheck.AddLambda([this]()->void {
			bCanNextCombo = false;

			if (bIsComboInputOn)
			{
				AttackStartComboState();
				AnimInstance->JumpToAttackMontageSection(iCurrentCombo);
			}
		});
	}


}

// Called every frame
void AKallari::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AKallari::Attack(bool IsAttack)
{
	if (IsAttack) {
		if (bCanNextCombo)
		{
			bIsComboInputOn = true;
		}
	}
	else {
		AttackStartComboState();
		AnimInstance->PlayAttackMontage();
		AnimInstance->JumpToAttackMontageSection(iCurrentCombo);
	}
	return true;
}




void AKallari::AttackStartComboState()
{
	bCanNextCombo = true;
	bIsComboInputOn = false;
	iCurrentCombo++;
}

void AKallari::AttackEnd()
{
	bCanNextCombo = false;
	bIsComboInputOn = false;
	iCurrentCombo = 0;
}




