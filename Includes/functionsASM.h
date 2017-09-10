/*
 * This document holds the functions prototypes of the functions detailed
 * in assembly language
 *
 * functionsASM.h
 *
 *  Created on: 8 sept. 2017
 *      Author: dene2303
 */

#ifndef INCLUDES_FUNCTIONSASM_H_
#define INCLUDES_FUNCTIONSASM_H_

// Addition
double AddEntierNonSigne32bits(unsigned int *TabIntNoS);
double AddEntierSigne32bits(int *TabIntS);
int AddFractionnaire32bits_Q7_24_Q15_16(int *TabIntS);

// Substraction
double SubEntierSigne32 (int *TabIntNoS);
double SubFlottant64bits(double *TabXXX);
long SubEntierNonSigne32bits(unsigned int *TabIntNoS);

// Multiplication
unsigned long long  MpyEntierNonSigneOp32bitsRes64bits(unsigned int *TabIntNoS);
double MpyFlottant64bits(double *TabXXX);
long long MpyEntierSigneOp32bitsRes64bits(int *TabInt);

// long long MpyfractionnaireOp32bitsRes64bits_Q7_24_Q15_16(int *TabInt);
// return value on Q23.40
#define MpyfractionnaireOp32bitsRes64bits_Q7_24_Q15_16 MpyEntierSigneOp32bitsRes64bits

#endif /* INCLUDES_FUNCTIONSASM_H_ */
