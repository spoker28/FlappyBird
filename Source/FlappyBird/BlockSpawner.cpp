// Fill out your copyright notice in the Description page of Project Settings.

#include "BlockSpawner.h"

// Sets default values
ABlockSpawner::ABlockSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ABlockSpawner::BeginPlay()
{
	Super::BeginPlay();
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ABlockSpawner::TimerFunction, 2.0f, true, 0.5f);
}

// Called every frame
void ABlockSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlockSpawner::SpawnActor()
{
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	GetWorld()->SpawnActor<ABlock>(SpawnLocation, SpawnRotation);
}

void ABlockSpawner::TimerFunction()
{
	ACurrentPlayer* Player = Cast<ACurrentPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player->IsPlayerStarted) {
		AActor* ActorSpawnerTofind = UGameplayStatics::GetActorOfClass(GetWorld(), ABlockSpawner::StaticClass());

		ABlockSpawner* ActorSpawnerReference = Cast<ABlockSpawner>(ActorSpawnerTofind);
		if (ActorSpawnerReference)
		{
			ActorSpawnerReference->SpawnActor();
		}
	}
}