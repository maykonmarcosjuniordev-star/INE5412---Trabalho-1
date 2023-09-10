#include "CPU.hpp"
#include "File.hpp"
#include "Scheduler.hpp"

class OperatingSystem {
    private:
        vector<ProcessParams *> params;
        vector<Process*> not_ready_queue;
        SchedulerStrategy *scheduler;

        SchedulerStrategy* choose_sched(char* algoritm) {
            if (algoritm == "FCFS") {
                return &FCFS_Scheduler(not_ready_queue);
            } else if (algoritm == "SJF") {
                return &SJF_Scheduler(not_ready_queue);
            }
            else if (algoritm == "PNP") {
                return &PNP_Scheduler(not_ready_queue);
            }
            else if (algoritm == "PP") {
                return &PP_Scheduler(not_ready_queue);
            }
            else {
                return &RR_Scheduler(not_ready_queue);
            }
        }
    public:
        OperatingSystem(char *algoritm) {
            CPU INE5412;
            File myfile;
            myfile.read_file(params);

            for (int i = 0; i < params.size(); i++) {
                not_ready_queue.push_back(&Process((i+1), *params[i]));
            }
            scheduler = choose_sched(algoritm);
        }
        void start() {

        }

        void delete_params() {
			for(int i = 0; i < params.size() ; i++) {
				ProcessParams *p = params[i];
				delete p;
			}
		}
};
