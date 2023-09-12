#include <iostream>
#include <iomanip>
#include <string.h>
#include "CPU.hpp"
#include "File.hpp"
#include "Scheduler.hpp"

class OperatingSystem
{
private:
    vector<Process *> not_ready_queue;
    CPU MyCPU;
    SchedulerStrategy *scheduler;

    SchedulerStrategy *choose_sched(std::string algoritm)
    {
        if (algoritm == "FCFS")
        {
            return &FCFS_Scheduler(not_ready_queue);
        }
        else if (algoritm == "SJF")
        {
            return &SJF_Scheduler(not_ready_queue);
        }
        else if (algoritm == "PNP")
        {
            return &PNP_Scheduler(not_ready_queue);
        }
        else if (algoritm == "PP")
        {
            return &PP_Scheduler(not_ready_queue);
        }
        else
        {
            return &RR_Scheduler(not_ready_queue);
        }
    }

    void not_ready_process(Process &p)
    {
        int i = 0;
        while (i < not_ready_queue.size() && not_ready_queue[i].get_criation_time() < p.get_creation_time())
        {
            ++i
        }
        not_ready_queue.insert(&p, i);
    }
    void print_processes_params(vector<ProcessParams *> &processes)
    {
        vector<ProcessParams *>::iterator iter = processes.begin();

        for (; iter < processes.end(); iter++)
        {
            ProcessParams *p = *iter;
            cout << *p;
        }
    }

public:
    OperatingSystem(std::string algoritm)
    {
        scheduler = choose_sched(algoritm);
        File myfile;
        vector<ProcessParams *> params;
        myfile.read_file(params);

        for (int i = 0; i < params.size(); i++)
        {
            Process p = Process((i + 1), *params[i]);
            not_ready_process(p);
        }
        MyCPU = INE5412;
    }

    void start()
    {
        std::cout << "tempo ";
        for (int i = 1; i <= not_ready_queue.size(); ++i)
        {
            std::cout << " P" << i;
        }
        std::cout << '\n';
        int i = 0;
        while (1)
        {
            std::cout << std::left << std::setw(2) << i;
            std::cout << "-";
            ++i;
            std::cout << std::left << std::setw(2) << i;
            std::cout << " ";
            Process *current = scheduler->scheduling(not_ready_queue);
            vector<std::string> vetor = scheduler->get_state(not_ready_queue.size());
            vetor[current->get_id() - 1] = "##";
            for (int i = 0; i < vetor.size(); ++i)
            {
                std::cout << vetor[i] << ' ';
            }
            std::cout << '\n';
        }
    }
};
