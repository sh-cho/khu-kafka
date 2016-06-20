#pragma once
#include <string>
using namespace std;

typedef unsigned short US;
class TopicHash
{
public:
	US topicId;
	string topicName;
	
	void Unpack(char* buffer);
	void Pack(char* buffer);
	US Key();


};

