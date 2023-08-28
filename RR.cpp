class RR			//Round-Robin com quantum = 2s, sem prioridade

{
    int execution_time = 0;

    int exec_RR(Processo *[p]) { //percorre a lista de processos e imprime a execucao de cada um
        int i = 0;
        while(p[i].executando != 3) {
            if (p[i].executando == 1) {
                p[i].executando = 2;
            }
            execution_time+=p[i].duracao;

            print_status(execution_time, p[i].ID, p[i].executando);
            if (p[i].duracao > 2) {
                p[i].duracao -= 2;
            } else {
                p[i].duracao = 0;
                p[i].executando = 3;
            }
            i++;
            if (i == p.length) {
                i = 0;
            }
        }
    }
};
