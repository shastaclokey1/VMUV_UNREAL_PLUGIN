// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#ifndef BYTEUTILITIES
#define BYTEUTILITIES

#include "CoreMinimal.h"
#include <vector>
#include <string>
using std::string;
using std::vector;

/**
 * 
 */
class VMUV_PLUGIN_API ByteUtilities
{
public:
	static const unsigned short rawDataLengthInBytes = 18;
	static const unsigned short rawDataLengthInShorts = rawDataLengthInBytes / 2;
	
	static void setRawDataInCnts(vector<unsigned char> bytes);
	static vector<unsigned short> getRawDataInCnts();
	static FString toCsvFormat();

private:
	static vector<unsigned short> rawDataInCnts;
	static FString moduleName;

	static unsigned short convertBytesToShort(vector<unsigned char> bytes, int ndx);

};

#endif //BYTEUTILITIES