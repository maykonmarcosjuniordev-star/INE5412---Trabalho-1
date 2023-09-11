#include <iostream>
#include "CPU.hpp"
#include "File.hpp"
#include "Scheduler.hpp"

class OperatingSystem
{
private:
    vector<Process *> not_ready_queue;
    CPU MyCPU;
    SchedulerStrategy *scheduler;

    SchedulerStrategy *choose_sched(char *algoritm)
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
    OperatingSystem(char *algoritm)
    {
        scheduler = choose_sched(algoritm);
        File myfile;
        vector<ProcessParams *> params;
        myfile.read_file(params);

        for (int i = 0; i < params.size(); i++)
        {
            not_ready_queue.push_back(&Process((i + 1), *params[i]));
            not_ready_queue.insert()
        }
    }

    void start()
    {
    }
};
