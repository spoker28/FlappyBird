// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlappyBirdGameModeBase.h"

AFlappyBirdGameModeBase::AFlappyBirdGameModeBase()
{
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;
    PrimaryActorTick.bAllowTickOnDedicatedServer = false;

    DefaultPawnClass = ACurrentPlayer::StaticClass();

    HUDClass = ACurrentPlayerHUD::StaticClass();

    ConstructorHelpers::FObjectFinder<AActor> CameraObj(TEXT("Class'/Script/FlappyBird.Camera'"));

    Camera = CameraObj.Object;



}

void AFlappyBirdGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    if (Camera != nullptr) {
        UE_LOG(LogTemp, Warning, TEXT("Camera"));

        APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

        OurPlayerController->SetViewTargetWithBlend(Camera, 2.f);

    }
}

