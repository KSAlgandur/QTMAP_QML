#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <linux/types.h>
#include <stdint.h>

namespace my_type

{

        struct word
    {
        __u8 addr8;
        __u32 data32;
    };
    word w;



}
#endif // DATA_TYPES_H
