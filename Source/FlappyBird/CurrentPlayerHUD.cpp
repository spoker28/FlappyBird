// Fill out your copyright notice in the Description page of Project Settings.


#include "CurrentPlayerHUD.h"

ACurrentPlayerHUD::ACurrentPlayerHUD()
{

	static ConstructorHelpers::FClassFinder<UUserWidget> UserScoreObj(TEXT("/Game/UI/Score_UI"));
	HUDWidgetClass = UserScoreObj.Class;
}


void ACurrentPlayerHUD::DrawHUD()
{
	Super::DrawHUD();

}

void ACurrentPlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hello"));
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}