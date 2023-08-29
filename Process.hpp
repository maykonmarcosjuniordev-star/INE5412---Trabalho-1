#include "ProcessParams.hpp"
#include "random"

struct Context {
    long int registers[6];
    long int SP;
    long int PC;
    long int ST;
    float progress;
};

class Process {
    public:
        Process(int id, ProcessParams param, int b, int e) {
            ID = id;
            params = param;
            start_time = -1;
            end_time = -1;
            state = new State;
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
            state->current_state = (state->current_state + 1)%4;
        }
        const char* get_state() {
            return state->states[state->current_state];
        }
        Context processing(int time_) {
            context.progress += 100 * (time_ / params.get_duration());
            if (context.progress >= 100.0) {
                state->current_state = 3;
            }
            for (int i = 0; i < 6; ++i) {
                context.registers[i] = random();
            }
            context.PC = random();
            context.SP = random();
            context.ST = random();
            return context;
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
        State *state;
        Context context;
};
