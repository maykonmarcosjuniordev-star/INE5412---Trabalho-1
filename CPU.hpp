#include "Context.hpp"

class CPU
{
protected:
    Context current_context;

private:
    virtual void preempt(Context new_context);
    virtual void set_context(Context new_context);

public:
};

class INE5412 : public CPU
{
    INE5412();
    void preempt(Context new_context)
    {
        current_context = new_context;
    }
    void set_context(Context new_context)
    {
        current_context = new_context;
    }
}
