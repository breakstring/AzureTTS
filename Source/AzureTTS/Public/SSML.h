// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SSML.generated.h"


UENUM(BlueprintType)
enum class ESSMLInterpretAsType : uint8
{
	Address,
	Cardinal,
	Number,
	Characters,
	SpellOut,
	Date,
	Digits,
	NumberDigit,
	Fraction,
	Ordinal,
	Telephone,
	Time,
	Name
};

UENUM(BlueprintType)
enum class ESSMLPhonemeAlphabetType : uint8
{
	Ipa UMETA(DisplayName = "International Phonetic Alphabet"),
	Sapi UMETA(DisplayName = "Speech service phonetic alphabet"),
	Ups UMETA(DisplayName = "Universal Phone Set")
};

UENUM(BlueprintType)
enum class ESSMLSilenceType : uint8
{
	Leading UMETA(DisplayName = "At the beginning of text"),
	Tailing UMETA(DisplayName = "In the end of text"),
	SentenceBoundary UMETA(DisplayName = "Between adjacent sentences")
};

UENUM(BlueprintType)
enum class ESSMLBreakStrength : uint8
{
	None UMETA(DisplayName = "0ms"),
	XWeak UMETA(DisplayName = "250ms"),
	Weak UMETA(DisplayName = "500ms"),
	Medium UMETA(DisplayName = "750ms"),
	Strong UMETA(DisplayName = "1000ms"),
	XStrong UMETA(DisplayName = "1250ms")
};

/**
 * @brief SSML Document Element Type
 */
UENUM(BlueprintType)
enum class ESSMLElementType : uint8
{
	Speak UMETA(DisplayName = "speak"),
	Voice UMETA(DisplayName = "voice"),
	Lang UMETA(DisplayName = "lang"),
	Break UMETA(DisplayName = "break"),
	P UMETA(DisplayName = "p"),
	S UMETA(DisplayName = "s"),
	Phoneme UMETA(DisplayName = "phoneme"),
	Lexicon UMETA(DisplayName = "lexicon"),
	Prosody UMETA(DisplayName = "prosody"),
	Say_As UMETA(DisplayName = "say-as"),
	Audio UMETA(DisplayName = "audio"),
	Bookmark UMETA(DisplayName = "bookmark"),
	Meta UMETA(DisplayName = "meta"),
	Metadata UMETA(DisplayName = "metadata"),
	Sub UMETA(DisplayName = "sub"),
	Emphasis UMETA(DisplayName = "emphasis"),
	Mark UMETA(DisplayName = "mark"),
	Desc UMETA(DisplayName = "desc"),
	MSTTS_Express_As UMETA(DisplayName = "mstts:expresss-as"),
	MSTTS_Silence UMETA(DisplayName = "mstts:silence"),
	MSTTS_BackgroundAudio UMETA(DisplayName = "mstts:backgroundaudio"),
	PlainText UMETA(DisplayName = "plain text")
};

/**
 * @brief SSML Document Element Node
 */
USTRUCT(BlueprintType)
struct FSSMLElementNode
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	ESSMLElementType ElementType;

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FString> Properties;

	UPROPERTY(BlueprintReadWrite)
	FString InnerText;
	
};


/**
 * @brief SSML Document
 */
USTRUCT(BlueprintType)
struct FSSMLDocument
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadWrite)
	/** Root Element must be "speak" **/
	FSSMLElementNode RootElement ;

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FString> Properties;
};