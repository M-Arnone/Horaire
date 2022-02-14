#ifndef LISTETRIEE_H
#define LISTETRIEE_H

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "Liste.h"
using namespace std;

template<class T>
class ListeTriee : public Liste<T>{
    private:
        
    public:
        ListeTriee();
        ListeTriee(const ListeTriee<T>& e);
        void insere(const T&);
        ListeTriee<T>& operator=(const ListeTriee<T> &e);
        ~ListeTriee();
};




#endif