// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTaskAzureTTS.h"
#include "Containers/UnrealString.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "AzureTTSLogMacroDefine.h"

UAsyncTaskAzureTTS::UAsyncTaskAzureTTS(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
		AddToRoot();
}

UAsyncTaskAzureTTS* UAsyncTaskAzureTTS::TTS(const EAzureAuthenticationMethod AuthenticationMethod,
	const FString AuthenticationValue, const FString Endpoint, const FString SSML,
	const EAzureSpeechAudioOutputFormat AudioFormat)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));
	UAsyncTaskAzureTTS* RequestTask = NewObject<UAsyncTaskAzureTTS>();
	RequestTask->Start(AuthenticationMethod, AuthenticationValue, Endpoint, SSML, AudioFormat);
	return RequestTask;
}

void UAsyncTaskAzureTTS::Start(const EAzureAuthenticationMethod AuthenticationMethod, const FString AuthenticationValue,
	const FString Endpoint, const FString SSML, const EAzureSpeechAudioOutputFormat AudioFormat)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAsyncTaskAzureTTS::HandleRequest);
	HttpRequest->SetURL(Endpoint);
	HttpRequest->SetVerb(TEXT("POST"));
	
	const UEnum* EnumPtr = FindObject<UEnum>((UObject*)ANY_PACKAGE, TEXT("EAzureSpeechAudioOutputFormat"));
	const FString AudioFormatValue = (EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(AudioFormat))).ToString().ToLower();
	
	HttpRequest->SetHeader(TEXT("X-Microsoft-OutputFormat"), AudioFormatValue);
	if (AuthenticationMethod == EAzureAuthenticationMethod::Subscription_Key)
	{
		HttpRequest->SetHeader(TEXT("Ocp-Apim-Subscription-Key"), AuthenticationValue);
	}
	else
	{
		HttpRequest->SetHeader(TEXT("Authorization"), TEXT("Bearer " + AuthenticationValue));
	}
	HttpRequest->SetHeader(TEXT("User-Agent"), TEXT(USER_AGENT));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/ssml+xml"));
	HttpRequest->SetContentAsString(SSML);

	UE_LOG(AzureTTS, Log, TEXT("---------- Send TTS Request ------------"));
	UE_LOG(AzureTTS, Log, TEXT("Request URL -> %s"), *Endpoint);
	TArray<FString> RequestHeaders = HttpRequest->GetAllHeaders();
	for (int32 i = 0; i < RequestHeaders.Num(); i++)
	{
		
		if ( !RequestHeaders[i].StartsWith(TEXT("Ocp-Apim-Subscription-Key"),ESearchCase::IgnoreCase) && !RequestHeaders[i].StartsWith(TEXT("Authorization"),ESearchCase::IgnoreCase))
		{
			FString Header = "RequestHeader -> ";
			Header.Append(RequestHeaders[i]);
			UE_LOG(AzureTTS, Log, TEXT("%s"), *Header);
		}
	}
	UE_LOG(AzureTTS, Log, TEXT("SSML content as below:"));
	UE_LOG(AzureTTS, Log, TEXT("%s"), *SSML);
	UE_LOG(AzureTTS, Log, TEXT("----------------------------------------"));

	HttpRequest->ProcessRequest();
}

void UAsyncTaskAzureTTS::HandleRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));
	RemoveFromRoot();
	TArray<uint8> Data;

	if (!HttpResponse.IsValid())
	{
		UE_LOG(AzureTTS, Error, TEXT("Connection failed."));
		OnFail.Broadcast(-1, Data);
		return;
	}

	const int32 ResponseCode = HttpResponse->GetResponseCode();
	Data = HttpResponse->GetContent();
	if (ResponseCode != 200)
	{
		UE_LOG(AzureTTS, Error, TEXT("Request failed with response code: %d"), ResponseCode);
		OnFail.Broadcast(ResponseCode, Data);
	}
	else
	{
		OnSuccess.Broadcast(200, Data);
	}
}
