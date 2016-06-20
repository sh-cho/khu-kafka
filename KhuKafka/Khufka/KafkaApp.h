#pragma once
#include <iostream>
#include <vector>
#include "Message.h"
#include "FixedFileBuffer.h"
class Producer;
class Broker;
class Consumer;
using namespace std;

/**
 *	Kafka Application Class
 *
 *	Coding Convention
 *	- camelCase
 */
class KafkaApp
{
	//vector<Producer> producerList;
	//Broker messageBroker;

//Constructor, Destructor
public:
	KafkaApp();
	~KafkaApp();

//Method
public:
	void run();
	

//static method
public:
	/**
	 *	비어있는거 -> ""
	 *	Tombstone -> "RIP"
	 */

	static int hashRecord[2];
	static FixedFileBuffer hashBuffer;

	static string hashTable[100];
	static int getAddrInHashTable(string key);
};