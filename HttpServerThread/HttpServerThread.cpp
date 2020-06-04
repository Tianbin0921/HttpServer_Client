#include "HttpServerThread.h"
#include "json.h"
#include <iostream>

//string����תJson
bool StringToJson(std::string strIn, Json::Value &jsonOut)
{
	Json::Reader jreader;
	try
	{
		if (jreader.parse(strIn, jsonOut))
			return true;
	}
	catch (int errCode)
	{
		/*std::cout << "StringToJson() Error Code:" << errCode << std::endl;*/
		return false;
	}
	return false;
}

//Json����תstring
bool JsonToString(Json::Value jsonIn, std::string &strOut)
{
	Json::FastWriter writer_fast;
	try
	{
		strOut = writer_fast.write(jsonIn); //Ĭ��std::string��ֵ����Ϊ���
		return true;
	}
	catch (double err)
	{
		//std::cout << "JsonToString() Error Code:" << err << std::endl;
		return false;
	}
	return false;
}

CHttpServerThread::CHttpServerThread()
{
	if (m_pHttpServer)
	{
		m_pHttpServer = NULL;
	}
}

CHttpServerThread::~CHttpServerThread()
{
	if (m_pHttpServer)
	{
		delete m_pHttpServer;
		m_pHttpServer = NULL;
	}
}

bool CHttpServerThread::handle_taskRequest(std::string url, std::string body, mg_connection *c, OnRspCallback rsp_callback)
{
	Json::Value root;
	if (StringToJson(body, root))
	{
		//int size = root.size();//��������
		//for (int j = 0; j < size; j++)
		//{
		//	std::cout << root[j]["taskOrder"].asString() << endl;
		//}
		std::cout << root["taskOrder"].asString() << endl;
	}

	return true;
}

void CHttpServerThread::ThreadRun()
{
	int nPort = 9000;
	std::string strPort = std::to_string(nPort);

	m_pHttpServer = new HttpServer;
	if (m_pHttpServer)
	{
		m_pHttpServer->Init();
		m_pHttpServer->AddHandler("/api/task/startTaskOrder", handle_taskRequest);

		while (!m_pHttpServer->Start(strPort))
		{
			std::cout << "�˿� " << nPort << " ��ռ��" << std::endl;
			nPort++;
			std::cout << "ʹ�� " << nPort << " ����" << std::endl;
		}
	}
}