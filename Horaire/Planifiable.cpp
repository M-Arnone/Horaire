#include "Planifiable.h"

//**********S E T T E R S**********
void Planifiable::setId(int i){id = i;}


//**********G E T T E R S**********
int Planifiable::getId()const{return id;}


//**********C O N S T R U C T O R S**********
Planifiable::Planifiable(){
	txt = NULL;
	tuple = NULL;
	setId(0);
}
Planifiable::Planifiable(int i){
	txt = NULL;
	tuple = NULL;
	setId(i);
}
Planifiable::Planifiable(const Planifiable& p){
	txt = NULL;
	tuple = NULL;
	setId(p.getId());
}


//**********D E S T R U C T O R**********
Planifiable::~Planifiable(){
	if(txt)
		delete txt;
	if(tuple)
		delete tuple;
}

