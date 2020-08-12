// Copyright 2020-current Getnamo. All Rights Reserved


#include "RVDConsumer.h"

URVDConsumer::URVDConsumer()
{
	PrimaryComponentTick.bCanEverTick = true;
	bListenToInt = false;
	bListenToFloat = false;
	bListenToString = false;
	bListenToVector = false;
	bListenToRotator = false;

	ListenIndex = 0;
}

void URVDConsumer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bListenToInt)
	{
		OnIntValue.Broadcast(URVDBlueprintLibrary::IntValueFromDebug(Category, ListenIndex));
	}

	if (bListenToFloat)
	{
		OnFloatValue.Broadcast(URVDBlueprintLibrary::FloatValueFromDebug(Category, ListenIndex));
	}

	if (bListenToString)
	{
		OnStringValue.Broadcast(URVDBlueprintLibrary::StringValueFromDebug(Category, ListenIndex));
	}

	if (bListenToVector)
	{
		OnVectorValue.Broadcast(URVDBlueprintLibrary::VectorValueFromDebug(Category, ListenIndex));
	}

	if (bListenToRotator)
	{
		OnRotatorValue.Broadcast(URVDBlueprintLibrary::RotatorValueFromDebug(Category, ListenIndex));
	}
}


void URVDConsumer::BeginPlay()
{
	Super::BeginPlay();
}
