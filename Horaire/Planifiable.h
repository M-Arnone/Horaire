#ifndef PLANIFIABLE_H
#define PLANIFIABLE_H
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include <fstream>
using namespace std;

class Planifiable{
	protected:
		int id;
		char* txt;
		char* tuple;
	public:
		static int idCourant;
		void setId(int i);

		int getId()const;

		Planifiable();
		Planifiable(int);
		Planifiable(const Planifiable&);

		virtual const char* Txt()   = 0;
	 	virtual const char* Tuple() = 0; 

	 	virtual ~Planifiable();
	 	
};

#endif