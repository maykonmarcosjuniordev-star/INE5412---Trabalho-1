#include "Process.hpp"
#include <vector>

class ProcessQueue {
    public:
        Process pop() {
            vector<Process *>::iterator it = queue.begin();
            queue.erase(queue.begin());           
        }
        Process push(Process *p) {
            queue.push_back(p);
        }
        int size() {
            return queue.size();
        }
        Process* begin () {
            return queue[0];
        }
    private:
        vector<Process *> queue;
};
