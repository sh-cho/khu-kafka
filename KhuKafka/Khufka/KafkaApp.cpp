#include "KafkaApp.h"
#include <Windows.h>

///string KafkaApp::hashTable[100] = { "" };
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
	cout <<	getAddrInHashTable("���û") << endl;
	cout <<	getAddrInHashTable("���û") << endl;
	cout <<	getAddrInHashTable("������") << endl;

	////Information ��� (IP, ...)
		//Message a(5,"����������");
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

	int input;
	while (1)
	{
		system("cls");
		cout << "1. Producer: �޽��� �߰�" << endl;
		cout << "2. Consumer: �޽��� ��û(by Topic)" << endl;
		cout << "3. Consumer: �޽��� ��û(by ProudcerID)" << endl;
		cout << "4. HashTable Ȯ��" << endl;
		cout << "> ";
		cin >> input;

		switch (input)
		{
		case 1:
			addMessage();
			break;

		case 2:
			requestMsgByTopic();
			break;

		case 3:
			requestMsgByProdID();
			break;

		case 4:
			cout << "topic ���û: " << getAddrInHashTable("���û") << endl;
			cout << "topic ���û: " << getAddrInHashTable("���û") << endl;
			cout << "topic ������: " << getAddrInHashTable("������") << endl;
			break;

		default:
			cout << "�����մϴ�" << endl;
			return;
		}

		system("pause");
	}
}

void KafkaApp::addMessage()
{
	system("cls");

	//�޽��� ���� �Է�
	//---- ProducerID
	//- Timestamp
	//- topic
	//- content
	int prodID;
	chrono::system_clock::time_point timeStamp = chrono::system_clock::now();
	USHORT topicID;
	char topic[17];
	char content[39];
	memset(topic, 0, 17);
	memset(content, 0, 39);

	cout << "- ProducerID, Timestamp, Topic, Content" << endl;
	cout << "ProducerID: ";
	cin >> prodID;

	cout << "TimeStamp: ������" << endl;
	
	cout << "Topic: ";
	cin >> topic;

	cout << "Content: ";
	cin >> content;

	topicID = getAddrInHashTable(string(topic));	//�ؽ����̺� �߰�
	Message msg(topicID, content);


	//�޽��� �߰� ����
	//if Producer�� �������� ������
	//	Producer ���� �� �޽��� �߰�
	//else //producer ����
	//	Producer file�� append
	for (Producer& producer : producerList)
	{
		if (producer.id == prodID)
		{
			//producer�� �� �޽��� �߰�
			
		}
	}

	//not found
	Producer newprod(prodID);
	producerList.push_back(newprod);
}

void KafkaApp::requestMsgByTopic()
{
}

void KafkaApp::requestMsgByProdID()
{
}

int KafkaApp::getAddrInHashTable(string key)
{
	int arr = abs((int)std::hash<std::string>{}(key));
	arr %= 100;

	TopicHash getItem;
	getItem.topicId = arr;
	hashBuffer.get(getItem, 0, false);
	if (getItem.topicName == "")	//����� ��
	{
		///hashTable[arr] = key;

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

			getItem.topicId = curr;
			hashBuffer.get(getItem, 0, false);

			if (getItem.topicName == "")
			{
				///hashTable[curr] = key;

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