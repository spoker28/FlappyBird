// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CurrentPlayer.h"
#include "Blueprint/UserWidget.h"
#include "CurrentPlayerHUD.h"

#include "FlappyBirdGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API AFlappyBirdGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

    virtual void BeginPlay() override;


public:
	AFlappyBirdGameModeBase();


protected:



};
