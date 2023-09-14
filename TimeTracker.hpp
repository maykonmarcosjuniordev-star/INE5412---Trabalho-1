#include <time.h>
#include <unistd.h>
#define CLOCK 1

class TimeTracker
{
private:
    int current_time;

public:
    TimeTracker()
    {
        current_time = 0;
    }
    const int get_time()
    {
        return current_time;
    }
    // espera um ciclo de CLOCK
    // e atualiza o current_time
    void cicle()
    {
        sleep(CLOCK);
        current_time += CLOCK;
    }
};
