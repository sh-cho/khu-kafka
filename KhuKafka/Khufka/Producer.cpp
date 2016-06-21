#include "Producer.h"
int fieldSize[4] = { 1,8,2,39 };

Producer::Producer()
	:fileBuffer(fieldSize, 4)
{
}

Producer::Producer(int _id)
	:id(_id), fileBuffer(fieldSize, 4)
{
}

//Producer::Producer(const Producer& prod)
//{
//}

Producer::~Producer()
{
}

void Producer::addMessage(Message msg)
{
}

