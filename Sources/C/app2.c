#include "Cfunctions.h"

<<<<<<< HEAD

double AddEntierNonSigne32bits(unsigned int *TabIntNoS);
double AddEntierSigne32bits( int *TabIntS);
double SubEntierSigne32 (int *TabIntNoS);
double SubFlottant64bits(float *TabXXX);
=======
long SubEntierNonSigne32bits(unsigned int *TabIntNoS);
>>>>>>> 9ae696efe24bae88dc0d3a34d19ad5b25d3cc874

int main(void)
{
    //Temporarily static variables instead of inputs from user
<<<<<<< HEAD
    //dataType = 1;
    //dataFormat = 1;
    //op = 1;

    //ObtenirType(Liste);
    //ObtenirFormat(Liste);
    //ObtenirOperation(Liste);
 //   AnalyserListe(Liste,TabShortNoS,TabShortS);
=======
//    dataType = 1;
//    dataFormat = 2;
//    op = 1;

//    ObtenirType(Liste);
//    ObtenirFormat(Liste);
//    ObtenirOperation(Liste);
//    AnalyserListe(Liste,TabShortNoS,TabShortS);
>>>>>>> 9ae696efe24bae88dc0d3a34d19ad5b25d3cc874

    //unsigned int param[] = { 3, 0x7};
    //int param1[] = { 0x25454546, 0x5FFFFFFF};
    //int param2[] = { 0x802A3FA2,0x5A2E51A3 };
    float param3[] = { 3.5,13.5 };



    //double result = AddEntierNonSigne32bits(param);
    //double result1 = AddEntierSigne32bits(param1);
    //double result2 = SubEntierSigne32(param2);
    float result3= SubFlottant64bits(param3);

    return 0;

}
