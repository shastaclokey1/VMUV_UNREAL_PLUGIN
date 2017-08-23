// Fill out your copyright notice in the Description page of Project Settings.

#include "Motus.h"
#include "VMUV_Plugin.h"
#include "../Logging/traceLogger.h"
#include "HeadMountedDisplay.h"
#include "MotionControllerComponent.h"

Motus::Motus()
{
	FString method = "Motus()";
	for (int i = 0; i < numSensors; i++)
		pads.push_back(sensorPads(i));
	if (pads.size() == 9)
		pads[8].activeThreshold = .45f;
	else
		traceLogger::queueMessage(traceLogger::buildMessage(moduleName, method, "Motus initiallization unsuccessful"));

}


void Motus::setAllSensorValues(vector<unsigned short> data)
{
	FString method = "setAllSensorValues()";
	if (data.size() < numSensors)
	{
		traceLogger::queueMessage(traceLogger::buildMessage(moduleName, method, "incorrect data(less than 9 values in data buff)"));
		return;
	}
	for (int i = 0; i < numSensors; i++)
		pads[i].setCurrentValue(data[i]);
}

FVector Motus::getXZVector()
{
	XZVector = FVector::ZeroVector;
	float x = 0;
	float z = 0;

	if (!pads[8].padActive())
		return XZVector;

	z = pads[0].getUnitVector() + (pads[1].getUnitVector() * sin45)
		- (pads[3].getUnitVector() * sin45) - pads[4].getUnitVector()
		- (pads[5].getUnitVector() * sin45) + (pads[7].getUnitVector() * sin45);

	x = (pads[1].getUnitVector() * sin45) + pads[2].getUnitVector()
		+ (pads[3].getUnitVector() * sin45) - (pads[5].getUnitVector() * sin45)
		- pads[6].getUnitVector() - (pads[7].getUnitVector() * sin45);

	XZVector.X = x;
	XZVector.Y = 0;
	XZVector.Z = z;
	XZVector.Normalize();

	return XZVector;
}

void Motus::setRoomScaleCoordinates()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayConnected())
	{
		FRotator trash;
		UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(trash, deviceRoomScaleCoordinates);
	}
}

