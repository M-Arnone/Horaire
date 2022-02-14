#include "Exception.h"

//**********S E T T E R S**********


//**********G E T T E R S**********

//**********C O N S T R U C T O R S**********
Exception::Exception(const char* m){
	message = NULL;
	message = new char[strlen(m)+1];
	strcpy(message,m);
}
Exception::Exception(const Exception& e){
	if(!e.message)
		message = 0;
	else{
		message = new char[strlen(e.message)+1];
		strcpy(message,e.message);
	}
}

//**********F U N C T I O N S**********



//**********O P E R A T O R  O V E R L O A D I N G**********
ostream& operator<< (ostream& s, const Exception& e)
{
 if(e.message)
 		s << e.message;
 return s;
} 

//**********D E S T R U C T O R**********
Exception::~Exception(){
	if(message)
		delete message;
}