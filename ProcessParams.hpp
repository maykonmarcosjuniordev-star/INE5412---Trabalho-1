#include <iostream>

using namespace std;

class ProcessParams {
public:
	ProcessParams(int c, int d, int p) { 
		creation_time = c;
		duration = d;
		priority = p;
	}

	friend ostream &operator<<(ostream& os, const ProcessParams& p) {
		os << "Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << endl;
		return os;
	}

    const int get_creation_time() {
        return creation_time;
    }

    const int get_duration() {
        return duration;
    }

    const int get_priority() {
        return priority;
    }

    void set_priority(int NewP) {
        priority = NewP;
    }

private:	
	int creation_time;
	int duration; // seconds
	int priority;
};
