// Author: Kenn Zhang
// Date: 2021-09-27
// Repo: https://github.com/breakstring/AzureTTS

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SSML.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "AzureTTSLogMacroDeclare.h"

#include "SSMLBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AZURETTS_API USSMLBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief 
	 * @param SSMLDocument SSML Document struct
	 * @return Whole xml document of this SSML document
	 */
	UFUNCTION(BlueprintPure, Category="AzureTTS")
	static FString GetSSMLDocumentOuterXml(const FSSMLDocument& SSMLDocument);
	

	
	/**
	 * @brief 
	 * @param SSMLElementNode SSML Element Node
	 * @return Element node outer xml
	 */
	UFUNCTION(BlueprintPure, Category="AzureTTS")
	static FString GetSSMLElementNodeOuterXml(const FSSMLElementNode& SSMLElementNode);


	UFUNCTION(BlueprintPure, Category="AzureTTS")
	static FSSMLElementNode& AppendChildElementNode(UPARAM(ref) FSSMLElementNode& ParentNode, const FSSMLElementNode& ChildNode);

	UFUNCTION(BlueprintPure, Category="AzureTTS")
	static FSSMLElementNode& AppendChildElement(UPARAM(ref) FSSMLElementNode& ParentNode,const FString Content);

	UFUNCTION(BlueprintPure, Category="AzureTTS")
	static FSSMLElementNode& AppendChildElementNodes(UPARAM(ref) FSSMLElementNode& ParentNode, const TArray<FSSMLElementNode>& ChildElementNodes);


	/**
	 * @brief Make a "speak" node
     * @param InnerXml InnerXml
	 * @param XmlLang Specifies the language of the root document. The value can contain a lowercase, two-letter language code (for example, en), or the language code and uppercase country/region (for example, en-US).
	 * @param Version "version" attribute, Indicates the version of the SSML specification used to interpret the document markup. The current version is 1.0.
	 * @param XmlNs "xmlns" attribute, Specifies the URI to the document that defines the markup vocabulary (the element types and attribute names) of the SSML document. The current URI is http://www.w3.org/2001/10/synthesis.
	 * @param XmlNsMSTTS "xmlns:mstts" attribute.
	 * @return "speak" node
	 */
	UFUNCTION(BlueprintPure, Category="AzureTTS")
	static FSSMLElementNode MakeSpeakElementNode(const FString InnerXml,UPARAM(DisplayName = "xml:lang") const FString XmlLang, UPARAM(DisplayName = "version") const FString Version="1.0",UPARAM(DisplayName = "xmlns") const FString XmlNs="http://www.w3.org/2001/10/synthesis",UPARAM(DisplayName = "xmlns:mstts")const FString XmlNsMSTTS = "https://www.w3.org/2001/mstts");
	
	/**
	 * @brief Make a "voice“ node
	 * @param InnerXml InnerXml
	 * @param Name Identifies the voice used for text-to-speech output. 
	 * @return "speak" node
	 */
	UFUNCTION(BlueprintPure, Category="AzureTTS")
	static FSSMLElementNode MakeVoiceElementNode(const FString InnerXml, const FString Name);


	/**
	 * @brief Make a "mstts:expresss-as" node
	 * @param InnerXml InnerXml
	 * @param Style Specifies the speaking style. Currently, speaking styles are voice-specific.
	 * @param StyleDegree Specifies the intensity of speaking style. Accepted values: 0.01 to 2 inclusive. The default value is 1 which means the predefined style intensity. The minimum unit is 0.01 which results in a slightly tendency for the target style. A value of 2 results in a doubling of the default style intensity.
	 * @param Role Specifies the speaking role-play. The voice will act as a different age and gender, but the voice name will not be changed.
	 * @return "mstts:expresss-as" node
	 */
	UFUNCTION(BlueprintPure, Category="AzureTTS",meta=(DisplayName="Make MSTTS Express-As Element Node"))
	static FSSMLElementNode MakeMSTTSExpressAsElementNode(const FString InnerXml, const FString Style = "", const FString StyleDegree = "", const FString Role="");

	/**
	 * @brief Make a "lang" node
	 * @param InnerXml InnerXml
	 * @param XmlLang Specifies the speaking languages. Currently, speaking different languages are voice-specific.
	 * @return "lang" node
	 */
	UFUNCTION(BlueprintPure,Category="AzureTTS")
	static FSSMLElementNode MakeLangElementNode(const FString InnerXml, const FString XmlLang);

	/**
	 * @brief Make a "break" node
	 * @param Strength Specifies the relative duration of a pause
	 * @param Time Specifies the absolute duration of a pause in seconds or milliseconds,this value should be set less than 5000ms. Examples of valid values are 2s and 500ms
	 * @return "break" node
	 */
	UFUNCTION(BlueprintPure,Category="AzureTTS")
	static FSSMLElementNode MakeBreakElementNode(const ESSMLBreakStrength Strength = ESSMLBreakStrength::None, const FString Time = "100ms" );

	/**
	 * @brief Make a "mstts:silence" node
	 * @param SilenceType Specifies the location of silence be added
	 * @param Value Specifies the absolute duration of a pause in seconds or milliseconds,this value should be set less than 5000ms. Examples of valid values are 2s and 500ms
	 * @return "mtts:silence" node
	 */
	UFUNCTION(BlueprintPure,Category="AzureTTS",meta=(DisplayName="Make MSTTS Silence Element Node"))
	static FSSMLElementNode MakeMSTTSSilenceElementNode(const ESSMLSilenceType SilenceType, const FString Value = "200ms");

	/**
	 * @brief Make a "p" node
	 * @param InnerXml InnerXml
	 * @return "p" node
	 */
	UFUNCTION(BlueprintPure,Category="AzureTTS",meta=(DisplayName="Make P Element Node"))
	static FSSMLElementNode MakePElementNode(const FString InnerXml);


	/**
	 * @brief Make a "s" node
	 * @param InnerXml InnerXml
	 * @return "s" node
	 */
	UFUNCTION(BlueprintPure,Category="AzureTTS",meta=(DisplayName="Make S Element Node"))
	static FSSMLElementNode MakeSElementNode(const FString InnerXml);

	/**
	 * @brief Make a "phoneme" node
	 * @param InnerXml InnerXml
	 * @param PhonemeAlphabetType Specifies the phonetic alphabet to use when synthesizing the pronunciation of the string in the ph attribute. 
	 * @param Ph A string containing phones that specify the pronunciation of the word in the phoneme element. If the specified string contains unrecognized phones, the text-to-speech (TTS) service rejects the entire SSML document and produces none of the speech output specified in the document.
	 * @return 
	 */
	UFUNCTION(BlueprintPure,Category="AzureTTS")
	static FSSMLElementNode MakePhonemeElementNode(const FString InnerXml, const ESSMLPhonemeAlphabetType PhonemeAlphabetType, const FString Ph);

	/**
	 * @brief Make "lexicon" node
	 * @param Uri The address of the external PLS document.
	 * @return "lexicon" node
	 */
	UFUNCTION(BlueprintPure,Category="AzureTTS")
	static FSSMLElementNode MakeLexiconElementNode(const FString Uri);

	/**
	 * @brief Make "prosody" node
	 * @param InnerXml InnerXml
	 * @param Pitch Indicates the baseline pitch for the text. You can express the pitch as: An absolute value, expressed as a number followed by "Hz" (Hertz). For example, <prosody pitch="600Hz">some text</prosody>; A relative value, expressed as a number preceded by "+" or "-" and followed by "Hz" or "st", that specifies an amount to change the pitch. For example: <prosody pitch="+80Hz">some text</prosody> or <prosody pitch="-2st">some text</prosody>. The "st" indicates the change unit is semitone, which is half of a tone (a half step) on the standard diatonic scale; A constant value: x-low/low/medium/high/x-high/default
	 * @param Contour Contour now supports both neural and standard voices. Contour represents changes in pitch. These changes are represented as an array of targets at specified time positions in the speech output. Each target is defined by sets of parameter pairs. For example:<prosody contour="(0%,+20Hz) (10%,-2st) (40%,+10Hz)">.The first value in each set of parameters specifies the location of the pitch change as a percentage of the duration of the text. The second value specifies the amount to raise or lower the pitch, using a relative value or an enumeration value for pitch (see pitch).
	 * @param Range A value that represents the range of pitch for the text. You can express range using the same absolute values, relative values, or enumeration values used to describe pitch.
	 * @param Rate Indicates the speaking rate of the text. You can express rate as: A relative value, expressed as a number that acts as a multiplier of the default. For example, a value of 1 results in no change in the rate. A value of 0.5 results in a halving of the rate. A value of 3 results in a tripling of the rate; A constant value: x-slow/slow/medium/fast/x-fast/default
	 * @param Duration The period of time that should elapse while the speech synthesis (TTS) service reads the text, in seconds or milliseconds. For example, 2s or 1800ms. Duration supports standard voices only.
	 * @param Volume Indicates the volume level of the speaking voice. You can express the volume as: An absolute value, expressed as a number in the range of 0.0 to 100.0, from quietest to loudest. For example, 75. The default is 100.0; A relative value, expressed as a number preceded by "+" or "-" that specifies an amount to change the volume. For example, +10 or -5.5; A constant value:silent/x-soft/soft/medium/loud/x-loud/default
	 * @return "prosody" node 
	 */
	UFUNCTION(BlueprintPure,Category="AzureTTS")
	static FSSMLElementNode MakeProsodyElementNode(const FString InnerXml, const FString Pitch = "default",
	                                               const FString Contour = "", const FString Range = "",
	                                               const FString Rate = "default", const FString Duration = "",
	                                               const FString Volume = "default");

	/**
	 * @brief Make a "say-as" node
	 * @param InnerXml InnerXml
	 * @param InterpretAs Indicates the content type of element's text
	 * @param Format Provides additional information about the precise formatting of the element's text for content types that might have ambiguous formats.
	 * @param Detail Indicates the level of detail to be spoken. For example, this attribute might request that the speech synthesis engine pronounce punctuation marks. There are no standard values defined for detail.
	 * @return "say-as" node
	 */
	UFUNCTION(BlueprintPure,Category="AzureTTS",meta=(DisplayName="Make Say-As Element Node"))
	static FSSMLElementNode MakeSayAsElementNode(const FString InnerXml, const ESSMLInterpretAsType InterpretAs,
	                                                  const FString Format = "", const FString Detail = "");

	/**
	 * @brief Make a "audio" node
	 * @param InnerXml InnerXml
	 * @param Src Specifies the location/URL of the audio file.
	 * @return "audio" node
	 */
	UFUNCTION(BlueprintPure,Category="AzureTTS")
	static FSSMLElementNode MakeAudioElementNode(const FString InnerXml,const FString Src);


	/**
	 * @brief Make a "mstts:backgroundaudio" node
	 * @param Src Specifies the location/URL of the background audio file.
	 * @param Volume Specifies the volume of the background audio file. Accepted values: 0 to 100 inclusive. 
	 * @param FadeIn Specifies the duration of the background audio "fade in" as milliseconds. The default value is 0, which is the equivalent to no fade in. Accepted values: 0 to 10000 inclusive.
	 * @param FadeOut Specifies the duration of the background audio fade out in milliseconds. The default value is 0, which is the equivalent to no fade out. Accepted values: 0 to 10000 inclusive.
	 * @return "mstts:backgroundaudio" node
	 */
	UFUNCTION(BlueprintPure,Category="AzureTTS",meta=(DisplayName="Make MSTTS Background Audio Element Node"))
	static FSSMLElementNode MakeMSTTSBackgroundAudioElementNode(const FString Src, const int Volume = 1, const int FadeIn=0, const int FadeOut=0);

	/**
	 * @brief Make a "bookmark" node
	 * @param Mark Specifies the reference text of the bookmark element.
	 * @return "bookmark" node
	 */
	UFUNCTION(BlueprintPure,Category="AzureTTS")
	static FSSMLElementNode MakeBookmarkElementNode(const FString Mark);


	/**
	 * @brief Make a "plain text" node. Yep, consider text as a node.
	 * @param Content content.
	 * @return "plain text" node.
	 */
	UFUNCTION(BlueprintPure,Category="AzureTTS")
	static FSSMLElementNode MakePlainTextElementNode(const FString Content);
};
