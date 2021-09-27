// Author: Kenn Zhang
// Date: 2021-09-27
// Repo: https://github.com/breakstring/AzureTTS

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FAzureTTSModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
