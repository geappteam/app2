#include "Cfunctions.h"
#include "test_asm.h"
#include "functionsASM.h"

main(){
//    //Tests used for development purposes
//    devTest();
//
//    //Validations of the tests needed for the APP (GE S5 APP2)
//    validationTest();
//
//    //Program: Process of the Binary Calculator
//    process();

    int TabDonnees[8] = {0,0,0,0,0,0,0,0};
    bool error = EncrypterDonneesInC(TabDonnees);

    return 0;

}
