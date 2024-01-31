// Copyright Epic Games, Inc. All Rights Reserved.

#include "LogTools_PluginBPLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

ULogTools_PluginBPLibrary::ULogTools_PluginBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

bool ULogTools_PluginBPLibrary::WithEditor()
{
#if WITH_EDITOR
	return true;
#else
	return false;
#endif
}


void ULogTools_PluginBPLibrary::PI_Print(const UObject* WorldContextObject, FString String1, FString String2, ELogEnum LogCategory, bool bPrintToScreen, bool bPrintToLog, FLinearColor TextColor, float Duration)
{
	FString SourceObjectPrefix = FString::Printf(TEXT("[%s] "), *GetNameSafe(WorldContextObject));
	FText text = FText::AsCultureInvariant(String1.Append(String2));
	switch (LogCategory)
	{
	case PI_Debug:
		UKismetSystemLibrary::PrintText(WorldContextObject, text, bPrintToScreen, bPrintToLog, TextColor, Duration);
		break;
	case PI_Warning:
		{ 
			UKismetSystemLibrary::PrintText(WorldContextObject, text, bPrintToScreen, false, TextColor, Duration);
			const FString FinalLogString = SourceObjectPrefix + *text.ToString();
			UE_LOG(LogBlueprint, Warning, TEXT("%s"), *FinalLogString);
		}
	
		break;
	case PI_Error:
		UKismetSystemLibrary::PrintText(WorldContextObject, text, bPrintToScreen, false, TextColor, Duration);

		const FString FinalLogString2 = SourceObjectPrefix + *text.ToString();
		UE_LOG(LogBlueprint, Error, TEXT("%s"), *FinalLogString2);
		UE_LOG(LogBlueprint, Error, TEXT("Callstack : \n %s"), *FFrame::GetScriptCallstack());
		break;
	}
}
