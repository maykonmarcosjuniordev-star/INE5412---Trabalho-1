#include "TimeTracker.hpp"
#include "Process.hpp"
#include <vector>

class SchedulerStrategy
{
protected:
    vector<Process *> ready_queue;
    int context_switch;
    vector<Context *> context_queue;
    bool preemp;

public:
    virtual void ready_process();
    virtual Process *get_next_process();
};

class FCFS_Scheduler : public SchedulerStrategy
{
public:
    FCFS_Scheduler(vector<Process *> &processes, bool Ipreemp)
    {
        ready_queue = processes;
        preemp = Ipreemp;
    }
    void ready_process(Process &p)
    {
        ready_queue.push_back(&p);
    }
};

class SJF_Scheduler : public SchedulerStrategy
{
public:
    SJF_Scheduler(vector<Process *> &processes)
    {
        ready_queue = processes;
    }
    void ready_process(Process &p)
    {
        ready_queue.push_back(&p);
    }
};

class PNP_Scheduler : public SchedulerStrategy
{
public:
    PNP_Scheduler(vector<Process *> &processes)
    {
        ready_queue = processes;
    }
    void ready_process(Process &p)
    {
        ready_queue.push_back(&p);
    }
};

class PP_Scheduler : public SchedulerStrategy
{
public:
    PP_Scheduler(vector<Process *> &processes)
    {
        ready_queue = processes;
    }
    void ready_process(Process &p)
    {
        ready_queue.push_back(&p);
    }
};

class RR_Scheduler : public SchedulerStrategy
{
public:
    RR_Scheduler(vector<Process *> &processes)
    {
        ready_queue = processes;
    }
    void ready_process(Process &p)
    {
        ready_queue.push_back(&p);
    }
};
