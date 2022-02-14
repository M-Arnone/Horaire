#ifndef EVENT_H
#define EVENT_H
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Timing.h"
#include "TimingException.h"
using namespace std;

class Event{

	protected:
		int code;
		char* intitule;
		Timing* timing;

	public:
		static int codeCourant;
		void setCode(int c);
		void setIntitule(const char *nom);
		void setTiming(const Timing& t);

		int getCode()const;
		const char* getIntitule()const;
		Timing getTiming()const;

		void Affiche()const;

		Event();
		Event(int c);
		Event(int c,const char *nom);
		Event(const Event& e);

		Event& operator=(const Event&);

		void Save(ofstream&)const;
		void Load(ifstream&);

		~Event();

};


#endif