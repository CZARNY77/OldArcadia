// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"

APlayerHUD::APlayerHUD()
{

	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarObj(TEXT("/Game/NWM"));
	HUDWidgetClass = HealthBarObj.Class;
}
void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

		if (CurrentWidget)	CurrentWidget->AddToViewport();
	}

}