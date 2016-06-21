#pragma once
#include <iostream>
#include <vector>
#include "Message.h"
#include "FixedFileBuffer.h"
#include "Producer.h"
using namespace std;

/**
 *	Kafka Application Class
 *
 *	Coding Convention
 *	- camelCase
 */
class KafkaApp
{
	//FixedFileBuffer<Producer> prodBuffer;
	fstream prodList;
	//vector<Producer> producerList;
	
//Constructor, Destructor
public:
	KafkaApp();
	~KafkaApp();

//Method
public:
	void run();
	void addMessage();
	void requestMsgByTopic();
	vector<Message> requestMsgByTopic(int to);
	vector<Message> requestMsgByProdID(int prodID);
	void printRequestMsgByProdID();
	void recoveryCheck();	//producerList Ȯ�� �� ����

//static method
public:
	/**
	 *	����ִ°� -> ""
	 *	Tombstone -> "RIP"
	 */
	static int hashRecord[2];
	static FixedFileBuffer<TopicHash> hashBuffer;

	//static string hashTable[100];
	static int getAddrInHashTable(string key);
};