#pragma once
#include <vector>
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
	//vector<Consumer> consumerList;
	//topic hashtable

public:
	KafkaApp();
	~KafkaApp();

public:
	void run();
	void configuration();
	void produceMessage();

//static
public:
	/**
	*	비어있는거 -> ""
	*	Tombstone -> "R.I.P"
	*/
	static string hashTable[100];
	static int getAddrInHashTable(string key)
	{
		int arr = std::hash<std::string>{}(key);
		arr %= 100;

		if (hashTable[arr] == "")
			hashTable[arr] = key;

		return 0;
	}
};