// Fill out your copyright notice in the Description page of Project Settings.

#include "ByteUtilities.h"
#include "VMUV_Plugin.h"
#include "../Logging/traceLogger.h"


vector<unsigned short> ByteUtilities::rawDataInCnts;
FString ByteUtilities::moduleName = "ByteUtilities.cpp";



void ByteUtilities::setRawDataInCnts(vector<unsigned char> bytes)
{
	FString method = "setRawDataInCnts()";
	if ((unsigned short)bytes.size() < rawDataLengthInBytes )
	{
		traceLogger::queueMessage(traceLogger::buildMessage(moduleName, method, "too much data passed to byte utilities/ data unpacked improperly"));
	}
	else
	{
		rawDataInCnts.clear();
		int i, j = 1;
		i = 0;
		int len = rawDataLengthInShorts;
		for (i = 0; i < len; i++, j += 2)
			rawDataInCnts.push_back(ByteUtilities::convertBytesToShort(bytes, j));
	}
}

vector<unsigned short> ByteUtilities::getRawDataInCnts()
{
	return rawDataInCnts;
}

FString ByteUtilities::toCsvFormat()
{
	FString rtn = FString::FromInt(rawDataInCnts[0]);

	for (int i = 1; i < rawDataLengthInShorts; i++)
	{
		FString val = "," + FString::FromInt(rawDataInCnts[i]);
		rtn += val;
	}
	
	return rtn;
}

unsigned short ByteUtilities::convertBytesToShort(vector<unsigned char> bytes, int ndx)
{
	unsigned short val = bytes[ndx + 1];
	val <<= 8;
	val |= (bytes[ndx] & 0xff);
	return val;
}

