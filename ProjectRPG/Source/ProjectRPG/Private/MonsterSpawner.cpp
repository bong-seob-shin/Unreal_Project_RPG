// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"
#include "Grux.h"


// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnerTransform"));

	RootComponent = Body;

	SpawnTime = 30.0f;
	MaxMonsterNum = 4;
}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SpawnTimerHandle,this, &AMonsterSpawner::SpawnGrux , SpawnTime, true, 5.0f);

}

// Called every frame
void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterSpawner::SpawnGrux()
{
	if (MaxMonsterNum < CurrentMonsterNum)
		return;

	FActorSpawnParameters GruxSpawnParams;
	FVector SpawnLocation = GetActorLocation();
	auto Grux = GetWorld()->SpawnActor(Cast<UClass>(AGrux::StaticClass()) ,&SpawnLocation, &FRotator::ZeroRotator,GruxSpawnParams);
	CurrentMonsterNum++;

	Cast<AGrux>(Grux)->OnGruxDie.BindLambda([this]()-> void{
		CurrentMonsterNum--;
		});
}

