#include "FixedFileBuffer.h"



FixedFileBuffer::FixedFileBuffer(int * _FieldSize, int _arrSize)
{
	bufferSize = 0;
	FieldSize = new int[_arrSize];
	for (int i = 0; i < _arrSize; i++)
	{
		FieldSize[i] = _FieldSize[i];
		bufferSize += _FieldSize[i];
	}
	Buffer = new char[bufferSize];
	memset(Buffer, 0, bufferSize);
}

FixedFileBuffer::~FixedFileBuffer()
{
}

void FixedFileBuffer::Open(char * name)
{
	file.open(name, ios::out | ios::in | ios::app | ios::binary);
}

void FixedFileBuffer::Insert(T _item)
{
	_item.Unpack(Buffer);
	file.write(Buffer, bufferSize);
	memset(Buffer, 0, bufferSize);
	return;
}

void FixedFileBuffer::get(T & _item)
{
	US key = _item.Key();

	file.seekg(ios::beg);
	while (1)
	{
		char* getBuffer;
		file.read(getBuffer,bufferSize);
		
		T item(getBuffer);

	}

	T.Pack(Buffer);
}
