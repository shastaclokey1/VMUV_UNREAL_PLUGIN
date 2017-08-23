// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#ifndef MOTUS_H
#define MOTUS_H

#include "CoreMinimal.h"
#include "sensorPads.h"
#include <vector>
#include <string>
using std::string;
using std::vector;

class VMUV_PLUGIN_API Motus
{
public:
	const int numSensors = 9;
	vector<sensorPads> pads;
	FVector deviceRoomScaleCoordinates;
	
	Motus();

	void setAllSensorValues(vector<unsigned short> data);
	FVector getXZVector();
	void setRoomScaleCoordinates();

private:
	const float sin45 = .707f;
	FString moduleName = "Motus.cpp";
	FVector XZVector = FVector::ZeroVector;
};

#endif //MOTUS_H