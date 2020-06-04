// HttpClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "json.h"
#include "HttpClient.h"

//回复处理回调函数
void handle_func(std::string rsp)
{
	// do sth according to rsp
	//std::cout << "http rsp1: " << rsp << std::endl;
}

int main()
{
	//GET请求例子
	//std::string url1 = "http://127.0.0.1:9000/api/exit";
	//HttpClient::SendReq(url1, handle_func);

	//POST Json例子
	std::string url2 = "http://127.0.0.1:9000/api/task/startTaskOrder";
	//std::string postJson =
	//	"{\"taskOrder\":\"11111111\","\
	//	"\"index\":1,"\
	//	"\"grade\":\"A\","\
	//	"\"outPutNo\":1,"\
	//	"\"pictureUrl\":\"E:\C++\http服务\HttpServer\HttpClient\1.jpg\","\
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

	//发送post，回复处理数据在指定的回调函数中执行
	HttpClient::SendPost(url2, "Content-Type: application/json; charset=utf-8\r\n", postJson, handle_func);

	system("pause");

    return 0;
}

