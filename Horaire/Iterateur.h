#ifndef ITERATEUR_H
#define ITERATEUR_H

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "Liste.h"

using namespace std;

template<class T>
class Liste;

template<class T>
struct Cellule;

template<class T>
class Iterateur{
    private:
    Liste<T>& li;
    Cellule<T> *pParcours;
         
    public:
    Iterateur(Liste<T> & l);

    void reset();
    bool end();

    Iterateur<T>& operator++();
    Iterateur<T> operator++(int);

    operator T()const;

};


#endif