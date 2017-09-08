#include <stdbool.h>
#include "test_asm.h"

unsigned long long  compiled(unsigned int *TabInt){
    return *TabInt * *(TabInt+1);
}

main()
{
    unsigned int args[] = {55, 55};

    test();

    unsigned long long val = compiled(args);
    //printf("%d\n", val);
}
