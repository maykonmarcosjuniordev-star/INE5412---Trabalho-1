#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <cstdlib>

class Context
{
public:
    virtual void processing() = 0;
    virtual ~Context() {}

    virtual void *get_registers() = 0;
    virtual void *get_SP() = 0;
    virtual void *get_PC() = 0;
    virtual void *get_ST() = 0;
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

    void *get_registers() override
    {
        return registers;
    }

    void *get_SP() override
    {
        return &SP;
    }

    void *get_PC() override
    {
        return &PC;
    }

    void *get_ST() override
    {
        return &ST;
    }
};

#endif // CONTEXT_HPP
