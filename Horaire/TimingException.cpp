#include "TimingException.h"
const int TimingException::JOUR_INVALIDE = 0;
const int TimingException::AUCUN_TIMING = 0;
const int TimingException::PROF_INDISPO = 5;
const int TimingException::GROUPE_INDISPO = 6;
const int TimingException::LOCAL_INDISPO = 7;

//**********S E T T E R S**********
void TimingException::setCode(int c){ code = c;}

//**********G E T T E R S**********
const char* TimingException::getMessage()const{return message;}

int TimingException::getCode()const{return code;}
//**********C O N S T R U C T O R S**********
TimingException::TimingException(const TimingException& e):Exception(e){
	setCode(e.code);
}

TimingException::TimingException(const char* m, int erreur):Exception(m){
	setCode(erreur);
}


//**********F U N C T I O N S**********



//**********O P E R A T O R  O V E R L O A D I N G**********


//**********D E S T R U C T O R**********