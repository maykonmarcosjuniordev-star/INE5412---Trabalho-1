#include "TimeTracker.hpp"
#include "ProcessQueue.hpp"

class Scheduler {
    public:
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
};
