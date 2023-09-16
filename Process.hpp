#include "ProcessParams.hpp"
#include "Context.hpp"
#include "random"
#include <string.h>
#define N_STATES 4

class Process
{
private:
    struct State
    {
        std::string states[N_STATES];
        // para coordenar com strings
        unsigned int current_state;
        State()
        {
            states[0] = "novo";
            states[1] = "pronto";
            states[2] = "executando";
            states[3] = "terminado";
            current_state = 0;
        }
    };
    // parâmetros lidos na entrada
    ProcessParams *params;
    // tempo na fila de prontos
    unsigned int wait_time;
    // tempo encerrado
    int end_time;
    // quanto falta para terminar
    unsigned int remaining_time;
    // estado de execução
    State state;
    // contexto
    Context *myContext;

public:
    Process(ProcessParams *P_param)
    {
        params = P_param;
        wait_time = 0;
        end_time = -1;
        remaining_time = params->get_duration();
        state = State();
        myContext = new INEcontext();
    }
    ~Process()
    {
        delete myContext;
    }
    int get_id() const
    {
        return params->get_id();
    }
    int get_creation_time() const
    {
        return params->get_creation_time();
    }
    int get_duration() const
    {
        return params->get_duration();
    }
    int get_priority() const
    {
        return params->get_priority();
    }
    void set_priority(int newP)
    {
        params->set_priority(newP);
    }
    int get_remaining_time() const
    {
        return remaining_time;
    }
    // tempo passado na fila de prontos
    void spend_time()
    {
        wait_time++;
    }
    int get_wait_time() const
    {
        return wait_time;
    }
    // se o processamento acabou, seta
    // end_time para o valor forncecido
    void set_end_time(int finish)
    {
        if (remaining_time == 0)
        {
            end_time = finish;
        }
    }
    int get_end_time() const
    {
        return end_time;
    }
    // tempo que encerrou - tempo que foi criado
    int get_turnaround() const
    {
        return (end_time - params->get_creation_time());
    }
    void change_state()
    {
        state.current_state = (state.current_state + 1) % (N_STATES);
    }
    void change_state(int steps)
    {
        state.current_state = (state.current_state + steps) % (N_STATES);
    }
    std::string get_state() const
    {
        return state.states[state.current_state];
    }
    Context *get_context()
    {
        return myContext;
    }
    // atualiza o tempo processando
    // retorna o contexto;
    Context *processing()
    {
        // nunca vai abaixo de 0
        remaining_time -= 1 * (1 && remaining_time);
        return myContext;
    }
};
