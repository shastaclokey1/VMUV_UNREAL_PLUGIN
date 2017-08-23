// Fill out your copyright notice in the Description page of Project Settings.

#include "dataStorage.h"
#include "VMUV_Plugin.h"
#include "../Utilities/ByteUtilities.h"


bool dataStorage::usePing = true;
vector<unsigned short> dataStorage::currentRawDataPing;
vector<unsigned short> dataStorage::currentRawDataPong;
Motus dataStorage::motus;

void dataStorage::setCurrentData(vector<unsigned short> data)
{
	if (usePing)
	{
		currentRawDataPing = data;
		usePing = false;
	}
	else
	{
		currentRawDataPong = data;
		usePing = true;
	}

	motus.setAllSensorValues(data);
}

vector<unsigned short> dataStorage::getCurrentData()
{
	if (usePing)
		return currentRawDataPong;
	else
		return currentRawDataPing;
}

FString dataStorage::getCurrentDataCsvFormat()
{
	return ByteUtilities::toCsvFormat();
}

FVector dataStorage::getXZVector()
{
	return motus.getXZVector();
}

FVector dataStorage::getMotusRoomScaleCoordinates()
{
	return motus.deviceRoomScaleCoordinates;
}

void dataStorage::setMotusRoomScaleCoordinates()
{
	motus.setRoomScaleCoordinates();
}



