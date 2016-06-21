#include "Producer.h"
int fieldSize[4] = { 1,8,2,39 };

Producer::Producer()
	:fileBuffer(fieldSize, 4)
{
}

Producer::Producer(int _id)
	:id(_id), fileBuffer(fieldSize, 4)
{
	string filename(to_string(id));
	filename += ".txt";
	fileBuffer.Open((char*)filename.c_str());
}

Producer::Producer(const Producer& prod)
	:id(prod.id), fileBuffer(fieldSize, 4)
{
	string filename(to_string(id));
	filename += ".txt";
	fileBuffer.Open((char*)filename.c_str());
}

Producer::~Producer()
{
}

void Producer::addMessage(Message msg)
{
	fileBuffer.Insert(msg);
}

void Producer::Unpack(char * buffer)
{
	memcpy_s((void*)&id, sizeof(id), &buffer[0], sizeof(id));
}

void Producer::Pack(char * buffer)
{
	memcpy_s(&buffer[0], sizeof(id), (void*)&id, sizeof(id));
}

USHORT Producer::Key()
{
	return id;
}
