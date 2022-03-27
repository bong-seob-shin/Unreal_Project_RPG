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
}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SpawnTimerHandle,this, &AMonsterSpawner::SpawnGrux ,10.0f, true, 5.0f);

}

// Called every frame
void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterSpawner::SpawnGrux()
{
	FActorSpawnParameters GruxSpawnParams;
	FVector SpawnLocation = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Current Actor Pos %d, %d, %d"), SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
	GetWorld()->SpawnActor(Cast<UClass>(AGrux::StaticClass()) ,&SpawnLocation, &FRotator::ZeroRotator,GruxSpawnParams);

}

