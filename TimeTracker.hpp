#include <time.h>
#include <unistd.h>
#define CLOCK 1

class TimeTracker
{
private:
    int *current_time;

public:
    TimeTracker()
    {
        *current_time = 0;
    }
    int *get_time()
    {
        return current_time;
    }
    void cicle()
    {
        sleep(CLOCK);
        current_time += CLOCK;
    }
};
