#include "ProcessParams.hpp"
#include "Context.hpp"
#include "random"

class Process {
    public:
        Process(int id, ProcessParams &P_param) {
            ID = id;
            params = P_param;
            start_time = -1;
            end_time = -1;
            state = State();
            myContext = INEcontext();
        }
        const int get_id() {
            return ID;
        }
        void set_start_time(int begin) {
            start_time = begin;
        }
        const int get_start_time() {
            return start_time;
        }
        const int get_duration() {
            return params.get_duration();
        }
        void set_priority(int newP) {
            params.set_priority(newP);
        }
        const int get_priority() {
            return params.get_priority();
        }
        void set_end_time(int finish) {
            end_time = finish;
        }
        const int get_end_time() {
            return end_time;
        }
        const int get_turnaround() {
            return (end_time - start_time);
        }
        void change_state() {
            state.current_state = (state.current_state + 1)%4;
        }
        const char* get_state() {
            return state.states[state.current_state];
        }
        Context processing(int time_) {
            myContext.progress += 100 * (time_ / params.get_duration());
            if (myContext.progress >= 100.0) {
                state.current_state = 3;
            }
            for (int i = 0; i < 6; ++i) {
                myContext.registers[i] = random();
            }
            myContext.PC = random();
            myContext.SP = random();
            myContext.ST = random();
            return myContext;
        }

    private:
        struct State {
            char * states[4];
            int current_state;
            State() {
                states[0] = "novo";
                states[1] = "pronto";
                states[2] = "executando";
                states[3] = "terminado";
                current_state = 0;
            }

        };
        
        int ID;
        ProcessParams params;
        int start_time;
        int end_time;
        State state;
        Context myContext;
};
