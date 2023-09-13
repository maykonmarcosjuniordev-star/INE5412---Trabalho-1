#include <iostream>
#ifndef ProcessParams_HPP
#define ProcessParams_HPP
using namespace std;

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

    friend ostream &operator<<(ostream &os, const ProcessParams &p)
    {
        os << " id = " << p.id << "Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << endl;
        return os;
    }

    const int get_creation_time()
    {
        return creation_time;
    }

    const int get_id()
    {
        return id;
    }

    const int get_duration()
    {
        return duration;
    }

    const int get_priority()
    {
        return priority;
    }

    void set_priority(int NewP)
    {
        priority = NewP;
    }
};
