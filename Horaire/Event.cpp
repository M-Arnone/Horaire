#include "Event.h"

//**********S T A T I C  V A R I A B L E S**********


//**********S E T T E R S**********
void Event::setCode(int c){code = c;}
		
void Event::setIntitule(const char *nom){
	if(intitule){
		delete intitule;
		intitule = NULL;
	}
	intitule = new char[strlen(nom)+1];
	strcpy(intitule,nom);
}

void Event::setTiming(const Timing& t){
	if(timing){
		delete timing;
		timing = NULL;
	}
	timing = new Timing(t);
}



//**********G E T T E R S**********
int Event::getCode()const{return code;}

const char* Event::getIntitule()const{return intitule;}

Timing Event::getTiming()const
{
	if(!timing)
		throw TimingException("Objet Timing n'existe pas",TimingException::AUCUN_TIMING);
	return *timing;		
}



//**********C O N S T R U C T O R S**********
Event::Event(){
	intitule = NULL;
	setCode(0);
	setIntitule("DEFAULT");
	timing = NULL;
}

Event::Event(int c, const char *nom){
	intitule = NULL;
	setCode(c);
	setIntitule(nom);
	timing = NULL;
}

Event::Event(const Event& e){
	intitule = NULL;
	timing = NULL;
	setCode(e.getCode());
	setIntitule(e.getIntitule());
	setTiming(e.getTiming());
}
Event& Event::operator=(const Event& t2){
		setCode(t2.getCode());
		if(intitule)
			delete(intitule);
		intitule = NULL;
		setIntitule(t2.getIntitule());
		timing = NULL;
		setTiming(t2.getTiming());
		return *this;
}

//**********F L U X**********
void Event::Save(ofstream& fichier)const{
	if(!fichier){
		cout << "Erreur d'ouverture Event::Save"<<endl;
		exit (1);
	}
	fichier.write((char*)&code,sizeof(int));

	int tmp = strlen(getIntitule());
	fichier.write((char*)&tmp,sizeof(int));
	fichier.write(getIntitule(),tmp);
	
	int verif = 0;
	if(!timing)
		fichier.write((char*)&verif,sizeof(int));
	else{
		verif = 1;
		fichier.write((char*)&verif,sizeof(int));
		timing->Save(fichier);
	}
	

}
void Event::Load(ifstream& fichier){
	if(!fichier.rdbuf()->is_open())
	{
		cout << "Erreur d'ouverture Event::Load"<< endl;
		exit(1);
	}
	fichier.read((char*)&code,sizeof(int));

	int taille;
	fichier.read((char*)&taille,sizeof(int));
	char *tmp = new char[taille+1];
	fichier.read((char*)tmp,taille);
	tmp[taille] = '\0';
	setIntitule(tmp);
	delete tmp;

	int verif;
	fichier.read((char*)&verif,sizeof(int));
	if(verif == 1){
		timing = new Timing();
		timing->Load(fichier);
	}


}

//**********P R I N T**********
void Event::Affiche()const{
	cout<<"Code :"<<code<<"\t\t";
	if(intitule){
		cout<<"Intitule :"<<intitule<<endl;
	}
	if(timing){
		cout<<"Timing :";
		timing->Affiche();
	}

}

Event::~Event(){
	if(intitule)
		delete intitule;
	if (timing) delete timing;
}

