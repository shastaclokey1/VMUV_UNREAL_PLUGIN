// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include "CoreMinimal.h"
#include <vector>
#include "Motus.h"
#include <string>
using std::string;
using std::vector;


/**
 * 
 */
class VMUV_PLUGIN_API dataStorage
{
public:

	static void setCurrentData(vector<unsigned short> data);
	static vector<unsigned short> getCurrentData();
	static FString getCurrentDataCsvFormat();
	static FVector getXZVector();
	static FVector getMotusRoomScaleCoordinates();
	static void setMotusRoomScaleCoordinates();

private:
	static vector<unsigned short> currentRawDataPing;
	static vector<unsigned short> currentRawDataPong;
	static Motus motus;
	static bool usePing;
	
};


#endif //DATASTORAGE_H