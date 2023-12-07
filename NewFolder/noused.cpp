#include<stdio.h>
#include<windows.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")

int main() 
{
	// 网络协议版本
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion != 2)) {
		printf("确定网络协议版本失败:%d\n", GetLastError());
		system("pause");
		return -1;
	}
	printf("网络协议版本确定！\r\n");

	// 创建socket
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == serverSocket) {
		printf("创建Socket失败:%d\n", GetLastError());
		system("pause");
		return -1;
	}
	printf("Socket创建成功\r\n!");
	//确定服务器协议地址簇
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(9527);
	//if (SOCKET_ERROR == serverSocket) {
	//	printf("创建地址簇失败:%d\n", GetLastError());
	//	system("pause");
	//	return -1;
	//}
	//printf("地址簇创建成功\r\n!");


	//绑定
	int r = bind(serverSocket, (sockaddr*)&addr, sizeof addr);
	if (-1 == r) {
		printf("绑定失败:%d\n", GetLastError());
		system("pause");
		return -1;
	}
	printf("绑定成功\r\n!");

	//监听
	r = listen(serverSocket, 10);
	if (-1 == r) {
		printf("监听失败:%d\n", GetLastError());
		system("pause");
		return -1;
	}
	printf("监听成功\r\n!");

	//接受客户端连接
	SOCKET clientSocket = accept(serverSocket, (sockaddr*)NULL, NULL);
	if (-1 == r) {
		printf("连接失败:%d\n", GetLastError());
		system("pause");
		return -1;
	}
	printf("连接成功\r\n!");


	//通信
	char buff[56];
	while (1) {
		r = recv(clientSocket, buff, 55, NULL);
		if (r > 0) {
			buff[r] = 0;
			printf(">>%s\r\n", buff);
		}
	}
	//Clear
	closesocket(serverSocket);
	WSACleanup();

	while (1);
	return 0;
}

