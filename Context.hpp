#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <cstdlib> // For the rand function

class Context
{

public:
    virtual void processing();
    Context() {}
    virtual ~Context() {}
    virtual long int *get_registers();
    virtual long int get_SP();
    virtual long int get_PC();
    virtual long int get_ST();
};

class INEcontext : public Context
{
private:
    long int registers[6];
    long int SP;
    long int PC;
    long int ST;

public:
    INEcontext()
    {
        for (int i = 0; i < 6; ++i)
        {
            registers[i] = rand();
        }
        PC = rand();
        SP = rand();
        ST = rand();
    }

    void processing() override
    {
        for (int i = 0; i < 6; ++i)
        {
            registers[i] = rand();
        }
        PC = rand();
        SP = rand();
        ST = rand();
    }
};

#endif // CONTEXT_HPP
