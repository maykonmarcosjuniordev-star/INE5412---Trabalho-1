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
    CPU *MyCPU;
    SchedulerStrategy *scheduler;
    std::vector<ProcessParams> not_ready_queue;
    std::vector<Process *> process_bucket;
    // esconde a seleção do algoritmo de escalonamento
    SchedulerStrategy *choose_sched(std::string algoritm)
    {
        if (algoritm == "SJF")
        {
            return new SJF_Scheduler(not_ready_queue.size());
        }
        else if (algoritm == "PNP")
        {
            return new Priority_Scheduler(not_ready_queue.size(), false);
        }
        else if (algoritm == "PP")
        {
            return new Priority_Scheduler(not_ready_queue.size(), true);
        }
        else if (algoritm == "RR")
        {
            return new RR_Scheduler(not_ready_queue.size());
        }
        else
        {
            return new FCFS_Scheduler(not_ready_queue.size());
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
        for (std::size_t i = 1; i <= not_ready_queue.size(); ++i)
        {
            std::cout << "| P"
                      << std::left
                      << std::setw(2) << i;
        }
        std::cout << "|" << std::endl;
    }
    // printa cada segundo do diagrama de tempo
    void print_state(int sec, std::vector<std::string> &output)
    {
        std::cout << std::right
                  << std::setw(2)
                  << (sec - 1)
                  << "-"
                  << std::left
                  << std::setw(2)
                  << sec << " | ";
        for (std::size_t i = 0; i < output.size(); ++i)
        {
            std::cout << output[i] << " | ";
            output[i] = "  ";
        }
        std::cout << std::endl;
    }
    // estatísticas finais do escalonamento
    void print_statistics(int Nprocess, int Ncontext_switch, std::vector<std::array<int, 2>> &end_data)
    {
        std::cout << "______|";
        for (int i = 0; i < Nprocess; ++i)
        {
            std::cout << "    |";
        }
        std::cout << "\nT_Time| ";
        float media = 0;
        for (int j = 0; j < Nprocess; ++j)
        {
            media += end_data[j][0];
            std::cout << std::right
                      << std::setw(2)
                      << end_data[j][0] << " | ";
        }

        int media2 = 0;
        std::cout << "\nW_Time| ";
        for (int j = 0; j < Nprocess; ++j)
        {
            media2 += end_data[j][1];
            std::cout << std::right
                      << std::setw(2)
                      << end_data[j][1] << " | ";
        }
        media /= static_cast<float>(Nprocess);
        media2 /= static_cast<float>(Nprocess);
        std::cout << "\nmedia T_Time = " << media
                  << "\nmedia W_Time = " << media2
                  << "\nNumero de trocas de contexto = "
                  << Ncontext_switch << "\n[T_time = Turnaround Time]"
                  << "\n[W_Time = Wait Time]"
                  << std::endl;
    }

public:
    OperatingSystem(std::string algoritm)
    {
        File myfile;
        myfile.read_file(not_ready_queue);
        scheduler = choose_sched(algoritm);
        MyCPU = new INE5412();
    }
    ~OperatingSystem()
    {
        delete MyCPU;
        delete scheduler;
        for (std::size_t i = 0; i < process_bucket.size(); ++i)
        {
            delete process_bucket[i];
        }
    }

    void start()
    {
        print_initial();
        // contador do diagrama de tempo
        int prontos = 0;
        int Nprocessos = not_ready_queue.size();
        // a saida associada a cada processo no diagrama de tempo
        std::vector<std::string> output = std::vector<std::string>(Nprocessos, "  ");
        bool running = Nprocessos;
        while (running)
        {
            // atualiza a fila de prontos e cria
            // processos a partir de seus parâmetros
            while ((prontos < Nprocessos) && (not_ready_queue[prontos]).get_creation_time() == scheduler->get_time())
            {
                Process *p = new Process(&(not_ready_queue[prontos]));
                process_bucket.push_back(p);
                scheduler->ready_process(process_bucket.back());
                prontos++;
            }
            // chama o escalonador
            Process *current = scheduler->scheduling();
            // consegue o status desse segundo
            scheduler->get_state(output);
            if (current != nullptr)
            {
                // seta a CPU
                MyCPU->set_context(current->get_context());
            }
            // verifica se ainda há processos não encerrados
            running = (current != nullptr) || (prontos == 0);
            // quando não houver processos para executar,
            // current process será nullptr.
            if (running)
            {
                print_state(scheduler->get_time(), output);
            }
        }
        std::vector<std::array<int, 2>> end_data(Nprocessos, {0, 0});
        scheduler->get_finished(end_data);
        // printa o resultado;
        print_statistics(Nprocessos, scheduler->get_context_switch(), end_data);
    }
};
