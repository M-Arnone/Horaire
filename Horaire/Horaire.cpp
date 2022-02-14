#include "Horaire.h"

//**********S E T T E R S**********


//**********G E T T E R S**********
ListeTriee<Professeur>& Horaire::getProfesseurs(){
    return professeurs;
}
ListeTriee<Groupe>& Horaire::getGroupes(){
    return groupes;
}
ListeTriee<Local>& Horaire::getLocaux(){
    return locaux;
}
ListeTriee<Cours>& Horaire::getCourss(){
    return courss;
}
//**********C O N S T R U C T O R S**********
Horaire::Horaire(){
}

//**********M E T H O D S**********
 void Horaire::ajouteProfesseur(const char *n,const char *p){
     idCourantP++;
     professeurs.insere(Professeur(idCourantP,n,p));
 }
void Horaire::afficheProfesseurs(){
    professeurs.Affiche();
}
void Horaire::supprimeProfesseurParIndice(int i){
    professeurs.retire(i);
}
void Horaire::supprimeProfesseurParId(int id){
    Iterateur<Professeur>it(professeurs);
    bool trouve = false;
    it.reset();
    int cpt = 0;
    Professeur p;
    while(!it.end() && !trouve){
        p = (Professeur)it;
        if(p.getId() == id)
            trouve = true;
        else {
            it++;
            cpt++;
        }         
    }
    if(trouve){
        professeurs.retire(cpt);
    }   
}
bool Horaire::professeurDisponible(int id,const Timing& timing){
    Iterateur<Cours> it(courss);
    Cours c;
    bool disponible = true;
    for(it.reset(); disponible && !it.end(); it++){
            c = (Cours)it;
            if(c.getidProfesseur() == id ){
                    if(timing.intersecte(c.getTiming()))
                            disponible = false;
            }
    }
    return disponible;
}


void Horaire::ajouteGroupe(int nb){
    groupes.insere(Groupe(idCourantG++,nb));
}
void Horaire::afficheGroupes(){
    groupes.Affiche();
}
void Horaire::supprimeGroupeParIndice(int i){
    groupes.retire(i);

}
void Horaire::supprimeGroupeParId(int id){
    Iterateur<Groupe>it(groupes);
    bool trouve = false;
    it.reset();
    int cpt = 0;
    Groupe g;
    while(!it.end() && !trouve){
        g = (Groupe)it;
        if(g.getId() == id)
                trouve = true;
        else{
            it++;
            cpt++;
        }
    }
    if(trouve)
        groupes.retire(cpt);
}
bool Horaire::groupeDisponible(int id, const Timing& timing){
    Iterateur<Cours> it(courss);
    Cours c;
    bool disponible = true;
    for(it.reset(); disponible && !it.end(); it++){
            c = (Cours)it;
            if(c.contientIdGroupe(id) )
                if(timing.intersecte(c.getTiming()) )
                    disponible = false;
            
    }
    return disponible;
}

void Horaire::ajouteLocal(const char*n){
    idCourantL++;
    locaux.insere(Local(idCourantL,n));

}
void Horaire::afficheLocaux(){
    locaux.Affiche();
}
void Horaire::supprimeLocalParIndice(int i){
    locaux.retire(i);
}
void Horaire::supprimeLocalParId(int id){
    Iterateur<Local> it(locaux);
    bool trouve = false;
    it.reset();
    int cpt = 0;
    Local l;
    while(!it.end() && !trouve){
        l = (Local)it;
        if(l.getId() == id)
                trouve = true;
        else{
            it++;
            cpt++;
        } 
    }
    if(trouve)
            locaux.retire(cpt);
}
bool Horaire::localDisponible(int id, const Timing& timing){
    Iterateur<Cours> it(courss);
    Cours c;
    bool disponible = true;
    for(it.reset(); disponible && !it.end(); it++){
            c = (Cours)it;
            if(c.getidLocal() == id)
                if(timing.intersecte(c.getTiming()))
                            disponible = false;
            
    }
    return disponible;
}




void Horaire::planifie(Cours& c, const Timing& timing){
    Timing tmp;
    Liste<int> temp;
    temp = c.getidGroupe();
    Iterateur<int> it(temp);

    if(!professeurDisponible(c.getidProfesseur(),timing))
        throw TimingException("Prof indisponible ou deja planifié",TimingException::PROF_INDISPO);

    if(!localDisponible(c.getidLocal(),timing))
        throw TimingException("Local indisponible ou déjà planifié",TimingException::LOCAL_INDISPO);

    for(it.reset();!it.end();it++)
    {
        if(!groupeDisponible(((int)it),timing))
            throw TimingException("Groupe indisponible ou déjà planifié",TimingException::GROUPE_INDISPO);
    }

    tmp.setJour(timing.getJour());
    tmp.setHeure(timing.getHeure());
    tmp.setDuree(timing.getDuree());

    c.setTiming(tmp);
    c.setCode(Event::codeCourant);
    Event::codeCourant++;

    courss.insere(c);

}


const char* Horaire::getTuple(const Cours& c){
    char *a = new char[400];
    char *nP = new char[400];
    char *nL = new char[400];
    int cpt;
    Timing tmp = c.getTiming();

    Iterateur<Professeur> itP(getProfesseurs());
    Professeur p;
    for(itP.reset();!itP.end();itP++){
            p = (Professeur)itP;
            if(p.getId() == c.getidProfesseur())
                sprintf(nP,"%s %s",p.getNom(),p.getPrenom());
    }

    Iterateur<Local> itL(locaux);
    Local l;
    for(itL.reset();!itL.end();itL++)
    {
        l = (Local)itL;
        if(l.getId() == c.getidLocal())
                strcpy(nL,l.getNom());  
    }
    sprintf(a,"%d;%s;%dh%d;%dh%d;%s;%s;%s;",
    c.getCode(),
    tmp.getJour(),
    tmp.getHeure().getHeure(),
    tmp.getHeure().getMinute(),
    tmp.getDuree().getHeure(),
    tmp.getDuree().getMinute(),
    nL,
    c.getIntitule(),
    nP);
    
    //liste de tous les grps ayant COURS
    Liste<int> grps(c.getidGroupe());
    //it de la liste de tous les grp ayant COURS
    Iterateur<int> itG(grps);
    //it de tous les grp existants
    Iterateur<Groupe> itGs(groupes);
    int id;
    Groupe g;
    for(itG.reset();!itG.end();itG++){
        cpt = 0;
        for(itGs.reset();!itGs.end();itGs++){
                id = (int)itG;
                g = (Groupe)itGs;
                if(cpt == id){
                        strcat(a,"G");
                        strcat(a,g.Txt());
                        strcat(a, ",");
                }
                cpt++;
        }
    }
    char *tuple = new char[strlen(a)+1];
    strcpy(tuple,a);
    delete a;
    delete nL;
    delete nP;
    strcpy(strrchr(tuple,','), "\0");
    return tuple;
}
void Horaire::supprimeCoursParCode(int code){
    Iterateur<Cours> it(courss);
    bool trouve = false;
    it.reset();
    int cpt = 0;
    Cours c;
    
    while(!it.end() && !trouve)
    {
        c = (Cours)it;
        if(c.getCode() == code)
            trouve = true;
        else{
            it++;
            cpt++;
        }
    }
    if(trouve)
        courss.retire(cpt);
}

void Horaire::Save(const char* nomFichier)const{
    ofstream fichier(nomFichier,ios::out);
    if(!fichier){
        cout << "Erreur d'ouverture du fichier" << endl;
        exit(1);
    }
    fichier.write((char*)&Planifiable::idCourant,sizeof(int));

    Liste<Professeur> tmpP(professeurs);
    int nbP = tmpP.getNombreElements();
    fichier.write((char*)&nbP,sizeof(int));
    Iterateur<Professeur> itP(tmpP);
    Professeur p;
    for(itP.reset();!itP.end();itP++){
            p = (Professeur)itP;
            p.Save(fichier);
    }

    Liste<Groupe> tmpG(groupes);
    int nbG = tmpG.getNombreElements();
    fichier.write((char*)&nbG,sizeof(int));
    Iterateur<Groupe> itG(tmpG);
    Groupe g;
    for(itG.reset();!itG.end();itG++){
            g = (Groupe)itG;
            g.Save(fichier);
    }

    Liste<Local> tmpL(locaux);
    int nbL = tmpL.getNombreElements();
    fichier.write((char*)&nbL,sizeof(int));
    Iterateur<Local> itL(tmpL);
    Local l;
    for(itL.reset();!itL.end();itL++){
            l = (Local)itL;
            l.Save(fichier);
    }

    fichier.write((char*)&Event::codeCourant,sizeof(int));

    Liste<Cours> tmpC(courss);
    int nbC = tmpC.getNombreElements();
    fichier.write((char*)&nbC,sizeof(int));
    Iterateur<Cours> itC(tmpC);
    Cours c;
    for(itC.reset();!itC.end();itC++){
            c = (Cours)itC;
            c.Save(fichier);
    }

    fichier.close();


}
void Horaire::Load(const char* nomFichier){
    ifstream fichier(nomFichier,ios::in);
    if (!fichier.rdbuf()->is_open())
    {
        cout << "Erreur d'ouverture Horaire::Load" << endl;
        exit(1);
    }

    ListeTriee<Professeur> P;
    ListeTriee<Groupe> G;
    ListeTriee<Local> L;
    ListeTriee<Cours> C;

    professeurs = P;
    groupes = G;
    locaux = L;
    courss = C;

    int idC,i;
    fichier.read((char*)&idC,sizeof(int));
    Planifiable::idCourant = idC;
    int nbP;
    fichier.read((char*)&nbP,sizeof(int));
    Professeur p;
    for(i = 0;i < nbP;i++)
    {
        p.Load(fichier);
        professeurs.insere(p);
    }
    int nbG;
    fichier.read((char*)&nbG,sizeof(int));
    Groupe g;
    for(i = 0;i < nbG; i++)
    {
        g.Load(fichier);
        groupes.insere(g);
    }
    int nbL;
    fichier.read((char*)&nbL,sizeof(int));
    Local l;
    for(i=0;i<nbL;i++)
    {
        l.Load(fichier);
        locaux.insere(l);
    }
    int idCC;
    fichier.read((char*)&idCC,sizeof(int));
    Event::codeCourant = idCC;
    int nbC;
    fichier.read((char*)&nbC,sizeof(int));
    Cours c;
   for(i=0;i<nbC;i++)
    {
            c.Load(fichier);
            courss.insere(c);
    }
    fichier.close();
}

void Horaire::importeProfesseurs(const char* nomFichier){
    ifstream fichier(nomFichier,ios::in);
    if(!fichier){
        cout << "Erreur d'ouverture importeProfesseur" << endl;
        exit(1);
    }
    else{
        char *nom, *prenom,*ch;
        ch = new char[400];
        nom = new char[400];
        prenom = new char[400];

        while(fichier.getline(ch, 400)){
            strcpy(nom, strtok(ch, ";")); 
            strcpy(prenom, strtok(NULL, ";"));
            ajouteProfesseur(nom,prenom);  
        }
        delete ch;
        delete nom;
        delete prenom;
        fichier.close();
    }
    

}
void Horaire::importeGroupes(const char* nomFichier){
    ifstream fichier(nomFichier,ios::in);
    if(!fichier){
        cout << "Erreur d'ouverture importeGroupes" << endl;
        exit(1);
    }
    else{
        char *ch, *grp;
        ch = new char[400];
        grp = new char[400];

        while(fichier.getline(ch, 500)){
            strcpy(grp, strtok(ch, ";"));
            ajouteGroupe(atoi(grp));
        }
        delete ch;
        delete grp;

        fichier.close();
    }
}
void Horaire::importeLocaux(const char* nomFichier){
    ifstream fichier(nomFichier,ios::in);
    if(!fichier){
        cout << "Erreur d'ouverture importeLocaux" << endl;
        exit(1);
    }
    else{
        char *ch, *l;
        ch = new char[400];
        l = new char[400];
        while(fichier.getline(ch, 500)){
            strcpy(l, strtok(ch, ";"));
            ajouteLocal(l);
        }
        delete ch;
        delete l;

        fichier.close();
    }
}
void Horaire::exporteHoraireProfesseur(int p_id){
    Cours c;
    Professeur p;
    Groupe g;
    int g_id;
    char    *nomFichier = new char[400],
            *tmp = new char[400],
            *g_tuple = new char[400];
    bool trouve = false,g_trouve = false;
    Iterateur<Cours> itC(getCourss());
    Iterateur<int> g_it(c.getIdGroupes());
    Iterateur<Professeur> itP(getProfesseurs());
    Iterateur<Groupe> itG(getGroupes());
    strcpy(nomFichier,"");
    //trouve le bon nom de fichier donc le bon prof à exporter
    for(itP.reset();!trouve && !itP.end();itP++){
        p = (Professeur)itP;
        if(p.getId() == p_id){
                strcat(nomFichier,p.getNom());
                strcat(nomFichier, "_");
                strcat(nomFichier,p.getPrenom());
                trouve = true;
        }
    }
    strcat(nomFichier,".txt");
    ofstream fichier(nomFichier,ios::out);
    if(!fichier.is_open()){
        cout << "Erreur d'ouverture Horaire::exporteHoraireProfesseur" << endl;
        exit(1);
    }
    else{
        fichier<<"Horaire de "<<p.getNom()<<" "<<p.getPrenom()<<" :\n"<<endl;
        //boucle permettant de trouver tous les cours correspondant
        //au prof qu'on exporte
        for(itC.reset() ;!itC.end();itC++){
            c = (Cours)itC;
            if(c.getidProfesseur() == p_id){
                strcpy(g_tuple,"");
                //on se balade dans tous les grp planifies
                for(g_it.reset();!g_it.end();g_it++){
                    g_id = (int)g_it;
                    //boucle permettant de trouver le bon grp
                    for(itG.reset();!g_trouve && !itG.end();itG++){
                        g = (Groupe)itG;
                        if(g.getId() == g_id)
                                g_trouve = true; 
                    }
                    //groupe planifie == groupe du cours donc ajt dans le tuple
                    if(g_trouve){
                        strcat(g_tuple, g.Txt());
                        strcat(g_tuple, ",");
                    }
                }
                //groupes ajouté à la chaine de caractère...
                //on va ajouter le reste (qui vient avant)
                sprintf(tmp,"%s\t%dh%d\t%dh%d\t%s\t%s\n",
                c.getTiming().getJour(),
                c.getTiming().getHeure().getHeure(),
                c.getTiming().getHeure().getMinute(),
                c.getTiming().getDuree().getHeure(),
                c.getTiming().getDuree().getMinute(),
                c.getIntitule(),
                g_tuple);
                fichier.write(tmp, sizeof(char)*strlen(tmp));
            }
                
        }
        fichier.close();
    }
    delete nomFichier;
    delete tmp;
    delete g_tuple;

}
void Horaire::exporteHoraireGroupe(int g_id){
    char    *nomFichier = new char[400],
            *tmp = new char[400],
            *p_tuple = new char[400];
    strcpy(nomFichier,"G");
    strcpy(tmp,"");
    strcpy(p_tuple,"");
    
    Groupe g;
    Professeur p;
    bool trouve = false,p_trouve = false;
    Iterateur<Groupe> itG(getGroupes());
    

    //trouve le bon nom de fichier donc le bon grp à exporter
    for(itG.reset();!trouve && !itG.end();itG++){
        g = (Groupe)itG;
        if(g.getId() == g_id){
                strcat(nomFichier,g.Txt());
                trouve = true;
        }
    }
    strcat(nomFichier,".txt");
    ofstream fichier(nomFichier,ios::out);
    if(!fichier.is_open()){
        cout << "Erreur d'ouverture Horaire::exporteHoraireGroupe" << endl;
        exit(1);
    }
    else{
        fichier<<"Horaire de G"<<g.Txt()<<" :\n"<<endl;
        Cours c;
        Iterateur<Cours> itC(getCourss());
        for(itC.reset();!itC.end();itC++){
            c = (Cours)itC;
            cout<<"COURS: ";
            c.Affiche();
            cout<<endl<<endl;
            if(c.contientIdGroupe(g_id)){

                    /*Iterateur<Professeur> itP(getProfesseurs());
                    for(itP.reset();!p_trouve && !itP.end();itP++){
                        p = (Professeur)itP;
                        if(p.getId() == c.getidProfesseur()){
                                p_trouve = true;
                        }
                    }
                    
                    if(p_trouve){
                        strcat(p_tuple,p.Txt());
                    }
                    sprintf(tmp,"%s\t%dh%d\t%dh%d\t%s\t%s\n",
                    c.getTiming().getJour(),
                    c.getTiming().getHeure().getHeure(),
                    c.getTiming().getHeure().getMinute(),
                    c.getTiming().getDuree().getHeure(),
                    c.getTiming().getDuree().getMinute(),
                    c.getIntitule(),
                    p_tuple);
                    fichier.write(tmp, sizeof(char)*strlen(tmp));*/
                
            }

        }
        fichier.close();
    }
    delete nomFichier;
    delete tmp;
    delete p_tuple;

}
void Horaire::exporteHoraireLocal(int l_id){
    char *nomFichier = new char [400],
        *g_tuple = new char[400],
        *tmp = new char[400];
    strcpy(nomFichier,"");
    Iterateur<Local> itL(getLocaux());
    bool trouve = false;
    Local l;
    bool g_trouve = false;
    Groupe g;
    int g_id;
    Iterateur<Groupe> itG(getGroupes());
    for(itL.reset();!trouve && !itL.end();itL++){
        l = (Local)itL;
        if(l.getId() == l_id){
                strcat(nomFichier,l.Txt());
                trouve = true;
        }
    }
    strcat(nomFichier,".txt");
    ofstream fichier(nomFichier,ios::out);
    if(!fichier.is_open()){
        cout << "Erreur d'ouverture Horaire::exporteHoraireLocal" << endl;
        exit(1);
    }
    else{
        fichier<<"Horaire de "<<l.Txt()<<" :\n"<<endl;
        Iterateur<Cours> itC(getCourss());
        Cours c;
        Iterateur<int> g_it(c.getIdGroupes());
        for(itC.reset();!itC.end();itC++){
            c = (Cours)itC;
            if(c.getidLocal() == l_id){

                
                //on se balade dans tous les grp planifies
                for(g_it.reset();!g_it.end();g_it++){
                    g_id = (int)g_it;
                    //boucle permettant de trouver le bon grp
                    for(itG.reset();!g_trouve && !itG.end();itG++){
                        g = (Groupe)itG;
                        if(g.getId() == g_id)
                                g_trouve = true; 
                    }
                    //groupe planifie == groupe du cours donc ajt dans le tuple
                    if(g_trouve){
                        strcat(g_tuple, g.Txt());
                        strcat(g_tuple, ",");
                    }
                }
                Iterateur<Professeur> itTmp(getProfesseurs());
                Professeur p;
                bool p_trouve = false;
                for(itTmp.reset();!p_trouve && !itTmp.end();itTmp++){
                    p = (Professeur)itTmp;
                    if(p.getId() == c.getidProfesseur())
                        p_trouve = true;
                }
                //recherche du bon prof;
                strcpy(g_tuple,"");
                sprintf(tmp,"%s\t%dh%d\t%dh%d\t%s\t%s\t%s\n",
                c.getTiming().getJour(),
                c.getTiming().getHeure().getHeure(),
                c.getTiming().getHeure().getMinute(),
                c.getTiming().getDuree().getHeure(),
                c.getTiming().getDuree().getMinute(),
                c.getIntitule(),
                g_tuple,
                p.Txt()
                );
                fichier.write(tmp, sizeof(char)*strlen(tmp));
            }
        }
        fichier.close();
    }
    delete nomFichier;
    delete g_tuple;
    delete tmp;

    

}
//**********D E S T R U C T O R**********
Horaire::~Horaire(){

}
