#include "Liste.h"


//**********S E T T E R S**********


//**********G E T T E R S**********

//**********C O N S T R U C T O R S**********

template <class T>
Liste<T>::Liste(){
    pTete = NULL;
}
template <class T>
Liste<T>::Liste(const Liste& l){
    
    Cellule<T> *pDest,*pOld;
    
    pOld = l.pTete;
    pTete = new Cellule<T>;
    pTete->psvt = NULL;

    pDest = pTete;
    pDest->valeur = pOld->valeur;
    pOld = pOld->psvt;

    while(pOld){
        pDest->psvt = new Cellule<T>;
        pDest = pDest->psvt;
        pDest->psvt = NULL;
        pDest->valeur = pOld->valeur;
        pOld = pOld->psvt;
    }

}

//**********M E T H O D S**********
template<class T>
bool Liste<T>::estVide(){
    return pTete ? false : true;
}

template <class T>
void Liste<T>::insere(const T& val){
    Cellule<T> *ptmp,*pParcours;

    ptmp = new Cellule<T>;
    ptmp->valeur = val;
    ptmp->psvt = NULL;

    if(!pTete){
        pTete = ptmp;
    }
    else{

        pParcours = pTete;
        while(pParcours->psvt)
            pParcours = pParcours->psvt;
        pParcours->psvt = ptmp;
        
    }
        
}

template <class T>
T Liste<T>::retire(int ind){
    //TO DO
    int i = 0;
    Cellule<T> *pParcours = pTete,*pPrec = NULL;
    pPrec = pParcours;
    while(pParcours->psvt && i < ind){
            pPrec = pParcours;
            pParcours = pParcours->psvt;
            i++;
    }
    if(pParcours == pTete)
        pTete = pParcours->psvt;
    else
    pPrec->psvt = pParcours->psvt;
    return pParcours->valeur;

}

template <class T>
int Liste<T>::getNombreElements()const{
    int i = 0;
    Cellule<T> *pParcours = pTete;
    while(pParcours){
        pParcours = pParcours->psvt;
        i++;
    }
    return i;
}

template <class T>
void Liste<T>::Affiche()const{ 
    if(!pTete)
    cout<<"Vecteur vide !!!"<<endl;
    else{
        Cellule<T> *pParcours = pTete;
        while(pParcours){
            cout<<"Valeur : "<<pParcours->valeur<<endl;
            pParcours = pParcours->psvt;
        }
    }
}



//**********O P E R A T O R  O V E R L O A D I N G**********
template <class T>
Liste<T>& Liste<T>::operator=(const Liste<T>& l){
    if(!l.pTete){
        pTete = NULL;
        return *this;
    }
        
    if(pTete){
        Cellule<T>* tmp;
        while(pTete){
            tmp = pTete;
            pTete = pTete->psvt;
            delete tmp;
        }
    }
    Cellule<T> *pDest,*pOld;
    
    pOld = l.pTete;
    pTete = new Cellule<T>;
    pTete->psvt = NULL;

    pDest = pTete;
    pDest->valeur = pOld->valeur;
    pOld = pOld->psvt;

    while(pOld){
        pDest->psvt = new Cellule<T>;
        pDest = pDest->psvt;
        pDest->psvt = NULL;
        pDest->valeur = pOld->valeur;
        pOld = pOld->psvt;
    }
    return *this;
}

//**********D E S T R U C T O R**********
template<class T>
Liste<T>::~Liste(){
    Cellule<T> *pCur, *pPrec;
    pCur = pTete;
    while(pCur){
        pPrec = pCur;
        pCur = pCur->psvt;
        delete pPrec;
    }
}

//**********INSTANCIATION DES TEMPLATES**********
template class Liste<int>;
#include "Professeur.h"
template class Liste<Professeur>;
#include "Groupe.h"
template class Liste<Groupe>;
#include "Local.h"
template class Liste<Local>;
#include "Cours.h"
template class Liste<Cours>;