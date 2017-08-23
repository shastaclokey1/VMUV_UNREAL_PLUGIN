// Fill out your copyright notice in the Description page of Project Settings.

#include "logger.h"
#include "PlatformFilemanager.h"
#include "FileManager.h"
#include "Paths.h"
#include <iostream>
using std::cout;
using std::endl;

FString logger::currentDir;
FString logger::logFileName = "VMUVlog.txt";
FString logger::logFilePath;
bool logger::logFileCreated = false;
bool logger::logConsoleData = false;
bool logger::logUnrealConsoleData = false;

void logger::createLogFile()
{
	logFileCreated = false;
	try
	{
#if DebugGame
		logConsoleData = true;
#else
		logUnrealConsoleData = true;
#endif


		IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
		IFileHandle* fileHandle = platformFile.OpenWrite(*logFileName, true);
		logFileCreated = true;
		if (fileHandle)
		{
			FString string = "*** New log file created ***\r\n";
			fileHandle->Write((const uint8*)TCHAR_TO_ANSI(*string), string.Len());
			delete fileHandle;
		}
	}
	catch(_exception)
	{ }
}

void logger::logMessage(FString msg)
{
	if (!logFileCreated)
		return;

	try
	{
		IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
		IFileHandle* fileHandle = platformFile.OpenWrite(*logFileName, true);
		if (fileHandle)
		{
			msg += "\r\n";
			fileHandle->Write((const uint8*)TCHAR_TO_ANSI(*msg), msg.Len());
			delete fileHandle;
		}

		if (logConsoleData)
			cout.write((const char*)TCHAR_TO_ANSI(*msg), msg.Len());
		else if (logUnrealConsoleData)
		{
			UE_LOG(LogTemp, Warning, TEXT("Logger message: %s"), *msg);
		}
	}
	catch (_exception)
	{ }
}

void logger::logMessage(vector<FString> msgs)
{
	FString msg = "";

	if (!logFileCreated)
		return;

	for (int i = 0; i < (int)msgs.size(); i++)
		msg += msgs[i];

	try
	{
		IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
		IFileHandle* fileHandle = platformFile.OpenWrite(*logFileName, true);
		if (fileHandle)
		{
			msg += "\r\n";
			fileHandle->Write((const uint8*)TCHAR_TO_ANSI(*msg), msg.Len());
			delete fileHandle;
		}

		if (logConsoleData)
			cout.write((const char*)TCHAR_TO_ANSI(*msg), msg.Len());
		else if (logUnrealConsoleData)
		{
			UE_LOG(LogTemp, Warning, TEXT("Logger message: %s"), *msg);
		}
	}
	catch (_exception)
	{ }
}
