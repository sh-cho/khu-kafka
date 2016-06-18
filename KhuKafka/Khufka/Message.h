/**
 *	Message
 */
#pragma once
#include <string>
#include <chrono>
using namespace std;

struct Message
{
	unsigned short topic;
	chrono::system_clock::time_point timeStamp;
	string content;

	Message(int _topic, string _content);
	~Message();
};


/////////////////////////////////////////////////////////////////////////
Message::Message(int _topic, string _content)
	:topic(_topic), content(_content)
{
	//메시지 타임스탬프 초기화 -> 메시지 만들어진 시간
	timeStamp = std::chrono::system_clock::now();
}

Message::~Message()
{
}