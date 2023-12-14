// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IOccupyGrid.generated.h"


// This class does not need to be modified.
UINTERFACE()
class UOccupyGrid : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CARDOPOLY_API IOccupyGrid
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FIntVector2 GetCenter();
	
	virtual TArray<FIntVector2> GetPositions();
};
