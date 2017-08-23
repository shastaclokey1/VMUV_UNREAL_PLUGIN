#pragma once

#ifndef SOCKETWRAPPER_H
#define SOCKETWRAPPER_H

#include "packetizer.h"
#include <WinSock2.h>
#include <string>
#include <iostream>
#include <vector>
#pragma comment(lib,"WS2_32")
using std::string;
using std::cout;
using std::endl;
using std::vector;


#define NETWORK_ERROR -1
#define NETWORK_OK 0



enum class Configuration
{
	server,
	client
};

enum class PacketTypes
{
	test,
	raw_data
};

class VMUV_PLUGIN_API socketWrapper
{
public:
	socketWrapper();

	static FString getVersion();
	vector<unsigned char> clientGetRxData() const;
	void clientStartRead();

	int getNumValidPacketsRead() const;
	bool getUsePing() const;
private:
	packetizer packetMaker;
	SOCKET listener, client;
	const int port = 11069;
	const int loopBackIpAddr = 16777343;
	vector<unsigned char> rxDataPing;
	vector<unsigned char> rxDataPong;
	bool usePing = true;
	Configuration config;
	bool clientIsBusy = false;
	FString moduleName = "SocketWrapper.cpp";  //don't know if I need this
	int numValidPacketsRead = 0;
	const static FString version;	//don't know if I need this
	
	
	void setRxData(vector<unsigned char> payload, PacketTypes type);


};





#endif //SOCKETWRAPPER_H