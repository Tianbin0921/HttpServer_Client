// HttpClient.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "json.h"
#include "HttpClient.h"

//�ظ�����ص�����
void handle_func(std::string rsp)
{
	// do sth according to rsp
	//std::cout << "http rsp1: " << rsp << std::endl;
}

int main()
{
	//GET��������
	//std::string url1 = "http://127.0.0.1:9000/api/exit";
	//HttpClient::SendReq(url1, handle_func);

	//POST Json����
	std::string url2 = "http://127.0.0.1:9000/api/task/startTaskOrder";
	//std::string postJson =
	//	"{\"taskOrder\":\"11111111\","\
	//	"\"index\":1,"\
	//	"\"grade\":\"A\","\
	//	"\"outPutNo\":1,"\
	//	"\"pictureUrl\":\"E:\C++\http����\HttpServer\HttpClient\1.jpg\","\
	//	"\"inspectAmount\":1}";

	Json::Value root;
	root["taskOrder"] = "20200604001";
	root["index"] = 1;
	root["grade"] = "BX1";
	root["outPutNo"] = 1;
	root["pictureUrl"] = "D:\projects\tobacco\1.jpg";
	root["pictureUrl"] = "";
	root["inspectAmount"] = 1;

	std::string postJson = root.toStyledString();

	//����post���ظ�����������ָ���Ļص�������ִ��
	HttpClient::SendPost(url2, "Content-Type: application/json; charset=utf-8\r\n", postJson, handle_func);

	system("pause");

    return 0;
}

