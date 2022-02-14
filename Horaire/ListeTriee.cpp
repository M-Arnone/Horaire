#include "ListeTriee.h"

//**********S E T T E R S**********


//**********G E T T E R S**********

//**********C O N S T R U C T O R S**********
template <class T>
ListeTriee<T>::ListeTriee() : Liste<T>(){}

template <class T>
ListeTriee<T>::ListeTriee(const ListeTriee<T>& e) : Liste<T>(e){}

//**********M E T H O D S**********
template <class T>
void ListeTriee<T>::insere(const T& val){
    Cellule<T> *pParcours = NULL, *pInsert = NULL,*pPrec = NULL;
    pInsert = new Cellule<T>;
    pInsert->valeur = val;
    pInsert->psvt = NULL;

    if(!this->pTete)
        this->pTete = pInsert; 
    else{
        pParcours = this->pTete;
        while(pParcours && pParcours->valeur < pInsert->valeur){
                pPrec = pParcours;
                pParcours = pParcours->psvt;
        }
        if(!pPrec){
            pInsert->psvt = this->pTete;
            this->pTete = pInsert;
        }
        else{
            pInsert->psvt = pParcours;
            pPrec->psvt = pInsert;
        }    
    }
    
}
//**********O P E R A T O R  O V E R L O A D I N G**********
template <class T>
ListeTriee<T>& ListeTriee<T>::operator=(const ListeTriee<T> &e){
    Liste<T>::operator=(e);
    return *this;
}
//**********D E S T R U C T O R**********
template <class T>
ListeTriee<T>::~ListeTriee(){
}
//**********INSTANCIATION DES TEMPLATES**********
template class ListeTriee<int>;
#include "Professeur.h"
template class ListeTriee<Professeur>;
#include "Groupe.h"
template class ListeTriee<Groupe>;
#include "Local.h"
template class ListeTriee<Local>;
#include "Cours.h"
template class ListeTriee<Cours>;