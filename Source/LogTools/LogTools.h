// Fill out your copyright notice in the Description page of Project Settings.

#ifndef LogTool_H
#define LogTool_H

#include "CoreMinimal.h"


// Helper file to log symply
// include in your source file
// TRACE("msg")
// TRACE("msg %s",*string)
//this file will fail to compile if included in a header...
 
LOGTOOLS_API DECLARE_LOG_CATEGORY_EXTERN(PI_Log, Log, All);

#if _MSC_VER
#define FUNC_NAME    *FString(__func__)
#else // FIXME - GCC?
#define FUNC_NAME    TEXT(__func__)
#endif

#define TRACE(Format, ...) \
{ \
const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
UE_LOG(PI_Log, Log, TEXT("%s | %s() [%d] : %s"),*GetNameSafe(this),FUNC_NAME,__LINE__, *Msg);\
}

#define TRACE_WARN(Format, ...) \
{ \
const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
UE_LOG(PI_Log, Warning, TEXT("%s | %s() [%d] : %s"),*GetNameSafe(this),FUNC_NAME,__LINE__, *Msg);\
}

#define TRACE_ERROR(Format, ...) \
{ \
const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
UE_LOG(PI_Log, Error, TEXT("%s | %s() [%d] : %s"),*GetNameSafe(this),FUNC_NAME,__LINE__, *Msg);\
}

#define TRACE_SCREEN(time,Format, ...) \
{ \
const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
if (Msg == "") \
{ \
TCHAR StdMsg[MAX_SPRINTF] = TEXT(""); \
FCString::Sprintf(StdMsg, TEXT("%s() : %s"), FUNC_NAME, *GetNameSafe(this)); \
GEngine->AddOnScreenDebugMessage(-1, time, FColor::White, StdMsg); \
UE_LOG(PI_Log, Log, TEXT("%s | %s() [%d] : %s"),*GetNameSafe(this),FUNC_NAME,__LINE__, *Msg);\
} \
else \
{ \
GEngine->AddOnScreenDebugMessage(-1, time, FColor::White, Msg); \
UE_LOG(PI_Log, Log, TEXT("%s | %s() [%d] : %s"),*GetNameSafe(this),FUNC_NAME,__LINE__, *Msg);\
} \
}

#define TRACE_STATIC(Format, ...) \
{ \
const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
UE_LOG(PI_Log, Log, TEXT("%s() : %s"), FUNC_NAME, *Msg);\
}

#define TRACE_STATIC_WARN(Format, ...) \
{ \
const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
UE_LOG(PI_Log, Warning, TEXT("%s() : %s"), FUNC_NAME, *Msg);\
}

#define TRACE_STATIC_ERROR(Format, ...) \
{ \
const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
UE_LOG(PI_Log, Error, TEXT("%s() : %s"), FUNC_NAME, *Msg);\
}



#endif

