// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamArrow.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AdamObjectPool.h"

// Sets default values
AAdamArrow::AAdamArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Bow_ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ARROW")); // 칼 스태틱 메쉬
	ArrowColBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ArrowColBox"));
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_ARROW(TEXT("/Game/PalaceWorld/Resources/Adam_Adventurer/Meshes/SM_Adam_Arrow.SM_Adam_Arrow"));
	if (SM_ARROW.Succeeded())
	{
		Bow_ArrowMesh->SetStaticMesh(SM_ARROW.Object);
	}
	
	SetRootComponent(Bow_ArrowMesh);

	// 충돌 프로파일 적용
	ArrowColBox->SetCollisionProfileName(TEXT("PlayerArrow"));
	ArrowColBox->SetBoxExtent(FVector(20.f, 20.f, 20.f));
	ArrowColBox->SetupAttachment(Bow_ArrowMesh);

	Movement->UpdatedComponent = ArrowColBox;
	Movement->InitialSpeed = 2000.f;
	Movement->MaxSpeed = 2000.f;
	Movement->bInitialVelocityInLocalSpace = true;
	Movement->ProjectileGravityScale = 0.2f;
	
}

// Called when the game starts or when spawned
void AAdamArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAdamArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAdamArrow::ReturnSelf()
{
	if (m_ObjectPool == nullptr)
		return;
	m_ObjectPool->ReturnObject(this);
	SetActive(false);
}

void AAdamArrow::SetActive(bool bIsActive)
{
	m_bIsActive = bIsActive;
	SetActorHiddenInGame(!m_bIsActive);
	SetActorEnableCollision(false);
}

