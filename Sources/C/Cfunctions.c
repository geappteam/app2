/*
 * Cfunctions.c
 *
 *  Created on: 8 sept. 2017
 *      Author: para2709
 */

#include "Cfunctions.h"

#pragma DATA_ALIGN(TabDonnees, 32)
int TabDonnees[8] = {0,0,0,0,0,0,0,0};
int Liste[3] = {0,0,0};
unsigned int TabIntNoS [2] = {0,0};
int TabIntS [2] = {0,0};
double TabDouble [2] = {0,0};
float TabFloat [2] = {0,0};


void process(){

    while(1)
    {
        printf("\n||||||||||||||||||| BINARY CALCULATOR :     BEGIN |||||||||||||||||||\n\n");

        //Program process
        ObtenirType(Liste);
        ObtenirFormat(Liste);
        ObtenirOperation(Liste);
        AnalyserListe(Liste);

        ClearListe();

        printf("\n||||||||||||||||||| BINARY CALCULATOR :     END |||||||||||||||||||\n\n");
    }
}

bool ObtenirType(int *Liste){
    if(Liste != NULL)
    {
        printf("\n| 1 => Unsigned Int | 2 => Signed Int | 3 => Fractional | 4 => Floating |\n\n");
        printf("Enter type: ");
        scanf("%d",Liste);

        if(*Liste > 0 && *Liste < 5)
            return SUCCESS;
    }
    return ERROR;
}

bool ObtenirFormat(int *Liste){
    if(Liste != NULL)
    {
        printf("\n\n| 1 => 16 bits | 2 => 32 bits | 3 => 40 bits | 4 => 64 bits |\n\n");
        printf("Enter format: ");
        scanf("%d",Liste+1);

        if(Liste[1] > 0 && Liste[1] < 5)
            return SUCCESS;
    }
    return ERROR;
}

bool ObtenirOperation(int *Liste){
    if(Liste != NULL)
    {
        printf("\n\n| 1 => + | 2 => - | 3 => * | 4 => / | 5 => Encryption |\n\n");
        printf("Enter operation: ");
        scanf("%d",Liste+2);

        if(Liste[2] > 0 && Liste[2] < 6)
            return SUCCESS;
    }
    return ERROR;
}

void AnalyserListe(int *Liste){

    bool noOperationFound = false;

    if(Liste != NULL)
    {
        int choix = ConvertirListe(Liste);

        if(choix != NULL)
        {
            printf("\n");
            switch (Liste[2]){
                case Addition :
                {
                    switch (choix){
                        case  UnsignedInt_32bits:
                        {
                            ChoisirOperandesIntNoS(TabIntNoS);
                            printf("%u", AddEntierNonSigne32bits(TabIntNoS));
                            break;
                        }
                        case  SignedInt_32bits:
                        {
                            ChoisirOperandesIntS(TabIntS);
                            printf("%d", AddEntierSigne32bits(TabIntS));
                            break;
                        }
                        case  Fractional_32bits:
                        {
                            ChoisirOperandesDouble(TabDouble);
                            TabIntS [0] = (int)(TabDouble[0] * (1<<24));
                            TabIntS [1] = (int)(TabDouble[1] * (1<<16));
                            int res = AddFractionnaire32bits_Q7_24_Q15_16(TabIntS);
                            printf("%#010X (%e)", res, ((double)res) / (1<<16));
                            break;
                        }
                        default:
                            noOperationFound = true;
                    }
                    break;
                }
                case Subtraction :
                {
                    switch (choix){
                        case  UnsignedInt_32bits:
                            ChoisirOperandesIntNoS(TabIntNoS);
                            printf("%u", SubEntierNonSigne32bits(TabIntNoS));
                            break;

                        case  SignedInt_32bits:
                            ChoisirOperandesIntS(TabIntS);
                            printf("%d", SubEntierSigne32bits(TabIntS));
                            break;

                        case  Floating_64bits:
                            ChoisirOperandesDouble(TabDouble);
                            printf("%e", SubFlottant64bits(TabDouble));
                            break;

                        default:
                            noOperationFound = true;
                    }
                    break;
                }
                case Multiplication :
                {
                    switch (choix){
                        case  UnsignedInt_32bits:
                        {
                            ChoisirOperandesIntNoS(TabIntNoS);
                            printf("%llu", MpyEntierNonSigneOp32bitsRes64bits(TabIntNoS));
                            break;
                        }
                        case  SignedInt_32bits:
                        {
                            ChoisirOperandesIntS(TabIntS);
                            printf("%lld", MpyEntierSigneOp32bitsRes64bits(TabIntS));
                            break;
                        }
                        case  Fractional_32bits:
                        {
                            ChoisirOperandesDouble(TabDouble);
                            TabIntS [0] = (int)(TabDouble[0] * (1<<24));
                            TabIntS [1] = (int)(TabDouble[1] * (1<<16));
                            long long res = MpyfractionnaireOp32bitsRes64bits_Q7_24_Q15_16(TabIntS);
                            printf("%#018llX (%e)", res, ((double)res) / (double)(((long long)1)<<40));
                            break;
                        }
                        case  Floating_64bits:
                        {
                            ChoisirOperandesDouble(TabDouble);
                            printf("%f", MpyFlottant64bits(TabDouble));
                            break;
                        }
                        default:
                            noOperationFound = true;
                    }
                    break;
                }
                case Division :
                {
                    switch (choix){
                        case  UnsignedInt_32bits:
                            printf("\n\n| 1 => Incrementation | 2 => SUBC |\n\n");
                            printf("Choose algorithm: ");
                            int algo;
                            scanf("%d", &algo);
                            algo += UnsignedInt_32bits;

                            if (algo == UnsignedInt_32bits_By_Incremenation){
                                ChoisirOperandesIntNoS(TabIntNoS);
                                printf("%u", DivIncrementation(TabIntNoS));
                                break;
                            }
                            else if (algo == UnsignedInt_32bits_By_Cond_Sub){
                                ChoisirOperandesIntNoS(TabIntNoS);
                                printf("%u", DivSubc(TabIntNoS));
                                break;
                            }

                        case  Floating_32bits:
                            ChoisirOperandesFloat(TabFloat);
                            printf("%f", DivFlottant32bits(TabFloat));
                            break;

                        default:
                            noOperationFound = true;
                    }
                    break;
                }
                case Encrypt :
                {
                    switch (choix){
                        case  SignedInt_32bits:
                            ChoisirDonnees(TabDonnees);
                            EncrypterDonnees(TabDonnees);
                            int i;
                            for (i = 0; i < 8; ++i)
                                printf("%d  ", TabDonnees[i]);
                            break;

                        default:
                            noOperationFound = true;
                    }
                    break;
                }
                default:
                    printf ("The operation selected is not valid!");
            }

            if (noOperationFound)
                printf("No suitable operation is available");
            printf("\n\n");
        }
    }

}

int ConvertirListe(int *Liste){
    int choix = ERROR;

    if(Liste != NULL   &&
        Liste[0] > 0   &&
        Liste[0] < 5   &&
        Liste[1] > 0   &&
        Liste[1] < 5)
            choix = 10*Liste[0] + Liste[1];

    return choix;
}

//TODO: Create all the functions needed below and verify format returned and entered
void ChoisirOperandesIntNoS(unsigned int *TabIntNoS){
    printf("\n\nEnter operand 1 (unsigned integer):\t");
    scanf("%u",TabIntNoS);
    printf("\n\nEnter operand 2 (unsigned integer):\t");
    scanf("%u",TabIntNoS+1);
}

void ChoisirOperandesIntS(signed int *TabIntS){
    printf("\n\nEnter operand 1 (integer):\t");
    scanf("%d",TabIntS);
    printf("\n\nEnter operand 2 (integer):\t");
    scanf("%d",TabIntS+1);
}

void ChoisirOperandesFloat(float *TabFloat){
    printf("\n\nEnter operand 1 (float):\t");
    scanf("%f",TabFloat);
    printf("\n\nEnter operand 2 (float):\t");
    scanf("%f",TabFloat+1);

}

void ChoisirOperandesDouble(double *TabDouble){
    printf("\n\nEnter operand 1 (Double):\t");
    scanf("%lf",TabDouble);
    printf("\n\nEnter operand 2 (Double):\t");
    scanf("%lf",TabDouble+1);

}

void ChoisirDonnees(int *TabDonnees){
    printf("\n");
    int i;
    for (i = 0; i < 8; ++i){
        printf("\nEnter operand %d (Donnees):\t", i+1);
        scanf("%d", TabDonnees++);
    }
}

bool EncrypterDonneesInC(int *TabDonnees){

    if(TabDonnees!=NULL){
        unsigned int key = 0xFFFFFFFF;

        int nbTours = 3; //According to the statement "5" in the "Guide étudiant" for validation test
        int i;
        int j;

        for(i = 0; i < nbTours; ++i){
            for(j = 0; j < 8; ++j){
                TabDonnees[j]^= key;
            }
        }
        return SUCCESS;
    }
    else
        return ERROR;
}

void ClearListe(){
    int i;
    for (i = 0; i < 3; ++i)
        Liste[i]=0;
}

