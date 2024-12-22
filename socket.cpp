#include <cstdio>
#include <cstring>
#include <stdexcept>
#include "socket.h"

std::string Socket::get()
{
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));  // clear buffer
    if (recv(*socket, buffer, sizeof(buffer), 0) == SOCKET_ERROR) {
        throw std::runtime_error("recv " + std::to_string(WSAGetLastError()));
    }
    return std::string(buffer);
}

void Socket::set(const std::string& str)
{
    if (send(*socket, str.data(), str.size(), 0) == SOCKET_ERROR) {
        throw std::runtime_error("send " + std::to_string(WSAGetLastError()));
    }
}
