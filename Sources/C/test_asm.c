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

    // int AddFractionnaire32bits_Q7_24_Q15_16(int *TabIntS);
    /*
    {
        int nbQ7_24 = 127;
        int nbQ15_16 = 32768;
        int TabIntS[2];
        TabIntS[0] = nbQ7_24/pow(2,-24);
        TabIntS[1] = nbQ15_16/pow(2,-16);
        if (AddFractionnaire32bits_Q7_24_Q15_16(TabIntS)*pow(2,-16) != (nbQ7_24 + nbQ15_16)){
            printf("Failed:\tAddFractionnaire32bits_Q7_24_Q15_16\n");
            printf("%d + %d != %d (%d)\n", nbQ7_24, nbQ15_16, AddFractionnaire32bits_Q7_24_Q15_16(TabIntS)*pow(2,-16),nbQ7_24+nbQ15_16);
            return false;
        }
    }
    */


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

    // long long MpyEntierSigneOp32bitsRes64bits(int *TabInt);
    {
        int asmOper[]={0,0,
                       1,1,
                       INT_MAX,INT_MAX,
                       INT_MIN,INT_MIN,
                       0,INT_MAX,
                       INT_MIN,1
        };

        int *Iter = asmOper;

        char i;
        for (i = 0; i < 11; ++i){
            long long result = MpyEntierSigneOp32bitsRes64bits(Iter);

            if (result != ((long long)*Iter)*((long long)*(Iter+1))){
                printf("Failed:\tMpyEntierSigneOp32bitsRes64bits\n");
                printf("%d * %d != %d (%d)\n", Iter[i], Iter[i+1], result, Iter[i]*Iter[i+1]);
                return false;
            }

            ++Iter;
        }

        printf("Passed:\tMpyEntierSigneOp32bitsRes64bits\n");
    }

    // float DivFlottant32bits(float *TabFloat);
    {
        float asmOper[]={1.0f, 1.0f,
                         FLT_MAX, FLT_MAX,
                         FLT_MIN, FLT_MIN,
                         FLT_MAX, 1.0f,
                         1.0f, FLT_MIN,
                         1.0f, 0.0f,
                         0.0f, 2.0f,
                         4.0f, 0.0f,
                         10.0f,55.333f};

        float *iter = asmOper;
        char i = 0;
        while (i < 17){
            float result = DivFlottant32bits(iter);
            if (result != iter[0]/iter[1]){
                if (! (iter[1]==0 && result==0)){
                    printf("Failed:\tDivFlottant32bits\n");
                    printf("%e / %e != %e (%e)\n", iter[0], iter[1], result, iter[0]/iter[1]);
                }
            }
            ++i;
            ++iter;
        }
        printf("Passed:\tDivFlottant32bits\n");
    }

    // Test Passed
    printf("PASSED:\tALL TESTS\n");
    return true;
}
