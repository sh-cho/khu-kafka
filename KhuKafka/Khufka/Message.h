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
	//�޽��� Ÿ�ӽ����� �ʱ�ȭ -> �޽��� ������� �ð�
	timeStamp = std::chrono::system_clock::now();
}

Message::~Message()
{
}