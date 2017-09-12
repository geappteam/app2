/*
 * test_asm.c
 *
 *  Created on: 8 sept. 2017
 *      Author: dene2303
 */

#include "test_asm.h"

#define NULL 0

/**
 * Returns true if every test passes
 * This test battery is used testing during development
 */
bool devTest(){

    // Testing

    // int AddFractionnaire32bits_Q7_24_Q15_16(int *TabIntS);
    // TODO: fix test procedure
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

    //  int DivSubc(unsigned int *TabIntNoS);
    { //TODO:fix test procedure -> asm function was damaged on merge dca73666323845c060c280fcbc4d2da705ed8303
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
                    return false;
                }
            }
            ++i;
            ++iter;
        }
        printf("Passed:\tDivFlottant32bits\n");
    }

    //  unsigned int DivSubc(unsigned int *TabIntNoS);
        {
            unsigned int TabIntNoS[12] = {2,4,5,55,8,808,4,2,0,55,8,0};
            unsigned int TabIntNoS1[2] = {2,4};
            unsigned int TabIntNoS2[2] = {5,55};
            unsigned int TabIntNoS3[2] = {8,808};
            unsigned int TabIntNoS4[2] = {4,2};
            unsigned int TabIntNoS5[2] = {0,55};
            unsigned int TabIntNoS6[2] = {8,0};
            unsigned int result[6] = {0,0,0,0,0,0};
            result[0] = DivSubc(TabIntNoS1);
            result[1] = DivSubc(TabIntNoS2);
            result[2] = DivSubc(TabIntNoS3);
            result[3] = DivSubc(TabIntNoS4);
            result[4] = DivSubc(TabIntNoS5);
            result[5] = DivSubc(TabIntNoS6);
            int error = NULL;
            if(result[0] == (TabIntNoS[1]/TabIntNoS[0])){
                if(result[1] == (TabIntNoS[3]/TabIntNoS[2])){
                    if(result[2] == (TabIntNoS[5]/TabIntNoS[4])){
                        if(result[3] == NULL){
                            if(result[4] == NULL){
                                if(result[5] == NULL)
                                    printf("Passed:\tDivSubc\n");
                                else
                                    error = 6;
                            }
                            else
                                error = 5;
                        }
                        else
                            error = 4;
                    }
                    else
                        error = 3;
                }
                else
                    error = 2;
            }
            else
            error = 1;

            if(error != NULL){
                printf("Failed:\tDivSubc\n");
                printf("%u / %u != %u \n", TabIntNoS[error], TabIntNoS[error-1], result[error-1]);
                printf("%u / %u = %u \n", TabIntNoS[error], TabIntNoS[error-1], (TabIntNoS[error]/TabIntNoS[error-1]));
            }
        }

    // void EncrypterDonnees (unsigned int *TabIntNoS);
    {
        //unsigned int testGroup[]={1,2,3,4,5,6,7,8};
        // Using a heap allocation to align memory
        int * testGroup;
        size_t blockSize = sizeof(unsigned int)*8;  // Application demands 8 * 32 bits
        testGroup= (int*) memalign(blockSize,blockSize);

        int i;
        for (i = 0; i < 8; ++i){
            testGroup[i] = i+1;
        }

        EncrypterDonnees(testGroup);

        for (i = 0; i < 8; ++i){
            unsigned int eval = (i+1)^0xFFFFFFFF;
            if(testGroup[i] != eval)
            {
                printf("Failed:\tEncrypterDonnees\n");
                printf("%#010X XOR 0xFFFFFFFF != %#010X\n", i+1, testGroup[i]);
                return false;
            }
        }

        free(testGroup);

        printf("Passed:\tEncrypterDonnees\n");
    }

    // Test Passed
    printf("PASSED:\tALL TESTS\n");
    return true;
}

/**
 * This procedure prints the results demanded in
 * http://www.gel.usherbrooke.ca/s5elec/a17/doc/app2/file/Validation_APP2_A17.pdf
 */
void validationTest(){

    printf("\f\nValidation APP2 S5elec H17\n");


    // AddEntierSigne32bits ( 4 294 967 295, 1) -> output in hex: 0xXXXX
    {
        int Operandes[] = {0xFFFFFFFF, 1};
        int Resultat = AddEntierSigne32bits(Operandes);
        printf("\n\nAddEntierSigne32bits (Bonus):\n\n\t");
        printf("%#010X + %d = %#010X\n", Operandes[0], Operandes[1], Resultat);
    }


    // AddFractionnaire32bits_Q7.24_Q15.16 ( 14.25, 1) -> output in decimal: integer
    {
        int Operandes[] = {(int)(14.25*(1<<24)), (int)(1<<16)};
        int Resultat = AddFractionnaire32bits_Q7_24_Q15_16(Operandes);
        printf("\n\nAddFractionnaire32bits_Q7.24_Q15.16 (resultat Q15.16):\n\n\t");
        printf("%.2f + %d = %d\n", ((double)Operandes[0])/(1<<24), Operandes[1]>>16, Resultat);
    }

    // SubEntierSigne32bits (1,2) -> unspecified format
    {
        int Operandes[] = {1, 2};
        int Resultat = SubEntierSigne32bits(Operandes);
        printf("\n\nSubEntierSigne32bits (Bonus):\n\n\t");
        printf("%d - %d = %d\n", Operandes[0], Operandes[1], Resultat);
    }

    // SubFlottant64bits ( 2.01 , 8.12 ) -> unspecified format
    {
        double Operandes[] = {2.01, 8.12};
        double Resultat = SubFlottant64bits(Operandes);
        printf("\n\nSubFlottant64bits:\n\n\t");
        printf("%.2f - %.2f = %.2f\n", Operandes[0], Operandes[1], Resultat);
    }

    // MpyEntierNonSigneOp32bitsRes64bits  ( 32 , 3221225472 ) -> hex : unsigned int
    {
        unsigned int Operandes[] = {32, 3221225472};
        unsigned long long Resultat = MpyEntierNonSigneOp32bitsRes64bits(Operandes);
        printf("\n\nMpyEntierNonSigneOp32bitsRes64bits:\n\n\t");
        printf("%u * %u = %#018llX\n", Operandes[0], Operandes[1], Resultat);
    }

    // MpyEntierSigneOp32bitsRes64bits  ( 32 , â€�1073741824 ) -> hex : signed int
    {
        int Operandes[] = {32, -1073741824};
        long long Resultat = MpyEntierSigneOp32bitsRes64bits(Operandes);
        printf("\n\nMpyEntierSigneOp32bitsRes64bits:\n\n\t");
        printf("%d * %d = %#018llX\n", Operandes[0], Operandes[1], Resultat);
    }

    // MpyfractionnaireOp32bitsRes64bits_Q7.24_Q15.16 (14.25 , 1) -> hex : Q23.40
    {
        int Operandes[] = {(int)(14.25*(1<<24)), (int)1<<16};
        long long Resultat = MpyfractionnaireOp32bitsRes64bits_Q7_24_Q15_16(Operandes);
        printf("\n\nMpyfractionnaireOp32bitsRes64bits_Q7.24_Q15.16:  (Q23.40)\n\n\t");
        printf("%.2f * %d = %#018llX\n", ((double)Operandes[0])/(1<<24), Operandes[1]>>16, Resultat);
    }

    // DivIncrementation (16777215 , 1) -> decimal : unsigned integer
    {
        printf("\n\nComputing ...\n");    // TODO: Optimize this function
        unsigned int Operandes[] = {16777215, 1};
        unsigned int Resultat = DivIncrementation(Operandes);
        printf("DivIncrementation:\n\n\t");
        printf("%u / %u = %u\n", Operandes[0], Operandes[1], Resultat);
    }

    // DivSubc ( 16777215 , 1 ) and (11 , 3) -> output in decimal: unsigned integer
    {
        unsigned int Operandes1[] = { 16777215, 1 };
        unsigned int Operandes2[] = { 11, 3 };
        unsigned int result1 = DivSubc(Operandes1);
        unsigned int result2 = DivSubc(Operandes2);
        printf("\n\nDivSubc TEST 1:\n\n\t");
        printf("%u / %u = %u\n", Operandes1[0], Operandes1[1], result1);
        printf("\n\nDivSubc TEST 2:\n\n\t");
        printf("%u / %u = %u\n", Operandes2[0], Operandes2[1], result2);
    }

    // DivFlottant32bits (11, 3) -> output in decimal: float
    {
        float Operandes[] = { 11, 3 };
        float Resultat = DivFlottant32bits(Operandes);
        printf("\n\nDivFlottant32bits:\n\n\t");
        printf("%.1f / %.1f = %f\n", Operandes[0], Operandes[1], Resultat);
    }

    // EncrypterDonnees (defini par le tuteur)
    {
        printf("\n\nEncrypterDonnees: Aucune valeurs specifies\n");
    }
}

