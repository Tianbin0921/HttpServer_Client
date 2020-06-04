// HttpClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "HttpClient.h"

// 初始化client静态变量
int HttpClient::client_exit_flag = 0;
ReqCallback HttpClient::s_req_callback;

//客户端的网络请求响应
void HttpClient::OnHttpEvent(mg_connection *connection, int event_type, void *event_data)
{
	http_message *hm = (struct http_message *)event_data;
	int connect_status;

	//事件类型
	switch (event_type)
	{
	//建立连接
	case MG_EV_CONNECT:
		connect_status = *(int *)event_data;
		if (connect_status != 0)
		{
			printf("Error connecting to server, error code: %d\n", connect_status);
			client_exit_flag = 1;
		}
		break;

	//收到回复
	case MG_EV_HTTP_REPLY:
		{
			printf("Got reply:\n%.*s\n", (int)hm->body.len, hm->body.p);
			std::string rsp = std::string(hm->body.p, hm->body.len);
			connection->flags |= MG_F_SEND_AND_CLOSE;
			client_exit_flag = 1; // 每次收到请求后关闭本次连接，重置标记

			//回调处理回复
			s_req_callback(rsp);
		}
		break;

	//断开连接
	case MG_EV_CLOSE:
		if (client_exit_flag == 0)
		{
			printf("Caution: Server closed connection\n");
			client_exit_flag = 1;
		};
		break;
	default:
		break;
	}
}


//发送一次请求，设置回复处理回调,修改 s_exit_flag=1 来关闭连接
void HttpClient::SendReq(const std::string &url, ReqCallback req_callback)
{
	// 给回调函数赋值
	s_req_callback = req_callback;
	mg_mgr mgr;
	mg_mgr_init(&mgr, NULL);
	auto connection = mg_connect_http(&mgr, OnHttpEvent, url.c_str(), NULL, NULL);
	mg_set_protocol_http_websocket(connection);
	printf("Send http request:\n%s\n", url.c_str());

	// loop
	while (client_exit_flag == 0)
	{
		mg_mgr_poll(&mgr, 500); //500ms超时时间，视情况使用超时
	}
	mg_mgr_free(&mgr);
}

//Post请求
void HttpClient::SendPost(const std::string &url, std::string CONTENTTYPE, std::string params, ReqCallback req_callback) 
{
	s_req_callback = req_callback;
	mg_mgr mgr;
	mg_mgr_init(&mgr, NULL);
	auto connection = mg_connect_http(&mgr, OnHttpEvent, url.c_str(), CONTENTTYPE.c_str(), params.c_str());
	mg_set_protocol_http_websocket(connection);
	printf("Send http post:\n%s\n", url.c_str());

	//connection->


	//循环获取事件响应
	while (client_exit_flag == 0)
	{
		mg_mgr_poll(&mgr, 500);
		//client_exit_flag = 0;
	}
	mg_mgr_free(&mgr);
}


