#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class CardopolyEditor : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static CardopolyEditor& Get();
};