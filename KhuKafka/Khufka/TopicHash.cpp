#include "TopicHash.h"


void TopicHash::Unpack(char * buffer)
{
//	buffer[0] = 0;
	//chrono::system_clock::time_point* a = (chrono::system_clock::time_point*)&buffer[1];
	memcpy_s((void*)&topicId, sizeof(topicId), &buffer[1], sizeof(topicId));
	//unsigned short* b = (unsigned short*)&buffer[9];
	char con[17];
	memcpy_s(con, 17, &buffer[3], 17);
	topicName = string(con);
}

void TopicHash::Pack(char * buffer)
{
	buffer[0] = 0;
	
	memcpy_s(&buffer[1], sizeof(topicId), (void*)&topicId, sizeof(topicId));

	memcpy_s(&buffer[3], 17, topicName.c_str(), 17);

}

USHORT TopicHash::Key()
{
	return topicId;
}
