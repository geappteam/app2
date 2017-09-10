#include <stdbool.h>
#include "Cfunctions.h"
#include "test_asm.h"
#include "functionsASM.h"

main()
{
    // Suite de test des fonctions assembleur
    test();

    //Temporarily static variables instead of inputs from user
    //dataType = 1;
    //dataFormat = 1;
    //op = 1;

    //ObtenirType(Liste);
    //ObtenirFormat(Liste);
    //ObtenirOperation(Liste);
    //AnalyserListe(Liste,TabShortNoS,TabShortS);
    //dataType = 1;
    //dataFormat = 2;
    //op = 1;

    //ObtenirType(Liste);
    //ObtenirFormat(Liste);
    //ObtenirOperation(Liste);
    //AnalyserListe(Liste,TabShortNoS,TabShortS);

    //unsigned int param[] = { 3, 0x7};
    //int param1[] = { 0x25454546, 0x5FFFFFFF};
    //int param2[] = { 0x802A3FA2,0x5A2E51A3 };
    //double param3[] = { 3.5,13.5 };
    double param4[] = { 0x4021333333333333,0xC004000000000000 };
    //double param4[] = {3500000000000000000,4000000000000000000};


    //double result = AddEntierNonSigne32bits(param);
    //double result1 = AddEntierSigne32bits(param1);
    //double result2 = SubEntierSigne32(param2);
    //double result3 = SubFlottant64bits(param3);
    double result4 = MpyFlottant64bits(param4);

    return 0;
}
