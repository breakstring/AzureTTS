// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTaskGetAzureVoiceList.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "JsonObjectConverter.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "AzureTTSLogMacroDefine.h"

UAsyncTaskGetAzureVoiceList::UAsyncTaskGetAzureVoiceList(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
		AddToRoot();
}

UAsyncTaskGetAzureVoiceList* UAsyncTaskGetAzureVoiceList::GetAzureVoiceList(
	const EAzureAuthenticationMethod AuthenticationMethod, const FString AuthenticationValue, const FString Endpoint)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));
	UAsyncTaskGetAzureVoiceList* RequestTask = NewObject<UAsyncTaskGetAzureVoiceList>();
	RequestTask->Start(AuthenticationMethod, AuthenticationValue, Endpoint);
	return RequestTask;
}

void UAsyncTaskGetAzureVoiceList::Start(const EAzureAuthenticationMethod AuthenticationMethod,
	const FString AuthenticationValue, const FString Endpoint)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAsyncTaskGetAzureVoiceList::HandleRequest);
	HttpRequest->SetURL(Endpoint);
	HttpRequest->SetVerb(TEXT("GET"));
	if (AuthenticationMethod == EAzureAuthenticationMethod::Subscription_Key)
	{
		HttpRequest->SetHeader(TEXT("Ocp-Apim-Subscription-Key"), AuthenticationValue);
	}
	else
	{
		HttpRequest->SetHeader(TEXT("Authorization"), TEXT("Bearer " + AuthenticationValue));
	}
	HttpRequest->ProcessRequest();
}

void UAsyncTaskGetAzureVoiceList::HandleRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse,
	bool bSuccess)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));
	RemoveFromRoot();
	TArray<FAzureSpeechVoiceInfomation> VoiceList;
	if (!HttpResponse.IsValid())
	{
		UE_LOG(AzureTTS, Error, TEXT("Connection failed."));
		OnFail.Broadcast(-1, VoiceList);
		return;
	}
	FString ResponseString = HttpResponse->GetContentAsString();
	int ResponseCode = HttpResponse->GetResponseCode();
	if(ResponseCode ==200)
	{
		if (FJsonObjectConverter::JsonArrayStringToUStruct<FAzureSpeechVoiceInfomation>(ResponseString, &VoiceList, 0, 0))
		{
			OnSuccess.Broadcast(200, VoiceList);
			return;
		}
		UE_LOG(AzureTTS, Error, TEXT("Get voice list failed. Server response content: %s"), *ResponseString);
		OnFail.Broadcast(-1, VoiceList);
	}
	else
	{
		UE_LOG(AzureTTS, Error, TEXT("Response code is: %d"), ResponseCode);
		OnFail.Broadcast(ResponseCode, VoiceList);
	}
}
