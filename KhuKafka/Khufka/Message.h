/**
 *	Message
 */
#pragma once
#include <string>
#include <chrono>
using namespace std;

typedef unsigned short US;

struct Message
{
	US topic;
	chrono::system_clock::time_point timeStamp;
	string content;

	Message(int _topic, string _content);
	Message(char* buffer);
	~Message();
	void Unpack(char* buffer);
	void Pack(char* buffer);
	US Key();
};


/////////////////////////////////////////////////////////////////////////
inline Message::Message(int _topic, string _content)
	:topic(_topic), content(_content)
{
	//메시지 타임스탬프 초기화 -> 메시지 만들어진 시간
	timeStamp = std::chrono::system_clock::now();
}

inline Message::Message(char * buffer)
{
}

inline Message::~Message()
{
}

inline void Message::Unpack(char * buffer)
{
	buffer[0] = 0;
	memcpy_s(&buffer[1], sizeof(timeStamp), (void*)&timeStamp, sizeof(timeStamp));
	//chrono::system_clock::time_point* a = (chrono::system_clock::time_point*)&buffer[1];
	memcpy_s(&buffer[9], sizeof(topic), (void*)&topic, sizeof(topic));
	//unsigned short* b = (unsigned short*)&buffer[9];
	memcpy_s(&buffer[11],39, content.c_str(), 39);
	//char* c = (char*)&buffer[11];

	return;
}

inline void Message::Pack(char * buffer)
{
	buffer[0] = 0;
	memcpy_s(&buffer[1], sizeof(timeStamp), (void*)&timeStamp, sizeof(timeStamp));
	//chrono::system_clock::time_point* a = (chrono::system_clock::time_point*)&buffer[1];
	memcpy_s(&buffer[9], sizeof(topic), (void*)&topic, sizeof(topic));
	//unsigned short* b = (unsigned short*)&buffer[9];
	memcpy_s(&buffer[11], 39, content.c_str(), 39);
	//char* c = (char*)&buffer[11];

	return;
}


inline US Message::Key()
{
	return topic;
}
