// Fill out your copyright notice in the Description page of Project Settings.

#include "SocketWrapper.h"
#include "VMUV_Plugin.h"
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include "../Logging/traceLogger.h"

const FString socketWrapper::version = "1.0.0";

socketWrapper::socketWrapper() : config(Configuration::client)
{
	rxDataPing.reserve(256);
	rxDataPong.reserve(256);
}

FString socketWrapper::getVersion()
{
	return version;
}

void socketWrapper::setRxData(vector<unsigned char> payload, PacketTypes type)
{
	FString method = "setRxData()";
	if (config == Configuration::server)
	{
		traceLogger::queueMessage(traceLogger::buildMessage(moduleName, method, "Socket wrapper config set to server"));
		return;
	}
	if (usePing)
	{
		rxDataPing.clear();
		for (int i = 0; i < (int)payload.size(); i++)
			rxDataPing.push_back(payload[i]);
		usePing = false;
	}
	else
	{
		rxDataPong.clear();
		for (int i = 0; i < (int)payload.size(); i++)
			rxDataPong.push_back(payload[i]);
		usePing = true;
	}
}

vector<unsigned char> socketWrapper::clientGetRxData() const
{
	FString method = "clientGetRxData";
	if (config == Configuration::server)
	{
		traceLogger::queueMessage(traceLogger::buildMessage(moduleName, method, "Socket wrapper config set to server"));
		return vector<unsigned char>();
	}
	if (usePing)
		return rxDataPong;
	else
		return rxDataPing;
}

void socketWrapper::clientStartRead()
{
	FString method = "clientStartRead()";
	if (clientIsBusy || config == Configuration::server)
	{
		traceLogger::queueMessage(traceLogger::buildMessage(moduleName, method, "Socket wrapper config set to server (or) client is busy"));
		return;
	}

	WORD sockVersion;
	WSADATA wsaData;
	int nret;
	char readBuff[256];

	sockVersion = MAKEWORD(1, 0);
	WSAStartup(sockVersion, &wsaData);

	//initiallize the client socket
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (client == INVALID_SOCKET)
	{
		nret = WSAGetLastError();
		UE_LOG(LogTemp, Error, TEXT("ERROR WITH socket() initiallization!"));
		traceLogger::queueMessage(traceLogger::buildMessage(moduleName, method, FString("Error With socket() initiallization") + FString::FromInt(nret)));
		closesocket(client);
		WSACleanup();
		return;
	}

	//prepare for connection by filling sockaddr struct with info about the server
	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = loopBackIpAddr;//*((LPIN_ADDR)*hostEntry->h_addr_list);
	serverInfo.sin_port = htons(port);

	//connect to the server!
	nret = connect(client, (LPSOCKADDR)&serverInfo, sizeof(serverInfo));
	if (nret == SOCKET_ERROR)
	{
		nret = WSAGetLastError();
		UE_LOG(LogTemp, Error, TEXT("ERROR WITH connect() function!"));
		traceLogger::queueMessage(traceLogger::buildMessage(moduleName, method, FString("Error With connect() initiallization: ") + FString::FromInt(nret)));
		closesocket(client);
		WSACleanup();
		return;
	}

	//get a data packet from the tcp connection
	nret = recv(client, readBuff, 7 + 19, 0);
	if (nret == SOCKET_ERROR)
	{
		nret = WSAGetLastError();
		UE_LOG(LogTemp, Error, TEXT("ERROR WITH recv() function!"));
		traceLogger::queueMessage(traceLogger::buildMessage(moduleName, method, "Error With recv() initiallization"));
		closesocket(client);
		WSACleanup();
		return;
	}
	//error check in case the server is sending wonky packets
	if (nret != 26)
	{
		traceLogger::queueMessage(traceLogger::buildMessage(moduleName, method, "data packet from recv() was wrong size"));
		closesocket(client);
		WSACleanup();
		return;
	}

	vector<unsigned char> packet, data;
	for (int i = 0; i < 7 + 19; i++)
		packet.push_back(readBuff[i]);

	//check packet validity and set it to the rxData
	bool rtn = packetMaker.isPacketValid(packet);
	if (rtn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Recieved valid packet from server ... unpacking."));
		data = packetMaker.unpackData(packet);
		setRxData(data, PacketTypes::raw_data);
		numValidPacketsRead++;
		closesocket(client);
		WSACleanup();
		return;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid data packet!"));
		traceLogger::queueMessage(traceLogger::buildMessage(moduleName, method, "not a valid packet"));
		closesocket(client);
		WSACleanup();
		return;
	}

}

int socketWrapper::getNumValidPacketsRead() const
{
	return numValidPacketsRead;
}

bool socketWrapper::getUsePing() const
{
	return usePing;
}





