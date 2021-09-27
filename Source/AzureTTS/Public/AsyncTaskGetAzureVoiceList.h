// Author: Kenn Zhang
// Date: 2021-09-27
// Repo: https://github.com/breakstring/AzureTTS

#pragma once

#include "CoreMinimal.h"
#include "AzureTTSMisc.h"
#include "Interfaces/IHttpRequest.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "AzureTTSLogMacroDeclare.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncTaskGetAzureVoiceList.generated.h"

/**
 * 
 */
UCLASS()
class AZURETTS_API UAsyncTaskGetAzureVoiceList : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetAzureVoiceListDelegate, int32, ResponseCode,
	                                             const TArray<FAzureSpeechVoiceInfomation>&, VoiceList);

	public:
	explicit UAsyncTaskGetAzureVoiceList(const FObjectInitializer& ObjectInitializer);

	/**
	* @brief Get a full list of voices for a specific azure region/endpoint.
	*
	* @param AuthenticationMethod - Authentication method used to send request.
	* @param AuthenticationValue - Subscription key or JWT token
	* @param Endpoint - Azure speech endpoint for get the voice list. e.g.https://australiaeast.tts.speech.microsoft.com/cognitiveservices/voices/list
	* @return
	*/
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "AzureTTS",meta = (DisplayName = "Get Azure Voice List (Async)"))
	static UAsyncTaskGetAzureVoiceList* GetAzureVoiceList(
		const EAzureAuthenticationMethod AuthenticationMethod, const FString AuthenticationValue, const FString Endpoint);

	public:
	UPROPERTY(BlueprintAssignable)
	FGetAzureVoiceListDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FGetAzureVoiceListDelegate OnFail;

	public:
	void Start(const EAzureAuthenticationMethod AuthenticationMethod, const FString AuthenticationValue, const FString Endpoint);

	private:
	void HandleRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess);
};
