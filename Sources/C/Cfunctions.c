/*
 * Cfunctions.c
 *
 *  Created on: 8 sept. 2017
 *      Author: para2709
 */

#include "Cfunctions.h"

void process(){

    while(1)
    {
        //Initializations
        int Liste[3] = {0,0,0};
        unsigned short TabShortNoS[2] = {0,0};
        short TabShortS[2] = {0,0};
        int TabDonnees[8] = {0,0,0,0,0,0,0,0};

        //Program process
        if( ObtenirType(Liste)      &&
            ObtenirFormat(Liste)    &&
            ObtenirOperation(Liste) &&
            AnalyserListe(Liste, TabShortNoS, TabShortS))
            printResult(TabShortNoS, TabShortS, TabDonnees);
        else
            printf("\n\n --- ERROR --- \n\n");
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
        printf("\n| 1 => + | 2 => - | 3 => * | 4 => / |\n\n");
        printf("Enter operation: ");
        scanf("%d",Liste+2);

        if(Liste[2] > 0 && Liste[2] < 6)
            return SUCCESS;
    }
    return ERROR;
}

bool AnalyserListe(int *Liste, unsigned int *TabIntNoS, signed int *TabIntS,float *TabFloat, double *TabDouble,int *TabDonnees, long *Tablong, unsigned long long *TablonglongNoS, long long *Tablonglong){

    bool isSuccess = true; //TODO: Implement if here's time error check for the following process

    if(Liste != NULL)
    {
        int choix = ConvertirListe(Liste);

        if(choix != NULL)
        {
            switch (Liste[2]){

                case Addition :
                    switch (choix){
                        case  UnsignedInt_32bits:
                            ChoisirOperandesIntNoS(TabIntNoS);
                            AddEntierNonSigne32bits(TabDouble);
                            break;
                        case  SignedInt_32bits:
                            ChoisirOperandesIntS(TabIntS);
                            AddEntierSigne32bits(TabDouble);
                            break;
                        case  Fractional_32bits:
                            ChoisirOperandesDouble(TabDouble);
                            AddFractionnaire32bits_Q7_24_Q15_16(TabIntS);
                            break;
                    }
                    break;
                case Subtraction :
                    switch (choix){
                        case  UnsignedInt_32bits:
                            ChoisirOperandesIntNoS(TabIntNoS);
                            SubEntierNonSigne32bits(Tablong);
                            break;
                        case  SignedInt_32bits:
                            ChoisirOperandesIntS(TabIntS);
                            SubEntierSigne32bits(TabIntS);
                            break;
                        case  Floating_64bits:
                            ChoisirOperandesFloat(TabDouble);
                            SubFlottant64bits(TabDouble);
                            break;
                    }
                    break;
                case Multiplication :
                    switch (choix){
                        case  UnsignedInt_32bits:
                            ChoisirOperandesIntNoS(TabIntNoS);
                            MpyEntierNonSigneOp32bitsRes64bits(TablonglongNoS);
                            break;
                        case  SignedInt_32bits:
                            ChoisirOperandesIntS(TabIntS);
                            MpyEntierSigneOp32bitsRes64bits(Tablonglong);
                            break;
                        case  Fractional_32bits:
                            ChoisirOperandesDouble(TabIntS);
                            MpyfractionnaireOp32bitsRes64bits_Q7_24_Q15_16(Tablonglong);
                            break;
                        case  Floating_64bits:
                            ChoisirOperandesFloat(TabDouble);
                            MpyFlottant64bits(TabDouble);
                            break;
                    }
                    break;
                case Division :
                    switch (choix){
                    case  UnsignedInt_32bits_By_Cond_Sub:
                        ChoisirOperandesIntNoS(TabIntNoS);
                        DivSubc(TabIntNoS);
                        break;
                    case  UnsignedInt_32bits_By_Incremenation:
                        ChoisirOperandesIntS(TabIntS);
                        DivIncrementation(TabIntS);
                        break;
                    case  Floating_32bits:
                        ChoisirOperandesFloat(TabFloat);
                        DivFlottant32bits(TabFloat);
                        break;
                    }
                    break;
                case Encrypt :
                    switch (choix){
                        case  SignedInt_32bits:
                            Choisir();
                            EncrypterDonnees(TabDonnees);
                            break;
                    }
                    break;
            }
        }
    }

    if(isSuccess)
        return SUCCESS;
    else
        return ERROR;
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
    scanf("%u",TabIntNoS[0]);
    printf("\n\nEnter operand 2 (unsigned integer):\t");
    scanf("%u",TabIntNoS[1]);
}

void ChoisirOperandesIntS(signed int *TabIntS){
    printf("\n\nEnter operand 1 (integer):\t");
    scanf("%u",TabIntS[0]);
    printf("\n\nEnter operand 2 (integer):\t");
    scanf("%u",TabIntS[1]);

}

void ChoisirOperandesFloat(float *TabFloat){
    printf("\n\nEnter operand 1 (float):\t");
    scanf("%u",TabFloat[0]);
    printf("\n\nEnter operand 2 (float):\t");
    scanf("%u",TabFloat[1]);

}

void ChoisirOperandesDouble(double *TabDouble){
    printf("\n\nEnter operand 1 (Double):\t");
    scanf("%u",TabDouble[0]);
    printf("\n\nEnter operand 2 (Double):\t");
    scanf("%u",TabDouble[1]);

}

void ChoisirDonnees(int *TabDonnees){
    printf("\n\nEnter operand 1 (Donnees):\t");
    scanf("%u",TabDonnees[0]);
    printf("\n\nEnter operand 2 (Donnees):\t");
    scanf("%u",TabDonnees[1]);

}

bool EncrypterDonneesInC(int *TabDonnees){
    unsigned int key = 0xFFFFFFFF;

    int nbTours = 3; //According to the statement in the Guide étudiant

    return SUCCESS;
}

void printResult(unsigned short *TabShortNoS, short *TabShortS,  int *TabDonnees){
}
