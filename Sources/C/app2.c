#include <stdbool.h>
#include "test_asm.h"

unsigned long long  compiled(unsigned long long in){
    return in<<16;
}

main()
{
    //  unsigned int args[] = {55, 55};

    test();

    unsigned long long val = compiled(0xFFFF);
    //printf("%d\n", val);
}
