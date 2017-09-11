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

        //Test AddFractionnaire32bits_Q7_24_Q15_16
        int nbQ7_24 = 1000;
        int nbQ15_16 = 32768;
        int TabIntS[2];
        TabIntS[0] = nbQ7_24/pow(2,-24);
        TabIntS[1] = nbQ15_16/pow(2,-16);
        int resultQ15_16 = AddFractionnaire32bits_Q7_24_Q15_16(TabIntS);
        int result = resultQ15_16*pow(2,-16);
        if (AddFractionnaire32bits_Q7_24_Q15_16(TabIntS) != (TabIntS[0] + TabIntS[1])){
                    printf("Failed:\tMpyEntierNonSigneOp32bitsRes64bits\n");
                    printf("%d * %d != %d\n", op2[0], op2[1], MpyEntierNonSigneOp32bitsRes64bits(op2));
                    return false;
                }
        //////////////////////////////////////////////////////////////////////////////////

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

    //  int DivSubc(unsigned int *TabIntNoS);
    {
        unsigned int TabIntNoS[2];
        TabIntNoS[0] =1030; //NUM
        TabIntNoS[1] =10; //DEN
        int result = DivSubc(TabIntNoS);

        if ((TabIntNoS[0]/TabIntNoS[1]) != result){
            printf("Failed:\tDivSubc\n");
            printf("%d / %d != %d\n", TabIntNoS[0], TabIntNoS[1], result);
            return false;
        }

        printf("Passed:\tDivSubc\n");
    }
    // Test Passed
    printf("PASSED:\tALL TESTS\n");
    return true;
}
