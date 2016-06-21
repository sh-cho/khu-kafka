#pragma once
#include <string>
using namespace std;

typedef unsigned short USHORT;
class TopicHash
{
public:
	USHORT topicId;
	string topicName;
	
	void Unpack(char* buffer);
	void Pack(char* buffer);
	USHORT Key();


};

