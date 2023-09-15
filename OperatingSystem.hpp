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
        for (int i = 1; i <= not_ready_queue.size(); ++i)
        {
            std::cout << "  P" << i;
        }
    }
    // printa cada segundo do diagrama de tempo
    void print_state(int sec, std::vector<std::string> &output)
    {
        std::cout << '\n'
                  << std::right
                  << std::setw(2)
                  << (sec - 1)
                  << "-"
                  << std::left
                  << std::setw(2)
                  << sec << "   ";
        for (int i = 0; i < output.size(); ++i)
        {
            std::cout << output[i] << "  ";
            output[i] = "  ";
        }
        static int debug = 0;
        // std::cout << "\ndebug = " << debug++ << std::endl;
    }
    // estatísticas finais do escalonamento
    void print_statistics(int Nprocess, int Ncontext_switch, std::vector<std::array<int, 2>> &end_data)
    {
        std::cout << "\nTurnaround\n";
        std::cout << "Time:   ";
        float media = 0;
        for (int j = 0; j < Nprocess; ++j)
        {
            media += end_data[j][0];
            std::cout << std::right
                      << std::setw(2)
                      << end_data[j][0] << "  ";
        }
        media /= static_cast<float>(Nprocess);
        std::cout << "| media = " << media << std::endl;

        media = 0;
        std::cout << "Wait\n";
        std::cout << "Time:   ";
        for (int j = 0; j < Nprocess; ++j)
        {
            media += end_data[j][1];
            std::cout << std::right
                      << std::setw(2)
                      << end_data[j][1] << "  ";
        }
        media /= static_cast<float>(Nprocess);
        std::cout << "| media = " << media << std::endl;
        std::cout << "N de trocas de contexto = " << Ncontext_switch << std::endl;
    }

public:
    OperatingSystem(std::string algoritm)
    {
        File myfile = File();
        myfile.read_file(not_ready_queue);
        scheduler = choose_sched(algoritm);
        MyCPU = new INE5412();
    }
    ~OperatingSystem()
    {
        delete MyCPU;
        delete scheduler;
        for (int i = 0; i < process_bucket.size(); ++i)
        {
            delete process_bucket[i];
        }
    }

    void start()
    {
        print_initial();
        // a saida associada a cada processo no diagrama de tempo
        std::vector<std::string> output = std::vector<std::string>(not_ready_queue.size(), "  ");
        // contador do diagrama de tempo
        int prontos = 0;
        int Nprocessos = not_ready_queue.size();
        bool running = Nprocessos;
        while (running)
        {
            // atualiza a fila de prontos e cria
            // processos a partir de seus parâmetros
            while ((prontos < not_ready_queue.size()) && (not_ready_queue[prontos]).get_creation_time() == scheduler->get_time())
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
