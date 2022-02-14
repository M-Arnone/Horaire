#ifndef PROFESSEUR_H
#define PROFESSEUR_H
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "Planifiable.h"
using namespace std;

class Professeur : public Planifiable{

	friend ostream& operator<<(ostream& s, const Professeur& p);
	
	private:
		char* nom;
		char* prenom;
		int compP(const Professeur&);
	public:
		void setNom(const char* n);
		void setPrenom(const char* p);

		const char* getNom()const;
		const char* getPrenom()const;

		Professeur();
		Professeur(int, const char*, const char* );
		Professeur(const Professeur&);

		const char* Txt();
		const char* Tuple();

		Professeur& operator=(const Professeur&);
		int operator<(const Professeur& );
		int operator>(const Professeur& );
		int operator==(const Professeur& );
		
		void Save(ofstream & fichier)const;
    	void Load(ifstream & fichier);

	    ~Professeur();
};

#endif