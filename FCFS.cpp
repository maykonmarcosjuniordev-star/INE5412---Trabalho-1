#include <Processo.cpp>

class FCFS			//First Come, First Served
{

    int order = 0;
    int execution_time = 0;

    int exec_FCFS(Processo *[p]) { //percorre a lista de processos e imprime a execucao de cada um
        for (int i = 0; i < p.length; i++) {
            if (p[i].executando == 1) {
                p[i].executando = 2;
            }
            execution_time+=p[i].duracao;

            print_status(execution_time, p[i].ID, p[i].executando);
            p[i].executando = 3;
        }
    }

};
