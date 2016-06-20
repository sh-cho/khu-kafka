#include "KafkaApp.h"

string KafkaApp::hashTable[100] = { "" };
int KafkaApp::hashRecord[2] = { 2,18 };
FixedFileBuffer KafkaApp::hashBuffer(hashRecord, 2);

////////////////////////////////////////////////////////////////////
// Private member function


////////////////////////////////////////////////////////////////////
// Constructor, Destructor
KafkaApp::KafkaApp()
{
	hashBuffer.Open("TopicTable.hash", ios::out | ios::in | ios::binary);


	
}

KafkaApp::~KafkaApp()
{
}


////////////////////////////////////////////////////////////////////
// Method
void KafkaApp::run()
{
	cout <<	getAddrInHashTable("���û") << endl ;
	cout <<	getAddrInHashTable("���û") << endl ;
	cout <<	getAddrInHashTable("������") << endl ;
	cout << getAddrInHashTable("��Ƽ��") << endl;

	////Information ��� (IP, ...)
		//Message a(5,"�ƾ��� ������ ��¥");
		//int aaa[4] = { 1,8,2,39 };
		//FixedFileBuffer b(aaa,4);
		//b.Open("5.txt");
		//b.Insert(a);
		//b.Insert(a);
		//b.Insert(a);
		//b.Insert(a);
		//b.Insert(a);
		//b.Insert(a);
		//Message te;
		//te.topic = 5;
		//int count = b.get(te);
		//count = b.get(te, count);

		//return;
		//;	//busy waiting

	//int input;
	//while (1)
	//{
	//	//system("cls");
	//	cout << "1. Producer: �޽��� �߰�" << endl;
	//	cout << "2. Consumer: �޽��� ��û(by Topic)" << endl;
	//	cout << "3. Consumer: �޽��� ��û(by ProudcerID)" << endl;
	//	cin >> input;

	//	switch (input)
	//	{
	//	case 1:
	//		break;

	//	case 2:
	//		break;

	//	case 3:
	//		break;

	//	default:
	//		cout << "�����մϴ�" << endl;
	//		return;
	//	}
	//}
}

int KafkaApp::getAddrInHashTable(string key)
{
	int arr = abs((int)std::hash<std::string>{}(key));
	arr %= 100;

	if (hashTable[arr] == "")
	{
		hashTable[arr] = key;

		TopicHash th;
		th.topicId = arr;
		th.topicName = key;

		hashBuffer.Update(th);
		return arr;
	}
	else
	{
		int curr = (arr + 1) % 100;
		while (1)
		{
			//�ѹ��� �� ������ ��
			if (arr == curr)
				return -1;


			if (hashTable[curr] == "")
			{
				hashTable[curr] = key;

				TopicHash th;
				th.topicId = curr;
				th.topicName = key;

				hashBuffer.Update(th);

				return curr;
			}

			curr = ((curr + 1) % 100);
		}
	}

	return -1;
}