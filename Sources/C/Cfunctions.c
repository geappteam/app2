/*
 * Cfunctions.c
 *
 *  Created on: 8 sept. 2017
 *      Author: para2709
 */

#include "Cfunctions.h"

bool ObtenirType(int *Liste){
    if(Liste != NULL)
    {
        Liste[0] = dataType;

        if(Liste[0] != 0 && Liste[0] < 5)
            return true;
    }
    return false;
}

bool ObtenirFormat(int *Liste){
    if(Liste != NULL)
    {
        Liste[1] = dataFormat;

        if(Liste[1] != 0 && Liste[1] < 5)
            return true;
    }
    return false;
}

bool ObtenirOperation(int *Liste){
    if(Liste != NULL)
    {
        Liste[2] = op;

        if(Liste[2] != 0 && Liste[2] < 6)
            return true;
    }
    return false;
}

bool AnalyserListe(int *Liste, unsigned short *TabShortNoS, short *TabShortS){
    if(Liste !=NULL)
    {
        int choix = ConvertirListe(Liste);

        if(choix != NULL)
        {
            switch (Liste[2]){

                case Addition :
                    switch (choix){
                        case  UnsignedInt_32bits:

                            break;
                        case  SignedInt_32bits:

                            break;
                        case  Fractional_32bits:

                            break;
                    }
                    break;
                case Subtraction :
                    switch (choix){
                        case  UnsignedInt_32bits:

                            break;
                        case  SignedInt_32bits:

                            break;
                        case  Floating_64bits:

                            break;
                    }
                    break;
                case Multiplication :
                    switch (choix){
                        case  UnsignedInt_32bits:

                            break;
                        case  SignedInt_32bits:

                            break;
                        case  Fractional_32bits:

                            break;
                        case  Floating_64bits:

                            break;
                    }
                    break;
                case Division :
                    switch (choix){
        //            case  SignedInt_32bits:    //TODO: Implement in Cunctions.h the two dataTypeNames and replace here
        //
        //                break;
        //            case  Fractional_32bits:
        //
        //                break;
                    case  Floating_32bits:

                        break;
                    }
                    break;
                case Encrypt :
                    switch (choix){
                        case  SignedInt_32bits:

                            break;
                    }
                    break;
            }
        }
    }

    return false;
}

int ConvertirListe(int *Liste){
    int choix = 0;

    if(Liste != NULL    &&
        Liste[0] != 0   &&
        Liste[0] < 5    &&
        Liste[1] != 0   &&
        Liste[1] < 5)
            choix = 10*Liste[0] + Liste[1];

    return choix;
}

bool ChoisirOperandesXXX(int *Tab){
    return false;
}

// Optionnel
//bool printResult(){
//    return false;
//}
