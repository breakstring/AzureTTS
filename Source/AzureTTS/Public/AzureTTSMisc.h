#pragma once

#include "AzureTTSMisc.generated.h"


#define USER_AGENT "AzureTTS Unreal Engine plugin"

UENUM(BlueprintType)
enum class EAzureAuthenticationMethod : uint8
{
	Subscription_Key UMETA(DisplayName = "Subscription Key"),
	Bearer UMETA(DisplayName = "Authorization: Bearer")
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


UENUM(BlueprintType)
enum class EAzureSpeechAudioOutputFormat : uint8
{
	Audio_16Khz_32Kbitrate_Mono_MP3 UMETA(DisplayName = "audio-16khz-32kbitrate-mono-mp3"),
	Audio_16Khz_64Kbitrate_Mono_MP3 UMETA(DisplayName = "audio-16khz-64kbitrate-mono-mp3"),
	Audio_16Khz_128Kbitrate_Mono_MP3 UMETA(DisplayName = "audio-16khz-128kbitrate-mono-mp3"),
	Audio_24Khz_48Kbitrate_Mono_MP3 UMETA(DisplayName = "audio-24khz-48kbitrate-mono-mp3"),
	Audio_24Khz_96Kbitrate_Mono_MP3 UMETA(DisplayName = "audio-24khz-96kbitrate-mono-mp3"),
	Audio_24Khz_160Kbitrate_Mono_MP3 UMETA(DisplayName = "audio-24khz-160kbitrate-mono-mp3"),
	Audio_48Khz_96Kbitrate_Mono_MP3 UMETA(DisplayName = "audio-48khz-96kbitrate-mono-mp3"),
	Audio_48Khz_192Kbitrate_Mono_MP3 UMETA(DisplayName = "audio-48khz-192kbitrate-mono-mp3"),
	Raw_8Khz_8Bit_Mono_Alaw UMETA(DisplayName = "raw-8khz-8bit-mono-alaw"),
	Raw_8Khz_8Bit_Mono_Mulaw UMETA(DisplayName = "raw-8khz-8bit-mono-mulaw"),
	Raw_16Khz_16Bit_Mono_PCM UMETA(DisplayName = "raw-16khz-16bit-mono-pcm"),
	Raw_24Khz_16Bit_Mono_PCM UMETA(DisplayName = "raw-24khz-16bit-mono-pcm"),
	Raw_48Khz_16Bit_Mono_PCM UMETA(DisplayName = "raw-48khz-16bit-mono-pcm"),
	Raw_16Khz_16Bit_Mono_Truesilk UMETA(DisplayName = "raw-16khz-16bit-mono-truesilk"),
	Raw_24Khz_16Bit_Mono_Truesilk UMETA(DisplayName = "raw-24khz-16bit-mono-truesilk"),
	Riff_8Khz_8Bit_Mono_Mulaw UMETA(DisplayName = "riff-8khz-8bit-mono-mulaw"),
	Riff_8Khz_8Bit_Mono_Alaw UMETA(DisplayName = "riff-8khz-8bit-mono-alaw"),
	Riff_16Khz_16Bit_Mono_PCM UMETA(DisplayName = "riff-16khz-16bit-mono-pcm"),
	Riff_24Khz_16Bit_Mono_PCM UMETA(DisplayName = "riff-24khz-16bit-mono-pcm"),
	Riff_48Khz_16Bit_Mono_PCM UMETA(DisplayName = "riff-48khz-16bit-mono-pcm"),
	Webm_16Khz_16Bit_Mono_Opus UMETA(DisplayName = "webm-16khz-16bit-mono-opus"),
	Webm_24Khz_16Bit_Mono_Opus UMETA(DisplayName = "webm-24khz-16bit-mono-opus"),
	Ogg_16Khz_16Bit_Mono_Opus UMETA(DisplayName = "ogg-16khz-16bit-mono-opus"),
	Ogg_24Khz_16Bit_Mono_Opus UMETA(DisplayName = "ogg-24khz-16bit-mono-opus"),
	Ogg_48Khz_16Bit_Mono_Opus UMETA(DisplayName = "ogg-48khz-16bit-mono-opus")
};