// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SSML.h"
#include "AzureTTSLogMacroDeclare.h"

#include "SSMLBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AZURETTS_API USSMLBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/**
	 * @brief 
	 * @param SSMLDocument SSML Document struct
	 * @return Whole xml document of this SSML document
	 */
	UFUNCTION(BlueprintPure, Category="AzureTTS")
	static FString GetSSMLDocumentOuterXml(const FSSMLDocument SSMLDocument);
	
	/**
	 * @brief 
	 * @param SSMLDocument SSML Document struct
	 * @return Inner xml document of this SSML document
	 */
	UFUNCTION(BlueprintPure, Category="AzureTTS")
	static FString GetSSMLDocumentInnerXml(const FSSMLDocument SSMLDocument);
};
