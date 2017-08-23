// Fill out your copyright notice in the Description page of Project Settings.

#include "orienter.h"
#include "../DataStorage/dataStorage.h"
#include "HeadMountedDisplay.h"
#include "MotionControllerComponent.h"

bool orienter::useViveTracker = false;
bool orienter::useHeadSet = true;
bool orienter::useHands = false;

FQuat orienter::inGameOffset;
FQuat orienter::latchPadDirection;
FQuat orienter::steeringOffset;
FVector orienter::trackerPos;
FQuat orienter::trackerRot(0, 0, 0, 1);

void orienter::snapMotusToGameAxis()
{
	FVector xz = dataStorage::getXZVector();
	steeringOffset = FQuat(0, 0, 0, 1);
	
	if (xz.Size() > 0)
	{
		FQuat playerRotation = FQuat(0, 0, 0, 1);
		FVector playerPosition;

		if (useViveTracker)
			playerRotation = trackerRot;
		else
		{
			FRotator tempRot;
			UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(tempRot, playerPosition);
			playerRotation = tempRot.Quaternion();
		}

		FVector playerRotationEuler = playerRotation.Euler();

		playerRotationEuler.X = 0;
		playerRotationEuler.Z = 0;
		playerRotation = FQuat::MakeFromEuler(playerRotationEuler);

		inGameOffset = playerRotation * latchPadDirection.Inverse();

		dataStorage::setMotusRoomScaleCoordinates();

	}
}

FQuat orienter::getOffset()
{
	return inGameOffset;
}

FQuat orienter::applyHandSteeringRotation()
{	
	throw std::exception("function not implemented yet");
}

FQuat orienter::applyHeadSteeringRotation()
{
	FVector xz = dataStorage::getXZVector();
	FQuat rtn(0, 0, 0, 1);

	//only "steer" if player is moving
	if (xz.Size() > 0)
	{
		FQuat playerRotation;
		FVector playerPosition;
		FRotator tempRot;
		UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(tempRot, playerPosition);
		playerRotation = tempRot.Quaternion();
		FVector playerRotationEuler = playerRotation.Euler();

		playerRotationEuler.X = 0;
		playerRotationEuler.Z = 0;
		playerRotation = FQuat::MakeFromEuler(playerRotationEuler);

		rtn = playerRotation * steeringOffset.Inverse();
	}
	else
	{
		FQuat playerRotation;
		FVector playerPosition;
		FRotator tempRot;
		UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(tempRot, playerPosition);
		playerRotation = tempRot.Quaternion();
		FVector playerRotationEuler = playerRotation.Euler();

		playerRotationEuler.X = 0;
		playerRotationEuler.Z = 0;
		playerRotation = FQuat::MakeFromEuler(playerRotationEuler);

		steeringOffset = playerRotation;
	}
	return rtn;
}

FQuat orienter::applyViveTrackerRotation()
{
	FVector xz = dataStorage::getXZVector();
	FQuat rtn(0, 0, 0, 1);

	//only "steer" if player is moving
	if (xz.Size() > 0)
	{
		FQuat playerRotation = trackerRot;
		FVector playerRotationEuler = playerRotation.Euler();

		playerRotationEuler.X = 0;
		playerRotationEuler.Z = 0;
		playerRotation = FQuat::MakeFromEuler(playerRotationEuler);

		rtn = playerRotation * steeringOffset.Inverse();
	}
	else
	{
		FQuat playerRotation = trackerRot;
		FVector playerRotationEuler = playerRotation.Euler();

		playerRotationEuler.X = 0;
		playerRotationEuler.Z = 0;
		playerRotation = FQuat::MakeFromEuler(playerRotationEuler);

		steeringOffset = playerRotation;
	}
	return rtn;
}

void orienter::setViveTrackerRotation(FVector pos, FQuat rot)
{
	trackerPos = pos;
	trackerRot = rot;
}

FVector orienter::getDeviceLocalPosition()
{
	return dataStorage::getMotusRoomScaleCoordinates();
}
