// Author: Kenn Zhang
// Date: 2021-09-27
// Repo: https://github.com/breakstring/AzureTTS
// @reference W3C, Speech Synthesis Markup Language (SSML) Version 1.0. https://www.w3.org/TR/2004/REC-speech-synthesis-20040907/#edef_voice
// @reference AzureTTS, Improve synthesis with Speech Synthesis Markup Language (SSML). https://docs.microsoft.com/en-us/azure/cognitive-services/speech-service/speech-synthesis-markup


#pragma once

#include "CoreMinimal.h"

#include "SSML.generated.h"


UENUM(BlueprintType)
enum class ESSMLInterpretAsType : uint8
{
	Address UMETA(DisplayName="address",ToolTip="The text is spoken as an address. The speech synthesis engine pronounces: I'm at <say-as interpret-as=\"address\">150th CT NE, Redmond, WA</say-as>As \"I'm at 150th court north east redmond washington.\""),
	Cardinal UMETA(DisplayName="cardinal",ToolTip="The text is spoken as a cardinal number. The speech synthesis engine pronounces:There are <say-as interpret-as=\"cardinal\">3</say-as> alternatives. As \"There are three alternatives.\""),
	Number UMETA(DisplayName="number",ToolTip="The text is spoken as a cardinal number. The speech synthesis engine pronounces:There are <say-as interpret-as=\"cardinal\">3</say-as> alternatives. As \"There are three alternatives.\""),
	Characters UMETA(DisplayName="characters",ToolTip="The text is spoken as individual letters (spelled out). The speech synthesis engine pronounces: <say-as interpret-as=\"characters\">test</say-as>. As \"T E S T.\""),
	SpellOut UMETA(DisplayName="spell-out",ToolTip="The text is spoken as individual letters (spelled out). The speech synthesis engine pronounces: <say-as interpret-as=\"characters\">test</say-as>. As \"T E S T.\""),
	Date UMETA(DisplayName="date",ToolTip="The text is spoken as a date. The format attribute specifies the date's format (d=day, m=month, and y=year). The speech synthesis engine pronounces: Today is <say-as interpret-as=\"date\" format=\"mdy\">10-19-2016</say-as>. As \"Today is October nineteenth two thousand sixteen.\""),
	Digits UMETA(DisplayName="digits",ToolTip="The text is spoken as a sequence of individual digits. The speech synthesis engine pronounces: <say-as interpret-as=\"number_digit\">123456789</say-as> As \"1 2 3 4 5 6 7 8 9.\""),
	NumberDigit UMETA(DisplayName="number_digit",ToolTip="The text is spoken as a sequence of individual digits. The speech synthesis engine pronounces: <say-as interpret-as=\"number_digit\">123456789</say-as> As \"1 2 3 4 5 6 7 8 9.\""),
	Fraction UMETA(DisplayName="fraction",ToolTip="The text is spoken as a fractional number. The speech synthesis engine pronounces: <say-as interpret-as=\"fraction\">3/8</say-as> of an inch. As \"three eighths of an inch.\""),
	Ordinal UMETA(DisplayName="ordinal",ToolTip="The text is spoken as an ordinal number. The speech synthesis engine pronounces: Select the <say-as interpret-as=\"ordinal\">3rd</say-as> option. As \"Select the third option\"."),
	Telephone UMETA(DisplayName="telephone",ToolTip="The text is spoken as a telephone number. The format attribute can contain digits that represent a country code. For example, "1" for the United States or "39" for Italy. The speech synthesis engine can use this information to guide its pronunciation of a phone number. The phone number might also include the country code, and if so, takes precedence over the country code in the format. The speech synthesis engine pronounces: The number is <say-as interpret-as=\"telephone\" format=\"1\">(888) 555-1212</say-as> As \"My number is area code eight eight eight five five five one two one two.\""),
	Time UMETA(DisplayName="time",ToolTip="The text is spoken as a time. The format attribute specifies whether the time is specified using a 12-hour clock (hms12) or a 24-hour clock (hms24). Use a colon to separate numbers representing hours, minutes, and seconds. The following are valid time examples: 12:35, 1:14:32, 08:15, and 02:50:45. The speech synthesis engine pronounces:The train departs at <say-as interpret-as=\"time\" format=\"hms12\">4:00am</say-as> As \"The train departs at four A M.\""),
	Name UMETA(DisplayName="name",ToolTip="The text is spoken as a person name. The speech synthesis engine pronounces: <say-as interpret-as=\"name\">ED</say-as> as [æd]. In Chinese names, some characters pronounce differently when they appear in a family name. For example, the speech synthesis engine says 仇 in <say-as interpret-as=\"address\">仇先生</say-as> as [qiú] instead of [chóu].")
};

UENUM(BlueprintType)
enum class ESSMLPhonemeAlphabetType : uint8
{
	Ipa UMETA(DisplayName = "ipa",ToolTip="International Phonetic Alphabet"),
	Sapi UMETA(DisplayName = "sapi",ToolTip="Speech service phonetic alphabet"),
	Ups UMETA(DisplayName = "ups",ToolTip="Universal Phone Set")
};

UENUM(BlueprintType)
enum class ESSMLSilenceType : uint8
{
	Leading UMETA(DisplayName = "Leading",ToolTip="At the beginning of text"),
	Tailing UMETA(DisplayName = "Tailing",ToolTip="In the end of text"),
	SentenceBoundary UMETA(DisplayName = "Sentenceboundary",ToolTip="Between adjacent sentences")
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
	MSTTS_Express_As UMETA(DisplayName = "mstts:express-as"),
	MSTTS_Silence UMETA(DisplayName = "mstts:silence"),
	MSTTS_BackgroundAudio UMETA(DisplayName = "mstts:backgroundaudio"),
	PlainText UMETA(DisplayName="plain text",ToolTip="Not official SSML element")
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
	FString InnerXml;
	
};


/**
 * @brief SSML Document
 */
USTRUCT(BlueprintType)
struct FSSMLDocument
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	FString XmlVersion = "1.0";

	/**
	 * @brief Root Element must be "speak"
	 */
	UPROPERTY(BlueprintReadWrite)
	/** Root Element must be "speak" **/
	FSSMLElementNode RootElement ;
	
};