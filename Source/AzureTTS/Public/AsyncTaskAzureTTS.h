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
#include "AsyncTaskAzureTTS.generated.h"

/**
 * 
 */
UCLASS()
class AZURETTS_API UAsyncTaskAzureTTS : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAzureTTSDelegate, int32, ResponseCode, const TArray<uint8>&, Data);

	public:
	UPROPERTY(BlueprintAssignable)
	FAzureTTSDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAzureTTSDelegate OnFail;

	explicit UAsyncTaskAzureTTS(const FObjectInitializer& ObjectInitializer);

	/**
	* @brief Convert text(SSML format) to voice. The ResponseCode is server response code or -1(Unknow error.), and the Data is raw data for audio file if sucess.
	*
	* @param AuthenticationMethod - Authentication method used to send request
	* @param AuthenticationValue - Subscription key or JWT token
	* @param Endpoint - Azure speech endpoint for TTS. e.g. https://southeastasia.tts.speech.microsoft.com/cognitiveservices/v1
	* @param SSML - SSML document
	* @param AudioFormat - Audio format
	* @return UAsyncTaskAzureTTS*
	*/
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "AzureTTS", meta = (DisplayName = "Text To Speach - Raw Data (Async)"))
	static UAsyncTaskAzureTTS* TTS(const EAzureAuthenticationMethod AuthenticationMethod, const FString AuthenticationValue,
		const FString Endpoint, const FString SSML, const EAzureSpeechAudioOutputFormat AudioFormat);

	void Start(const EAzureAuthenticationMethod AuthenticationMethod, const FString AuthenticationValue, const FString Endpoint,
		const FString SSML, const EAzureSpeechAudioOutputFormat AudioFormat);

	private:
	void HandleRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess);
};
