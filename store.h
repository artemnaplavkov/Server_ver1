#pragma once

#include <string>
#include <vector>
#include "socket.h"

struct Notebook {
    std::string name;
    int year;
    int ram;
    int ssd;
    float price;

    void input(Socket&);
    friend std::istream& operator>>(std::istream&, Notebook&);
    friend std::ostream& operator<<(std::ostream&, const Notebook&);
    friend bool operator==(const Notebook&, const Notebook&) = default;
};

struct Store {
    std::vector<Notebook> arr;

    void create(Socket&);
    void write() const;
    void read();
    std::string print() const;
    std::string find(Socket&) const;
};
