// Copyright Epic Games, Inc. All Rights Reserved.


#include "ArcadiaGameModeBase.h"
#include "PlayerHUD.h"

AArcadiaGameModeBase::AArcadiaGameModeBase() : Super()
{
	HUDClass = APlayerHUD::StaticClass();
}