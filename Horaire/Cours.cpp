#include "Cours.h"
//**********S E T T E R S**********

void Cours::setidProfesseur(const int p){
    idProfesseur = p;
}

void Cours::setidLocal(const int l){
    idLocal = l;
}
void Cours::setidGroupe(const Liste<int> g){
    idGroupes = g;
}
//**********G E T T E R S**********
int Cours::getidProfesseur()const{
    return idProfesseur;
}
int Cours::getidLocal()const{
    return idLocal;
}
Liste<int> Cours::getidGroupe()const{
    return Liste<int>(idGroupes);
}
Liste<int>& Cours::getIdGroupes(){
    return idGroupes;
}


//**********C O N S T R U C T O R S**********
Cours::Cours():Event(){
    setidProfesseur(0);
    setidLocal(0);
}
Cours::Cours(const Cours& c):Event(c){
    setidProfesseur(c.getidProfesseur());
    setidLocal(c.getidLocal());
    idGroupes = c.getidGroupe();
}

//**********M E T H O D S**********
int Cours::compC(const Cours& c){
    int ret = 0;
    if(getTiming() < c.getTiming())ret = -1;
    else
        if(getTiming() > c.getTiming()) ret = 1;
    return ret;
}
void Cours::ajouteIdGroupe(int id){
    idGroupes.insere(id);
}
bool Cours::contientIdGroupe(int id){
    Iterateur<int> it(idGroupes);
    bool trouve = false;
    for (it.reset() ; !trouve && !it.end() ; it++){
        if(id == (int)it) trouve = true;
    }
    return trouve;
}

//**********O P E R A T O R  O V E R L O A D I N G**********
ostream& operator<<(ostream& s,const Cours& c){
    s<<"Code : "<<c.getCode()<<endl;
    s<<"Intitule : "<<c.getIntitule()<<endl;
    s<<"idProf :"<<c.getidProfesseur()<<endl;
    s<<"idLocal :"<<c.getidLocal()<<endl;
    Cours tmp(c);
    Iterateur<int> it(tmp.idGroupes);
    for(it.reset();!it.end();it++){
        s<<"idGroupe :"<<(int)it<<endl;
    }
    s<<"Timing : ";
    c.timing->Affiche();
    return s;
}

Cours& Cours::operator=(const Cours& c){
    setCode(c.getCode());
    setIntitule(c.getIntitule());
    setTiming(c.getTiming());
    setidProfesseur(c.getidProfesseur());
    setidLocal(c.getidLocal());
    idGroupes = c.getidGroupe();
    return *this;
}

int Cours::operator<(const Cours& c){
    return compC(c) < 0;
}
int Cours::operator>(const Cours& c){
    return compC(c) > 0;
}
int Cours::operator==(const Cours& c){
    return compC(c) == 0;
}
void Cours::Save(ofstream & fichier)const{
    if(!fichier)
	{
		cout << "Erreur d'ouverture Local::Save"<< endl;
		exit(1);
	}
    Event::Save(fichier);
    fichier.write((char*)&idProfesseur, sizeof(int));
    fichier.write((char*)&idLocal, sizeof(int));
    int nbG = idGroupes.getNombreElements();
    fichier.write((char*)&nbG,sizeof(int));
    Liste<int> g;
    g = getidGroupe();
    Iterateur<int> itG(g);
    int id;
    for(itG.reset();!itG.end();itG++)
    {
        id = (int)itG;
        fichier.write((char*)&id,sizeof(int));
    }
}
void Cours::Load(ifstream & fichier){
    if(!fichier.rdbuf()->is_open())
	{
		cout << "Erreur d'ouverture Local::Load"<< endl;
		exit(1);
	}
    Event::Load(fichier);
    fichier.read((char*)&idProfesseur,sizeof(int));
    fichier.read((char*)&idLocal,sizeof(int));
    int nbC;
    fichier.read((char*)&nbC,sizeof(int));
    Liste<int> tmpG;
    int grp;
    for(int i = 0;i<nbC;i++)
    {
        fichier.read((char*)&grp,sizeof(int));
        tmpG.insere(grp);
    }
    idGroupes = tmpG;
    
}

//**********D E S T R U C T O R************
Cours::~Cours(){

}