// Fill out your copyright notice in the Description page of Project Settings.

#include "client.h"
#include "VMUV_Plugin.h"
#include "../Utilities/ByteUtilities.h"
#include "../DataStorage/dataStorage.h"

socketWrapper client::swClient;

void client::service()
{
	swClient.clientStartRead();
	vector<unsigned char> dataBytes = swClient.clientGetRxData();
	ByteUtilities::setRawDataInCnts(dataBytes);
	vector<unsigned short> dataShort = ByteUtilities::getRawDataInCnts();

	dataStorage::setCurrentData(dataShort);
}

