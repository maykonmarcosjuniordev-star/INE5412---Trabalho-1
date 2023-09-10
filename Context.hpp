#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "random"
class Context {
    public:
        long int *registers;
        long int SP;
        long int PC;
        long int ST;
        float progress;
};

class INEcontext : public Context {
    public:
        long int registers[6];
        long int SP;
        long int PC;
        long int ST;
        float progress;
        INEcontext() {
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
};
