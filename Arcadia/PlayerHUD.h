// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class ARCADIA_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	APlayerHUD();

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Interface")
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Interface")
	class UUserWidget* CurrentWidget;
};
