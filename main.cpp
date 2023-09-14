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
    std::string opcoes[5] = {"FCFS", "SJF", "PNP", "PP", "RR"};
    int cond = 0;
    if (argc == 2)
    {
        algoritm = argv[1];
        for (int i = 0; i < 5; ++i)
        {
            cond |= (algoritm == opcoes[i]);
        }
        if (!cond)
        {
            printf("ERRO! As opções de algoritmo são:\n"
                   "FCFS, SJF, PNP, PP, RR\n");
            return 1;
        }
    }
    OperatingSystem OS = OperatingSystem(algoritm);
    OS.start();
    return 0;
}
