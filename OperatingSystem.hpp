#include "CPU.hpp"
#include "File.hpp"
#include "Scheduler.hpp"

class OperatingSystem {
    public:
        OperatingSystem() {
            CPU INE5412;
        }
        void init(char *algoritm, bool preemp) {
            File myfile;
            myfile.read_file();
            myfile.print_processes_params();
        }

    private:
        void start(char* algoritm, bool preemp) {

        }
};
