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
	file.close();
	delete[] Buffer;
}

void FixedFileBuffer::Open(char * name,int mode)
{
	
	fstream out(name, ios::out | ios::app);
	out.close();

	if (mode == 0)
		file.open(name, ios::out | ios::in | ios::binary | ios::ate);
	else
		file.open(name, mode);

	file.clear();
}

int FixedFileBuffer::Update(T _item, int startPoint)
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

void FixedFileBuffer::Insert(T _item)
{
	///_item.Unpack(Buffer);
	_item.Pack(Buffer);	//성현
	file.write(Buffer, bufferSize);
	memset(Buffer, 0, bufferSize);
	return;
}

int FixedFileBuffer::get(T & _item, int startPoint, bool isGetAndDel)
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
