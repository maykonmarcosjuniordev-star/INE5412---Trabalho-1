#include <vector>
#include <string.h>
#include "TimeTracker.hpp"
#include "Process.hpp"
#define QUANTUM 2

class SchedulerStrategy
{
protected:
    vector<Process *> ready_queue;
    TimeTracker watch;
    int context_switch;
    vector<Context *> context_queue;
    // bool preemp;
    virtual void ready_process()
    {
        ready_queue.push_back(p);
    }
    bool is_ready(vector<Process *> &not_ready_queue)
    {
        if (not_ready_queue.size() && (not_ready_queue[0])->get_creation_time() < *(watch.get_time()))
        {
            ready_process(not_ready_queue[0]);
            not_ready_queue.erase(not_ready_queue.begin());
            return 1;
        }
        return 0;
    }

public:
    virtual Process *scheduling(vector<Process *> not_ready_queue);
    virtual vector<std::string> get_state(int not_ready_size)
    {
        int my_size = not_ready_size + ready_queue.size();
        vector<std::string> output = vector<std::string>(size, "  ");
        std::string temp = "";

        vector<Process *>::iterator iter = ready_queue.begin();

        for (; iter < ready_queue.end(); iter++)
        {
            output[iter.get_id() - 1] = "--";
        }
        return output;
    }
    Process *next_process()
    {
        return ready_queue.at(0);
    }
};

class FCFS_Scheduler : public SchedulerStrategy
{
public:
    FCFS_Scheduler(vector<Process *> &processes)
    {
        ready_queue = vector<Process *>(processes.size(), nullptr);
    }
    std::string scheduling(vector<Process *> &not_ready_queue)
    {
        std::string output = "";
        if (ready_queue.size())
            if (is_ready(not_ready_queue))
            {
            }
    }
};

class SJF_Scheduler : public SchedulerStrategy
{
public:
    SJF_Scheduler(vector<Process *> &processes)
    {
        ready_queue = vector<Process *>(processes.size(), nullptr);
    }
    void ready_process(Process &p)
    {
        int i = 0;
        while (i < ready_queue.size() && ready_queue[i].get_duration() < p.get_duration())
        {
            ++i
        }
        ready_queue.insert(&p, i);
    }
};

class PNP_Scheduler : public SchedulerStrategy
{
public:
    PNP_Scheduler(vector<Process *> &processes)
    {
        ready_queue = vector<Process *>(processes.size(), nullptr);
    }
    void ready_process(Process &p)
    {
        int i = 0;
        while (i < ready_queue.size() && ready_queue[i].get_priority() > p.get_priority())
        {
            ++i
        }
        ready_queue.insert(&p, i);
    }
};

class PP_Scheduler : public SchedulerStrategy
{
public:
    PP_Scheduler(vector<Process *> &processes)
    {
        ready_queue = vector<Process *>(processes.size(), nullptr);
    }
    void ready_process(Process &p)
    {
        int i = 0;
        while (i < ready_queue.size() && ready_queue[i].get_priority() > p.get_priority())
        {
            ++i
        }
        ready_queue.insert(&p, i);
    }
};

class RR_Scheduler : public SchedulerStrategy
{
private:
    int quantum;

public:
    RR_Scheduler(vector<Process *> &processes)
    {
        ready_queue = vector<Process *>(processes.size(), nullptr);
        quantum = QUANTUM;
    }
};
