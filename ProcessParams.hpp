#include <iostream>
#ifndef ProcessParams_HPP
#define ProcessParams_HPP

class ProcessParams
{
private:
    int creation_time;
    int duration; // seconds
    int priority;
    int id;

public:
    ProcessParams(int c, int d, int p, int newID)
    {
        creation_time = c;
        duration = d;
        priority = p;
        id = newID;
    }

    friend std::ostream &operator<<(std::ostream &os, const ProcessParams &p)
    {
        os << "\nid = " << p.id
           << " creation time = "
           << p.creation_time
           << " duration = "
           << p.duration
           << " priority = "
           << p.priority << '\n';
        return os;
    }

    int get_creation_time() const
    {
        return creation_time;
    }

    int get_id() const
    {
        return id;
    }

    int get_duration() const
    {
        return duration;
    }

    int get_priority() const
    {
        return priority;
    }

    void set_priority(int NewP)
    {
        priority = NewP;
    }
};
#endif // ProcessParams_HPP
