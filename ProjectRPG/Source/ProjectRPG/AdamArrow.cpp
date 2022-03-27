// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamArrow.h"
#include "AdamObjectPool.h"

// Sets default values
AAdamArrow::AAdamArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Bow_ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ARROW")); // Ä® ½ºÅÂÆ½ ¸Þ½¬
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_ARROW(TEXT("/Game/PalaceWorld/Resources/Adam_Adventurer/Meshes/SM_Adam_Arrow.SM_Adam_Arrow"));
	if (SM_ARROW.Succeeded())
	{
		Bow_ArrowMesh->SetStaticMesh(SM_ARROW.Object);
	}
	Bow_ArrowMesh->SetCollisionProfileName(TEXT("NoCollision"));
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
}

