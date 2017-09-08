#include <stdio.h>

typedef int bool;
#define true 1
#define false 0

// Assembly functions prototypes
int Addition8IntASM(int a, int b, int c, int d, int e, int f, int g, int h);
float AdditionFloatASM(float i);
int AddSatureASM(int,int);

// C functions prototypes
bool ObtenirType(int *Liste);
bool ObtenirFormat(int *Liste);
bool ObtenirOperation(int *Liste);

main(void)
{
    int a,b,c,d,e,f,g,h;

    a = 1;
    b = 1;
    c = 1;
    d = 1;
    e = 1;
    f = 1;
    g = 1;
    h = 1;

    int result1 = Addition8IntASM(a,b,c,d,e,f,g,h);

    float i;

    i = 1.5;

    float result2 = AdditionFloatASM(i);

    int result3 = AddSatureASM(0xFFFFFFF0, 0x10);

    return 0;

}

// C functions
bool ObtenirType(int *Liste){
    return true;
}

bool ObtenirFormat(int *Liste){
    return true;
}

bool ObtenirOperation(int *Liste){
    return true;
}

