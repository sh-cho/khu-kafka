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
	//Producer(const Producer& prod);
	~Producer();

	int id;
	FixedFileBuffer fileBuffer;
	//fstream* file;

	void addMessage(Message msg);
};

