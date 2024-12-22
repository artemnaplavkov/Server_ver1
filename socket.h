#pragma once

#include <winsock2.h>
#include <string>

struct Socket {
    SOCKET* socket;

    std::string get();
    void set(const std::string&);
};
