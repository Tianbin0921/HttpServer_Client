// HttpServerThread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "HttpServerThread.h"
int main()
{
	CHttpServerThread httpserver;
	httpserver.StartThread();

	system("pause");

    return 0;
}

