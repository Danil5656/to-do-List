#include "../include/Interface.h"

int main()
{
    #ifdef _WIN32
        system("chcp 65001");
    #endif
    Interface interface;
    interface.run();
    return 0;
}
