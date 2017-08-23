// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include "CoreMinimal.h"
#include <string>
#include <vector>
using std::vector;
using std::string;

/**
 * 
 */
class VMUV_PLUGIN_API logger
{
public:
	static void createLogFile();
	static void logMessage(FString msg);
	static void logMessage(vector<FString> msgs);

private:
	static FString currentDir;
	static FString logFileName;
	static FString logFilePath;
	static bool logFileCreated;
	static bool logConsoleData;
	static bool logUnrealConsoleData;
};


#endif //LOGGER_H