// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#ifndef SENSORPADS_H
#define SENSORPADS_H

#include "CoreMinimal.h"

class VMUV_PLUGIN_API sensorPads
{
public:
	float activeThreshold;
	short maxAllowable = 3300;
	short minAllowable = 250;

	sensorPads(int id);

	void setCurrentValue(unsigned short val);
	unsigned short getRawCurrentValue();
	float getUnitVector();
	bool padActive();
	float getpctActive();

private:
	int id;
	unsigned short currentVal;
	unsigned short maxVal;
	unsigned short minVal;
	float pctActive;
	bool isActive;

	unsigned short screenValue(unsigned short val);
	void checkMaxMin(unsigned short val);
	void calculatePctActive();
};

#endif //SENSORPADS_H