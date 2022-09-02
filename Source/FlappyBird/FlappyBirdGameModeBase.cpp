// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlappyBirdGameModeBase.h"

AFlappyBirdGameModeBase::AFlappyBirdGameModeBase()
{
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;
    PrimaryActorTick.bAllowTickOnDedicatedServer = false;

    DefaultPawnClass = ACurrentPlayer::StaticClass();

    HUDClass = ACurrentPlayerHUD::StaticClass();

}

void AFlappyBirdGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    /*if (HUDWidget) {
        CurrentWidget = CreateWidget<UUsecScore_UI>(GetWorld(), HUDWidget);
        if (CurrentWidget)
        {
            CurrentWidget->AddToViewport();
        }
    }*/

    

}

