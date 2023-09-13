#include <vector>
#include <string.h>
#include "TimeTracker.hpp"
#include "Process.hpp"
#define QUANTUM 2
#define CLOCK 1

class SchedulerStrategy
{
protected:
    std::vector<Process *> ready_queue;
    std::vector<Process *> finished_queue;
    Process *current_process;
    TimeTracker watch;
    int context_switch;
    std::vector<Context *> context_queue;
    void processing(Process *p)
    {
        p->processing(CLOCK);
    }

public:
    virtual int *get_time() 4
    {
        return watch.get_time();
    }
    virtual void ready_process(Process *p)
    {
        ready_queue.push_back(p);
        p->change_state();
    }
    virtual void get_state(vector<std::string> output)
    {
        for (int i = 0; i < ready_queue.size(); i++)
        {
            output[ready_queue[i]->get_id() - 1] = "--";
        }
        if (current_process)
        {
            output[current_process->get_id()] == "##";
        }
    }
    virtual void get_finish(std::vector<int[2]> *output)
    {
        if (ready_queue.size() || !context_switch || current_process == nullptr)
        {
            return nullptr;
        }
        Process *temp = nullptr;
        for (int i = 0; i < output->size(); ++i)
        {
            temp = finished_queue[i];
            output[temp->get_id() - 1][0] = temp->get_turnaround();
            output[temp->get_id() - 1][1] = temp->get_wait_time();
        }
    }
    virtual Process *scheduling();
};

class FCFS_Scheduler : public SchedulerStrategy
{
public:
    FCFS_Scheduler(int queue_size)
    {
        ready_queue = vector<Process *>(queue_size, nullptr);
        finished_queue = vector<Process *>(queue_size, nullptr);
        current_process = nullptr;
        watch = TimeTracker();
        context_switch = 0;
    }
    Process *scheduling()
    {
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
    SJF_Scheduler(int queue_size)
    {
        ready_queue = vector<Process *>(queue_size, nullptr);
        finished_queue = vector<Process *>(queue_size, nullptr);
        current_process = nullptr;
        watch = TimeTracker();
        context_switch = 0;
    }
    void ready_process(Process *p)
    {
        int i = 0;
        while (i < ready_queue.size() && ready_queue[i]->get_duration() < p->get_duration())
        {
            ++i
        }
        ready_queue.insert(p, i);
        p->change_state();
    }
};

class PNP_Scheduler : public SchedulerStrategy
{
public:
    PNP_Scheduler(int queue_size)
    {
        ready_queue = vector<Process *>(queue_size, nullptr);
        finished_queue = vector<Process *>(queue_size, nullptr);
        current_process = nullptr;
        watch = TimeTracker();
        context_switch = 0;
    }
    void ready_process(Process *p)
    {
        int i = 0;
        while (i < ready_queue.size() && ready_queue[i]->get_priority() > p->get_priority())
        {
            ++i
        }
        ready_queue.insert(p, i);
        p->change_state();
    }
};

class PP_Scheduler : public SchedulerStrategy
{
public:
    PP_Scheduler(int queue_size)
    {
        ready_queue = vector<Process *>(queue_size, nullptr);
        finished_queue = vector<Process *>(queue_size, nullptr);
        current_process = nullptr;
        watch = TimeTracker();
        context_switch = 0;
    }
    void ready_process(Process *p)
    {
        int i = 0;
        while (i < ready_queue.size() && ready_queue[i]->get_priority() > p->get_priority())
        {
            ++i
        }
        ready_queue.insert(p, i);
        p->change_state();
    }
};

class RR_Scheduler : public SchedulerStrategy
{
private:
    int quantum;

public:
    RR_Scheduler(int queue_size)
    {
        ready_queue = vector<Process *>(queue_size, nullptr);
        finished_queue = vector<Process *>(queue_size, nullptr);
        current_process = nullptr;
        watch = TimeTracker();
        context_switch = 0;
        quantum = QUANTUM;
    }
};
