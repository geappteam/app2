#ifndef _CFUNCTIONS_H
#define _CFUNCTIONS_H

#include <stdbool.h>
#include <stdlib.h>

static int Liste[3] = {0};
static int dataType = 0;
static int dataFormat = 0;
static int op = 0;

enum operation {
    Addition = 1,
    Subtraction = 2,
    Multiplication = 3,
    Division   = 4,
    Encrypt   = 5
};

enum dataTypeName {
    UnsignedInt = 12,
    SignedInt = 22,
    Fractional = 32,
    Floating   = 44
    //...
};

bool ObtenirType(int *Liste);

bool ObtenirFormat(int *Liste);

bool ObtenirOperation(int *Liste);

bool AnalyserListe(int *Liste, unsigned short *TabShortNoS, short *TabShortS);

int ConvertirListe(int *Liste);

bool ChoisirOperandesXXX(int *Tab);

// Optionnel
//bool printResult();

#endif //_CFUNCTIONS_H
