#ifndef HORAIRE_H
#define HORAIRE_H
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "Planifiable.h"
#include "Professeur.h"
#include "Groupe.h"
#include "Local.h"
#include "Cours.h"
#include "Iterateur.h"
#include "ListeTriee.h"

using namespace std;
class Horaire{
    private:
    ListeTriee<Professeur> professeurs;
    ListeTriee<Groupe> groupes;
    ListeTriee<Local> locaux;
    ListeTriee<Cours> courss;
    public:
    static int idCourantP;
    static int idCourantG;
    static int idCourantL;
    Horaire();
    ~Horaire();

    ListeTriee<Professeur>& getProfesseurs();
    ListeTriee<Groupe>& getGroupes();
    ListeTriee<Local>& getLocaux();
    ListeTriee<Cours>& getCourss();
    
    void ajouteProfesseur(const char*,const char*);
    void afficheProfesseurs();
    void supprimeProfesseurParIndice(int);
    void supprimeProfesseurParId(int);
    bool professeurDisponible(int i,const Timing& timing);
    Professeur getProfesseur(int id);
    

    void ajouteGroupe(int);
    void afficheGroupes();
    void supprimeGroupeParIndice(int);
    void supprimeGroupeParId(int);
    bool groupeDisponible(int, const Timing&);
    Groupe getGroupe(int);

    void ajouteLocal(const char*);
    void afficheLocaux();
    void supprimeLocalParIndice(int);
    void supprimeLocalParId(int);
    bool localDisponible(int, const Timing&);
    Local getLocal(int);

    void planifie(Cours& c, const Timing& t);
    void supprimeCoursParCode(int code);
    const char* getTuple(const Cours& c);

    void Save(const char* nomFichier)const;
    void Load(const char* nomFichier);

    void importeProfesseurs(const char* nomFichier);
    void importeGroupes(const char* nomFichier);
    void importeLocaux(const char* nomFichier);

    void exporteHoraireProfesseur(int p_id);
    void exporteHoraireGroupe(int id);
    void exporteHoraireLocal(int id);
};

#endif