#include "Professeur.h"

//**********S E T T E R S**********
void Professeur::setNom(const char* n){
	if(nom){
		delete nom;
		prenom = NULL;
	}
	nom = new char[strlen(n)+1];
	strcpy(nom,n);
}
void Professeur::setPrenom(const char *p){
	if(prenom){
		delete prenom;
		prenom = NULL;
	}
	prenom = new char[strlen(p)+1];
	strcpy(prenom,p);
}


//**********G E T T E R S**********
const char* Professeur::getNom()const{ return nom;}
const char* Professeur::getPrenom()const{ return prenom;}


//**********C O N S T R U C T O R S**********
Professeur::Professeur():Planifiable(){
	nom = NULL;
	prenom = NULL;
	setNom("DEFAULT");
	setPrenom("DEFAULT");
}
Professeur::Professeur(int id, const char *n,const char *p):Planifiable(id){
	nom = NULL;
	prenom = NULL;
	setNom(n);
	setPrenom(p);
}
Professeur::Professeur(const Professeur& p):Planifiable(p){
	nom = NULL;
	prenom = NULL;
	setNom(p.getNom());
	setPrenom(p.getPrenom());
}
const char* Professeur::Txt(){
	if(txt)
		delete txt;
	char buffer[400];
	sprintf(buffer,"%s %s",nom,prenom);

	txt = new char[strlen(buffer) +1];
	strcpy(txt,buffer);
	return txt;
}
const char* Professeur::Tuple(){
	if(tuple)
		delete tuple;
	char buffer[400];
	sprintf(buffer,"%d;%s;%s",id,nom,prenom);

	tuple = new char[strlen(buffer) + 1];
	strcpy(tuple,buffer);
	return tuple;

}

//**********M E T H O D S**********
int Professeur::compP(const Professeur& p){
	int ret = strcmp(this->getNom(),p.getNom());
	if(ret == 0){
		ret = strcmp(this->getPrenom(),p.getPrenom());
	}
	return ret;
}
void Professeur::Save(ofstream & fichier)const{
	if(!fichier){
		cout << "Erreur d'ouverture Professeur::Save"<<endl;
		exit (1);
	}
	int id = getId();
	fichier.write((char*)&id, sizeof(int));
	
	int taille_nom = strlen(getNom())+1;
	fichier.write((char*)&taille_nom,sizeof(int));
	fichier.write(getNom(),taille_nom);

	int taille_prenom = strlen(getPrenom())+1;
	fichier.write((char*)&taille_prenom,sizeof(int));
	fichier.write(getPrenom(),taille_prenom);

}
void Professeur::Load(ifstream & fichier){
	if(!fichier.rdbuf()->is_open())
	{
		cout << "Erreur d'ouverture Professeur::Load"<< endl;
		exit(1);
	}
    fichier.read((char*)&id,sizeof(int));
    int taille_nom;
    fichier.read( (char*)&taille_nom, sizeof(int) );
    if(taille_nom){
		char *tmp = new char[taille_nom+1];
		fichier.read((char*)tmp,taille_nom);
		setNom(tmp);
		delete tmp;
	}

    int taille_prenom;
    fichier.read((char*)&taille_prenom, sizeof(int) );
    if(taille_prenom){
		char *tmp = new char[taille_prenom+1];
		fichier.read((char*)tmp,taille_prenom);
		setPrenom(tmp);
		delete tmp;
	}
	    

}
//**********O P E R A T O R  O V E R L O A D I N G**********
ostream& operator<<(ostream& s, const Professeur& p){
	s<<"Id : "<<p.getId()<<"  Nom : "<<p.getNom()<<"  Prenom : "<<p.getPrenom()<<endl;
	return s;
}
Professeur& Professeur::operator=(const Professeur& p){
	setId(p.getId());
	setNom(p.getNom());
	setPrenom(p.getPrenom());
	
	return *this;
}

int Professeur::operator<(const Professeur & p){
	return compP(p) < 0;
}
int Professeur::operator>(const Professeur & p){
	return compP(p) > 0;
}
int Professeur::operator==(const Professeur & p){
	return compP(p) == 0;
}

//**********D E S T R U C T O R**********
Professeur::~Professeur(){
	if(nom)
		delete nom;
	if(prenom)
		delete prenom;
}

