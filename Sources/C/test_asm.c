/*
 * test_asm.c
 *
 *  Created on: 8 sept. 2017
 *      Author: dene2303
 */

#include "test_asm.h"

/**
 * Returns true if every test passes
 */
bool test(){

    // Testing

    // unsigned long long  MpyEntierNonSigneOp32bitsRes64bits(unsigned int *TabInt);
    {
        unsigned int op1[] = { 50, 50 };
        unsigned int op2[] = {0xFFFFFFFF, 0xFFFFFFFF};

        if (MpyEntierNonSigneOp32bitsRes64bits(op2) != (unsigned long long)op2[0] * op2[1]){
            printf("Failed:\tMpyEntierNonSigneOp32bitsRes64bits\n");
            printf("%d * %d != %d\n", op2[0], op2[1], MpyEntierNonSigneOp32bitsRes64bits(op2));
            return false;
        }

        if (MpyEntierNonSigneOp32bitsRes64bits(op1) != (unsigned long long)op1[0] * op1[1]){
            printf("Failed:\tMpyEntierNonSigneOp32bitsRes64bits\n");
            printf("%d * %d != %d\n", op1[0], op1[1], MpyEntierNonSigneOp32bitsRes64bits(op1));
            return false;
        }

        printf("Passed:\tMpyEntierNonSigneOp32bitsRes64bits\n");
    }

    // long long MpyfractionnaireOp32bitsRes64bits_Q7_24_Q15_16(int *TabInt);
    {
        int asmOper[2];
        double operand1 = -4.125;
        double operand2 = 655.25;

        asmOper[0] = (int)(operand1*16777216.0); // Q7.24
        asmOper[1] = (int)(operand2*65536.0);   // Q15.16

        long long result = MpyfractionnaireOp32bitsRes64bits_Q7_24_Q15_16(asmOper);
        double parsedRes = (double)(result / 1099511627776.0);

        if (parsedRes != operand1*operand2){
            printf("Failed:\tMpyfractionnaireOp32bitsRes64bits_Q7_24_Q15_16\n");
            printf("%f * %f != %f\n", operand1, operand2, parsedRes);
            return false;
        }

        printf("Passed:\tMpyfractionnaireOp32bitsRes64bits_Q7_24_Q15_16\n");
    }

    // Test Passed
    printf("PASSED:\tALL TESTS\n");
    return true;
}
