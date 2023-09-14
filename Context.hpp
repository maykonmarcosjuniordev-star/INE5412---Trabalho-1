#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <cstdlib> // For the rand function

class Context
{
public:
    virtual void processing() = 0; // Pure virtual function
    virtual ~Context() {}

    virtual long int *get_registers() = 0;
    virtual long int get_SP() = 0;
    virtual long int get_PC() = 0;
    virtual long int get_ST() = 0;
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

    long int *get_registers() override
    {
        return registers;
    }

    long int get_SP() override
    {
        return SP;
    }

    long int get_PC() override
    {
        return PC;
    }

    long int get_ST() override
    {
        return ST;
    }
};

#endif // CONTEXT_HPP
