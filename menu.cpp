#include "menu.h"
#include "store.h"

void menu(Socket& socket)
{
    Store store;
    std::string str;
    while (true) {
        socket.set(str + "1-read 2-create 3-print 4-find");
        str.clear();
        int key = std::atoi(socket.get().data());
        switch (key) {
            case 1:
                store.read();
                break;
            case 2:
                store.create(socket);
                store.write();
                break;
            case 3:
                str = store.print();
                break;
            case 4:
                str = store.find(socket);
                break;
            default:
                socket.set("exit");
                return;
        }
    }
}
