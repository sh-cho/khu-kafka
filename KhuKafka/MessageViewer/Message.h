/**
 *	Message
 */
#pragma once
#include <string>
#include <chrono>
using namespace std;

typedef unsigned short USHORT;

struct Message
{
	USHORT topic;
	chrono::system_clock::time_point timeStamp;
	string content;

	Message(USHORT _topic = 0, string _content = "");
	Message(char* buffer);
	~Message();
	void Unpack(char* buffer);
	void Pack(char* buffer);
	USHORT Key();
};


/////////////////////////////////////////////////////////////////////////
inline Message::Message(USHORT _topic, string _content)
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
	//buffer[0] = 0;
	memcpy_s((void*)&timeStamp, sizeof(timeStamp), &buffer[1], sizeof(timeStamp));
	//chrono::system_clock::time_point* a = (chrono::system_clock::time_point*)&buffer[1];
	memcpy_s((void*)&topic, sizeof(topic), &buffer[9], sizeof(topic));
	//unsigned short* b = (unsigned short*)&buffer[9];
	char con[39];
	memcpy_s(con, 39, &buffer[11], 39);
	content = string(con);
	//char* c = (char*)&buffer[11];
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


inline USHORT Message::Key()
{
	return topic;
}
