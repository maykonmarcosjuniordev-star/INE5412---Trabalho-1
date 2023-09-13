#include <vector>
#include <string.h>
#include "TimeTracker.hpp"
#include "Process.hpp"
#define QUANTUM 2
#define CLOCK 1

class SchedulerStrategy
{
protected:
    vector<Process *> ready_queue;
    vector<Process *> finished_queue;
    Process *current_process;
    TimeTracker watch;
    int context_switch;
    vector<Context *> context_queue;
    virtual void ready_process(ProcessParams *p)
    {
        Process *temp = &(Process(p)))
        ready_queue.push_back(temp);
        temp->change_state();
    }
    virtual bool get_readys(vector<ProcessParams *> &not_ready_queue)
    {
        int output = 0;
        while (not_ready_queue.size() && (not_ready_queue[0])->get_creation_time() == *(watch.get_time()))
        {
            ready_process((not_ready_queue[0]));
            not_ready_queue.erase(not_ready_queue.begin());
            output = 1;
        }
        return output;
    }
    void processing(Process *p)
    {
        p->processing(CLOCK);
    }

public:
    virtual Process *scheduling(vector<ProcessParams *> not_ready_queue);
    virtual int *get_time()
    {
        return watch.get_time();
    }
    virtual void get_state(vector<std::string> output)
    {
        for (int i = 0; i < ready_queue.size(); i++)
        {
            output[ready_queue[i]->get_id() - 1] = "--";
        }
    }
};

class FCFS_Scheduler : public SchedulerStrategy
{
public:
    FCFS_Scheduler(vector<ProcessParams *> &processes)
    {
        ready_queue = vector<Process *>(processes.size(), nullptr);
        finished_queue = vector<Process *>(processes.size(), nullptr);
        current_process = nullptr;
        watch = TimeTracker();
        context_switch = 0;
    }
    Process *scheduling(vector<ProcessParams *> &not_ready_queue)
    {
        get_readys(not_ready_queue);
        watch.cicle();
        if ((current_process == nullptr) && ready_queue.size())
        {
            current_process = ready_queue[0];
            context_switch++;
        }
        else if (current_process->get_remaining_time() == 0)
        {
            finished_queue.push_back(current_process);
            current_process = ready_queue[0];
            ready_queue.erase(ready_queue.begin());
            context_switch++;
        }
        for (int i = 0; i < ready_queue.size(); ++i)
        {
            ready_queue[i]->spend_time();
        }
        return current_process;
    }
};

class SJF_Scheduler : public SchedulerStrategy
{
public:
    SJF_Scheduler(vector<ProcessParams *> &processes)
    {
        ready_queue = vector<Process *>(processes.size(), nullptr);
        finished_queue = vector<Process *>(processes.size(), nullptr);
        current_process = nullptr;
        watch = TimeTracker();
        context_switch = 0;
    }
    void ready_process(ProcessParams &p)
    {
        int i = 0;
        while (i < ready_queue.size() && ready_queue[i].get_duration() < p.get_duration())
        {
            ++i
        }
        Process *temp = &(Process(p)))
        ready_queue.insert(temp, i);
        temp->change_state();
    }
};

class PNP_Scheduler : public SchedulerStrategy
{
public:
    PNP_Scheduler(vector<ProcessParams *> &processes)
    {
        ready_queue = vector<Process *>(processes.size(), nullptr);
        finished_queue = vector<Process *>(processes.size(), nullptr);
        current_process = nullptr;
        watch = TimeTracker();
        context_switch = 0;
    }
    void ready_process(ProcessParams &p)
    {
        int i = 0;
        while (i < ready_queue.size() && ready_queue[i].get_priority() > p.get_priority())
        {
            ++i
        }
        Process *temp = &(Process(p)))
        temp->change_state();
        ready_queue.insert(temp, i);
    }
};

class PP_Scheduler : public SchedulerStrategy
{
public:
    PP_Scheduler(vector<Process *> &processes)
    {
        ready_queue = vector<ProcessParams *>(processes.size(), nullptr);
        finished_queue = vector<Process *>(processes.size(), nullptr);
        current_process = nullptr;
        watch = TimeTracker();
        context_switch = 0;
    }
    void ready_process(ProcessParams &p)
    {
        int i = 0;
        while (i < ready_queue.size() && ready_queue[i].get_priority() > p.get_priority())
        {
            ++i
        }
        Process *temp = &(Process(p)))
        temp->change_state();
        ready_queue.insert(temp, i);
    }
};

class RR_Scheduler : public SchedulerStrategy
{
private:
    int quantum;

public:
    RR_Scheduler(vector<ProcessParams *> &processes)
    {
        ready_queue = vector<Process *>(processes.size(), nullptr);
        finished_queue = vector<Process *>(processes.size(), nullptr);
        current_process = nullptr;
        watch = TimeTracker();
        context_switch = 0;
        quantum = QUANTUM;
    }
};
