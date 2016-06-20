#pragma once
#include <fstream>
#include <memory>
#include "Message.h"
#include "TopicHash.h"


#define T TopicHash

class FixedFileBuffer
{
public:
	FixedFileBuffer(int* _FieldSize, int _arrSize);
	~FixedFileBuffer();
	int bufferSize;
	char* Buffer;
	int* FieldSize;

	std::fstream file;
	
	void Open(char* name,int mode = 0);
	int Update(T _item, int startPoint = 0);
	void Insert(T _item);
	//bool get(T& _item);
	int get(T& _item,int startPoint = 0);

};

