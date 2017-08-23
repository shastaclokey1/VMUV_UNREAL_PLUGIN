// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#ifndef CLIENT_H
#define CLIENT_H


#include "CoreMinimal.h"
#include "SocketWrapper.h"


/**
 * 
 */
class VMUV_PLUGIN_API client
{
public:
	static void service();



private:
	static socketWrapper swClient;
};


#endif //CLIENT_H