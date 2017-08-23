// Fill out your copyright notice in the Description page of Project Settings.

#include "SocketInput.h"
#include "VMUV_Plugin.h"
#include "TCP/SocketWrapper.h"
#include "Utilities/ByteUtilities.h"
#include "DataStorage/dataStorage.h"
#include "TCP/client.h"
#include "Logging/traceLogger.h"
#include "HeadMountedDisplay.h"
#include "MotionControllerComponent.h"
#include "Orientation/orienter.h"
#include "Logging/logger.h"
#include "pluginInterface.h"
#include <vector>
using std::vector;

//socketWrapper workingClientSocket;

// Sets default values for this component's properties
USocketInput::USocketInput()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USocketInput::BeginPlay()
{
	Super::BeginPlay();
	pluginInterface::initialize();

	
}


// Called every frame
void USocketInput::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	
	pluginInterface::service();
	FVector blub = pluginInterface::getXZVector();
	UE_LOG(LogTemp, Warning, TEXT("XZVector: %s"), *blub.ToString());
	
	

	
	//////Testing TCP functionality////////
	/*client::service();
	vector<unsigned short> processedData = dataStorage::getCurrentData();
	FString dataString = dataStorage::getCurrentDataCsvFormat();
	UE_LOG(LogTemp, Warning, TEXT("Data from processed data array then from csv formatted fstring: "));
	for (int j = 0; j < (int)processedData.size(); j++)
	{
		FString tmpString = FString::FromInt(processedData[j]);
		UE_LOG(LogTemp, Warning, TEXT("Data: %s"), *tmpString);
	}
	UE_LOG(LogTemp, Warning, TEXT("Formatted data: %s"), *dataString);


	//////Testing traceLogger///////
	string mod = "SocketInput.cpp";
	string method = "TickComponent()";
	string msg = "testing traceLogger";
	traceLogger::queueMessage(traceLogger::buildMessage(mod, method, msg));
	if (traceLogger::hasMessages())
	{
		string outMsg = traceLogger::traceLoggerMessageToString(traceLogger::deQueueMessage());
		UE_LOG(LogTemp, Warning, TEXT("Message from traceLogger: %s"), *FString(outMsg.c_str()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Something wrong with traceLogging"));
	}


	///////////testing tracking stuff////////////
	bool HMDconnected = UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayConnected();
	bool HMDenabled = UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled();
	UE_LOG(LogTemp, Warning, TEXT("Is HMD Connected(Using UHeadMountedDisplayFunctionLibrary)?: %s"), *FString::FromInt(HMDconnected));
	UE_LOG(LogTemp, Warning, TEXT("Is HMD Enabled(Using UHeadMountedDisplayFunctionLibrary)?: %s"), *FString::FromInt(HMDenabled));
	FRotator currentRot;
	FVector currentPos;
	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(currentRot, currentPos);
	FQuat rotAsQuat = currentRot.Quaternion();
	UE_LOG(LogTemp, Warning, TEXT("HMD position(Using UHeadMountedDisplayFunctionLibrary)?: %s"), *currentPos.ToString());
	UE_LOG(LogTemp, Warning, TEXT("HMD rotation(Using UHeadMountedDisplayFunctionLibrary)?: %s"), *rotAsQuat.ToString());
	
	/////////testing orienter class/////////////
	currentRot = FRotator(orienter::applyHeadSteeringRotation());
	currentPos = orienter::getDeviceLocalPosition();
	rotAsQuat = currentRot.Quaternion();
	UE_LOG(LogTemp, Warning, TEXT("HMD position(Using orienter)?: %s"), *currentPos.ToString());
	UE_LOG(LogTemp, Warning, TEXT("HMD rotation(Using orienter)?: %s"), *rotAsQuat.ToString());


	//////////testing logger/////////////
	logger::logMessage("testing the logger");*/
	


	//IMotionController;
	//EControllerHand;
	//UMotionControllerComponent leftHand;
	//FTransform LHTransform = leftHand.GetRelativeTransform();
	/*IHeadMountedDisplay *hmd;
	bool isConnected = hmd->IsHMDConnected();
	UE_LOG(LogTemp, Warning, TEXT("Is HMD Connected(Using IHeadMountedDisplay)?: %s"), *FString::FromInt(isConnected));
	FQuat currentRot;
	FVector currentPos;
	hmd->GetCurrentOrientationAndPosition(currentRot, currentPos);
	UE_LOG(LogTemp, Warning, TEXT("HMD position(Using IHeadMountedDisplay)?: %s"), *currentPos.ToString());
	UE_LOG(LogTemp, Warning, TEXT("HMD rotation(Using IHeadMountedDisplay)?: %s"), *currentRot.ToString());*/
	
	

	
}


