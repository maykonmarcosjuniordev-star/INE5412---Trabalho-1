#include "Context.hpp"

class CPU
{
protected:
    Context *current_context;

private:
    virtual void set_context(Context *new_context);

public:
};

class INE5412 : public CPU
{
public:
    INE5412();
    void set_context(Context *new_context)
    {
        current_context = new_context;
        current_context->processing();
    }
};
