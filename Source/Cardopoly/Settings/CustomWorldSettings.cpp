// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomWorldSettings.h"
#include "GameplayWorldSettings.h"


UGameplayWorldSettings* ACustomWorldSettings::GetGameplayWorldSettings(const UWorld& InWorld)
{
	const AWorldSettings* WorldSettings = InWorld.GetWorldSettings();
	const ACustomWorldSettings* CustomWorldSettings = Cast<ACustomWorldSettings>(WorldSettings);
	
	return Cast<UGameplayWorldSettings>(CustomWorldSettings->LevelSpecificSettings);
}
