#include "Timing.h"

//**********S T A T I C  V A R I A B L E S**********
const char Timing::LUNDI[] = "Lundi";
const char Timing::MARDI[] = "Mardi";
const char Timing::MERCREDI[] = "Mercredi";
const char Timing::JEUDI[] = "Jeudi";
const char Timing::VENDREDI[] = "Vendredi";
const char Timing::SAMEDI[] = "Samedi";
const char Timing::DIMANCHE[] = "Dimanche";


//**********S E T T E R S**********
void Timing::setJour(const char *j){ 
	if(jour){
		delete jour;
		jour = NULL;
	}
	if(strcmp(j,"Lundi") != 0 &&
		strcmp(j,"Mardi") != 0 &&
		strcmp(j,"Mercredi") != 0 &&
		strcmp(j,"Jeudi") != 0 &&
		strcmp(j,"Vendredi") != 0 &&
		strcmp(j,"Samedi") != 0 &&
		strcmp(j,"Dimanche") != 0 &&
		strcmp(j,"DEFAULT") != 0 
		)
		throw TimingException("Le jour n'est pas valide",TimingException::JOUR_INVALIDE);
	jour = new char[strlen(j)+1];
	strcpy(jour,j);
			//throw TimingException("Le jour n'est pas valide",TimingException::JOUR_INVALIDE);
}
void Timing::setHeure(const Temps& h){ heure = h;}
void Timing::setDuree(const Temps& d){ duree = d;}


//**********G E T T E R S**********
char* Timing::getJour()const{ return jour;}
Temps Timing::getHeure()const{ return heure;}
Temps Timing::getDuree()const{ return duree;}


//**********C O N S T R U C T O R S**********
Timing::Timing(){
	jour = NULL;
	setJour("DEFAULT");
}
Timing::Timing(const char* j,Temps h,Temps d){
	jour = NULL;
	setJour(j);
	setHeure(h);
	setDuree(d);

}
Timing::Timing(const Timing& t){
	jour = NULL;
	setJour(t.getJour());
	setHeure(t.getHeure());
	setDuree(t.getDuree());
}


//**********O P E R A T O R  O V E R L O A D I N G**********
int Timing::compT(const Timing& t){
	int a = 0, b = 0;

	if(strcmp(t.getJour(),"Lundi") == 0)	a = 1;
	else
		if(strcmp(t.getJour(),"Mardi") == 0)	a = 2;
		else
			if(strcmp(t.getJour(),"Mercredi") == 0)	a = 3;
			else
				if(strcmp(t.getJour(),"Jeudi") == 0)	a = 4;
				else
					if(strcmp(t.getJour(),"Vendredi") == 0)	a = 5;
					else
						if(strcmp(t.getJour(),"Samedi") == 0)	a = 6;
						else
							if(strcmp(t.getJour(),"Dimanche") == 0)	a = 7;

	if(strcmp(this->getJour(),"Lundi") == 0)		b = 1;
	else
		if(strcmp(this->getJour(),"Mardi") == 0)		b = 2;
		else
			if(strcmp(this->getJour(),"Mercredi") == 0)	b = 3;
			else
				if(strcmp(this->getJour(),"Jeudi") == 0)		b = 4;
				else
					if(strcmp(this->getJour(),"Vendredi") == 0)	b = 5;
					else
						if(strcmp(this->getJour(),"Samedi") == 0)		b = 6;
						else
							if(strcmp(this->getJour(),"Dimanche") == 0)	b = 7;


	if(b < a) return -1;
	if(b > a) return 1;

	if(a == b){
		if(this->getHeure() < t.getHeure()) return -1;
		else
			if(this->getHeure() > t.getHeure()) return 1;
			else
				if(this->getDuree() < t.getDuree()) return -1;
				else
					if(this->getDuree() > t.getDuree()) return 1;	

	}
	return 0;
}

int Timing::operator<(const Timing& t){
	return compT(t) == -1;
}
int Timing::operator>(const Timing& t){
	return compT(t) == 1;
}
int Timing::operator==(const Timing&  t){
	return compT(t) == 0;
}


//**********F L U X**********
void Timing::Save(ofstream& fichier) const{
	if(!fichier){
		cout << "Erreur d'ouverture"<<endl;
		exit (1);
	}
	int tmp = strlen(getJour())+1;
	fichier.write((char*)&tmp,sizeof(int));
	fichier.write(jour,tmp);
	heure.Save(fichier);
	duree.Save(fichier);

}
void Timing::Load(ifstream& fichier){
	if(!fichier.rdbuf()->is_open())
	{
		cout << "erreur d'ouverture !"<< endl;
		return;
	}
	int taille;
	fichier.read((char*)&taille,sizeof(int));
	char* tmp = new char[taille+1];
	fichier.read((char*)tmp,taille);
	setJour(tmp);
	delete tmp;
	heure.Load(fichier);
	duree.Load(fichier);
}
bool Timing::intersecte(const Timing& t) const{
    if(strcmp(this->getJour(),t.getJour()) != 0 ) return false; // jour diff
	else{
			Temps this_debut(getHeure());
			Temps this_duree(getDuree());
			Temps this_fin;
			this_fin = this_debut + this_duree;

			Temps debut(t.getHeure());
			Temps duree(t.getDuree());
			Temps fin;
			fin = debut+duree;
			
			if(this_debut > fin) return false;
			if(this_fin < debut) return false;
	}
	return true;
}

//**********D E S T R U C T O R**********
Timing::~Timing(){
	if(jour)
		delete jour;
}


//**********P R I N T**********
void Timing::Affiche() const{
	cout<<"Jour :"<<jour<<endl;
	cout<<"Heure :";
	heure.Affiche();
	cout<<endl;
	cout<<"Duree :";
	duree.Affiche();
	cout<<endl;
}