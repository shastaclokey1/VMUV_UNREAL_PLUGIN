// Fill out your copyright notice in the Description page of Project Settings.

#include "packetizer.h"
#include "VMUV_Plugin.h"
#include <iostream>
using std::cout;
using std::endl;

#define BUFF_SIZE   256

unsigned char packetizer::getPacketType(vector<unsigned char> packet)
{
	if (isPacketValid(packet))
		return packet[2];
	else
		return 0xff;
}

short packetizer::calculateCheckSum(vector<unsigned char> payload)
{
	short chksum = 0;

	if (payload.size() != 0)
	{
		for (int i = 0; i < static_cast<int>(payload.size()); i++)
			chksum += (unsigned short)(payload[i]);
	}

	return chksum;
}

bool packetizer::isPacketValid(vector<unsigned char> packet)
{
	if (static_cast<int>(packet.size()) == 7)
		return false;

	if (packet[0] != sync1)
		return false;

	if (packet[1] != sync2)
		return false;

	unsigned char  type = packet[2];
	short len = static_cast<unsigned short>(packet[3]);
	len <<= 8;
	len |= static_cast<unsigned short>(packet[4] & 0xff);

	if (len > BUFF_SIZE)
		return false;

	unsigned short chkSum = (unsigned short)packet[5 + len];
	chkSum <<= 8;
	chkSum |= (unsigned short)packet[6 + len];

	vector<unsigned char> extractedPayload;

	for (int i = 0; i < len; i++)
		extractedPayload.push_back(packet[i + 5]);

	short calcChkSum = calculateCheckSum(extractedPayload);

	if (calcChkSum != chkSum)
		return false;


	return true;
}

vector<unsigned char> packetizer::packetizeData(vector<unsigned char> payload, int type)
{
	if (payload.size() == 0)
	{ }//TODO possibly add error check here

	unsigned short len = static_cast<unsigned short>(payload.size());

	if (len > BUFF_SIZE)
	{ }//TODO possibly add error check here

	short chkSum = calculateCheckSum(payload);

	vector<unsigned char> packetizedData;
	packetizedData.push_back(sync1);
	packetizedData.push_back(sync2);
	packetizedData.push_back(type);
	packetizedData.push_back(static_cast<unsigned char>((len >> 8) & 0xff));
	packetizedData.push_back(static_cast<unsigned short>(len & 0xff));

	for (int i = 0; i < len; i++)
		packetizedData.push_back(payload[i]);

	packetizedData.push_back(static_cast<unsigned char>((chkSum >> 8) & 0xff));
	packetizedData.push_back(static_cast<unsigned char>(chkSum & 0xff));

	return packetizedData;
}

vector<unsigned char> packetizer::unpackData(vector<unsigned char> packet)
{
	short len = static_cast<unsigned short>(packet[3] & 0xff);
	len <<= 8;
	len |= static_cast<unsigned short>(packet[4] & 0xff);

	vector<unsigned char> unpackedData;

	for (unsigned short i = 0; i < len; i++)
		unpackedData.push_back(packet[i + 5]);

	return unpackedData;
}