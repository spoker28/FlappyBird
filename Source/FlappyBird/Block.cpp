// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"

#include "BlockSpawner.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FVector CurrentPosition = this->GetActorTransform().GetLocation();

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

	UpWood = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("UpWood"));
	UpWood->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UPaperSprite> SpriteAssetObjUp(TEXT("PaperSprite'/Game/Sprites/TreeTrunkHalfRes_Sprite.TreeTrunkHalfRes_Sprite'"));
	UpWood->SetSprite(SpriteAssetObjUp.Object);
	FVector UpWoodPosition = CurrentPosition;
	UpWoodPosition.Z = 170;
	UpWood->SetRelativeLocation(UpWoodPosition, false);
	FRotator UpWoodRotator(0.0f, 90.0f, 0.0f);
	UpWood->SetRelativeRotation(UpWoodRotator, false);
	UpWood->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	UpWood->SetCollisionResponseToAllChannels(ECR_Overlap);
	UpWood->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	UpWood->ComponentTags.Add(FName("Death"));

	DownWood = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("DownWood"));
	DownWood->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UPaperSprite> SpriteAssetObjDown(TEXT("PaperSprite'/Game/Sprites/TreeTrunkHalfRes_Sprite.TreeTrunkHalfRes_Sprite'"));
	DownWood->SetSprite(SpriteAssetObjDown.Object);
	FVector DownWoodPosition = CurrentPosition;
	DownWoodPosition.Z = -170;
	DownWood->SetRelativeLocation(DownWoodPosition, false);
	FRotator DownWoodRotator(0.0f, 90.0f, 0.0f);
	DownWood->SetRelativeRotation(DownWoodRotator, false);
	DownWood->SetCollisionObjectType(ECC_WorldDynamic);
	DownWood->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    DownWood->SetCollisionResponseToAllChannels(ECR_Overlap);
	DownWood->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	DownWood->ComponentTags.Add(FName("Death"));

	ScoreUp = CreateDefaultSubobject<UBoxComponent>(TEXT("ScoreUp"));
	ScoreUp->SetupAttachment(RootComponent);
	FRotator ScoreUpRotator(0.0f, 90.0f, 0.0f);
	ScoreUp->SetRelativeRotation(ScoreUpRotator, false);
	FVector ScoreUpScale(1.0f, 0.6f, 1.0f);
	ScoreUp->SetRelativeScale3D(ScoreUpScale);
	ScoreUp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ScoreUp->SetCollisionResponseToAllChannels(ECR_Overlap);
	ScoreUp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	ScoreUp->ComponentTags.Add(FName("Score up"));

	OnActorBeginOverlap.AddDynamic(this, &ABlock::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	FVector CurrentPosition = this->GetActorTransform().GetLocation();
	CurrentPosition.Z += FMath::RandRange(-50, 50);
	this->SetActorLocation(CurrentPosition, false);
	
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrentPosition = this->GetActorTransform().GetLocation();
	CurrentPosition.Y += 100.0f * DeltaTime;
	this->SetActorLocation(CurrentPosition, false);
}

void ABlock::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	ABlockDeleter* Deleter = Cast<ABlockDeleter>(OtherActor);
	if (Deleter)
	{
		this->Destroy();
	}
}