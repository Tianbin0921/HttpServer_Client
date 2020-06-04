// HttpClient.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "HttpClient.h"

// ��ʼ��client��̬����
int HttpClient::client_exit_flag = 0;
ReqCallback HttpClient::s_req_callback;

//�ͻ��˵�����������Ӧ
void HttpClient::OnHttpEvent(mg_connection *connection, int event_type, void *event_data)
{
	http_message *hm = (struct http_message *)event_data;
	int connect_status;

	//�¼�����
	switch (event_type)
	{
	//��������
	case MG_EV_CONNECT:
		connect_status = *(int *)event_data;
		if (connect_status != 0)
		{
			printf("Error connecting to server, error code: %d\n", connect_status);
			client_exit_flag = 1;
		}
		break;

	//�յ��ظ�
	case MG_EV_HTTP_REPLY:
		{
			printf("Got reply:\n%.*s\n", (int)hm->body.len, hm->body.p);
			std::string rsp = std::string(hm->body.p, hm->body.len);
			connection->flags |= MG_F_SEND_AND_CLOSE;
			client_exit_flag = 1; // ÿ���յ������رձ������ӣ����ñ��

			//�ص�����ظ�
			s_req_callback(rsp);
		}
		break;

	//�Ͽ�����
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


//����һ���������ûظ�����ص�,�޸� s_exit_flag=1 ���ر�����
void HttpClient::SendReq(const std::string &url, ReqCallback req_callback)
{
	// ���ص�������ֵ
	s_req_callback = req_callback;
	mg_mgr mgr;
	mg_mgr_init(&mgr, NULL);
	auto connection = mg_connect_http(&mgr, OnHttpEvent, url.c_str(), NULL, NULL);
	mg_set_protocol_http_websocket(connection);
	printf("Send http request:\n%s\n", url.c_str());

	// loop
	while (client_exit_flag == 0)
	{
		mg_mgr_poll(&mgr, 500); //500ms��ʱʱ�䣬�����ʹ�ó�ʱ
	}
	mg_mgr_free(&mgr);
}

//Post����
void HttpClient::SendPost(const std::string &url, std::string CONTENTTYPE, std::string params, ReqCallback req_callback) 
{
	s_req_callback = req_callback;
	mg_mgr mgr;
	mg_mgr_init(&mgr, NULL);
	auto connection = mg_connect_http(&mgr, OnHttpEvent, url.c_str(), CONTENTTYPE.c_str(), params.c_str());
	mg_set_protocol_http_websocket(connection);
	printf("Send http post:\n%s\n", url.c_str());

	//connection->


	//ѭ����ȡ�¼���Ӧ
	while (client_exit_flag == 0)
	{
		mg_mgr_poll(&mgr, 500);
		//client_exit_flag = 0;
	}
	mg_mgr_free(&mgr);
}


