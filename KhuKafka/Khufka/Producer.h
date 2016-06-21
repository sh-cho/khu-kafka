#pragma once
#include <fstream>
#include "Message.h"
#include "FixedFileBuffer.h"
using namespace std;

class Producer
{
public:
	Producer();
	Producer(int _id);
	Producer(const Producer& prod);
	~Producer();

	int id;
	FixedFileBuffer<Message> fileBuffer;
	//fstream* file;

	void addMessage(Message msg);
	void Unpack(char* buffer);
	void Pack(char* buffer);
	USHORT Key();
	//unpack
	//key
};