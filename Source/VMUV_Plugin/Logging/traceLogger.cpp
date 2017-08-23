// Fill out your copyright notice in the Description page of Project Settings.

#include "traceLogger.h"
#include "VMUV_Plugin.h"

unsigned int traceLogger::buffHead = 0;
unsigned int traceLogger::buffTail = 0;
unsigned int traceLogger::buffSize = 32;
traceLoggerMessage traceLogger::msgBuff[BUFF_SIZE];

unsigned int traceLogger::getBuffSize()
{
	return buffSize;
}

int traceLogger::getNumMessagesQueued()
{
	unsigned int head = buffHead % buffSize;
	unsigned int tail = buffTail % buffSize;

	if (head < tail)
		head += buffSize;

	return ((int)head - (int)tail);

}

bool traceLogger::hasMessages()
{
	return (getNumMessagesQueued() > 0);
}

bool traceLogger::queueMessage(traceLoggerMessage msg)
{
	if (!isRoomInBuff())
		return false;

	msgBuff[buffHead % buffSize] = msg;
	buffHead++;
	
	return true;
}

traceLoggerMessage traceLogger::deQueueMessage()
{
	traceLoggerMessage rtn = msgBuff[buffTail % buffSize];
	buffTail++;

	return rtn;
}

traceLoggerMessage traceLogger::buildMessage(FString modName, FString method, FString msg)
{
	traceLoggerMessage rtn;

	rtn.moduleName = modName;
	rtn.methodName = method;
	rtn.message = msg;

	return rtn;
}

void traceLogger::getAllMessages(traceLoggerMessage getMsg[BUFF_SIZE], int& bufferSize)
{
	int size = getNumMessagesQueued();
	for (int i = 0; i < size; i++)
		getMsg[i] = deQueueMessage();
	bufferSize = size;
}

FString traceLogger::traceLoggerMessageToString(traceLoggerMessage msg)
{
	return (msg.moduleName + ": " + msg.methodName + ": " + msg.message + "\r\n");
}

bool traceLogger::isRoomInBuff()
{
	int numMsgsQueued = getNumMessagesQueued();
	return ((numMsgsQueued >= 0) && (numMsgsQueued < (int)buffSize));
}


