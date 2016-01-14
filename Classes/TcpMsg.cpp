#include "TcpMsg.h"

std::mutex TcpMsg::mutex;

static TcpMsg _sharedContext;
TcpMsg* TcpMsg::shareTcpMsg()
{
	static bool s_bFirstUse = true;
	if (s_bFirstUse)
	{
		s_bFirstUse = false;
	}
	return &_sharedContext;
}

TcpMsg::TcpMsg() : m_isRuning(false), m_recvQueue(NULL), m_sendQueue(NULL)
{
	m_recvQueue = new Queue();
	m_sendQueue = new Queue();
}

TcpMsg::~TcpMsg()
{
	CC_SAFE_DELETE(m_recvQueue);
	CC_SAFE_DELETE(m_sendQueue);
}

void TcpMsg::tcp_start()
{
	m_isRuning = true;
	m_socket.Connect(SERVER_HOST, SERVER_PORT);

	std::thread tRecv(&TcpMsg::th_recv, this, this);
	std::thread tSend(&TcpMsg::th_send, this, this);
	tRecv.detach();
	tSend.detach();

	CCLOG("tcp_start");
}

void TcpMsg::tcp_stop()
{
	m_isRuning = false;
	CCLOG("tcp_stop");
}

bool TcpMsg::isRuning()
{
	return m_isRuning;
}

Pocket* TcpMsg::MakePocket(const char* msg, int msgid){
	Pocket* pk = new Pocket();

	pk->length = strlen(msg);
	pk->id = msgid;
	pk->version = 1;
	pk->msg = new char[pk->length];
	memset(pk->msg, 0, pk->length);
	memcpy(pk->msg, msg, pk->length);

	return pk;
};
Pocket* TcpMsg::MakePocketFromData(const char* data){
	Pocket* pk = new Pocket;
	return pk;
};

Queue* TcpMsg::getRecvQueue()
{
	return m_recvQueue;
}

Queue* TcpMsg::getSendQueue()
{
	return m_sendQueue;
}

void TcpMsg::pushSendQueue(std::string str, int msgid)
{
	Pocket* pk = TcpMsg::MakePocket(str.c_str(), msgid);
	if (m_sendQueue != NULL)
	{
		m_sendQueue->PushPocket(pk);
	}
	CCLOG("m_sendQueue have %d",m_sendQueue->getSize());
}

void TcpMsg::pushRecvQueue(std::string str)
{
	Pocket* pk = TcpMsg::MakePocket(str.c_str(), 101);
	if (m_recvQueue != NULL)
	{
		m_recvQueue->PushPocket(pk);
	}
	CCLOG("m_recvQueue have %d", m_sendQueue->getSize());
}

void TcpMsg::tcpCheck(void)
{
	if (!m_socket.Check())
	{
		CCLOG("Socket connection Error:%d", m_socket.GetError());
		
		//m_socket = NULL;

		bool status = false;
		while (!status)
		{
			if (m_socket.Connect(SERVER_HOST, SERVER_PORT))
			{
				status = true;
				CCLOG("Reconnection Success");
			}
			else
			{
				CCLOG("Reconnection Failure");
				return;
			}
		}
	}
}

//发送数据逻辑;
void TcpMsg::sendFunc(void)
{
	//网络检测;
	tcpCheck();
	if (m_sendQueue != NULL && m_sendQueue->getSize() > 0)
	{
		Pocket* pk = m_sendQueue->PullPocket();
		if (pk->id)
		{
			int s = m_socket.Send(pk->msg, pk->length, 0);
			CC_SAFE_DELETE(pk);
			CCLOG("sendFunc");
		}
	}
}

//接收数据逻辑;
void TcpMsg::recvFunc(void)
{
	CCLOG("recvFunc");

	//网络检测;
	tcpCheck();

	//取消息头,前面17个字节为消息头;
	//char recvHeadBuf[17] = "\0";
	//int recvLen = m_socket.Recv(recvHeadBuf, sizeof(recvHeadBuf), 0);
	//if (recvLen != 17 && recvLen != -1)
	//{
	//	while (recvLen < 17)
	//	{
	//		int tLen = m_socket.Recv(recvHeadBuf + recvLen, sizeof(recvHeadBuf - recvLen), 0);//一直读到把消息头接收完;
	//		if (tLen != -1)
	//		{
	//			recvLen += tLen;
	//		}
	//	}
	//}

	
	//if (recvLen != -1)
	//{
		//接收消息体;
		int readSize = 0; //当前读取消息的长度;
		std::string rec_msg;
		//如果消息体长度大于0;

		int msgLen = 10;
		if (msgLen > 0)
		{
			char* msgBody = new char[msgLen + 1];
			memset(msgBody, 0, msgLen + 1);
			//while (readSize < msgLen)
			//{
				int recvLen = m_socket.Recv(msgBody + readSize, msgLen - readSize, 0);//一直读到把消息体接收完;
				if (recvLen>0)
				{
					rec_msg.assign((const char *)msgBody, msgLen);
					CCLOG("RECV: %d,%s", msgLen, rec_msg.c_str());
					pushRecvQueue(rec_msg);//将消息添加到队列中;
				}
			//}
			CC_SAFE_DELETE_ARRAY(msgBody);

		}
	//}
}

void TcpMsg::th_send(TcpMsg* TcpMsg)
{
	CCLOG("th_send start");
	//TcpMsg* TcpMsg = ((TcpMsg*) r);
	while (TcpMsg->m_isRuning)
	{
		CCLOG("th_send");
		//TcpMsg::mutex.lock();
		TcpMsg->sendFunc();
		//TcpMsg::mutex.unlock();
#ifdef WIN32
		Sleep(SLEEP_TIME);
#else
		sleep(SLEEP_TIME / 1000.0f);
#endif
	}
	CCLOG("th_send end");
}

void TcpMsg::th_recv(TcpMsg* TcpMsg)
{
	CCLOG("th_recv start");
	//TcpMsg* TcpMsg = ((TcpMsg*) r);
	while (TcpMsg->m_isRuning)
	{
		CCLOG("th_recv");
		//TcpMsg::mutex.lock();
		TcpMsg->recvFunc();
		//TcpMsg::mutex.unlock();
#ifdef WIN32
		Sleep(SLEEP_TIME);
#else
		sleep(SLEEP_TIME / 1000.0f);
#endif
	}
	CCLOG("th_recv end");
}