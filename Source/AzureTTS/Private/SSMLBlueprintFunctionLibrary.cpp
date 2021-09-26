// Fill out your copyright notice in the Description page of Project Settings.


#include "SSMLBlueprintFunctionLibrary.h"

// ReSharper disable once CppUnusedIncludeDirective
#include "AzureTTSLogMacroDefine.h"


FString USSMLBlueprintFunctionLibrary::GetSSMLDocumentOuterXml(const FSSMLDocument& SSMLDocument)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	FString Result = "";
	if(!SSMLDocument.XmlVersion.IsEmpty())
	{
		Result.Append("<?xml version=\"");
		Result.Append(SSMLDocument.XmlVersion);
		Result.Append("\"?>");
	}
	Result.Append(GetSSMLElementNodeOuterXml(SSMLDocument.RootElement));
	return Result;
}



FString USSMLBlueprintFunctionLibrary::GetSSMLElementNodeOuterXml(const FSSMLElementNode& SSMLElementNode)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	if(SSMLElementNode.ElementType == ESSMLElementType::PlainText)
		return SSMLElementNode.InnerXml;
	
	FString Result="<";
	bool bClosedTag;
	switch (SSMLElementNode.ElementType)
	{
		case ESSMLElementType::Break:
		case ESSMLElementType::MSTTS_Silence:
		case ESSMLElementType::MSTTS_BackgroundAudio:
		case ESSMLElementType::Lexicon:
		case ESSMLElementType::Mark:
		case ESSMLElementType::Bookmark:
			bClosedTag = true;
			break;
		default:
			bClosedTag = false;
		break;
	}
	/** It should be a closed xml tag, if no innerxml in a "audio" node **/
	if(SSMLElementNode.ElementType == ESSMLElementType::Audio && SSMLElementNode.InnerXml.IsEmpty())
		bClosedTag = true;
	
	/** Get Enum **/
	const UEnum* EnumPtr = FindObject<UEnum>((UObject*)ANY_PACKAGE, TEXT("ESSMLElementType"), true);
	
	/** Get element node tag **/
	FString XmlTag = (EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(SSMLElementNode.ElementType))).ToString().ToLower();
	Result.Append(XmlTag);

	for (auto& Elem :SSMLElementNode.Properties)
	{
		FString PropertyKey = Elem.Key;
		FString PropertyValue = *Elem.Value;
		if(!PropertyValue.IsEmpty())
		{
			Result.Append(" ");
			Result.Append(PropertyKey);
			Result.Append("=\"");
			Result.Append(PropertyValue);
			Result.Append("\"");
		}
	}
	if(bClosedTag)
	{
		Result.Append("/>");
	}
	else
	{
		Result.Append(">");
		Result.Append(SSMLElementNode.InnerXml);
		Result.Append("</");
		Result.Append(XmlTag);
		Result.Append(">");
	}
	
	return Result;
}

FSSMLElementNode& USSMLBlueprintFunctionLibrary::AppendChildElementNode(UPARAM(ref) FSSMLElementNode& ParentNode,
	const FSSMLElementNode& ChildNode)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	return AppendChildElement(ParentNode,GetSSMLElementNodeOuterXml(ChildNode));
}

FSSMLElementNode& USSMLBlueprintFunctionLibrary::AppendChildElement(UPARAM(ref) FSSMLElementNode& ParentNode, const FString Content)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	ParentNode.InnerXml.Append(Content);
	return ParentNode;
}

FSSMLElementNode& USSMLBlueprintFunctionLibrary::AppendChildElementNodes(UPARAM(ref) FSSMLElementNode& ParentNode,
	const TArray<FSSMLElementNode>& ChildElementNodes)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	for (int i = 0; i < ChildElementNodes.Num(); ++i)
	{
		AppendChildElementNode(ParentNode,ChildElementNodes[i]);
	}
	return ParentNode;
}

FSSMLElementNode USSMLBlueprintFunctionLibrary::MakeSpeakElementNode(const FString InnerXml,
	const FString XmlLang,  const FString Version, const FString XmlNs, const FString XmlNsMSTTS)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	FSSMLElementNode SpeakElementNode;
	SpeakElementNode.ElementType=ESSMLElementType::Speak;
	SpeakElementNode.InnerXml = InnerXml;
	
	if(!Version.IsEmpty())
		SpeakElementNode.Properties.Add("version",Version);

	if(!XmlNs.IsEmpty())
		SpeakElementNode.Properties.Add("xmlns",XmlNs);

	if(!XmlLang.IsEmpty())
		SpeakElementNode.Properties.Add("xml:lang",XmlLang);

	if(!XmlNsMSTTS.IsEmpty())
		SpeakElementNode.Properties.Add("xmlns:mstts",XmlNsMSTTS);

	return SpeakElementNode;
}

FSSMLElementNode USSMLBlueprintFunctionLibrary::MakeVoiceElementNode(const FString InnerXml,const FString Name)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	FSSMLElementNode VoiceElementNode;
	VoiceElementNode.ElementType=ESSMLElementType::Voice;
    VoiceElementNode.InnerXml = InnerXml;

	if(!Name.IsEmpty())
		VoiceElementNode.Properties.Add("name",Name);
	
	return VoiceElementNode;
}

FSSMLElementNode USSMLBlueprintFunctionLibrary::MakeMSTTSExpressAsElementNode(const FString InnerXml,
	const FString Style, const FString StyleDegree, const FString Role)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	FSSMLElementNode MSTTSExpressAsElementNode;
	MSTTSExpressAsElementNode.ElementType=ESSMLElementType::MSTTS_Express_As;
	MSTTSExpressAsElementNode.InnerXml = InnerXml;

	if(!Style.IsEmpty())
		MSTTSExpressAsElementNode.Properties.Add("style",Style);
	if(!StyleDegree.IsEmpty())
		MSTTSExpressAsElementNode.Properties.Add("styledegree",StyleDegree);
	if(!Role.IsEmpty())
		MSTTSExpressAsElementNode.Properties.Add("role",Role);
	
	return MSTTSExpressAsElementNode;
}

FSSMLElementNode USSMLBlueprintFunctionLibrary::MakeLangElementNode(const FString InnerXml, const FString XmlLang)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	FSSMLElementNode LangElementNode;
	LangElementNode.ElementType=ESSMLElementType::Lang;
	LangElementNode.InnerXml = InnerXml;

	if(!XmlLang.IsEmpty())
		LangElementNode.Properties.Add("xml:lang",XmlLang);
	
	return  LangElementNode;
}

FSSMLElementNode USSMLBlueprintFunctionLibrary::MakeBreakElementNode(const ESSMLBreakStrength Strength,const FString Time)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	FSSMLElementNode BreakElementNode;
	BreakElementNode.ElementType=ESSMLElementType::Break;

	if(!Time.IsEmpty())
		BreakElementNode.Properties.Add("time",Time);
	
	FString StrengthValue;
	switch (Strength)
	{
	case ESSMLBreakStrength::XWeak:
		StrengthValue = "x-weak";
		break;
	case ESSMLBreakStrength::Weak:
		StrengthValue = "weak";
		break;
	case ESSMLBreakStrength::Medium:
		StrengthValue = "medium";
		break;
	case ESSMLBreakStrength::Strong:
		StrengthValue = "strong";
		break;
	case ESSMLBreakStrength::XStrong:
		StrengthValue = "x-strong";
		break;
	default:
		StrengthValue = "";
		break;
	}	
	if(!StrengthValue.IsEmpty())
		BreakElementNode.Properties.Add("strength",StrengthValue);
	
	return  BreakElementNode;	
}

FSSMLElementNode USSMLBlueprintFunctionLibrary::MakeMSTTSSilenceElementNode(const ESSMLSilenceType SilenceType,
	const FString Value)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	FSSMLElementNode MSTTSSilenceElementNode;
	MSTTSSilenceElementNode.ElementType=ESSMLElementType::MSTTS_Silence;

	/** Get Enum **/
	const UEnum* EnumPtr = FindObject<UEnum>((UObject*)ANY_PACKAGE, TEXT("ESSMLSilenceType"), true);
	FString Type = (EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(SilenceType))).ToString().ToLower();
	MSTTSSilenceElementNode.Properties.Add("type",Type);
	MSTTSSilenceElementNode.Properties.Add("value",Value);
	
	return  MSTTSSilenceElementNode;
}

FSSMLElementNode USSMLBlueprintFunctionLibrary::MakePElementNode(const FString InnerXml)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	FSSMLElementNode PElementNode;
	PElementNode.ElementType=ESSMLElementType::P;
	PElementNode.InnerXml = InnerXml;

	return  PElementNode;
}

FSSMLElementNode USSMLBlueprintFunctionLibrary::MakeSElementNode(const FString InnerXml)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	FSSMLElementNode SElementNode;
	SElementNode.ElementType=ESSMLElementType::S;
	SElementNode.InnerXml = InnerXml;

	return  SElementNode;	
}

FSSMLElementNode USSMLBlueprintFunctionLibrary::MakePhonemeElementNode(const FString InnerXml,
	const ESSMLPhonemeAlphabetType PhonemeAlphabetType, const FString Ph)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	FSSMLElementNode PhonemeElementNode;
	PhonemeElementNode.ElementType=ESSMLElementType::Phoneme;
	PhonemeElementNode.InnerXml = InnerXml;
	const UEnum* EnumPtr = FindObject<UEnum>((UObject*)ANY_PACKAGE, TEXT("ESSMLPhonemeAlphabetType"), true);
	const FString Alphabet = (EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(PhonemeAlphabetType))).ToString().ToLower();
	PhonemeElementNode.Properties.Add("alphabet",Alphabet);
	PhonemeElementNode.Properties.Add("ph",Ph);
	
	return PhonemeElementNode;
}

FSSMLElementNode USSMLBlueprintFunctionLibrary::MakeLexiconElementNode(const FString Uri)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	FSSMLElementNode LexiconElementNode;
	LexiconElementNode.ElementType = ESSMLElementType::Lexicon;
	LexiconElementNode.Properties.Add("uri",Uri);

	return LexiconElementNode;
}

FSSMLElementNode USSMLBlueprintFunctionLibrary::MakeProsodyElementNode(const FString InnerXml, const FString Pitch,
	const FString Contour, const FString Range, const FString Rate, const FString Duration, const FString Volume)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	FSSMLElementNode ProsodyElementNode;
	ProsodyElementNode.ElementType = ESSMLElementType::Prosody;
	ProsodyElementNode.InnerXml = InnerXml;

	if(!Pitch.IsEmpty())
		ProsodyElementNode.Properties.Add("pitch",Pitch);

	if(!Contour.IsEmpty())
		ProsodyElementNode.Properties.Add("contour",Contour);

	if(!Range.IsEmpty())
		ProsodyElementNode.Properties.Add("range",Range);

	if(!Rate.IsEmpty())
		ProsodyElementNode.Properties.Add("rate",Rate);

	if(!Duration.IsEmpty())
		ProsodyElementNode.Properties.Add("duration",Duration);

	if(!Volume.IsEmpty())
		ProsodyElementNode.Properties.Add("volume",Volume);

	return ProsodyElementNode;
}

FSSMLElementNode USSMLBlueprintFunctionLibrary::MakeSayAsElementNode(const FString InnerXml,
	const ESSMLInterpretAsType InterpretAs, const FString Format, const FString Detail)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	FSSMLElementNode SayAsElementNode;
	SayAsElementNode.ElementType = ESSMLElementType::Say_As;
	SayAsElementNode.InnerXml = InnerXml;
	const UEnum* EnumPtr = FindObject<UEnum>((UObject*)ANY_PACKAGE, TEXT("ESSMLInterpretAsType"), true);
	const FString InterpretAsValue = (EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(InterpretAs))).ToString().ToLower();
	SayAsElementNode.Properties.Add("interpret-as",InterpretAsValue);
	if(!Format.IsEmpty())
		SayAsElementNode.Properties.Add("format",Format);
	if(!Detail.IsEmpty())
		SayAsElementNode.Properties.Add("detail",Detail);
	
	return SayAsElementNode;
}

FSSMLElementNode USSMLBlueprintFunctionLibrary::MakeAudioElementNode(const FString InnerXml,const FString Src)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	FSSMLElementNode AudioElementNode;
	AudioElementNode.ElementType = ESSMLElementType::Audio;
	AudioElementNode.InnerXml = InnerXml;
	AudioElementNode.Properties.Add("src",Src);

	return AudioElementNode;
}

FSSMLElementNode USSMLBlueprintFunctionLibrary::MakeMSTTSBackgroundAudioElementNode(const FString Src, const int Volume,
	const int FadeIn, const int FadeOut)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	FSSMLElementNode MSTTSBackgroundAudioElementNode;
	MSTTSBackgroundAudioElementNode.ElementType = ESSMLElementType::MSTTS_BackgroundAudio;
	MSTTSBackgroundAudioElementNode.Properties.Add("src",Src);
	if(Volume>=0 && Volume<=100)
		MSTTSBackgroundAudioElementNode.Properties.Add("volume",FString::FromInt(Volume));
	else
		MSTTSBackgroundAudioElementNode.Properties.Add("volume","1");

	if(FadeIn>=0 && FadeIn<=10000)
		MSTTSBackgroundAudioElementNode.Properties.Add("fadein",FString::FromInt(FadeIn));
	else
		MSTTSBackgroundAudioElementNode.Properties.Add("fadein","0");

	if(FadeOut>=0 && FadeOut<=10000)
		MSTTSBackgroundAudioElementNode.Properties.Add("fadeout",FString::FromInt(FadeOut));
	else
		MSTTSBackgroundAudioElementNode.Properties.Add("fadeout","0");

	return MSTTSBackgroundAudioElementNode;
}

FSSMLElementNode USSMLBlueprintFunctionLibrary::MakeBookmarkElementNode(const FString Mark)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));

	FSSMLElementNode BookmarkElementNode;
	BookmarkElementNode.ElementType = ESSMLElementType::Bookmark;
	BookmarkElementNode.Properties.Add("mark",Mark);
	return BookmarkElementNode;
}

FSSMLElementNode USSMLBlueprintFunctionLibrary::MakePlainTextElementNode(const FString Content)
{
	UE_LOG(AzureTTS,Log,TEXT(__FUNCTION__));
	FSSMLElementNode PlainTextElementNode;
	PlainTextElementNode.ElementType = ESSMLElementType::PlainText;
	PlainTextElementNode.InnerXml = Content;
	return PlainTextElementNode;
}


