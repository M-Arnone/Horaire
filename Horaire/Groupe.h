#ifndef GROUPE_H
#define GROUPE_H
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "Planifiable.h"
using namespace std;

class Groupe : public Planifiable{

	friend ostream& operator<<(ostream& s, const Groupe& g);

	private:
		int gnum;
		int compG(const Groupe&);
	public:
		void setNumero(int gn);

		int getNumero()const;

		Groupe();
		Groupe(int, int);
		Groupe(const Groupe&);

		const char* Txt();
		const char* Tuple();

		Groupe& operator=(const Groupe&);
		int operator<(const Groupe& );
		int operator>(const Groupe& );
		int operator==(const Groupe& );

		void Save(ofstream & fichier)const;
    	void Load(ifstream & fichier);

		~Groupe();
};

#endif