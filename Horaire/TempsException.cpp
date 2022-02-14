#include "TempsException.h"
const int TempsException::HEURE_INVALIDE = 1;
const int TempsException::MINUTE_INVALIDE = 2;
const int TempsException::DEPASSEMENT = 3;
const int TempsException::FORMAT_INVALIDE = 4;

//**********S E T T E R S**********
void TempsException::setCode(int c){ code = c;}
//**********G E T T E R S**********
const char* TempsException::getMessage()const{return message;}

int TempsException::getCode()const{return code;}

//**********C O N S T R U C T O R S**********

TempsException::TempsException(const TempsException& e):Exception(e){
	setCode(e.code);
}
TempsException::TempsException(const char* m, int erreur):Exception(m){
	setCode(erreur);
}


//**********F U N C T I O N S**********



//**********O P E R A T O R  O V E R L O A D I N G**********


//**********D E S T R U C T O R**********
