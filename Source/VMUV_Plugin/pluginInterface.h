// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>
using std::string;

/**
 * 
 */
class VMUV_PLUGIN_API pluginInterface
{
public:
	static FString versionInfo;
	static bool enableHeadSteering;
	static bool enableHandSteering;
	static bool enableViveTrackerSteering;
	static bool isViveTrackerPresent;
	static bool autoOrientEnable;
	static bool shouldOrientMotus;

	static void initialize();
	static void service();
	static FVector getXZVector();
	static FQuat getCharacterRotation();
	static FVector getDeviceLocationInRoomScaleCoordinates();
	static void setViveTrackerOrientation(FVector position, FQuat rotation);

private:
	static bool isInitialized;
	static bool autoOrientComplete;

	static void orientMotus();
};
