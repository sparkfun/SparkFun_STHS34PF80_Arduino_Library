#ifndef __SparkFun_STHS34PF80_Library_H__
#define __SparkFun_STHS34PF80_Library_H__

#include "sths34pf80_class.h"

bool STHS34PF80::begin()
{
    return false;
}

bool STHS34PF80::getData()
{
    return false;
}

bool STHS34PF80::isConencted()
{
    uint8_t devId = 0;
    int32_t err = sths34pf80_device_id_get(&sensor, &devId);
    if(err)
        return false;
    return devId == STHS34PF80_ID;
}

#endif