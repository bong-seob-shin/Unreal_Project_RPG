// Fill out your copyright notice in the Description page of Project Settings.


#include "PalaceRampageMonster.h"
#include "AdamCharacterStatComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "AdamCharacterWidget.h"
#include "RampageAnimInstance.h"

// Sets default values
APalaceRampageMonster::APalaceRampageMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CharacterStat = CreateDefaultSubobject<UAdamCharacterStatComponent>(TEXT("CHARACTERSTAT"));
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	
	HPBarWidget->SetupAttachment(GetMesh());

	// 메쉬 방향
	//GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -95.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_RAMPAGE(TEXT("/Game/PalaceWorld/Resources/ParagonRampage/Characters/Heroes/Rampage/Meshes/Rampage.Rampage"));
	if (SK_RAMPAGE.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_RAMPAGE.Object);
	}
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> RAMPAGE_ANIM(TEXT("/Game/PalaceWorld/Blueprints/Animations/Monster/RampageAnimBP.RampageAnimBP_C"));
	if (RAMPAGE_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(RAMPAGE_ANIM.Class);
	}

	// 체력바 UI
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 230.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/PalaceWorld/Blueprints/UI/UI_HPBar.UI_HPBar_C"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}

}

// Called when the game starts or when spawned
void APalaceRampageMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APalaceRampageMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APalaceRampageMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APalaceRampageMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	RampageAnim = Cast<URampageAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == RampageAnim)
	{
		UE_LOG(PalaceWorld, Error, TEXT("Animinstance Nullptr"));
		return;
	}
	RampageAnim->OnMontageEnded.AddDynamic(this, &APalaceRampageMonster::OnAttackMontageEnded);
}

void APalaceRampageMonster::Attack()
{
	if (!bIsAttacking)
	{
		RampageAnim->PlayRandAttackMontage();
		bIsAttacking = true;
		
	}
}

void APalaceRampageMonster::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAttacking = false;
	RampageAnim->SetRandAtkAnimIdx();
}

