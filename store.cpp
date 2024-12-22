#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include "store.h"

void Notebook::input(Socket& socket)
{
    socket.set("name = ");
    name = socket.get();
    socket.set("year = ");
    year = std::atoi(socket.get().data());
    socket.set("ram = ");
    ram = std::atoi(socket.get().data());
    socket.set("ssd = ");
    ssd = std::atoi(socket.get().data());
    socket.set("price = ");
    price = std::atof(socket.get().data());
}

std::istream& operator>>(std::istream& is, Notebook& note)
{
    is >> note.name >> note.year >> note.ram >> note.ssd >> note.price;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Notebook& note)
{
    os << note.name << "\t" << note.year << "\t" << note.ram << "\t" << note.ssd
       << "\t" << note.price;
    return os;
}

void Store::create(Socket& socket)
{
    arr.clear();
    socket.set("notebooks number = ");
    int n = std::atoi(socket.get().data());
    if (n < 1)
        return;
    for (int i = 0; i < n; i++)
        arr.emplace_back().input(socket);
}

void Store::write() const
{
    std::ofstream os("notebooks.txt");
    for (int i = 0; i < arr.size(); i++)
        os << arr[i] << "\n";
}

void Store::read()
{
    arr.clear();
    std::ifstream is("notebooks.txt");
    while (not is.eof()) {
        Notebook note;
        is >> note;
        if (is.good())
            arr.push_back(note);
    }
}

std::string Store::print() const
{
    std::ostringstream os;
    os << "name\tyear\tram\tssd\tprice\n";
    for (int i = 0; i < arr.size(); i++)
        os << arr[i] << "\n";
    return os.str();
}

std::string Store::find(Socket& socket) const
{
    socket.set("name = ");
    std::string name = socket.get();
    std::ostringstream os;
    os << "name\tyear\tram\tssd\tprice\n";
    for (int i = 0; i < arr.size(); i++)
        if (name == arr[i].name)
            os << arr[i] << "\n";
    return os.str();
}
