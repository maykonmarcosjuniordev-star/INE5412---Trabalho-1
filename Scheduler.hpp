#include <vector>
#include <string.h>
#include "TimeTracker.hpp"
#include "Process.hpp"
#define QUANTUM 2

class SchedulerStrategy
{
protected:
    // processos que já terminaram sua execução
    std::vector<Process *> finished_queue;
    // processo executando
    Process *current_process;
    // gerenciador de tempo
    TimeTracker watch;
    // se é ou não preemptivo
    bool preemp;
    // conta quantas trocas de contexto
    int context_switch;
    // processos prontos para executar
    std::vector<Process *> ready_queue;
    // salvando contextos
    std::vector<Context *> context_queue;
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
            current_process->change_state();
            // novo contexto sai da fila de prontos
            ready_queue.erase(ready_queue.begin());
            // houve troca de contexto
            context_switch++;
            // atualiza a fila de contextos
            context_queue.push_back(current_process->get_context());
        }
    }
    // retorna se encerrou um processo,
    // não interfere na fila de prontos,
    // só na de encerrados e de contexto
    virtual bool end_process()
    {
        bool output = (current_process != nullptr) && (current_process->get_remaining_time() == 0);
        if (output)
        {
            int idx = current_process->get_id() - 1;
            if (idx < 0 || idx >= static_cast<int>(finished_queue.size()))
            {
                return false;
            }
            finished_queue[idx] = current_process;
            // estado é encerrado
            current_process->change_state();
            current_process->set_end_time(get_time());
            context_queue.pop_back();
            if (ready_queue.size() == 0)
            {
                current_process = nullptr;
            }
        }
        return output;
    }
    // checa se é necessário e preempta um processo
    virtual void preempt() {}

public:
    SchedulerStrategy(int Nprocess = 100, bool is_preemp = false)
        : finished_queue(Nprocess, nullptr), current_process(nullptr),
          watch(), preemp(is_preemp), context_switch(0)
    {
    }
    virtual ~SchedulerStrategy() {}
    // retorna current_time do relógio
    virtual int get_time() const
    {
        return watch.get_time();
    }
    // getter do número de trocas de contexto
    virtual int get_context_switch() const
    {
        return context_switch;
    }
    // mapeia o estado do processador para um vetor de strings
    virtual void get_state(std::vector<std::string> &output)
    {
        for (std::size_t i = 0; i < ready_queue.size(); i++)
        {
            // processos aguardando a execução
            int idx = ready_queue[i]->get_id() - 1;
            if (idx >= 0 && idx < static_cast<int>(output.size()))
            {
                output[idx] = "--";
            }
        }
        if (current_process != nullptr)
        {
            // processo executando
            int idx = current_process->get_id() - 1;
            if (idx >= 0 && idx < static_cast<int>(output.size()))
            {
                output[idx] = "##";
            }
        }
    }
    // retorna as estatísticas finais
    virtual void get_finished(std::vector<std::array<int, 2>> &output)
    {
        Process *temp = nullptr;
        for (std::size_t i = 0; i < output.size(); ++i)
        {
            temp = finished_queue[i];
            int idx = temp->get_id() - 1;
            if (idx >= 0 && idx < static_cast<int>(output.size()))
            {
                output[idx][0] = temp->get_turnaround();
                output[idx][1] = temp->get_wait_time();
            }
        }
    }
    // escalonador default, sem preempção
    // tcheca o processo, o insere na
    // fila de prontos e atualiza o estado
    virtual void ready_process(Process *p)
    {
        if (p != nullptr)
        {
            ready_queue.push_back(p);
            p->change_state();
        }
    }
    // escalonamento padrão
    // retornando o processo executando
    virtual Process *scheduling()
    {
        if (current_process != nullptr)
        { // processo executando
            current_process->processing();
        }
        // verifica se precia encerrar um processo e o faz
        if ((current_process == nullptr) || end_process())
        {
            alternate_process();
        }
        else if (preemp)
        { // a preempção default é vazia
            preempt();
        }
        // todos na fila de prontos passam tempo sem serem processados
        for (std::size_t i = 0; i < ready_queue.size(); ++i)
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
    FCFS_Scheduler(int Nprocess = 100)
        : SchedulerStrategy(Nprocess, false)
    {
    }
};

class SJF_Scheduler : public SchedulerStrategy
{
public:
    SJF_Scheduler(int Nprocess = 100, bool is_preemp = false)
        : SchedulerStrategy(Nprocess, is_preemp)
    {
    }
    // organiza pela duração
    void ready_process(Process *p) override
    {
        if (p == nullptr)
        {
            return;
        }
        std::size_t i = 0;
        while (i < ready_queue.size() && ready_queue[i]->get_duration() < p->get_duration())
        {
            ++i;
        }
        ready_queue.insert(ready_queue.begin() + i, p);
        p->change_state();
    }
    // preempta se houver processos mais curtos
    void preempt() override
    {
        if (ready_queue.size() && (current_process->get_duration() > ready_queue[0]->get_duration()))
        {
            current_process->change_state(-1);
            ready_process(current_process);
            alternate_process();
        }
    }
};

class Priority_Scheduler : public SchedulerStrategy
{
public:
    Priority_Scheduler(int Nprocess = 100, bool is_preemp = false)
        : SchedulerStrategy(Nprocess, is_preemp)
    {
    }
    // organiza pela prioridade
    void ready_process(Process *p) override
    {
        if (p == nullptr)
        {
            return;
        }
        std::size_t i = 0;
        while (i < ready_queue.size() && ready_queue[i]->get_priority() > p->get_priority())
        {
            ++i;
        }
        ready_queue.insert(ready_queue.begin() + i, p);
        p->change_state();
    }
    // preempta se houver processo prioritários
    void preempt() override
    {
        if (ready_queue.size() && (current_process->get_priority() < ready_queue[0]->get_priority()))
        {
            current_process->change_state(-1);
            ready_process(current_process);
            alternate_process();
        }
    }
};

class RR_Scheduler : public SchedulerStrategy
{
private:
    unsigned int quantum;
    unsigned int remaining;

public:
    RR_Scheduler(int Nprocess = 100, int Nquantum = QUANTUM)
        : SchedulerStrategy(Nprocess, true), quantum(Nquantum), remaining(Nquantum)
    {
    }
    Process *scheduling() override
    {
        if (current_process != nullptr)
        {
            current_process->processing();
        }
        // evita alternância dupla
        bool must_altern = true;
        // verifica se precia encerrar um processo e o faz
        // caso seja a primeira iteração também
        if (end_process() || (current_process == nullptr))
        {
            must_altern = false;
            alternate_process();
        }
        if (remaining == 0)
        {
            // retorna ao valor;
            remaining = quantum;
            if (must_altern)
            {
                // se não acabou volta para a fila de prontos
                ready_process(current_process);
                // alternância ocorre mesmo que seja pelo mesmo processo
                alternate_process();
            }
        }
        // todos na fila de prontos passam tempo sem serem processados
        for (std::size_t i = 0; i < ready_queue.size(); ++i)
        {
            ready_queue[i]->spend_time();
        }
        watch.cicle();
        // decrementa o tempo restante
        remaining--;
        return current_process;
    }
};
