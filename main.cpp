#include <stdio.h>
#include "OperatingSystem.hpp"
#include <cstring>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        printf("ERRO! Você deve digitar apenas %s ou"
               " %s <algoritmo de escalonamento>\n",
               argv[0], argv[0]);
        return 1;
    }
    std::string algoritm = "FCFS";
    if (argc == 2)
    {
        algoritm = argv[1];
    }
    OperatingSystem OS = OperatingSystem(algoritm);
    OS.start();
    return 0;
}
