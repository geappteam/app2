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

bool AnalyserListe(int *Liste, unsigned short *TabShortNoS, short *TabShortS){

    bool isSuccess = false;

    if(Liste != NULL)
    {
        int choix = ConvertirListe(Liste);

        if(choix != NULL)
        {
            switch (Liste[2]){

                case Addition :
                    switch (choix){
                        case  UnsignedInt_32bits:
                            //isSuccess = ChoisirOperandesIntNoS(TabShortNoS);
                            //AddEntierNonSigne32bits();
                            break;
                        case  SignedInt_32bits:
                            //isSuccess = ChoisirOperandesIntS(TabShortS);
                            //AddEntierSigne32bits();
                            break;
                        case  Fractional_32bits:
                            //isSuccess = ChoisirOperandesDouble(TabShortS);
                            //AddFractionnaire32bits_Q7_24_Q15_16();
                            break;
                    }
                    break;
                case Subtraction :
                    switch (choix){
                        case  UnsignedInt_32bits:
                            //isSuccess = ChoisirOperandesIntNoS(TabShortNoS);
                            //SubEntierNonSigne32bits();
                            break;
                        case  SignedInt_32bits:
                            //isSuccess = ChoisirOperandesIntS(TabShortS);
                            //SubEntierSigne32bits();
                            break;
                        case  Floating_64bits:
                            //isSuccess = ChoisirOperandesFloat(TabShortNoS);
                            //SubFlottant64bits();
                            break;
                    }
                    break;
                case Multiplication :
                    switch (choix){
                        case  UnsignedInt_32bits:
                            //isSuccess = ChoisirOperandesIntNoS(TabShortNoS);
                            //MpyEntierNonSigneOp32bitsRes64bits();
                            break;
                        case  SignedInt_32bits:
                            //isSuccess = ChoisirOperandesIntS(TabShortNoS);
                            //MpyEntierSigneOp32bitsRes64bits();
                            break;
                        case  Fractional_32bits:
                            //isSuccess = ChoisirOperandesDouble(TabShortNoS);
                            //MpyfractionnaireOp32bitsRes64bits_Q7_24_Q15_16();
                            break;
                        case  Floating_64bits:
                            //isSuccess = ChoisirOperandesFloat(TabShortNoS);
                            //MpyFlottant64bits();
                            break;
                    }
                    break;
                case Division :
                    switch (choix){
        //            case  SignedInt_32bits:    //TODO: Implement in Cunctions.h the two dataTypeNames and replace here
        //                isSuccess = ChoisirOperandesIntS(TabShortS);
                          //DivSubc();
        //                break;
        //            case  Fractional_32bits:
        //                isSuccess = ChoisirOperandesDouble(TabShortS);
        //                break;
                    case  Floating_32bits:
                        //isSuccess = ChoisirOperandesFloat(TabShortNoS);
                        //DivFlottant32bits();
                        break;
                    }
                    break;
                case Encrypt :
                    switch (choix){
                        case  SignedInt_32bits:
                            //isSuccess = ChoisirDonnees(TabShortNoS);
                            //EncrypterDonnees(TabDonnees);
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
bool ChoisirOperandesIntNoS(unsigned int *TabIntNoS){
    return ERROR;
}

bool ChoisirOperandesIntS(signed int *TabIntS){
    return ERROR;
}

bool ChoisirOperandesFloat(float *TabFloat){
    return ERROR;
}

bool ChoisirOperandesDouble(double *TabDouble){
    return ERROR;
}

bool ChoisirDonnees(int *TabDonnees){
    return ERROR;
}

void printResult(unsigned short *TabShortNoS, short *TabShortS,  int *TabDonnees){
}
