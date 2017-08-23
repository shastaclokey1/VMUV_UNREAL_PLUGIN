// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#ifndef TRACELOGGER
#define TRACELOGGER

#include "CoreMinimal.h"
#include <string>
using std::string;

#define BUFF_SIZE 32

struct traceLoggerMessage
{
	FString moduleName;
	FString methodName;
	FString message;
};

class VMUV_PLUGIN_API traceLogger
{
public:
	static unsigned int getBuffSize();
	static int getNumMessagesQueued();
	static bool hasMessages();
	static bool queueMessage(traceLoggerMessage msg);
	static traceLoggerMessage deQueueMessage();
	static traceLoggerMessage buildMessage(FString modName, FString method, FString msg);
	static void getAllMessages(traceLoggerMessage getMsg[BUFF_SIZE], int& bufferSize);
	static FString traceLoggerMessageToString(traceLoggerMessage msg);


private:
	static unsigned int buffHead;
	static unsigned int buffTail;
	static unsigned int buffSize;
	static traceLoggerMessage msgBuff[BUFF_SIZE];

	static bool isRoomInBuff();
};

#endif //TRACELOGGER
