#pragma once

#include "AzureTTSMisc.generated.h"

UENUM(BlueprintType)
enum class EAzureAuthenticationMethod : uint8
{
	SUBSCRIPTION_KEY UMETA(DisplayName = "Subscription Key"),
	BEARER UMETA(DisplayName = "Authorization: Bearer")
};


USTRUCT(BlueprintType)
struct FAzureSpeechVoiceInfomation
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString Name;

	UPROPERTY(BlueprintReadOnly)
	FString DisplayName;

	UPROPERTY(BlueprintReadOnly)
	FString LocalName;

	UPROPERTY(BlueprintReadOnly)
	FString ShortName;

	UPROPERTY(BlueprintReadOnly)
	FString Gender;

	UPROPERTY(BlueprintReadOnly)
	FString Locale;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> StyleList;

	UPROPERTY(BlueprintReadOnly)
	FString SampleRateHertz;

	UPROPERTY(BlueprintReadOnly)
	FString VoiceType;

	UPROPERTY(BlueprintReadOnly)
	FString Status;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> SecondaryLocaleList;
};