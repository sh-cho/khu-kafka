#include "KafkaApp.h"

string KafkaApp::hashTable[100] = { "" };


////////////////////////////////////////////////////////////////////
// Private member function


////////////////////////////////////////////////////////////////////
// Constructor, Destructor
KafkaApp::KafkaApp()
{

}

KafkaApp::~KafkaApp()
{
}


////////////////////////////////////////////////////////////////////
// Method
void KafkaApp::run()
{
	//Information ��� (IP, ...)

	
		Message a(5,"�ƾ��� ������ ��¥");
		int aaa[4] = { 1,8,2,39 };
		FixedFileBuffer b(aaa,4);
		b.Open("5.txt");
		b.Insert(a);
		;	//busy waiting
	
}
