// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "UObject/ObjectMacros.h"
#include "AzureTTSLogMacroDeclare.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncTaskGetAzureTTSToken.generated.h"

/**
 * 
 */
UCLASS()
class AZURETTS_API UAsyncTaskGetAzureTTSToken : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
	/**
	* @brief Construct a new declare dynamic multicast delegate for request task
	*
	*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetAzureTTSTokenDelegate, int32, ResponseCode, FString, AzureTTSToken);

	
	public:
	explicit UAsyncTaskGetAzureTTSToken(const FObjectInitializer& ObjectInitializer);

	/**
	 * @brief Get the Azure TTS Access Token
	 * @param SubscriptionKey - Azure speech Service Subscription Key: Ocp-Apim-Subscription-Key
	 * @param IssueTokenEndpoint - Azure endpoint used to get the TTS access key. e.g. https://<REGION_IDENTIFIER>.api.cognitive.microsoft.com/sts/v1.0/issueToken
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "AzureTTS",
		meta = (DisplayName = "Get Azure TTS Token (Async)"))
	static UAsyncTaskGetAzureTTSToken* GetAzureTTSToken(const FString SubscriptionKey, const FString IssueTokenEndpoint);

	public:
	UPROPERTY(BlueprintAssignable)
	FGetAzureTTSTokenDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FGetAzureTTSTokenDelegate OnFail;

	public:
	void Start(FString SubscriptionKey, FString IssueTokenEndpoint);

	private:
	void HandleRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess);
};
