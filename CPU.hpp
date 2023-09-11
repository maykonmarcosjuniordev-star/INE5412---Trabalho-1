#include "Context.hpp"

class CPU
{
private:
    virtual void preempt(Context new_context);
    virtual void set_context(Context new_context);

public:
};

class INE5412 : public CPU
{
    void preempt(Context new_context)
    {
    }
    void set_context(Context new_context)
    {
    }
}
