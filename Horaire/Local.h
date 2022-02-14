#ifndef LOCAL_H
#define LOCAL_H
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "Planifiable.h"
using namespace std;

class Local : public Planifiable{

	friend ostream& operator<<(ostream& s, const Local& l);

	private:
		char* nom;
		int compL(const Local&);
	public:
		void setNom(const char* n);

		const char* getNom()const;

		Local();
		Local(int,const char *);
		Local(const Local&);

		const char* Txt();
		const char* Tuple();

		Local& operator=(const Local&);
		int operator<(const Local& );
		int operator>(const Local& );
		int operator==(const Local& );
		
		void Save(ofstream & fichier)const;
    	void Load(ifstream & fichier);
		
		~Local();
};

#endif