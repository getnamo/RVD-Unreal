// Copyright 2020-current Getnamo. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RVDBlueprintLibrary.generated.h"

/**
* NB: these definitions have code duplications, but it's intended this way to keep the system simple for now
* Correct approach would be to use templating, but that's a variable success with unreal built in types.
*/

USTRUCT()
struct FRVDTimeData
{
	GENERATED_USTRUCT_BODY()

	//In seconds
	UPROPERTY()
	float Frame;

	//In milliseconds, used for event ordering
	UPROPERTY()
	double Precise;

	
	void SetWithFrameTime(float InFrameTime);
};

//Ints
USTRUCT()
struct FRVDIntData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int32 Value;

	UPROPERTY()
	FRVDTimeData Timestamp;
};

USTRUCT()
struct FRVDIntHistoryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<FRVDIntData> Values;

	UPROPERTY()
	int32 LoopIndex;

	UPROPERTY()
	int32 MaxIndex;

	FRVDIntHistoryData() { LoopIndex = 0; MaxIndex = 100; }
};

//Floats
USTRUCT()
struct FRVDFloatData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	float Value;

	UPROPERTY()
	FRVDTimeData Timestamp;
};

USTRUCT()
struct FRVDFloatHistoryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<FRVDFloatData> Values;

	UPROPERTY()
	int32 LoopIndex;

	UPROPERTY()
	int32 MaxIndex;

	FRVDFloatHistoryData() { LoopIndex = 0; MaxIndex = 100; }
};

//Strings
USTRUCT()
struct FRVDStringData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FString Value;

	UPROPERTY()
	FRVDTimeData Timestamp;
};

USTRUCT()
struct FRVDStringHistoryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<FRVDStringData> Values;

	UPROPERTY()
	int32 LoopIndex;

	UPROPERTY()
	int32 MaxIndex;

	FRVDStringHistoryData() { LoopIndex = 0; MaxIndex = 100; }
};

//Vectors
USTRUCT()
struct FRVDVectorData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FVector Value;

	UPROPERTY()
	FRVDTimeData Timestamp;
};

USTRUCT()
struct FRVDVectorHistoryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<FRVDVectorData> Values;

	UPROPERTY()
	int32 LoopIndex;

	UPROPERTY()
	int32 MaxIndex;

	FRVDVectorHistoryData() { LoopIndex = 0; MaxIndex = 100; }
};

//Rotators
USTRUCT()
struct FRVDRotatorData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FRotator Value;

	UPROPERTY()
	FRVDTimeData Timestamp;
};

USTRUCT()
struct FRVDRotatorHistoryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<FRVDRotatorData> Values;

	UPROPERTY()
	int32 LoopIndex;

	UPROPERTY()
	int32 MaxIndex;

	FRVDRotatorHistoryData() { LoopIndex = 0; MaxIndex = 100; }
};


USTRUCT()
struct FRVDebugData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TMap<FString, FRVDIntHistoryData> IntData;

	UPROPERTY()
	TMap<FString, FRVDFloatHistoryData> FloatData;

	UPROPERTY()
	TMap<FString, FRVDStringHistoryData> StringData;

	UPROPERTY()
	TMap<FString, FRVDVectorHistoryData> VectorData;

	UPROPERTY()
	TMap<FString, FRVDRotatorHistoryData> RotatorData;

};

/** Main class used for setting and retrieving data types */
class FRVDebug
{
public:
	FRVDebug();
	~FRVDebug();

	//Setting
	void SetIntValue(int32 Value, const FString& Category = TEXT("default"), float FrameTime = 0.f);
	void SetFloatValue(float Value, const FString& Category = TEXT("default"), float FrameTime = 0.f);
	void SetStringValue(FString Value, const FString& Category = TEXT("default"), float FrameTime = 0.f);
	void SetVectorValue(FVector Value, const FString& Category = TEXT("default"), float FrameTime = 0.f);
	void SetRotatorValue(FRotator Value, const FString& Category = TEXT("default"), float FrameTime = 0.f);

	//Getting
	int32 IntFromDebug(const FString& Category = TEXT("default"), int32 Index = 0);
	float FloatFromDebug(const FString& Category = TEXT("default"), int32 Index = 0);
	FString StringFromDebug(const FString& Category = TEXT("default"), int32 Index = 0);
	FVector VectorFromDebug(const FString& Category = TEXT("default"), int32 Index = 0);
	FRotator RotatorFromDebug(const FString& Category = TEXT("default"), int32 Index = 0);

	//for now applies to all data types
	void SetMax(int32 NewMax = 100);

protected:
	TSharedPtr<FRVDebugData> Data;
	int32 Max;
};

/**
 * 
 */
UCLASS()
class REALTIMEVALUEDEBUG_API URVDBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	URVDBlueprintLibrary();

	//Setting

	UFUNCTION(BlueprintCallable, Category = "Realtime Value Debug Static", meta = (WorldContext = "WorldContextObject"))
	static void DebugIntValue(int32 Value, const FString& Category = TEXT("default"), UObject* WorldContextObject = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Realtime Value Debug Static", meta = (WorldContext = "WorldContextObject"))
	static void DebugFloatValue(float Value, const FString& Category = TEXT("default"), UObject* WorldContextObject = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Realtime Value Debug Static", meta = (WorldContext = "WorldContextObject"))
	static void DebugStringValue(FString Value, const FString& Category = TEXT("default"), UObject* WorldContextObject = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Realtime Value Debug Static", meta = (WorldContext = "WorldContextObject"))
	static void DebugVectorValue(FVector Value, const FString& Category = TEXT("default"), UObject* WorldContextObject = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Realtime Value Debug Static", meta = (WorldContext = "WorldContextObject"))
	static void DebugRotatorValue(FRotator Value, const FString& Category = TEXT("default"), UObject* WorldContextObject = nullptr);

	//Getting

	//Index is an offset 0 = latest, -1 is the one before that etc...
	UFUNCTION(BlueprintCallable, Category = "Realtime Value Debug Static", meta = (WorldContext = "WorldContextObject"))
	static int32 IntValueFromDebug(const FString& Category = TEXT("default"), int32 Index = 0, UObject* WorldContextObject = nullptr);

	//Index is an offset 0 = latest, -1 is the one before that etc...
	UFUNCTION(BlueprintCallable, Category = "Realtime Value Debug Static", meta = (WorldContext = "WorldContextObject"))
	static float FloatValueFromDebug(const FString& Category = TEXT("default"), int32 Index = 0, UObject* WorldContextObject = nullptr);

	//Index is an offset 0 = latest, -1 is the one before that etc...
	UFUNCTION(BlueprintCallable, Category = "Realtime Value Debug Static", meta = (WorldContext = "WorldContextObject"))
	static FString StringValueFromDebug(const FString& Category = TEXT("default"), int32 Index = 0, UObject* WorldContextObject = nullptr);

	//Index is an offset 0 = latest, -1 is the one before that etc...
	UFUNCTION(BlueprintCallable, Category = "Realtime Value Debug Static", meta = (WorldContext = "WorldContextObject"))
	static FVector VectorValueFromDebug(const FString& Category = TEXT("default"), int32 Index = 0, UObject* WorldContextObject = nullptr);

	//Index is an offset 0 = latest, -1 is the one before that etc...
	UFUNCTION(BlueprintCallable, Category = "Realtime Value Debug Static", meta = (WorldContext = "WorldContextObject"))
	static FRotator RotatorValueFromDebug(const FString& Category = TEXT("default"), int32 Index = 0, UObject* WorldContextObject = nullptr);



protected:
	static TSharedPtr<FRVDebug> DebugHandler;
};
