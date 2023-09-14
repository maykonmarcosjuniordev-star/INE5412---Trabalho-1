#include "ProcessParams.hpp"
#include "Context.hpp"
#include "random"

class Process
{
public:
    Process(ProcessParams *P_param)
    {
        params = P_param;
        wait_time = 0;
        end_time = -1;
        remaining_time = params->get_duration();
        state = State();
        myContext = INEcontext();
    }
    const int get_id()
    {
        return params->get_id();
    }
    const int get_creation_time()
    {
        return params->get_creation_time();
    }
    const int get_duration()
    {
        return params->get_duration();
    }
    void set_priority(int newP)
    {
        params->set_priority(newP);
    }
    const int get_priority()
    {
        return params->get_priority();
    }
    const int get_remaining_time()
    {
        return remaining_time;
    }
    // tempo passado na fila de prontos
    void spend_time()
    {
        wait_time++;
    }
    const int get_wait_time()
    {
        return wait_time;
    }
    // se o processamento acabou
    // seta end_time para o valor forncecido
    void set_end_time(int finish)
    {
        if (remaining_time == 0)
        {
            end_time = finish;
        }
    }
    const int get_end_time()
    {
        return end_time;
    }
    // tempo que encerrou - tempo que foi criado
    const int get_turnaround()
    {
        return (end_time - params->get_creation_time());
    }
    void change_state()
    {
        state.current_state++;
    }
    const char *get_state()
    {
        return state.states[state.current_state];
    }
    Context *get_context()
    {
        return &myContext;
    }
    // atualiza o tempo processoando
    // retorna o contexto;
    Context *processing()
    {
        // nunca vai abaixo de 0
        remaining_time -= 1 * (1 && remaining_time);
        return &myContext;
    }

private:
    struct State
    {
        char *states[4];
        // para coordenar com strings
        int current_state;
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
    Context myContext;
};
