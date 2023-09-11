#include <time.h>

class TimeTracker
{
private:
    int current_time = 0;

public:
    int get_time()
    {
        return current_time;
    }
};
