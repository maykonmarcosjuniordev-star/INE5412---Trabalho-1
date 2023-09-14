#include "Context.hpp"

class CPU
{
protected:
    Context *current_context;

public:
    CPU() {}
    virtual ~CPU() {}

    virtual void set_context(Context *new_context);
};

class INE5412 : public CPU
{
public:
    INE5412()
    {
        current_context = nullptr;
    }
    ~INE5412() {}
    void set_context(Context *new_context) override
    {
        current_context = new_context;
        current_context->processing();
    }
};
