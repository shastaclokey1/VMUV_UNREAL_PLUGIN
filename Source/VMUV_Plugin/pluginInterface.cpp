// Fill out your copyright notice in the Description page of Project Settings.

#include "pluginInterface.h"
#include "Logging/logger.h"
#include "TCP/SocketWrapper.h"
#include "TCP/client.h"
#include "Logging/traceLogger.h"
#include "Orientation/orienter.h"
#include "DataStorage/dataStorage.h"
#include <vector>
using std::vector;


FString pluginInterface::versionInfo = "1.0.0";
bool pluginInterface::enableHeadSteering = false;
bool pluginInterface::enableHandSteering = false;
bool pluginInterface::enableViveTrackerSteering = false;
bool pluginInterface::isViveTrackerPresent = false;
bool pluginInterface::autoOrientEnable = false;
bool pluginInterface::shouldOrientMotus = false;

bool pluginInterface::isInitialized = false;
bool pluginInterface::autoOrientComplete = false;

void pluginInterface::initialize()
{
	if (!isInitialized)
	{
		logger::createLogFile();
		logger::logMessage("Unreal Motus Plugin v" + versionInfo + "\r\n");
		logger::logMessage("Client side TCP v" + socketWrapper::getVersion() + "\r\n");

		isInitialized = true;
	}
}

void pluginInterface::service()
{
	client::service();

	if (traceLogger::hasMessages())
	{
		traceLoggerMessage msgs[BUFF_SIZE];
		int numMsgs;
		traceLogger::getAllMessages(msgs, numMsgs);
		FString strMsg;

		for (int i = 0; i < numMsgs; i++)
		{
			strMsg = traceLogger::traceLoggerMessageToString(msgs[i]);
			logger::logMessage(strMsg);
		}
	}

	orienter::useHands = enableHandSteering;
	orienter::useHeadSet = enableHeadSteering;
	orienter::useViveTracker = enableViveTrackerSteering;

	if (autoOrientEnable && !autoOrientComplete)
		shouldOrientMotus = true;

	if (shouldOrientMotus)
	{
		orientMotus();
		shouldOrientMotus = false;
	}
	
}

FVector pluginInterface::getXZVector()
{
	return dataStorage::getXZVector();
}

FQuat pluginInterface::getCharacterRotation()
{
	FQuat axesOffset = orienter::getOffset();
	FQuat steering(0, 0, 0, 1);

	try
	{
		if (enableHeadSteering)
			steering = orienter::applyHeadSteeringRotation();
		else if (enableHandSteering)
			steering; //= orienter::applyHandSteeringRotation(); comment out when method is implemented in orienter class
		else if (enableViveTrackerSteering && isViveTrackerPresent)
			steering = orienter::applyViveTrackerRotation();
	}
	catch (std::exception c)
	{
		logger::logMessage("PluginInterface.cpp: getCharacterRotation: " + FString(c.what()));
	}
	
	return (axesOffset * steering);
}

FVector pluginInterface::getDeviceLocationInRoomScaleCoordinates()
{
	return orienter::getDeviceLocalPosition();
}

void pluginInterface::setViveTrackerOrientation(FVector position, FQuat rotation)
{
	orienter::setViveTrackerRotation(position, rotation);
}

void pluginInterface::orientMotus()
{
	FVector xz = dataStorage::getXZVector();

	if (xz.Size() > 0)
	{
		orienter::snapMotusToGameAxis();

		vector<unsigned short> data;
		for (int i = 0; i < 9; i++)
			data.push_back(0);

		dataStorage::setCurrentData(data);
		dataStorage::setCurrentData(data);

		if (autoOrientEnable)
			autoOrientComplete = true;
	}
}
