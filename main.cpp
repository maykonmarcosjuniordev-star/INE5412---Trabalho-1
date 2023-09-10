#include <stdio.h>
#include "OperatingSystem.hpp"

int main (int argc, char **argv) {
    if (argc > 2) {
        printf("ERRO! Você deve digitar apenas %s ou"
               " %s <algoritmo de escalonamento>\n",
               argv[0], argv[0]);
        return 1;
    }
    char *algoritm = "FCFS";
    char *opcoes[6] = {"FCFS", "SJF", "PNP", "PP", "RR"};
    int cond = 0;
    if (argc == 2) {
        algoritm = argv[1];
        for (int i = 0; i < 6; ++i) {
            cond += i*(algoritm == opcoes[i]);
        }
        if (cond == -4) {
            printf("ERRO! As opções de algoritmo são:\n" 
                "FCFS, SJF, PNP, PP, RR\n");
            return 1;
        }
    }
    OperatingSystem OS = OperatingSystem(algoritm);
    OS.start();
    return 0;
}
