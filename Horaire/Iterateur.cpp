#include "Iterateur.h"

//**********C O N S T R U C T O R S**********

template<class T>
Iterateur<T>::Iterateur(Liste<T>& l):li(l),pParcours(l.pTete){}

//**********M E T H O D S**********
template<class T>
void Iterateur<T>::reset(){
    pParcours = li.pTete;
}

template<class T>
bool Iterateur<T>::end(){
    if(!pParcours)
        return true;
    return false;
}


//**********O P E R A T O R  O V E R L O A D I N G**********
template<class T>
Iterateur<T>& Iterateur<T>::operator++()
{
	if(end())
        return *this;
	pParcours = pParcours->psvt;

	return *this;
}
template<class T>
Iterateur<T>  Iterateur<T>::operator++(int)
{
	if(end())
        return *this;
	Iterateur<T> tmp(*this);
	pParcours = pParcours->psvt;

	return tmp;
}

template<class T>
Iterateur<T>::operator T()const
{
	return pParcours->valeur;
}


//**********D E S T R U C T O R**********


//**********INSTANCIATION DES TEMPLATES**********
template class Iterateur<int>;
#include "Professeur.h"
template class Iterateur<Professeur>;
#include "Groupe.h"
template class Iterateur<Groupe>;
#include "Local.h"
template class Iterateur<Local>;
#include "Cours.h"
template class Iterateur<Cours>;