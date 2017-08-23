// Fill out your copyright notice in the Description page of Project Settings.

#include "sensorPads.h"
#include "VMUV_Plugin.h"

//#define TEST

sensorPads::sensorPads(int id)
{
	this->id = id;

#ifdef TEST
	maxAllowable = 3000;
	minAllowable = 800;
#endif	//TEST

	maxVal = maxAllowable;
	minVal = minAllowable;
	currentVal = -1;
	pctActive = 0;
	activeThreshold = .75f;
	isActive = false;
#ifdef TEST
	activeThreshold = .45f;
#endif //TEST

}

void sensorPads::setCurrentValue(unsigned short val)
{
	screenValue(val);
	checkMaxMin(val);
	calculatePctActive();
}

unsigned short sensorPads::getRawCurrentValue()
{
	return currentVal;
}

float sensorPads::getUnitVector()
{
	if (isActive)
		return pctActive;
	else
		return 0;
}

bool sensorPads::padActive()
{
	return isActive;
}

float sensorPads::getpctActive()
{
	return pctActive;
}

unsigned short sensorPads::screenValue(unsigned short val)
{
	currentVal = val;
	if (currentVal > maxAllowable)
		currentVal = maxAllowable;

	if (currentVal < minAllowable)
		currentVal = minAllowable;

	return currentVal;
}

void sensorPads::checkMaxMin(unsigned short val)
{
	if (val > maxVal)
		maxVal = val;

	if (val < minVal)
		minVal = val;
}

void sensorPads::calculatePctActive()
{
	if (currentVal == -1)
	{
		pctActive = 0;
		return;
	}

	float num = (currentVal - minAllowable);
	float denom = (maxAllowable - minAllowable);

	pctActive = 1.0f - (num / denom);

	if (pctActive > activeThreshold)
		isActive = true;
	else
		isActive = false;
}
