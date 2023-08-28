class Processo
{
    int ID;
    int begin;
    int end;
    int duration;
    //prioridade
    int current_state;
    int execution_time;
        Processo(int id, int b, int e, int d)
        {
        ID = id;
        begin = b;
        end = e;
        duration = d;
        current_state = 0;
        execution_time = 0;
        }

};


class FCFS			//First Come, First Served
{

};

class SJF			//Shortest Job First
{

};

class PSP			//Por prioridade, sem preempC'C#o
{


};


class PCP			//Por prioridade, com preempC'C#o
{

};


class RR			//Round-Robin com quantum = 2s, sem prioridade

{

};



int
main ()
{
    char *reg;
    double *SP;			//stack pointer
    double *PC;			//program counter 
    double *ST;			//status



    return 0;
}
