#include <winsock2.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include "socket.h"
#pragma comment(lib, "WS2_32.lib")

int main()
try {
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;
    WSAStartup(MAKEWORD(2, 0), &WSAData);
    if ((server = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        throw std::runtime_error("socket " + std::to_string(WSAGetLastError()));
    }
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);
    if (connect(server, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        throw std::runtime_error("connect " +
            std::to_string(WSAGetLastError()));
    }
    std::cout << "connected to server" << std::endl
        << "enter \"exit\" to disconnect" << std::endl;

    Socket socket(&server);
    std::string str;
    while (true) {
        str = socket.get();
        if (str == "exit") {
            std::cout << "thank you for using client" << std::endl;
            break;
        }
        std::cout << str << std::endl;
        std::cin >> str;
        socket.set(str);
    }
    closesocket(server);
    WSACleanup();
}
catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
}
