#include "sths34pf80_api/sths34pf80_reg.h"

class STHS34PF80
{
    public:
        bool begin();
        bool getData();
        bool isConencted();

    protected: 
        stmdev_ctx_t sensor;
};