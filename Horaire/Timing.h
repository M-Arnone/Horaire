#ifndef TIMING_H
#define TIMING_H
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Temps.h"
#include "TimingException.h"
using namespace std;


class Timing{
	private:
		char* jour;
		Temps heure;
		Temps duree;


	public:
		static const char LUNDI[]; //static constexpr const char* LUNDI = "Lundi";, pq pas comme ça ? decla + init direct
		static const char MARDI[];
		static const char MERCREDI[];
		static const char JEUDI[];
		static const char VENDREDI[];
		static const char SAMEDI[];
		static const char DIMANCHE[];
		
		void setJour(const char *j);
		void setHeure(const Temps& h);
		void setDuree(const Temps& d);

		char* getJour()const;
		Temps getHeure()const;
		Temps getDuree()const;

		Timing();
		Timing(const char* j,Temps h,Temps d);
		Timing(const Timing& t);

		int compT(const Timing& t);		
		int operator<(const Timing& t);
		int operator>(const Timing& t);
		int operator==(const Timing& t);

		~Timing();

		void Save(ofstream&) const;
		void Load(ifstream&);

		void Affiche() const;

		bool intersecte(const Timing& t) const;

};

#endif