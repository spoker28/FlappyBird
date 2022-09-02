// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/ArrowComponent.h"
#include "PaperFlipbook.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Sound/SoundCue.h"
#include "TimerManager.h"

#include "CurrentPlayer.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API ACurrentPlayer : public APaperCharacter
{
	GENERATED_BODY()

public:

    ACurrentPlayer();

	UPROPERTY(VisibleDefaultsOnly)
		bool IsAlive;
	UPROPERTY(VisibleDefaultsOnly)
		bool IsPlayerStarted;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Sound")
		USoundCue* JumpSoundCue;

	FTimerHandle Timer;


private:

    UAudioComponent* JumpAudioComponent;

	UPROPERTY(VisibleDefaultsOnly, Category="Score")
		int Score;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Jump();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void RotatePlayerAfterDeath();

	UFUNCTION(BlueprintPure, Category = "Score")
		int GetScore();

	UFUNCTION(BlueprintCallable, Category = "Score")
		void UpdateScore();

	UFUNCTION(BlueprintPure, Category = "Score")
	    FText GetScoreIntText();


};
