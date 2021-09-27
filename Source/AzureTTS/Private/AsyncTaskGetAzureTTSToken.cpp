// Author: Kenn Zhang
// Date: 2021-09-27
// Repo: https://github.com/breakstring/AzureTTS

#include "AsyncTaskGetAzureTTSToken.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "AzureTTSLogMacroDefine.h"

UAsyncTaskGetAzureTTSToken::UAsyncTaskGetAzureTTSToken(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
		AddToRoot();
}

UAsyncTaskGetAzureTTSToken* UAsyncTaskGetAzureTTSToken::GetAzureTTSToken(const FString SubscriptionKey,
	const FString IssueTokenEndpoint)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	UAsyncTaskGetAzureTTSToken* RequestTask = NewObject<UAsyncTaskGetAzureTTSToken>();
	RequestTask->Start(SubscriptionKey, IssueTokenEndpoint);
	return RequestTask;
}

void UAsyncTaskGetAzureTTSToken::Start(FString SubscriptionKey, FString IssueTokenEndpoint)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAsyncTaskGetAzureTTSToken::HandleRequest);
	HttpRequest->SetURL(IssueTokenEndpoint);
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetHeader(TEXT("Ocp-Apim-Subscription-Key"), SubscriptionKey);
	HttpRequest->SetHeader(TEXT("Content-type"), TEXT("application/x-www-form-urlencoded"));

	HttpRequest->ProcessRequest();
}

void UAsyncTaskGetAzureTTSToken::HandleRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse,
	bool bSuccess)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));
	RemoveFromRoot();
	if (!HttpResponse.IsValid())
	{
		UE_LOG(AzureTTS, Error, TEXT("Connection failed."));
		OnFail.Broadcast(-1, TEXT(""));
		return;
	}

	const int ResponseCode = HttpResponse->GetResponseCode();
	const FString ResponseContent = HttpResponse->GetContentAsString();
	if (ResponseCode == 200)
	{
		OnSuccess.Broadcast(200, ResponseContent);
	}
	else
	{
		UE_LOG(AzureTTS, Error, TEXT("Response code is %d"), ResponseCode);
		OnFail.Broadcast(ResponseCode, TEXT(""));
	}
}
