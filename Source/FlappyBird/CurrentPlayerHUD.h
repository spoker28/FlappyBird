// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "CurrentPlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API ACurrentPlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	ACurrentPlayerHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Score")
		TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Score")
		class UUserWidget* CurrentWidget;
	
};
