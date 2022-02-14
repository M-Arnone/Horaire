#ifndef TEMPS_H
#define TEMPS_H
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <ctype.h>
#include <fstream>
#include "TempsException.h"
using namespace std;

class Temps{

	friend Temps operator+(int a, Temps t);
	friend Temps operator-(int a, Temps t);
	friend ostream& operator<<(ostream& s, const Temps& t);
	friend istream& operator>>(istream& s,Temps& t);

	private:
		int heure,minute;
		int TimeToDuration(const Temps&);
		Temps DurationToTime(int);
	public:
		
		void setHeure(int h);
		void setMinute(int m);

		int getHeure()const;
		int getMinute()const;

		void Affiche()const;

		Temps();
		Temps(int m);
		Temps(int h, int m);
		Temps(const Temps& t);

		Temps operator+(int a);
		Temps operator+(const Temps& t);

		Temps operator-(int a);
		Temps operator-(const Temps& t);


		int compT(const Temps& t);
		int operator<(const Temps& t);
		int operator>(const Temps& t);
		int operator==(const Temps& t);

		Temps operator++(); //pré-incrémentation
		Temps operator++(int); //post-incrémentation

		Temps operator--(); 
		Temps operator--(int); 

		void Save(ofstream&) const;
		void Load(ifstream&);

		~Temps();


};

#endif