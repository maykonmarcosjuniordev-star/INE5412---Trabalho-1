#include <stdio.h>
#include "OperatingSystem.hpp"

int main (int argc, char **argv) {
    if (argc > 2) {
        printf("ERRO! Você deve digitar apenas %s ou"
               " %s <algoritmo de escalonamento>\n",
               argv[0]);
        return 1;
    }
    char *algoritm = "todos";
    char *opcoes[6] = {"todos", "FCFS", "SJF", "PNP", "PP", "RR"};
    int cond = -4;
    if (argc == 2) {
        algoritm = argv[1];
        for (int i = 1; i < 6; ++i) {
            cond += i*(algoritm == opcoes[i]);
        }
        if (cond == -4) {
            printf("ERRO! As opções de algoritmo são:\n" 
                "FCFS, SJF, PNP, PP, RR ou todos\n");
        }
    }
    OperatingSystem OS;
    // dessa forma, se o algoritmo escolhido
    // for o de Prioridade Preemptivo, cond vai ser 0
    // e será o unico caso que !cond será verdadeiro
    OS.init(algoritm, !cond);
    return 0;
}
