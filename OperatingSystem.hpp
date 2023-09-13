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
    void print_processes_params(std::vector<ProcessParams *> &processes)
    {
        std::vector<ProcessParams *>::iterator iter = processes.begin();

        for (; iter < processes.end(); iter++)
        {
            ProcessParams *p = *iter;
            std::cout << *p;
        }
    }

public:
    OperatingSystem(std::string algoritm)
    {
        scheduler = choose_sched(algoritm);
        File myfile;
        myfile.read_file(not_ready_queue);
        MyCPU = INE5412();
    }

    void start()
    {
        std::cout << "tempo ";
        for (int i = 1; i <= not_ready_queue.size(); ++i)
        {
            std::cout << " P" << i;
        }
        std::vector<std::string> output = vector<std::string>(not_ready_queue.size(), "  ");
        int i = 0;
        while (1)
        {
            std::cout << '\n';
            std::cout << std::left << std::setw(2) << i;
            std::cout << "-";
            ++i;
            std::cout << std::left << std::setw(2) << i;
            std::cout << " ";
            Process *current = scheduler->scheduling(not_ready_queue);
            scheduler->get_state(output);
            if (current != nullptr)
            {
                output[current->get_id() - 1] = "##";
                MyCPU.set_context(current->processing())
            }
            for (int j = 0; j < output.size(); ++j)
            {
                std::cout << output[j] << ' ';
            }
            if ((current == nullptr) && !(not_ready_queue.size()) {
                break;
            }
        }
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
};
