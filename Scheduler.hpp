#include <vector>
#include <string.h>
#include "TimeTracker.hpp"
#include "Process.hpp"
#define QUANTUM 2

class SchedulerStrategy
{
protected:
    std::vector<Process *> ready_queue;
    std::vector<Process *> finished_queue;
    std::vector<Context *> context_queue;
    // gerenciador de tempo
    TimeTracker watch;
    // se é ou não preemptivo
    bool preemp;
    Process *current_process;
    // conta quantas trocas de contexto
    int context_switch;
    // checa o processo, o insere na
    // fila de prontos e atualiza o estado
    virtual void ready_process(Process *p)
    {
        if (p)
        {
            ready_queue.push_back(p);
            p->change_state();
        }
    }
    // checa se há processos para substituir e
    // substitui o processo atual, atualizando
    // também a fila de prontos e de contextos
    virtual void alternate_process()
    {
        if (ready_queue.size() > 0)
        {
            // substitui o processo pelo próximo
            current_process = ready_queue[0];
            // estado é executando
            current_process->chage_state();
            // novo contexto sai da fila de prontos
            ready_queue.erase(ready_queue.begin());
            // houve troca de contexto
            context_switch++;
            // atualiza a fila de contextos
            context_queue.push_back(current_process->processing());
        }
    }
    // retorna se encerrou um processo,
    // não interfere na fila de prontos,
    // só na de encerrados e de contexto
    virtual bool end_process()
    {
        bool output = current_process && (current_process->get_remaining_time() == 0);
        if (output)
        {
            finished_queue[current_process->get_id() - 1] = current_process;
            // ezstado é encerrado
            current_process->change_state();
            current_process->set_end_time(get_time());
            context_queue.pop_back();
        }
        return output;
    }
    // roca se processo e contexto
    // checa se é necessário e preempta um processo
    virtual void preempt()
    {
        return;
    }

public:
    // retorna current_time do relógio
    virtual const int get_time()
    {
        return watch.get_time();
    }
    // getter do número de trocas de contexto
    virtual const int get_context_switch()
    {
        return context_switch;
    }
    // traduz o estado da fila de prontos para a saída
    virtual void get_state(vector<std::string> output)
    {
        for (int i = 0; i < ready_queue.size(); i++)
        {
            // processos aguardando a execução
            output[ready_queue[i]->get_id() - 1] = "--";
        }
        if (current_process)
        {
            // processo executando
            output[current_process->get_id()] == "##";
        }
    }
    // retorna as estatísticas finais
    virtual void get_finished(std::vector<int[2]> *output)
    {
        if (ready_queue.size() || !context_switch || current_process == nullptr)
        {
            return nullptr;
        }
        Process *temp = nullptr;
        for (int i = 0; i < output->size(); ++i)
        {
            temp = finished_queue[i];
            output[temp->get_id() - 1][0] = temp->get_turnaround();
            output[temp->get_id() - 1][1] = temp->get_wait_time();
        }
    }
    // escalonador default, sem preempção
    virtual Process *scheduling()
    {
        // verifica se precia encerrar um processo e o faz
        if ((current_process == nullptr) || end_process())
        {
            alternate_process();
        }
        else if (preemp)
        {
            preempt();
        }
        // todos na fila de prontos passam tempo sem serem processados
        for (int i = 0; i < ready_queue.size(); ++i)
        {
            ready_queue[i]->spend_time();
        }
        // passa um ciclo clock
        watch.cicle();
        return current_process;
    }
};

class FCFS_Scheduler : public SchedulerStrategy
{
public:
    FCFS_Scheduler(int queue_size)
    {
        finished_queue = vector<Process *>(queue_size, nullptr);
        current_process = nullptr;
        watch = TimeTracker();
        preemp = false;
        context_switch = 0;
    }
};

class SJF_Scheduler : public SchedulerStrategy
{
public:
    SJF_Scheduler(int queue_size)
    {
        finished_queue = vector<Process *>(queue_size, nullptr);
        current_process = nullptr;
        watch = TimeTracker();
        preemp = false;
        context_switch = 0;
    }
    SJF_Scheduler(int queue_size, bool is_preemp)
    {
        finished_queue = vector<Process *>(queue_size, nullptr);
        current_process = nullptr;
        watch = TimeTracker();
        preemp = is_preemp;
        context_switch = 0;
    }
    // organiza pela duração
    void ready_process(Process *p)
    {
        int i = 0;
        while (i < ready_queue.size() && ready_queue[i]->get_duration() < p->get_duration())
        {
            ++i
        }
        ready_queue.insert(p, i);
        p->change_state();
    }
    // preempta se houver processos mais curtos
    void preempt()
    {
        if (current_process->get_duration() > ready_queue[0]->get_duration())
        {
            ready_process(current_process);
            current_process = ready_queue[0];
            ready_queue.erase(ready_queue.begin());
            context_switch++;
            context_queue.pop_back();
            context_queue.push_back(current_process->processing());
        }
    }
};

class Priority_Scheduler : public SchedulerStrategy
{
public:
    Priority_Scheduler(int queue_size, bool is_preemp)
    {
        finished_queue = vector<Process *>(queue_size, nullptr);
        current_process = nullptr;
        preemp = is_preemp;
        watch = TimeTracker();
        context_switch = 0;
    }
    // organiza pela prioridade
    void ready_process(Process *p)
    {
        if (p)
        {
            int i = 0;
            while (i < ready_queue.size() && ready_queue[i]->get_priority() > p->get_priority())
            {
                ++i
            }
            ready_queue.insert(p, i);
            p->change_state();
        }
    }
    // preempta se houver processo prioritários
    void preempt()
    {
        if (current_process->get_priority() < ready_queue[0]->get_priority())
        {
            ready_process(current_process);
            current_process = ready_queue[0];
            ready_queue.erase(ready_queue.begin());
            context_switch++;
            context_queue.pop_back();
            context_queue.push_back(current_process->processing());
        }
    }
};

class RR_Scheduler : public SchedulerStrategy
{
private:
    int quantum;
    int remaining;

public:
    RR_Scheduler(int queue_size)
    {
        finished_queue = vector<Process *>(queue_size, nullptr);
        current_process = nullptr;
        watch = TimeTracker();
        context_switch = 0;
        // nesse caso, preempta processos encerrados
        preemp = true;
        quantum = QUANTUM;
        remaining = quantum;
    }
    Process *scheduling()
    {
        if (remaining == 0)
        {
            // retorna ao valor;
            remaining = quantum;
            // se não acabou volta para a fila de prontos
            if (current_process && current_process->get_remaining_time() > 0)
            {
                ready_process(current_process);
            }
            // alternância sempre ocorre, mesmo que seja pelo mesmo processo
            alternate_process();
        }
        // verifica se precia encerrar um processo e o faz
        else if ((current_process == nullptr))
        {
            alternate_process();
        }
        end_process();
        watch.cicle();
        // decrementa o tempo restante
        remaining--;
        return current_process;
    }
};
