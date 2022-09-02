// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "GameplayTagContainer.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

#include "BlockDeleter.h"

#include "Block.generated.h"

UCLASS()
class FLAPPYBIRD_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

	/*UFUNCTION()
		void DestroyActor();*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Block")
		UPaperSpriteComponent* UpWood;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Block")
		UPaperSpriteComponent* DownWood;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score up")
		UBoxComponent* ScoreUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collider")
		UBoxComponent* BoxCollider;
		//UPaperSpriteComponent* ScoreUp;

	FGameplayTag Death;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);


};
