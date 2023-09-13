#include <iostream>
#include <iomanip>
#include <vector>
#include <string.h>
#include "CPU.hpp"
#include "File.hpp"
#include "Scheduler.hpp"

class OperatingSystem
{
private:
    CPU MyCPU;
    SchedulerStrategy *scheduler;
    std::vector<ProcessParams *> not_ready_queue;
    SchedulerStrategy *choose_sched(std::string algoritm)
    {
        if (algoritm == "FCFS")
        {
            return &FCFS_Scheduler(not_ready_queue.size());
        }
        else if (algoritm == "SJF")
        {
            return &SJF_Scheduler(not_ready_queue.size());
        }
        else if (algoritm == "PNP")
        {
            return &PNP_Scheduler(not_ready_queue.size());
        }
        else if (algoritm == "PP")
        {
            return &PP_Scheduler(not_ready_queue.size());
        }
        else
        {
            return &RR_Scheduler(not_ready_queue.size());
        }
    }

    void get_readys()
    {
        while (not_ready_queue.size() && (not_ready_queue[0])->get_creation_time() == scheduler->get_time())
        {
            scheduler->ready_process(&(Process(not_ready_queue[0])));
            not_ready_queue.erase(not_ready_queue.begin());
        }
    }
    void print_processes_params(std::vector<ProcessParams *> &processes)
    {
        std::vector<ProcessParams *>::iterator iter = processes.begin();

        for (; iter < processes.end(); iter++)
        {
            ProcessParams *p = *iter;
            std::cout << *p;
        }
    }
    void print_initial()
    {
        std::cout << "tempo ";
        for (int i = 1; i <= not_ready_queue.size(); ++i)
        {
            std::cout << " P" << i;
        }
    }
    void print_state(int *sec, std::vector<std::string> *output)
    {
        std::cout << '\n'
                  << std::left
                  << std::setw(2)
                  << sec++
                  << "-"
                  << std::left
                  << std::setw(2)
                  << sec << " ";
        for (int i = 0; i < output->size(); ++i)
        {
            std::cout << output[i] << ' ';
        }
    }
    void print_statistics()
    {
        std::vector<int[2]> end_data = std::vector<int[2]>(output.size(), {0, 0});
        scheduler->get_finished(&end_data);
        std::cout << "Turnaround\n";
        std::cout << "Time:   ";
        int media = 0;
        for (int j = 0; j < output.size(); ++j)
        {
            media += end_data[j][0];
            std::cout << end_data[j][0] << '  ';
        }
        std::cout << "media = " << media << std::endl;

        media = 0;
        std::cout << "Wait";
        std::cout << "Time:   ";
        for (int j = 0; j < output.size(); ++j)
        {
            media += end_data[j][0];
            std::cout << end_data[j][1] << '  ';
        }
        std::cout << "media = " << media << std::endl;
    }

public:
    OperatingSystem(std::string algoritm)
    {
        scheduler = choose_sched(algoritm);
        File myfile = File();
        myfile.read_file(not_ready_queue);
        MyCPU = INE5412();
    }

    void start()
    {
        print_initial();
        std::vector<std::string> output = vector<std::string>(not_ready_queue.size(), "  ");
        int sec = 0;
        bool running = 1 && (not_ready_queue.size());
        while (running)
        {
            get_readys();
            Process *current = scheduler->scheduling();
            scheduler->get_state(output);
            if (current != nullptr)
            {
                MyCPU.set_context(current->processing());
            }
            print_state(&sec, &output);
            running = (not_ready_queue.size()) || (current != nullptr);
        }
        print_statistics();
    }
};
