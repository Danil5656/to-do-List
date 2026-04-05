#include "../include/Interface.h"

/**
 * @brief Точка входа в программу
 * @return int - код завершения программы (0 при успешном выходе)
 */
int main()
{
    #ifdef _WIN32
        system("chcp 65001");
    #endif
    Interface interface;
    interface.run();
    return 0;
}
