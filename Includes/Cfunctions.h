#ifndef _CFUNCTIONS_H
#define _CFUNCTIONS_H

#include <stdbool.h>
#include <stdio.h>
#include "functionsASM.h"

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
    UnsignedInt_32bits_By_Incremenation = 13,  //TODO: 'Y' must be replaced by a real number, then remove comments
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

bool AnalyserListe(int *Liste);

int ConvertirListe(int *Liste);

void ChoisirOperandesIntNoS(unsigned int *TabIntNoS);

void ChoisirOperandesIntS(signed int *TabIntS);

void ChoisirOperandesFloat(float *TabFloat);

void ChoisirOperandesDouble(double *TabDouble);

void ChoisirDonnees(int *TabDonnees);

void printResult(unsigned short *TabShortNoS, short *TabShortS,  int *TabDonnees);

void ClearListe();

void ChoisirCryptData(int TabDonnees[8]);

#endif //_CFUNCTIONS_H
