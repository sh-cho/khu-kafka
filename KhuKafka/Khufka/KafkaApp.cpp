#include "KafkaApp.h"
#include <Windows.h>

///string KafkaApp::hashTable[100] = { "" };
int KafkaApp::hashRecord[2] = { 2,18 };
FixedFileBuffer<TopicHash> KafkaApp::hashBuffer(hashRecord, 2);
int prodFieldSize[1] = {2};

////////////////////////////////////////////////////////////////////
// Private member function


////////////////////////////////////////////////////////////////////
// Constructor, Destructor
KafkaApp::KafkaApp()
	//:prodBuffer(prodFieldSize, 1)
{
	hashBuffer.Open("TopicTable.hash", ios::out | ios::in | ios::binary);
	//prodBuffer.Open("ProducerList.bin", ios::out | ios::in | ios::binary);
	prodList.open("ProducerList.txt", ios::in);

	recoveryCheck();
}

KafkaApp::~KafkaApp()
{
}


////////////////////////////////////////////////////////////////////
// Method
void KafkaApp::run()
{
	cout <<	getAddrInHashTable("기상청") << endl;
	cout <<	getAddrInHashTable("통계청") << endl;
	cout <<	getAddrInHashTable("국정원") << endl;

	////Information 출력 (IP, ...)
		//Message a(5,"ㅁㅁㅁㅁㅁ");
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
		cout << "1. Producer: 메시지 추가" << endl;
		cout << "2. Consumer: 메시지 요청(by Topic)" << endl;
		cout << "3. Consumer: 메시지 요청(by ProudcerID)" << endl;
		cout << "4. HashTable 확인" << endl;
		cout << "5. Kafka 종료" << endl;
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
			printRequestMsgByProdID();
			break;

		case 4:
			cout << "topic 기상청: " << getAddrInHashTable("기상청") << endl;
			cout << "topic 통계청: " << getAddrInHashTable("통계청") << endl;
			cout << "topic 국정원: " << getAddrInHashTable("국정원") << endl;
			break;

		case 5:
			cout << "Exit" << endl;
			exit(1);

		default:
			//cout << "종료합니다" << endl;
			continue;
		}

		system("pause");
	}
}

void KafkaApp::addMessage()
{
	system("cls");

	//메시지 정보 입력
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

	cout << "TimeStamp: 생성됨" << endl;
	
	cout << "Topic: ";
	cin >> topic;

	cout << "Content: ";
	cin >> content;

	topicID = getAddrInHashTable(string(topic));	//해시테이블 추가
	Message msg(topicID, content);

	prodList.seekg(ios::beg);
	while (!prodList.eof())
	{
		int id;
		prodList >> id;

		if (id == prodID)
		{
			Producer pro(id);
			pro.addMessage(msg);
			return;
		}

	}

	prodList.close();
	fstream savePro;
	savePro.open("ProducerList.txt", ios::out | ios::app);
	savePro << '\t' << prodID;
	Producer pro(prodID);
	pro.addMessage(msg);

	prodList.open("ProducerList.txt", ios::in);
	//메시지 추가 로직
	//if Producer가 존재하지 않으면
	//	Producer 생성 뒤 메시지 추가
	//else //producer 존재
	//	Producer file에 append
	//
	//for (Producer& producer : producerList)
	//{
	//	if (producer.id == prodID)
	//	{
	//		//producer에 새 메시지 추가
	//		producer.addMessage(msg);
	//		return;
	//	}
	//}

	//while (1)
	//{
	//	Producer prod;
	//	if (prodBuffer.Read(prod) != -1)	//read==-1 -> eof
	//	{
	//		
	//	}
	//}

	////not found
	////Producer newprod(prodID);
	//producerList.push_back(Producer(prodID));
	//
	////메시지추가
	//producerList[producerList.size() - 1].addMessage(msg);


}

void KafkaApp::requestMsgByTopic()
{
	system("cls");

	string topic;
	//memset(topic, 0, 17);

	cout << "Find topic: ";
	cin >> topic;

	int topicID = getAddrInHashTable(topic);

	vector<Message> messageVec = requestMsgByTopic(topicID);

	for (auto i : messageVec)
	{
		cout << i.topic << ":" << i.content << ":" << i.content << endl;
	}
}

vector<Message> KafkaApp::requestMsgByTopic(int to)
{
	//이거 반복
	
	vector<Message> messageVec;
	Message getMessage;
	while (!prodList.eof())
	{
		int id;
		prodList >> id;
		Producer pro(id);
		getMessage.topic = to;
		int startPos = 0;
		while (startPos = pro.fileBuffer.get(getMessage, startPos))
		{
			if (startPos == -1)
				break;
			else
			{
				messageVec.push_back(getMessage);
			}
		}
		
	}

	return messageVec;
	
}

void KafkaApp::printRequestMsgByProdID()
{
	system("cls");

	int prodID;

	cout << "Find Producer ID: ";
	cin >> prodID;

	vector<Message> messageVec = requestMsgByProdID(prodID);

	for (auto i : messageVec)
	{
		cout << i.topic << ":" << i.content << ":" << i.content << endl;
	}
	

}

vector<Message> KafkaApp::requestMsgByProdID(int prodID)
{
		
	vector<Message> messageVec;
	Message getMessage;


	Producer pro(prodID);
	int startPos = 0;
	while (startPos = pro.fileBuffer.Read(getMessage, startPos))
	{
		if (startPos == -1)
			break;
		else
		{
			messageVec.push_back(getMessage);
		}
	}

	return messageVec;
}


void KafkaApp::recoveryCheck()
{
	//
}

int KafkaApp::getAddrInHashTable(string key)
{
	int arr = abs((int)std::hash<std::string>{}(key));
	arr %= 100;

	TopicHash getItem;
	getItem.topicId = arr;
	hashBuffer.get(getItem, 0, false);
	if (getItem.topicName == "")	//비었을 때
	{
		///hashTable[arr] = key;

		TopicHash th;
		th.topicId = arr  +1 ;
		th.topicName = key;

		hashBuffer.Update(th);
		return arr + 1;
	}
	else
	{
		int curr = (arr + 1) % 100;
		while (1)
		{
			//한바퀴 다 돌았을 때
			if (arr == curr)
				return -1;

			getItem.topicId = curr;
			hashBuffer.get(getItem, 0, false);

			if (getItem.topicName == "")
			{
				///hashTable[curr] = key;

				TopicHash th;
				th.topicId = curr + 1;
				th.topicName = key;

				hashBuffer.Update(th);

				return curr + 1;
			}

			curr = ((curr + 1) % 100);
		}
	}

	return -1;
}