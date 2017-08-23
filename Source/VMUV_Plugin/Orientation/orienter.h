// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#ifndef ORIENTER_H
#define ORIENTER_H

#include "CoreMinimal.h"

/**
 * 
 */
class VMUV_PLUGIN_API orienter
{
public:
	static bool useViveTracker;
	static bool useHeadSet;
	static bool useHands;

	static void snapMotusToGameAxis();
	static FQuat getOffset();
	static FQuat applyHandSteeringRotation(); //need to implement this
	static FQuat applyHeadSteeringRotation();
	static FQuat applyViveTrackerRotation();
	static void setViveTrackerRotation(FVector pos, FQuat rot);
	static FVector getDeviceLocalPosition();
private:
	static FQuat inGameOffset;
	static FQuat latchPadDirection;
	static FQuat steeringOffset;
	static FVector trackerPos;
	static FQuat trackerRot;

};


#endif //ORIENTER_H