#pragma once
#ifndef __HTTP_SERVER_THREAD_H_
#define __HTTP_SERVER_THREAD_H_
#include "HttpServer.h"
#include "T_Thread.h"

class CHttpServerThread :public T_Thread
{
public:
	CHttpServerThread();
	~CHttpServerThread();

	void ThreadRun();

protected:
	static bool handle_taskRequest(std::string url, std::string body, mg_connection *c, OnRspCallback rsp_callback);
private:
	HttpServer * m_pHttpServer;
};

#endif