#include "Local.h"

//**********S E T T E R S**********
void Local::setNom(const char* n){
	if(nom){
		delete nom;
		nom = NULL;
	}
	nom = new char[strlen(n)+1];
	strcpy(nom,n);
}


//**********G E T T E R S**********
const char* Local::getNom()const{ return nom;}


//**********C O N S T R U C T O R S**********
Local::Local():Planifiable(){
	nom = NULL;
	setNom("DEFAULT");
}
Local::Local(int id,const char *n):Planifiable(id){
	nom = NULL;
	setNom(n);
}
Local::Local(const Local& l):Planifiable(l){
	nom = NULL;
	setNom(l.getNom());
}
//**********M E T H O D S**********
int Local::compL(const Local& l){
	return strcmp(this->getNom(),l.getNom());
}

//**********O P E R A T O R  O V E R L O A D I N G**********
ostream& operator<<(ostream& s, const Local& l){
	s<<"Id : "<<l.getId()<<"  Local : "<<l.getNom()<<endl;
	return s;
}
Local& Local::operator=(const Local& l){
	setId(l.getId());
	setNom(l.getNom());

	return *this;
}
int Local::operator<(const Local& l){
	return compL(l) < 0;
}
int Local::operator>(const Local& l){
	return compL(l) > 0;
}
int Local::operator==(const Local& l){
	return compL(l) == 0;

}
//**********M E T H O D S**********
const char* Local::Txt(){
	if(txt)
		delete txt;
	char buffer[400];
	sprintf(buffer,"%s",nom);
	txt = new char[strlen(buffer) +1];
	strcpy(txt,buffer);
	return txt;
}

const char* Local::Tuple(){
	if(tuple)
		delete tuple;
	char buffer[400];
	sprintf(buffer,"%d;%s",id,nom);
	tuple = new char[strlen(buffer) +1];
	strcpy(tuple,buffer);
	return tuple;
}
void Local::Save(ofstream & fichier)const{
	if(!fichier)
	{
		cout << "Erreur d'ouverture Local::Save"<< endl;
		exit(1);
	}
	fichier.write((char*)&id,sizeof(int));

    int taille_nom = strlen(getNom())+1;
    fichier.write((char*)&taille_nom,sizeof(int));
    fichier.write(getNom(),taille_nom);
}
void Local::Load(ifstream & fichier){
	if(!fichier.rdbuf()->is_open())
	{
		cout << "Erreur d'ouverture Local::Load"<< endl;
		exit(1);
	}
	fichier.read((char*)&id,sizeof(int));
    int taille_nom;
    fichier.read((char*)&taille_nom,sizeof(int));
	if(taille_nom){
		char *tmp = new char[taille_nom+1];
		fichier.read((char*)tmp,taille_nom);
		setNom(tmp);
		delete tmp;
	}
    
}
//**********D E S T R U C T O R**********
Local::~Local(){
	if(nom)
		delete nom;
}
