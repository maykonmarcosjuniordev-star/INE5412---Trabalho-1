#include <iostream>
#include <iomanip>
#include <array>
#include <vector>
#include <string.h>
#include "CPU.hpp"
#include "File.hpp"
#include "Scheduler.hpp"

class OperatingSystem
{
private:
    CPU MyCPU;
    SchedulerStrategy scheduler;
    std::vector<ProcessParams> not_ready_queue;
    // esconde a seleção do algoritmo de escalonamento
    SchedulerStrategy choose_sched(std::string algoritm)
    {
        SchedulerStrategy output;
        if (algoritm == "FCFS")
        {
            output = FCFS_Scheduler(not_ready_queue.size());
        }
        else if (algoritm == "SJF")
        {
            output = SJF_Scheduler(not_ready_queue.size());
        }
        else if (algoritm == "PNP")
        {
            output = Priority_Scheduler(not_ready_queue.size(), false);
        }
        else if (algoritm == "PP")
        {
            output = Priority_Scheduler(not_ready_queue.size(), true);
        }
        else
        {
            output = RR_Scheduler(not_ready_queue.size());
        }
        return output;
    }
    // cria processos a partir de seus parâmetros
    void get_readys()
    {
        while (not_ready_queue.size() && (not_ready_queue[0]).get_creation_time() == scheduler.get_time())
        {
            Process p = Process(&(not_ready_queue[0]));
            scheduler.ready_process(p);
            not_ready_queue.erase(not_ready_queue.begin());
        }
    }
    /*
    void print_processes_params(std::vector<ProcessParams *> &processes)
    {
        std::vector<ProcessParams *>::iterator iter = processes.begin();

        for (; iter < processes.end(); iter++)
        {
            ProcessParams *p = *iter;
            std::cout << *p;
        }
    }
    */
    // inicio do diagrama de tempo
    void print_initial()
    {
        std::cout << "tempo ";
        for (int i = 1; i <= not_ready_queue.size(); ++i)
        {
            std::cout << " P" << i;
        }
    }
    // printa cada segundo do diagrama de tempo
    void print_state(int *sec, std::vector<std::string> output)
    {
        std::cout << '\n'
                  << std::left
                  << std::setw(2)
                  << sec++
                  << "-"
                  << std::left
                  << std::setw(2)
                  << sec << " ";
        for (int i = 0; i < output.size(); ++i)
        {
            std::cout << output[i] << ' ';
        }
    }
    // estatísticas finais do escalonamento
    void print_statistics(int Nprocess)
    {
        std::vector<std::array<int, 2>> end_data(Nprocess, {0, 0});

        scheduler.get_finished(end_data);
        std::cout << "Turnaround\n";
        std::cout << "Time:   ";
        int media = 0;
        for (int j = 0; j < Nprocess; ++j)
        {
            media += end_data[j][0];
            std::cout << end_data[j][0] << "  ";
        }
        media /= Nprocess;
        std::cout << "media = " << media << std::endl;

        media = 0;
        std::cout << "Wait";
        std::cout << "Time:   ";
        for (int j = 0; j < Nprocess; ++j)
        {
            media += end_data[j][1];
            std::cout << end_data[j][1] << "  ";
        }
        media /= Nprocess;
        std::cout << "media = " << media << std::endl;
        std::cout << "N trocas de contexto = " << scheduler.get_context_switch() << std::endl;
    }

public:
    OperatingSystem(std::string algoritm)
    {
        scheduler = choose_sched(algoritm);
        File myfile = File();
        myfile.read_file(not_ready_queue);
        MyCPU = INE5412();
    }
    ~OperatingSystem() {}

    void start()
    {
        print_initial();
        // a saida associada a cada processo no diagrama de tempo
        std::vector<std::string> output = std::vector<std::string>(not_ready_queue.size(), "  ");
        // contador do diagrama de tempo
        int sec = 0;
        bool running = 1 && (not_ready_queue.size());
        while (running)
        {
            // atualiza a fila de prontos
            get_readys();
            // chama o escalonador
            Process *current = scheduler.scheduling();
            // consegue o status desse segundo
            scheduler.get_state(output);
            if (current != nullptr)
            {
                // seta a CPU
                MyCPU.set_context(current->get_context());
            }
            print_state(&sec, output);
            // verifica se ainda há processos
            running = (not_ready_queue.size()) || (current != nullptr);
        }
        // printa o resultado;
        print_statistics(output.size());
    }
};
