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

    // Test Passed
    printf("PASSED:\tALL TESTS\n");
    return true;
}
