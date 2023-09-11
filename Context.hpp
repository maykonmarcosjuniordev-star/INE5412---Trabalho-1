#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "random"
class Context
{
public:
    long int *registers;
    long int SP;
    long int PC;
    long int ST;
    float progress;
    // altera aleatoriamente os registradores
    // e retorna se o processo já acabou
    int processing(int time_);
};

class INEcontext : public Context
{
public:
    long int registers[6];
    long int SP;
    long int PC;
    long int ST;
    float progress;
    INEcontext()
    {
        registers[0] = random();
        registers[1] = random();
        registers[2] = random();
        registers[3] = random();
        registers[4] = random();
        registers[5] = random();
        PC = random();
        ST = random();
        SP = random();
        progress = static_cast<float>(random());
    }
    // altera aleatoriamente os registradores
    // e retorna se o processo já acabou
    int processing(int time_)
    {
        int saida = 2;
        progress += 100 * (time_ / params.get_duration());
        if (progress >= 100.0)
        {
            saida = 3;
        }
        for (int i = 0; i < 6; ++i)
        {
            registers[i] = random();
        }
        PC = random();
        SP = random();
        ST = random();
    };
