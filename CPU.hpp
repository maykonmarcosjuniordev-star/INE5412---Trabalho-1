#include "Context.hpp"

class CPU {
    public:
        CPU();

        void exec(Process p) {
            printf("Executando...\nProcesso %d executou por %ds",p.get_id(), (p.get_end_time()-p.get_start_time()));
        }

    private:
        void preempt(Context new_context) {

        }
        void set_context(Context new_context) {

        }
};
