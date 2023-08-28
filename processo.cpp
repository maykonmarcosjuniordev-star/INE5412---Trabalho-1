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


