// Copyright 2020-current Getnamo. All Rights Reserved


#include "RVDBlueprintLibrary.h"
#include "UObject/Object.h"

TSharedPtr<FRVDebug> URVDBlueprintLibrary::DebugHandler = nullptr;

void FRVDTimeData::SetWithFrameTime(float InFrameTime)
{
	Precise = FPlatformTime::Seconds();
	Frame = InFrameTime;
}

FRVDebug::FRVDebug()
{
	Data = MakeShareable(new FRVDebugData);
}

FRVDebug::~FRVDebug()
{
	Data = nullptr;
}


void FRVDebug::SetIntValue(int32 Value, const FString& Category /*= TEXT("default")*/, float FrameTime)
{
	FRVDIntData NewValue;
	NewValue.Timestamp.SetWithFrameTime(FrameTime);

	NewValue.Value = Value;

	//Create bucket if needed
	if (!Data->IntData.Contains(Category))
	{
		FRVDIntHistoryData History;
		History.MaxIndex = Max;
		Data->IntData.Add(Category, History);
	}

	auto& Bucket = Data->IntData[Category];
	
	//Add if num below max, replace if above or equal
	if (Bucket.Values.Num() < Bucket.MaxIndex)
	{
		Bucket.Values.Add(NewValue);
		Bucket.LoopIndex++;
	}
	else
	{
		if (Bucket.LoopIndex >= Bucket.MaxIndex)
		{
			Bucket.LoopIndex = 0;
		}
		Bucket.Values[Bucket.LoopIndex] = NewValue;
		Bucket.LoopIndex++;
	}
}

void FRVDebug::SetFloatValue(float Value, const FString& Category /*= TEXT("default")*/, float FrameTime)
{
	FRVDFloatData NewValue;
	NewValue.Timestamp.SetWithFrameTime(FrameTime);

	NewValue.Value = Value;

	//Create bucket if needed
	if (!Data->FloatData.Contains(Category))
	{
		FRVDFloatHistoryData History;
		History.MaxIndex = Max;
		Data->FloatData.Add(Category, History);
	}

	auto& Bucket = Data->FloatData[Category];

	//Add if num below max, replace if above or equal
	if (Bucket.Values.Num() < Bucket.MaxIndex)
	{
		Bucket.Values.Add(NewValue);
		Bucket.LoopIndex++;
	}
	else
	{
		if (Bucket.LoopIndex >= Bucket.MaxIndex)
		{
			Bucket.LoopIndex = 0;
		}
		Bucket.Values[Bucket.LoopIndex] = NewValue;
		Bucket.LoopIndex++;
	}
}

void FRVDebug::SetStringValue(FString Value, const FString& Category /*= TEXT("default")*/, float FrameTime)
{
	FRVDStringData NewValue;
	NewValue.Timestamp.SetWithFrameTime(FrameTime);

	NewValue.Value = Value;

	//Create bucket if needed
	if (!Data->StringData.Contains(Category))
	{
		FRVDStringHistoryData History;
		History.MaxIndex = Max;
		Data->StringData.Add(Category, History);
	}

	auto& Bucket = Data->StringData[Category];

	//Add if num below max, replace if above or equal
	if (Bucket.Values.Num() < Bucket.MaxIndex)
	{
		Bucket.Values.Add(NewValue);
		Bucket.LoopIndex++;
	}
	else
	{
		if (Bucket.LoopIndex >= Bucket.MaxIndex)
		{
			Bucket.LoopIndex = 0;
		}
		Bucket.Values[Bucket.LoopIndex] = NewValue;
		Bucket.LoopIndex++;
	}
}

void FRVDebug::SetVectorValue(FVector Value, const FString& Category /*= TEXT("default")*/, float FrameTime)
{
	FRVDVectorData NewValue;
	NewValue.Timestamp.SetWithFrameTime(FrameTime);

	NewValue.Value = Value;

	//Create bucket if needed
	if (!Data->VectorData.Contains(Category))
	{
		FRVDVectorHistoryData History;
		History.MaxIndex = Max;
		Data->VectorData.Add(Category, History);
	}

	auto& Bucket = Data->VectorData[Category];

	//Add if num below max, replace if above or equal
	if (Bucket.Values.Num() < Bucket.MaxIndex)
	{
		Bucket.Values.Add(NewValue);
		Bucket.LoopIndex++;
	}
	else
	{
		if (Bucket.LoopIndex >= Bucket.MaxIndex)
		{
			Bucket.LoopIndex = 0;
		}
		Bucket.Values[Bucket.LoopIndex] = NewValue;
		Bucket.LoopIndex++;
	}
}

void FRVDebug::SetRotatorValue(FRotator Value, const FString& Category /*= TEXT("default")*/, float FrameTime)
{
	FRVDRotatorData NewValue;
	NewValue.Timestamp.SetWithFrameTime(FrameTime);

	NewValue.Value = Value;

	//Create bucket if needed
	if (!Data->RotatorData.Contains(Category))
	{
		FRVDRotatorHistoryData History;
		History.MaxIndex = Max;
		Data->RotatorData.Add(Category, History);
	}

	auto& Bucket = Data->RotatorData[Category];

	//Add if num below max, replace if above or equal
	if (Bucket.Values.Num() < Bucket.MaxIndex)
	{
		Bucket.Values.Add(NewValue);
		Bucket.LoopIndex++;
	}
	else
	{
		if (Bucket.LoopIndex >= Bucket.MaxIndex)
		{
			Bucket.LoopIndex = 0;
		}
		Bucket.Values[Bucket.LoopIndex] = NewValue;
		Bucket.LoopIndex++;
	}
}

int32 FRVDebug::IntFromDebug(const FString& Category /*= TEXT("default")*/, int32 Index /*= 0*/)
{
	if (!Data->IntData.Contains(Category))
	{
		return 0;
	}

	auto& Bucket = Data->IntData[Category];
	
	//convert index offset, check for loop back
	int32 DesiredIndex = Bucket.LoopIndex + Index;
	if (DesiredIndex < 0)
	{
		if (Bucket.Values.Num() == 0)
		{
			return 0;
		}
		while (DesiredIndex < 0)
		{
			DesiredIndex += Bucket.Values.Num();
		}
	}
	return Bucket.Values[DesiredIndex].Value;
}

float FRVDebug::FloatFromDebug(const FString& Category /*= TEXT("default")*/, int32 Index /*= 0*/)
{
	if (!Data->FloatData.Contains(Category))
	{
		return 0.f;
	}

	auto& Bucket = Data->FloatData[Category];

	//convert index offset, check for loop back
	int32 DesiredIndex = Bucket.LoopIndex + Index;
	if (DesiredIndex < 0)
	{
		if (Bucket.Values.Num() == 0)
		{
			return 0.f;
		}
		while (DesiredIndex < 0)
		{
			DesiredIndex += Bucket.Values.Num();
		}
	}
	return Bucket.Values[DesiredIndex].Value;
}

FString FRVDebug::StringFromDebug(const FString& Category /*= TEXT("default")*/, int32 Index /*= 0*/)
{
	if (!Data->StringData.Contains(Category))
	{
		return TEXT("");
	}

	auto& Bucket = Data->StringData[Category];

	//convert index offset, check for loop back
	int32 DesiredIndex = Bucket.LoopIndex + Index;
	if (DesiredIndex < 0)
	{
		if (Bucket.Values.Num() == 0)
		{
			return TEXT("");
		}
		while (DesiredIndex < 0)
		{
			DesiredIndex += Bucket.Values.Num();
		}
	}
	return Bucket.Values[DesiredIndex].Value;
}

FVector FRVDebug::VectorFromDebug(const FString& Category /*= TEXT("default")*/, int32 Index /*= 0*/)
{
	if (!Data->VectorData.Contains(Category))
	{
		return FVector(0.f);
	}

	auto& Bucket = Data->VectorData[Category];

	//convert index offset, check for loop back
	int32 DesiredIndex = Bucket.LoopIndex + Index;
	if (DesiredIndex < 0)
	{
		if (Bucket.Values.Num() == 0)
		{
			return FVector(0.f);
		}
		while (DesiredIndex < 0)
		{
			DesiredIndex += Bucket.Values.Num();
		}
	}
	return Bucket.Values[DesiredIndex].Value;
}

FRotator FRVDebug::RotatorFromDebug(const FString& Category /*= TEXT("default")*/, int32 Index /*= 0*/)
{
	if (!Data->RotatorData.Contains(Category))
	{
		return FRotator(0.f);
	}

	auto& Bucket = Data->RotatorData[Category];

	//convert index offset, check for loop back
	int32 DesiredIndex = Bucket.LoopIndex + Index;
	if (DesiredIndex < 0)
	{
		if (Bucket.Values.Num() == 0)
		{
			return FRotator(0.f);
		}
		while (DesiredIndex < 0)
		{
			DesiredIndex += Bucket.Values.Num();
		}
	}
	return Bucket.Values[DesiredIndex].Value;
}

void FRVDebug::SetMax(int32 NewMax /*= 100*/)
{
	Max = NewMax;
}

URVDBlueprintLibrary::URVDBlueprintLibrary()
{
	DebugHandler = MakeShareable(new FRVDebug);
}

void URVDBlueprintLibrary::DebugIntValue(int32 Value, const FString& Category /*= TEXT("default")*/, UObject* WorldContextObject /*= nullptr*/)
{
	float FrameTime = 0.f;
	if (WorldContextObject != nullptr)
	{
		FrameTime = WorldContextObject->GetWorld()->TimeSeconds;
	}
	
	DebugHandler->SetIntValue(Value, Category, FrameTime);
}

void URVDBlueprintLibrary::DebugFloatValue(float Value, const FString& Category /*= TEXT("default")*/, UObject* WorldContextObject /*= nullptr*/)
{
	float FrameTime = 0.f;
	if (WorldContextObject != nullptr)
	{
		FrameTime = WorldContextObject->GetWorld()->TimeSeconds;
	}

	DebugHandler->SetFloatValue(Value, Category, FrameTime);
}

void URVDBlueprintLibrary::DebugStringValue(FString Value, const FString& Category /*= TEXT("default")*/, UObject* WorldContextObject /*= nullptr*/)
{
	float FrameTime = 0.f;
	if (WorldContextObject != nullptr)
	{
		FrameTime = WorldContextObject->GetWorld()->TimeSeconds;
	}

	DebugHandler->SetStringValue(Value, Category, FrameTime);
}

void URVDBlueprintLibrary::DebugVectorValue(FVector Value, const FString& Category /*= TEXT("default")*/, UObject* WorldContextObject /*= nullptr*/)
{
	float FrameTime = 0.f;
	if (WorldContextObject != nullptr)
	{
		FrameTime = WorldContextObject->GetWorld()->TimeSeconds;
	}

	DebugHandler->SetVectorValue(Value, Category, FrameTime);
}

void URVDBlueprintLibrary::DebugRotatorValue(FRotator Value, const FString& Category /*= TEXT("default")*/, UObject* WorldContextObject /*= nullptr*/)
{
	float FrameTime = 0.f;
	if (WorldContextObject != nullptr)
	{
		FrameTime = WorldContextObject->GetWorld()->TimeSeconds;
	}

	DebugHandler->SetRotatorValue(Value, Category, FrameTime);
}

int32 URVDBlueprintLibrary::IntValueFromDebug(const FString& Category /*= TEXT("default")*/, int32 Index /*= 0*/, UObject* WorldContextObject /*= nullptr*/)
{
	return DebugHandler->IntFromDebug(Category, Index);
}

float URVDBlueprintLibrary::FloatValueFromDebug(const FString& Category /*= TEXT("default")*/, int32 Index /*= 0*/, UObject* WorldContextObject /*= nullptr*/)
{
	return DebugHandler->FloatFromDebug(Category, Index);
}

FString URVDBlueprintLibrary::StringValueFromDebug(const FString& Category /*= TEXT("default")*/, int32 Index /*= 0*/, UObject* WorldContextObject /*= nullptr*/)
{
	return DebugHandler->StringFromDebug(Category, Index);
}

FVector URVDBlueprintLibrary::VectorValueFromDebug(const FString& Category /*= TEXT("default")*/, int32 Index /*= 0*/, UObject* WorldContextObject /*= nullptr*/)
{
	return DebugHandler->VectorFromDebug(Category, Index);
}

FRotator URVDBlueprintLibrary::RotatorValueFromDebug(const FString& Category /*= TEXT("default")*/, int32 Index /*= 0*/, UObject* WorldContextObject /*= nullptr*/)
{
	return DebugHandler->RotatorFromDebug(Category, Index);
}

