#ifndef _CFUNCTIONS_H
#define _CFUNCTIONS_H

#include <stdbool.h>
#include <stdio.h>
#include "functionsASM.h"

#define NULL 0

#define ERROR 0
#define SUCCESS 1

#define UNSIGNED_INT_MAX 65535

enum operation {
    Addition = 1,
    Subtraction = 2,
    Multiplication = 3,
    Division   = 4,
    Encrypt   = 5
};

enum dataTypeName {
    UnsignedInt_32bits = 12,
    UnsignedInt_32bits_By_Incremenation = 13,
    UnsignedInt_32bits_By_Cond_Sub = 14,
    SignedInt_32bits = 22,
    Fractional_32bits = 32,
    Floating_32bits = 42,
    Floating_64bits   = 44
};

void process();

bool ObtenirType(int *Liste);

bool ObtenirFormat(int *Liste);

bool ObtenirOperation(int *Liste);

bool AnalyserListe(int *Liste, unsigned int *TabIntNoS, signed int *TabIntS,float *TabFloat, double *TabDouble,int *TabDonnees);

int ConvertirListe(int *Liste);

bool ChoisirOperandesIntNoS(unsigned int *TabIntNoS);

bool ChoisirOperandesIntS(signed int *TabIntS);

bool ChoisirOperandesFloat(float *TabFloat);

bool ChoisirOperandesDouble(double *TabDouble);

bool ChoisirDonnees(int *TabDonnees);

bool EncrypterDonneesInC(int *TabDonnees);

void printResult(unsigned short *TabShortNoS, short *TabShortS,  int *TabDonnees);

#endif //_CFUNCTIONS_H
