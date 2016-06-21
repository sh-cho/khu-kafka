#pragma once
#include <fstream>
#include <memory>
#include "Message.h"
#include "TopicHash.h"


//#define T TopicHash
template <typename T>
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
	int Read(T& _item, int startPoint = 0, bool isGetAndDel = true);
	int get(T& _item,int startPoint = 0, bool isGetAndDel = true);

};

///////////////////////////////////////////////////////////////////////////
template <typename T>
FixedFileBuffer<T>::FixedFileBuffer(int * _FieldSize, int _arrSize)
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

template <typename T>
FixedFileBuffer<T>::~FixedFileBuffer()
{
	file.close();
	delete[] Buffer;
}

template <typename T>
void FixedFileBuffer<T>::Open(char * name, int mode)
{

	fstream out(name, ios::out | ios::app);
	out.close();

	if (mode == 0)
		file.open(name, ios::out | ios::in | ios::binary | ios::ate);
	else
		file.open(name, mode);

	file.clear();
}

template <typename T>
int FixedFileBuffer<T>::Update(T _item, int startPoint)
{
	file.clear();

	int count = 0;
	USHORT key = _item.Key();

	//무조건 첫번째거 get ?
	if (startPoint == 0)
	{
		file.seekg(ios::beg);
		file.seekp(ios::beg);
	}
	else
	{
		file.seekg(startPoint, ios::beg);
		file.seekp(startPoint, ios::beg);
	}

	while (!file.eof())
	{
		count += bufferSize;
		char* getBuffer;
		getBuffer = new char[bufferSize];
		memset(getBuffer, 0, bufferSize);
		file.read(getBuffer, bufferSize);

		if (getBuffer[0] == true)	//isDeleted
		{
			delete[] getBuffer;
			continue;
		}
		T item;
		item.Unpack(getBuffer);

		if (item.Key() == key)
		{
			_item.Pack(Buffer);
			//char isd[1];
			//isd[0] = '1';
			char isd = 1;
			file.seekg(-bufferSize + 1, ios::cur);
			file.write(Buffer, bufferSize);

			delete[] getBuffer;
			return count;
		}

		delete[] getBuffer;

	}
	return -1;

}

template <typename T>
void FixedFileBuffer<T>::Insert(T _item)
{
	///_item.Unpack(Buffer);
	_item.Pack(Buffer);	//성현
	file.write(Buffer, bufferSize);
	memset(Buffer, 0, bufferSize);
	return;
}

template<typename T>
inline int FixedFileBuffer<T>::Read(T& _item, int startPoint, bool isGetAndDel)
{

	file.clear();

	int count = startPoint;

	//무조건 첫번째거 get ?
	if (startPoint == 0)
	{
		file.seekg(ios::beg);
		file.seekp(ios::beg);
	}
	else
	{
		file.seekg(startPoint, ios::beg);
		file.seekp(startPoint, ios::beg);
	}

	while (!file.eof())
	{
		count += bufferSize;
		char* getBuffer;
		getBuffer = new char[bufferSize];
		memset(getBuffer, 0, bufferSize);
		file.read(getBuffer, bufferSize);

		if (getBuffer[0] == true)	//isDeleted
		{
			delete[] getBuffer;
			continue;
		}
		T item;
		item.Unpack(getBuffer);

		
		if (item.Key() != 0)
		{
			_item = item;

			//char isd[1];
			//isd[0] = '1';
			if (isGetAndDel)
			{
				char isd = 1;
				file.seekg(-bufferSize, ios::cur);
				file.write(&isd, 1);
			}

			delete[] getBuffer;
			return count;
		}

		delete[] getBuffer;

	}

	return -1;


	////file curr is end
	//if ((int)file.tellg() == ios::end || !file.good())
	//{
	//	return -1;
	//}

	//if (startPoint != 0)
	//	file.seekg(startPoint, ios::beg);
	//else
	//	file.seekg(ios::beg);

	//file.read((char*)&Buffer, bufferSize);
	//_item.Unpack(Buffer);

	///*if (isGetAndDel)
	//{
	//	char isd = 1;
	//	file.seekg(-bufferSize, ios::cur);
	//	file.write(&isd, 1);
	//}*/

	//return (startPoint + bufferSize);
}

template <typename T>
int FixedFileBuffer<T>::get(T & _item, int startPoint, bool isGetAndDel)
{
	file.clear();

	int count = startPoint;
	USHORT key = _item.Key();

	//무조건 첫번째거 get ?
	if (startPoint == 0)
	{
		file.seekg(ios::beg);
		file.seekp(ios::beg);
	}
	else
	{
		file.seekg(startPoint, ios::beg);
		file.seekp(startPoint, ios::beg);
	}

	while (!file.eof())
	{
		count += bufferSize;
		char* getBuffer;
		getBuffer = new char[bufferSize];
		memset(getBuffer, 0, bufferSize);
		file.read(getBuffer, bufferSize);

		if (getBuffer[0] == true)	//isDeleted
		{
			delete[] getBuffer;
			continue;
		}
		T item;
		item.Unpack(getBuffer);

		if (item.Key() == key)
		{

			_item = item;

			//char isd[1];
			//isd[0] = '1';
			if (isGetAndDel)
			{
				char isd = 1;
				file.seekg(-bufferSize, ios::cur);
				file.write(&isd, 1);
			}

			delete[] getBuffer;
			return count;
		}

		delete[] getBuffer;

	}

	return -1;
}