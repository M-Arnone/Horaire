#include "Groupe.h"
//**********S E T T E R S**********
void Groupe::setNumero(int gn){gnum = gn;}


//**********G E T T E R S**********
int Groupe::getNumero()const{return gnum;}


//**********C O N S T R U C T O R S**********
Groupe::Groupe():Planifiable(){
	setNumero(0);
}
Groupe::Groupe(int id, int gn):Planifiable(id){
	setNumero(gn);
}
Groupe::Groupe(const Groupe& g):Planifiable(g){
	setNumero(g.getNumero());
}

//**********M E T H O D S**********
const char* Groupe::Txt(){
	if(txt)
		delete txt;
	char buffer[400];
	sprintf(buffer,"%d",gnum);
	txt = new char[strlen(buffer) +1];
	strcpy(txt,buffer);
	return txt;
}
const char* Groupe::Tuple(){
	if(tuple)
		delete tuple;
	char buffer[400];
	if(gnum == -1)
		sprintf(buffer,"%d;-1",id);
	else sprintf(buffer,"%d;G%d",id,gnum);
	tuple = new char[strlen(buffer) +1];
	strcpy(tuple,buffer);
	return tuple;
}
int Groupe::compG(const Groupe& g){
	if(this->getNumero() < g.getNumero()) return -1;
	if(this->getNumero() > g.getNumero()) return 1;
	return 0;
}
void Groupe::Save(ofstream & fichier)const{
	if(!fichier)
	{
		cout << "Erreur d'ouverture Groupe::Save"<< endl;
		exit(1);
	}
	fichier.write((char*)&id,sizeof(int));
    fichier.write((char*)&gnum,sizeof(int));
}
void Groupe::Load(ifstream & fichier){
	if(!fichier.rdbuf()->is_open())
	{
		cout << "Erreur d'ouverture Groupe::Load"<< endl;
		exit(1);
	}
	fichier.read((char*)&id,sizeof(int));
    fichier.read((char*)&gnum,sizeof(int));
}

//**********O P E R A T O R  O V E R L O A D I N G**********
ostream& operator<<(ostream& s, const Groupe& g){
	s<<"Id : "<<g.getId()<<"  Groupe : "<<g.getNumero()<<endl;
	return s;
}
Groupe& Groupe::operator=(const Groupe& g){
	setId(g.getId());
	setNumero(g.getNumero());
	return *this;
}
int Groupe::operator<(const Groupe& g){
	return compG(g) == -1;
}
int Groupe::operator>(const Groupe& g){
	return compG(g) == 1;
}
int Groupe::operator==(const Groupe& g){
	return compG(g) == 0;
}


//**********D E S T R U C T O R**********
Groupe::~Groupe(){
	
}