#pragma once
#include <string>
#include <functional>
#include "mongoose.h"

// �˴�������function�࣬typedef�ٺ��溯��ָ�븳ֵ��Ч
using ReqCallback = std::function<void(std::string)>;

class HttpClient
{
public:
	HttpClient() {}
	~HttpClient() {}

	static void SendReq(const std::string &url, ReqCallback req_callback);
	static void SendPost(const std::string &url, std::string CONTENTTYPE, std::string params, ReqCallback req_callback);
	static void OnHttpEvent(mg_connection *connection, int event_type, void *event_data);
	static int client_exit_flag;
	static ReqCallback s_req_callback;
};

