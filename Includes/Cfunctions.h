#ifndef _CFUNCTIONS_H
#define _CFUNCTIONS_H

#include <stdbool.h>
#include <stdio.h>

#define NULL 0

#define ERROR 0
#define SUCCESS 1

enum operation {
    Addition = 1,
    Subtraction = 2,
    Multiplication = 3,
    Division   = 4,
    Encrypt   = 5
};

enum dataTypeName {
    UnsignedInt_32bits = 12,
//    UnsignedInt_32bits = 1Y,  //TODO: 'Y' must be replaced by a real number, then remove comments
//    UnsignedInt_32bits = 1Y,
    SignedInt_32bits = 22,
    Fractional_32bits = 32,
    Floating_32bits = 42,
    Floating_64bits   = 44
};

void process();

bool ObtenirType(int *Liste);

bool ObtenirFormat(int *Liste);

bool ObtenirOperation(int *Liste);

bool AnalyserListe(int *Liste, unsigned short *TabShortNoS, short *TabShortS);

int ConvertirListe(int *Liste);

bool ChoisirOperandesIntNoS(unsigned int *TabIntNoS);

bool ChoisirOperandesIntS(signed int *TabIntS);

bool ChoisirOperandesFloat(float *TabFloat);

bool ChoisirOperandesDouble(double *TabDouble);

void printResult();

#endif //_CFUNCTIONS_H
