#ifndef LISTE_H
#define LISTE_H

#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
template<class T>
class Iterateur;

template<class T>
struct Cellule{
    T valeur;
    Cellule<T> *psvt;
};

template<class T>
class Liste{
    protected:
        Cellule<T> *pTete;
    public:
        Liste ();
        Liste(const Liste<T>&);
        
        bool estVide();
        int getNombreElements()const;
        virtual void insere(const T&);
        T retire(int);

        Liste<T>& operator=(const Liste<T>&);

        void Affiche()const;

        virtual ~Liste();

        friend class Iterateur<T>;
};


#endif