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
	Broker messageBroker;
	//vector<Consumer> consumerList;
	//topic hashtable

public:
	KafkaApp();
	~KafkaApp();

public:
	void run();
	void configuration();
};