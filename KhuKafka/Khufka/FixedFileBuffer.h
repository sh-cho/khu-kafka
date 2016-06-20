#pragma once
#include <fstream>
#include "Message.h"

#define T Message
class FixedFileBuffer
{
public:
	FixedFileBuffer(int* _FieldSize, int _arrSize);
	~FixedFileBuffer();
	int bufferSize;
	char* Buffer;
	int* FieldSize;

	std::fstream file;
	
	void Open(char* name);

	void Insert(T _item);
	void get(T& _item);

};

