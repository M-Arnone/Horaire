#ifndef COURS_H
#define COURS_H
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "Event.h"
#include "Iterateur.h"
using namespace std;
class Cours : public Event{

	friend ostream& operator<<(ostream& s,const Cours& c);

	private:
		int idProfesseur;
		int idLocal;
		Liste<int> idGroupes;
		int compC(const Cours&);

	public:
		void setidProfesseur(const int p);
		void setidLocal(const int l);
		void setidGroupe(const Liste<int> g);

		int getidProfesseur()const;
		int getidLocal()const;
		Liste<int> getidGroupe()const;
		Liste<int>& getIdGroupes();

		Cours();
		Cours(const Cours& c);

		void ajouteIdGroupe(int id);
		bool contientIdGroupe(int id);

		Cours& operator=(const Cours&);
		int operator<(const Cours& );
		int operator>(const Cours& );
		int operator==(const Cours& );

        void Save(ofstream & fichier)const;
        void Load(ifstream & fichier);

		~Cours();

};


#endif