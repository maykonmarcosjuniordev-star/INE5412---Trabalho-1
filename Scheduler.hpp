#include "TimeTracker.hpp"
#include "Process.hpp"
#include <vector>

class SchedulerStrategy {
    protected:
        vector<Process *> ready_queue;
        int context_switch;
        vector<Context *> context_queue;
    public:
<<<<<<< HEAD
        Scheduler(TimeTracker watch, int context_switch, bool preemptive, vector<Process*> ready_queue, 
        vector<Process*> not_ready_queue, vector<Context> context_queue) {
            watch = TimeTracker();
            context_switch = 0;
            ready_queue = vector<Process*>();
            not_ready_queue = not_ready_queue;
            context_queue = vector<Context>();
            preemptive = preemptive;
        }
    
        void run(vector<Process*> ready_queue, vector<Process*> not_ready_queue) {
            while (not_ready_queue.size() > 0) {
                //not_ready_queue[0]->State().current_state = 2;
                ready_queue.push_back(not_ready_queue[0]); 
                not_ready_queue.erase(not_ready_queue.begin());
            }
        }

    private:
        TimeTracker watch;
        int context_switch;
        bool preemptive;
        vector<Process*> ready_queue;
        vector<Process*> not_ready_queue;
        vector<Context> context_queue;
=======
        virtual void ready_process();
        virtual void get_next_process();
};

class FCFS_Scheduler : public SchedulerStrategy {
    public:
        FCFS_Scheduler(vector<Process *> &processes) {
            ready_queue = processes;
        }
        void ready_process(Process &p) {
            ready_queue.push_back(&p);
        }
};


class SJF_Scheduler : public SchedulerStrategy {
    public:
        SJF_Scheduler(vector<Process *> &processes) {
            ready_queue = processes;
        }
        void ready_process(Process &p) {
            ready_queue.push_back(&p);
        }
};

class PNP_Scheduler : public SchedulerStrategy {
    public:
        PNP_Scheduler(vector<Process *> &processes) {
            ready_queue = processes;
        }
        void ready_process(Process &p) {
            ready_queue.push_back(&p);
        }
};



class PP_Scheduler : public SchedulerStrategy {
    public:
        PP_Scheduler(vector<Process *> &processes) {
            ready_queue = processes;
        }
        void ready_process(Process &p) {
            ready_queue.push_back(&p);
        }
};



class RR_Scheduler : public SchedulerStrategy {
    public:
        RR_Scheduler(vector<Process *> &processes) {
            ready_queue = processes;
        }
        void ready_process(Process &p) {
            ready_queue.push_back(&p);
        }
>>>>>>> e29808f (Aaptação do diagrama de classes)
};
