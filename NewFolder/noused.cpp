#include<stdio.h>
#include<windows.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")

int main() 
{
	// ����Э��汾
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion != 2)) {
		printf("ȷ������Э��汾ʧ��:%d\n", GetLastError());
		system("pause");
		return -1;
	}
	printf("����Э��汾ȷ����\r\n");

	// ����socket
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == serverSocket) {
		printf("����Socketʧ��:%d\n", GetLastError());
		system("pause");
		return -1;
	}
	printf("Socket�����ɹ�\r\n!");
	//ȷ��������Э���ַ��
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(9527);
	//if (SOCKET_ERROR == serverSocket) {
	//	printf("������ַ��ʧ��:%d\n", GetLastError());
	//	system("pause");
	//	return -1;
	//}
	//printf("��ַ�ش����ɹ�\r\n!");


	//��
	int r = bind(serverSocket, (sockaddr*)&addr, sizeof addr);
	if (-1 == r) {
		printf("��ʧ��:%d\n", GetLastError());
		system("pause");
		return -1;
	}
	printf("�󶨳ɹ�\r\n!");

	//����
	r = listen(serverSocket, 10);
	if (-1 == r) {
		printf("����ʧ��:%d\n", GetLastError());
		system("pause");
		return -1;
	}
	printf("�����ɹ�\r\n!");

	//���ܿͻ�������
	SOCKET clientSocket = accept(serverSocket, (sockaddr*)NULL, NULL);
	if (-1 == r) {
		printf("����ʧ��:%d\n", GetLastError());
		system("pause");
		return -1;
	}
	printf("���ӳɹ�\r\n!");


	//ͨ��
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

