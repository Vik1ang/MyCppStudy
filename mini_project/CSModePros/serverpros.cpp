#include <iostream>
#include <string>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
	WSADATA wsa_data;
	WORD lib_version = MAKEWORD(2, 2);

	// 初始化
	if (WSAStartup(lib_version, &wsa_data) != 0)
	{
		std::cout << "Init Operating error\n";
		return EXIT_FAILURE;
	}
	if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 2)
	{
		WSACleanup();
		std::cout << "Cannot find valid lib.\n";
	}

	// 创建套接字
	SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == INVALID_SOCKET)
	{
		std::cout << "套接字创建失败\n";
		WSACleanup();
		return EXIT_FAILURE;
	}

	// 绑定套接字
	sockaddr_in sock_address;
	sock_address.sin_family = AF_INET;
	sock_address.sin_port = htons(1234);
	sock_address.sin_addr.S_un.S_addr = ADDR_ANY;

	if (bind(server_socket, (sockaddr*)&sock_address, sizeof(sock_address)) == SOCKET_ERROR)
	{
		std::cout << "绑定失败\n";
		closesocket(server_socket);
		WSACleanup();
		return EXIT_FAILURE;
	}

	// 监听操作
	if (listen(server_socket, 30) == SOCKET_ERROR)
	{
		std::cout << "监听失败\n";
		WSACleanup();
		closesocket(server_socket);
		return EXIT_FAILURE;
	}

	// 进入监听状态
	SOCKET client_socket;
	sockaddr_in client_sin;
	bool flags = false; // 标志是否有客户端连接

	while (true)
	{
		if (!flags)
		{
			std::cout << "\n服务端已启动，等待客户端连接 ...... \n";
		}
		int len = sizeof(client_sin);
		client_socket = accept(server_socket, (sockaddr*)&client_sin, &len);
		if (client_socket == INVALID_SOCKET)
		{
			flags = true;
			std::cout << "accept error.\n";
			closesocket(server_socket);
			closesocket(client_socket);
			WSACleanup();
			return EXIT_FAILURE;
		}

		if (!flags)
		{
			std::cout << "服务器收到了一个客户端连接:" << inet_ntoa(client_sin.sin_addr) << std::endl;
			flags = false;
		}

		// 接收数据信息
		char r_msg[512];
		memset(r_msg, 0, 512);
		int recv_msg_len = recv(client_socket, r_msg, sizeof(r_msg), 0);
		if (recv_msg_len)
		{
			std::cout << "\n已收到客户端消息:" << r_msg << std::endl;
		}

		std::string sendMsg;
		std::cout << "\n请输入要发送的消息:" << std::endl;
		std::getline(std::cin, sendMsg);
		send(client_socket, sendMsg.c_str(), strlen(sendMsg.c_str()), 0);

		closesocket(client_socket);
	}

	closesocket(server_socket);
	WSACleanup();

	return EXIT_SUCCESS;
}