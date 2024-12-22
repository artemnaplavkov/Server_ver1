#include <winsock2.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include "menu.h"
#include "socket.h"
#pragma comment(lib, "WS2_32.lib")

int main()
try {
    WSADATA WSAData;
    SOCKET server, client;  // sockets
    SOCKADDR_IN serverAddr, clientAddr;
    WSAStartup(MAKEWORD(2, 0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);  // create server
    if (server == INVALID_SOCKET) {
        throw std::runtime_error("socket " + std::to_string(WSAGetLastError()));
    }
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);
    if (bind(server, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) ==
        SOCKET_ERROR) {
        throw std::runtime_error("bind " + std::to_string(WSAGetLastError()));
    }
    if (listen(server, 0) == SOCKET_ERROR) {
        throw std::runtime_error("listen " + std::to_string(WSAGetLastError()));
    }
    std::cout << "listening for incoming connections...." << std::endl;
    int clientAddrSize = sizeof(clientAddr);
    if ((client = accept(server, (SOCKADDR*)&clientAddr, &clientAddrSize)) ==
        INVALID_SOCKET) {
        throw std::runtime_error("accept " + std::to_string(WSAGetLastError()));
    }
    std::cout << "client connected" << std::endl;

    Socket socket(&client);
    menu(socket);
    closesocket(client);
    closesocket(server);
    WSACleanup();
}
catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
}
