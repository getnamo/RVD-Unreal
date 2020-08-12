// Copyright 2020-current Getnamo. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RVDBlueprintLibrary.h"
#include "RVDConsumer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRVDIntSignature, int32, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRVDFloatSignature, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRVDStringSignature, FString, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRVDVectorSignature, FVector, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRVDRotatorSignature, FRotator, Value);

/**
* Simple Listener to debug values being sent. Not optimal. Subclass to provide easy utility for debuggin the value visually.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REALTIMEVALUEDEBUG_API URVDConsumer : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintAssignable, Category = "RVD Events")
	FRVDIntSignature OnIntValue;

	UPROPERTY(BlueprintAssignable, Category = "RVD Events")
	FRVDFloatSignature OnFloatValue;

	UPROPERTY(BlueprintAssignable, Category = "RVD Events")
	FRVDStringSignature OnStringValue;

	UPROPERTY(BlueprintAssignable, Category = "RVD Events")
	FRVDVectorSignature OnVectorValue;

	UPROPERTY(BlueprintAssignable, Category = "RVD Events")
	FRVDRotatorSignature OnRotatorValue;

	//applies to all listens
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SocketIO Connection Properties")
	FString Category;

	//applies to all listens
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SocketIO Connection Properties")
	int32 ListenIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SocketIO Connection Properties")
	bool bListenToInt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SocketIO Connection Properties")
	bool bListenToFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SocketIO Connection Properties")
	bool bListenToString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SocketIO Connection Properties")
	bool bListenToVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SocketIO Connection Properties")
	bool bListenToRotator;

	URVDConsumer();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;	
};
