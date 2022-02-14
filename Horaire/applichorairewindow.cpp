#include "applichorairewindow.h"
#include "ui_applichorairewindow.h"

#include <QDesktopWidget>
#include <QMessageBox>
#include <QInputDialog>

#include <iostream>
using namespace std;

int Event::codeCourant = 1;
int Planifiable::idCourant = 1;

int Horaire::idCourantP = 0;
int Horaire::idCourantG = 0;
int Horaire::idCourantL = 0;

ApplicHoraireWindow::ApplicHoraireWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ApplicHoraireWindow)
{
    ui->setupUi(this);

    // Configuration de la table des professeurs
    ui->tableWidgetProfesseurs->setColumnCount(3);
    ui->tableWidgetProfesseurs->setRowCount(0);
    QStringList labelsTableProfesseurs;
    labelsTableProfesseurs << "id" << "Nom" << "Prenom";
    ui->tableWidgetProfesseurs->setHorizontalHeaderLabels(labelsTableProfesseurs);
    ui->tableWidgetProfesseurs->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetProfesseurs->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetProfesseurs->horizontalHeader()->setVisible(true);
    ui->tableWidgetProfesseurs->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidgetProfesseurs->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetProfesseurs->verticalHeader()->setVisible(false);
    ui->tableWidgetProfesseurs->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des groupes
    ui->tableWidgetGroupes->setColumnCount(2);
    ui->tableWidgetGroupes->setRowCount(0);
    QStringList labelsTableGroupes;
    labelsTableGroupes << "id" << "Numero";
    ui->tableWidgetGroupes->setHorizontalHeaderLabels(labelsTableGroupes);
    ui->tableWidgetGroupes->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tableWidgetGroupes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetGroupes->horizontalHeader()->setVisible(true);
    ui->tableWidgetGroupes->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidgetGroupes->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetGroupes->verticalHeader()->setVisible(false);
    ui->tableWidgetGroupes->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des locaux
    ui->tableWidgetLocaux->setColumnCount(2);
    ui->tableWidgetLocaux->setRowCount(0);
    QStringList labelsTableLocaux;
    labelsTableLocaux << "id" << "Nom";
    ui->tableWidgetLocaux->setHorizontalHeaderLabels(labelsTableLocaux);
    ui->tableWidgetLocaux->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetLocaux->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetLocaux->horizontalHeader()->setVisible(true);
    ui->tableWidgetLocaux->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidgetLocaux->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetLocaux->verticalHeader()->setVisible(false);
    ui->tableWidgetLocaux->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des cours
    ui->tableWidgetCourss->setColumnCount(8);
    ui->tableWidgetCourss->setRowCount(0);
    QStringList labelsTableCourss;
    labelsTableCourss << "code" << "Jour" << "Heure" << "Duree" << "Local" << "Intitule" << "Professeur" << "Groupes";
    ui->tableWidgetCourss->setHorizontalHeaderLabels(labelsTableCourss);
    ui->tableWidgetCourss->setSelectionMode(QAbstractItemView::NoSelection);
    //ui->tableWidgetCourss->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetCourss->horizontalHeader()->setVisible(true);
    ui->tableWidgetCourss->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidgetCourss->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetCourss->verticalHeader()->setVisible(false);
    ui->tableWidgetCourss->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Pour faire joli
    ui->pushButtonAjouterProfesseur->setStyleSheet("background-color: lightgreen");
    ui->pushButtonAjouterGroupe->setStyleSheet("background-color: lightgreen");
    ui->pushButtonAjouterLocal->setStyleSheet("background-color: lightgreen");
    ui->pushButtonSupprimerProfesseur->setStyleSheet("background-color: orange");
    ui->pushButtonSupprimerGroupe->setStyleSheet("background-color: orange");
    ui->pushButtonSupprimerLocal->setStyleSheet("background-color: orange");
    ui->pushButtonPlanifier->setStyleSheet("background-color: lightblue");
    ui->pushButtonSelectionner->setStyleSheet("background-color: lightblue");

    // On fixe la taille et la position de la fenetre
    setFixedSize(1070,647);
    move((QApplication::desktop()->width()-width())/2,(QApplication::desktop()->height()-height())/2);
}

ApplicHoraireWindow::~ApplicHoraireWindow()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des professeurs /////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::ajouteTupleTableProfesseurs(const char *tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple,199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char id[20];
    strcpy(id,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char nom[40];
    strcpy(nom,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char prenom[40];
    strcpy(prenom,tmp);

    // Ajout possible
    int nbLignes = ui->tableWidgetProfesseurs->rowCount();
    nbLignes++;
    ui->tableWidgetProfesseurs->setRowCount(nbLignes);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(id);
    ui->tableWidgetProfesseurs->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(nom);
    ui->tableWidgetProfesseurs->setItem(nbLignes-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(prenom);
    ui->tableWidgetProfesseurs->setItem(nbLignes-1,2,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::videTableProfesseurs()
{
    ui->tableWidgetProfesseurs->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getIndiceProfesseurSelectionne()
{
    QModelIndexList liste = ui->tableWidgetProfesseurs->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des groupes /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::ajouteTupleTableGroupes(const char *tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple,199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char id[20];
    strcpy(id,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char numero[40];
    strcpy(numero,tmp);

    // Ajout possible
    int nbLignes = ui->tableWidgetGroupes->rowCount();
    nbLignes++;
    ui->tableWidgetGroupes->setRowCount(nbLignes);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(id);
    ui->tableWidgetGroupes->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(numero);
    ui->tableWidgetGroupes->setItem(nbLignes-1,1,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::videTableGroupes()
{
    ui->tableWidgetGroupes->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getIndicesGroupesSelectionnes(int* tab)
{
    QModelIndexList liste = ui->tableWidgetGroupes->selectionModel()->selectedRows();
    if (liste.size() == 0) return 0;
    for (int i=0 ; i<liste.size() ; i++) tab[i] = liste.at(i).row();
    return liste.size();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des locaux //////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::ajouteTupleTableLocaux(const char *tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple,199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char id[20];
    strcpy(id,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char nom[40];
    strcpy(nom,tmp);

    // Ajout possible
    int nbLignes = ui->tableWidgetLocaux->rowCount();
    nbLignes++;
    ui->tableWidgetLocaux->setRowCount(nbLignes);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(id);
    ui->tableWidgetLocaux->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(nom);
    ui->tableWidgetLocaux->setItem(nbLignes-1,1,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::videTableLocaux()
{
    ui->tableWidgetLocaux->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getIndiceLocalSelectionne()
{
    QModelIndexList liste = ui->tableWidgetLocaux->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des professeurs /////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::ajouteTupleTableCourss(const char *tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[300];
    strncpy(Tuple,tuple,299);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char code[20];
    strcpy(code,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char jour[20];
    strcpy(jour,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char heure[20];
    strcpy(heure,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char duree[20];
    strcpy(duree,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char local[20];
    strcpy(local,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char intitule[40];
    strcpy(intitule,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char professeur[60];
    strcpy(professeur,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char groupes[100];
    strcpy(groupes,tmp);

    // Ajout possible
    int nbLignes = ui->tableWidgetCourss->rowCount();
    nbLignes++;
    ui->tableWidgetCourss->setRowCount(nbLignes);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(code);
    ui->tableWidgetCourss->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(jour);
    ui->tableWidgetCourss->setItem(nbLignes-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(heure);
    ui->tableWidgetCourss->setItem(nbLignes-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(duree);
    ui->tableWidgetCourss->setItem(nbLignes-1,3,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(local);
    ui->tableWidgetCourss->setItem(nbLignes-1,4,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(intitule);
    ui->tableWidgetCourss->setItem(nbLignes-1,5,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(professeur);
    ui->tableWidgetCourss->setItem(nbLignes-1,6,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(groupes);
    ui->tableWidgetCourss->setItem(nbLignes-1,7,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::videTableCourss()
{
    ui->tableWidgetCourss->setRowCount(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions permettant d'afficher des boites de dialogue /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::dialogueMessage(const char* titre,const char* message)
{
   QMessageBox::information(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::dialogueErreur(const char* titre,const char* message)
{
   QMessageBox::critical(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ApplicHoraireWindow::dialogueDemandeTexte(const char* titre,const char* question)
{
    QString chaine = QInputDialog::getText(this,titre,question);
    strcpy(buffer,chaine.toStdString().c_str());
    return buffer;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::dialogueDemandeInt(const char* titre,const char* question)
{
    return QInputDialog::getInt(this,titre,question);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles aux widgets de la fenetre /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ApplicHoraireWindow::getNomProfesseur()
{
    strcpy(nomProfesseur,ui->lineEditNomProfesseur->text().toStdString().c_str());
    return nomProfesseur;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setNomProfesseur(const char* nom)
{
    ui->lineEditNomProfesseur->setText(nom);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ApplicHoraireWindow::getPrenomProfesseur()
{
    strcpy(prenomProfesseur,ui->lineEditPrenomProfesseur->text().toStdString().c_str());
    return prenomProfesseur;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setPrenomProfesseur(const char* nom)
{
    ui->lineEditPrenomProfesseur->setText(nom);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getNumeroGroupe()
{
    char tmp[80];
    strcpy(tmp,ui->lineEditNumeroGroupe->text().toStdString().c_str());
    int num = atoi(tmp);
    if (num == 0) num = -1;
    return num;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::videNumeroGroupe()
{
    ui->lineEditNumeroGroupe->setText("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ApplicHoraireWindow::getNomLocal()
{
    strcpy(nomLocal,ui->lineEditNomLocal->text().toStdString().c_str());
    return nomLocal;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setNomLocal(const char* nom)
{
    ui->lineEditNomLocal->setText(nom);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ApplicHoraireWindow::getJourSelectionne()
{
    strcpy(jour,ui->comboBoxJour->currentText().toStdString().c_str());
    return jour;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getHeuresDebut()
{
    char tmp[80];
    strcpy(tmp,ui->lineEditHeuresDebut->text().toStdString().c_str());
    int num = atoi(tmp);
    return num;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::videHeuresDebut()
{
    ui->lineEditHeuresDebut->setText("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getMinutesDebut()
{
    char tmp[80];
    strcpy(tmp,ui->lineEditMinutesDebut->text().toStdString().c_str());
    int num = atoi(tmp);
    return num;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::videMinutesDebut()
{
    ui->lineEditMinutesDebut->setText("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getDuree()
{
    char tmp[80];
    strcpy(tmp,ui->lineEditDuree->text().toStdString().c_str());
    int num = atoi(tmp);
    if (num == 0) num = -1;
    return num;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::videDuree()
{
    ui->lineEditDuree->setText("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ApplicHoraireWindow::getIntitule()
{
    strcpy(intitule,ui->lineEditIntitule->text().toStdString().c_str());
    return intitule;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setIntitule(const char* intitule)
{
    ui->lineEditIntitule->setText(intitule);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ApplicHoraireWindow::isJourChecked()
{
    return ui->checkBoxJour->isChecked();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setJourChecked(bool b)
{
    ui->checkBoxJour->setChecked(b);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ApplicHoraireWindow::isProfesseurChecked()
{
    return ui->checkBoxProfesseur->isChecked();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setProfesseurChecked(bool b)
{
    ui->checkBoxProfesseur->setChecked(b);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ApplicHoraireWindow::isGroupeChecked()
{
    return ui->checkBoxGroupe->isChecked();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setGroupeChecked(bool b)
{
    ui->checkBoxGroupe->setChecked(b);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ApplicHoraireWindow::isLocalChecked()
{
    return ui->checkBoxLocal->isChecked();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setLocalChecked(bool b)
{
    ui->checkBoxLocal->setChecked(b);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonAjouterProfesseur_clicked()
{
    cout << "Clic sur bouton Ajouter Professeur" << endl;
    if(strcmp(getNomProfesseur(),"") == 0 || strcmp(getPrenomProfesseur(),"") == 0)
        dialogueErreur("ERREUR","Veuillez remplir tous les champs disponibles !!!");

    h.ajouteProfesseur(getNomProfesseur(),getPrenomProfesseur());
    videTableProfesseurs();

    Iterateur<Professeur> it(h.getProfesseurs());
    Professeur p;
    it.reset();
    while(!it.end()){
        p = (Professeur)it;
        ajouteTupleTableProfesseurs(p.Tuple());
        it++;
    }
    setNomProfesseur("");
    setPrenomProfesseur("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonAjouterGroupe_clicked()
{
    cout << "Clic sur bouton Ajouter Groupe" << endl;
    //erreur en cas de numéro pas bon
    if(getNumeroGroupe() == -1){
        h.ajouteGroupe(dialogueDemandeInt("ERREUR","Veuillez rentrer un int !"));
    }
    else h.ajouteGroupe(getNumeroGroupe());
    videTableGroupes();
    Iterateur<Groupe> it(h.getGroupes());
    Groupe g;
    it.reset();
    while(!it.end()){
        g = (Groupe)it;
        ajouteTupleTableGroupes(g.Tuple());
        it++;
    }
    videNumeroGroupe();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonAjouterLocal_clicked()
{
    cout << "Clic sur bouton Ajouter Local" << endl;
    if(strcmp(getNomLocal(),"") == 0)
        dialogueErreur("ERREUR","Veuillez remplir tous les champs disponibles !!!");
    h.ajouteLocal(getNomLocal());
    videTableLocaux();

    Iterateur<Local> it(h.getLocaux());
    Local l;
    it.reset();
    while(!it.end()){
        l = (Local)it;
        ajouteTupleTableLocaux(l.Tuple());
        it++;
    }
    setNomLocal("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonSupprimerProfesseur_clicked()
{
    cout << "Clic sur bouton Supprimer Professeur" << endl;
    int i = getIndiceProfesseurSelectionne();
    if(i == -1)
        dialogueErreur("ERREUR","Aucun professeur n'a été sélectionné");
    else{
        h.supprimeProfesseurParIndice(i);
        videTableProfesseurs();
        Iterateur<Professeur> it(h.getProfesseurs());
        Professeur p ;
        it.reset();
        while(!it.end()){
            p = (Professeur)it;
            ajouteTupleTableProfesseurs(p.Tuple());
            it++;
        }
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonSupprimerGroupe_clicked()
{
    cout << "Clic sur bouton Supprimer Groupe" << endl;
    int tab[400] = {-1};
    getIndicesGroupesSelectionnes(tab);
    int i = 0;
    if(tab[0] == -1)
        dialogueErreur("ERREUR","Aucun groupe n'a été sélectionné");
    else{
        while(tab[i]){
            h.supprimeGroupeParIndice(tab[i]);
            i++;
        }
        videTableGroupes();
        Iterateur<Groupe> it(h.getGroupes());
        Groupe g;
        it.reset();
        while(!it.end()){
            g = (Groupe)it;
            ajouteTupleTableGroupes(g.Tuple());
            it++;
        }

    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonSupprimerLocal_clicked()
{
    cout << "Clic sur bouton Supprimer Local" << endl;
    int i = getIndiceLocalSelectionne();
    if(i == -1)
        dialogueErreur("ERREUR","Aucun local n'a été sélectionné");
    else{
        h.supprimeLocalParIndice(i);
        videTableLocaux();
        Iterateur<Local> it(h.getLocaux());
        Local l ;
        it.reset();
        while(!it.end()){
            l = (Local)it;
            ajouteTupleTableLocaux(l.Tuple());
            it++;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonPlanifier_clicked()
{
    cout << "Clic sur bouton Planifier" << endl;
    try{
        int tab[40] ={-1};
        if (getJourSelectionne() && (getIndiceProfesseurSelectionne()!=-1) && getIndicesGroupesSelectionnes(tab) && (getIndiceLocalSelectionne()!=-1) && getHeuresDebut()>=0 && getMinutesDebut()>=0 && getDuree() && getIntitule()){
                Timing timing;
                Temps temps(getHeuresDebut(),getMinutesDebut());
                timing.setJour(getJourSelectionne());
                timing.setHeure(temps);
                timing.setDuree(getDuree());

                Cours c;
                c.setTiming(timing);
                c.setIntitule(getIntitule());

                //chercher idProf avec indice;
                Iterateur<Professeur> itP(h.getProfesseurs());
                Professeur p;
                int cpt = 0,id = 0;
                for(itP.reset();!itP.end();itP++){
                    
                    if(cpt == getIndiceProfesseurSelectionne()){
                        p = (Professeur)itP;
                        id = p.getId();
                    } 
                    cpt++;
                }
                c.setidProfesseur(id);

                //de même avec local
                Iterateur<Local> itL(h.getLocaux());
                Local l;
                cpt = 0, id = 0;
                for(itL.reset();!itL.end();itL++){
                    if(cpt == getIndiceLocalSelectionne()){
                        l = (Local)itL;
                        id = l.getId();
                    }
                    cpt++;
                }
                c.setidLocal(id);

                //de même pr les grp aussi mais avec un tab car on peut
                //avoir plusieurs grp pr un même cours
                
                cpt = 0,id = 1;
                cpt = getIndicesGroupesSelectionnes(tab);
                for(int i=0; i<cpt; i++){
                    id = tab[i];
                    c.ajouteIdGroupe(id);
                }
                h.planifie(c,timing);
                ajouteTupleTableCourss(h.getTuple(c));
        }
        else{
            dialogueErreur("ERREUR","Champ manquant");
        }

    }
    catch (TimingException &e)
    {
        dialogueErreur("Problème disponibilité", e.getMessage());
    }
    catch (TempsException &e)
    {
        dialogueErreur("Problème Encodage", e.getMessage());
    }
        

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonSelectionner_clicked()
{
    cout << "Clic sur bouton Selectionner" << endl;
    char *jour = new char[400];
    int idG = 0, idL = 0, idP = 0;
    int i_g,i_l,i_p, i = 0;
    int tab[400];

    if(isJourChecked())
        strcpy(jour,getJourSelectionne());

    if(isProfesseurChecked()){
        //recherce idProf à l'aide de l'indice
        i_p = getIndiceProfesseurSelectionne();
        Iterateur<Professeur> itP(h.getProfesseurs()); 
        Professeur p;   
        bool trouve = false;  
        for(i = 0,itP.reset();!trouve && !itP.end() ;i++,itP++){
            if(i == i_p){
                p = (Professeur)itP;    
                trouve = true;
            }
        }
        if(trouve)
            idP = p.getId();
    }
    if(isGroupeChecked()){
        i_g = getIndicesGroupesSelectionnes(tab);
        Iterateur<Groupe> itG(h.getGroupes());
        Groupe g;
        bool trouve = false;
        for(i = 0, itG.reset();!trouve && !itG.end();i++,itG++){
            if(i == i_g){
                g = (Groupe)itG;
                trouve = true;
            }
        }
        if(trouve)
            idG = g.getId();
    }
    if(isLocalChecked()){
        i_l = getIndiceLocalSelectionne();
        Iterateur<Local> itL(h.getLocaux());
        Local l;
        bool trouve = false;
        for(i = 0,itL.reset();!trouve && !itL.end();i++,itL++){
            if(i == i_l){
                l = (Local)itL;
                trouve = true;
            }
        }
        if(trouve)
            idL = l.getId();
    }

    //affichage cours
    Iterateur<Cours> itC(h.getCourss());
    Cours c;
    videTableCourss();
    for(itC.reset();!itC.end();itC++){
        c = (Cours)itC;
        if(isJourChecked() && strcmp(c.getTiming().getJour(),jour) != 0)
                continue;  
        else 
            if(isLocalChecked() && c.getidLocal() != idL)
                continue;                
            else 
                if(isProfesseurChecked() && c.getidProfesseur() != idP)
                    continue;    
                else 
                    if(isGroupeChecked() && !c.contientIdGroupe(idG)) 
                        continue; 
                    else ajouteTupleTableCourss(h.getTuple(c)); 
    }

    delete jour;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les items de menu //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionQuitter_triggered()
{
    cout << "Clic sur Menu Fichier --> Item Quitter" << endl;
    // TO DO

    QApplication::quit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionOuvrir_triggered()
{

    cout << "Clic sur Menu Fichier --> Item Ouvrir" << endl;
    char nomFichier[80];
    strcpy(nomFichier,dialogueDemandeTexte("Ouvrir Horaire...","Nom du fichier ?"));
    strcat(nomFichier,".hor");
    cout << "Nom fichier = " << nomFichier << endl;
    h.Load(nomFichier);
    // TO DO
    ResetProfesseurs();
    ResetGroupes();
    ResetLocaux(); 
    ResetCourss();
    ResetFields();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionNouveau_triggered()
{
    cout << "Clic sur Menu Fichier --> Item Nouveau" << endl;

   
    ListeTriee<Professeur> P;
    ListeTriee<Groupe> G;
    ListeTriee<Local> L;
    ListeTriee<Cours> C;

    h.getProfesseurs() = P;
    h.getGroupes() = G;
    h.getLocaux() = L;
    h.getCourss() = C;

    Event::codeCourant = 1;
    Planifiable::idCourant = 1;

    ResetProfesseurs();
    ResetGroupes();
    ResetLocaux(); 
    ResetCourss();
    ResetFields();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionEnregistrer_triggered()
{
    cout << "Clic sur Menu Fichier --> Item Enregistrer" << endl;

    char nomFichier[80];
    strcpy(nomFichier,dialogueDemandeTexte("Enregistrer Horaire...","Nom du fichier ?"));
    strcat(nomFichier,".hor");
    cout << "Nom fichier = " << nomFichier << endl;
    h.Save(nomFichier);
    ResetProfesseurs();
    ResetGroupes();
    ResetLocaux(); 
    ResetCourss();
    ResetFields();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionSupprimerProfesseur_triggered()
{
    cout << "Clic sur Menu Supprimer --> Item Professeur" << endl;
    int i = dialogueDemandeInt("SUPPRIMER","id du professeur à supprimer");
    h.supprimeProfesseurParId(i);
    videTableProfesseurs();
    Iterateur<Professeur> it(h.getProfesseurs());
    Professeur p ;
    it.reset();
    while(!it.end()){
        p = (Professeur)it;
        ajouteTupleTableProfesseurs(p.Tuple());
        it++;
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionSupprimerGroupe_triggered()
{
    cout << "Clic sur Menu Supprimer --> Item Groupe" << endl;
    // TO DO
    int i = dialogueDemandeInt("SUPPRIMER","id du groupe à supprimer");
    h.supprimeGroupeParId(i);
    videTableGroupes();
    Iterateur<Groupe> it(h.getGroupes());
    Groupe g;
    it.reset();
    while(!it.end()){
        g = (Groupe)it;
        ajouteTupleTableGroupes(g.Tuple());
        it++;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionSupprimerLocal_triggered()
{
    cout << "Clic sur Menu Supprimer --> Item Local" << endl;
    int i = dialogueDemandeInt("SUPPRIMER","id du local à supprimer");
    h.supprimeLocalParId(i);
    videTableLocaux();
    Iterateur<Local> it(h.getLocaux());
    Local l;
    it.reset();
    while(!it.end()){
        l = (Local)it;
        ajouteTupleTableLocaux(l.Tuple());
        it++;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionSupprimerCours_triggered()
{
    cout << "Clic sur Menu Supprimer --> Item Cours" << endl;
    int i = dialogueDemandeInt("SUPPRIMER","id du cours à supprimer");
    h.supprimeCoursParCode(i);
    videTableCourss();
    Iterateur<Cours> it(h.getCourss());
    Cours c;
    it.reset();
    while(!it.end()){
        c = (Cours)it;
        ajouteTupleTableCourss(h.getTuple(c));
        it++;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionImporterProfesseurs_triggered()
{
    cout << "Clic sur Menu Importer --> Item Professeurs" << endl;
    char nomFichier[80];
    strcpy(nomFichier,dialogueDemandeTexte("Importer Professeur...","Nom du fichier ?"));
    strcat(nomFichier,".csv");
    cout << "Nom fichier = " << nomFichier << endl;
    h.importeProfesseurs(nomFichier);
    ResetProfesseurs();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionImporterGroupes_triggered()
{
    cout << "Clic sur Menu Importer --> Item Groupes" << endl;
    char nomFichier[80];
    strcpy(nomFichier,dialogueDemandeTexte("Importer Groupes...","Nom du fichier ?"));
    strcat(nomFichier,".csv");
    cout << "Nom fichier = " << nomFichier << endl;
    h.importeGroupes(nomFichier);
    ResetGroupes();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionImporterLocaux_triggered()
{
    cout << "Clic sur Menu Importer --> Item Locaux" << endl;
    char nomFichier[80];
    strcpy(nomFichier,dialogueDemandeTexte("Importer Locaux...","Nom du fichier ?"));
    strcat(nomFichier,".csv");
    cout << "Nom fichier = " << nomFichier << endl;
    h.importeLocaux(nomFichier);
    ResetLocaux();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionExporterProfesseur_triggered()
{
    cout << "Clic sur Menu Exporter horaire --> Item Professeur" << endl;
    int i = dialogueDemandeInt("EXPORTER","id du prof à exporter");
    if(i){
        h.exporteHoraireProfesseur(i);
    }
    else{
        dialogueErreur("ERREUR","Veuillez mettre un id valide..");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionExporterGroupe_triggered()
{
    cout << "Clic sur Menu Exporter horaire --> Item Groupe" << endl;
    int i = dialogueDemandeInt("EXPORTER","id du groupe à exporter");
    if(i){
        h.exporteHoraireGroupe(i);
    }
    else{
        dialogueErreur("ERREUR","Veuillez mettre un id valide..");
    }
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionExporterLocal_triggered()
{
    cout << "Clic sur Menu Exporter horaire --> Item Local" << endl;
    int i = dialogueDemandeInt("EXPORTER","id du local à exporter");
    if(i){
        h.exporteHoraireLocal(i);
    }
    else{
        dialogueErreur("ERREUR","Veuillez mettre un id valide..");
    }
}




void ApplicHoraireWindow::ResetProfesseurs(){

    videTableProfesseurs();
    Iterateur<Professeur> it(h.getProfesseurs()); 
    Professeur p;        
    for(it.reset();!it.end();it++){
        p = (Professeur)it; 
        ajouteTupleTableProfesseurs(p.Tuple());
    }
}


void ApplicHoraireWindow::ResetGroupes(){

    videTableGroupes();
    Iterateur<Groupe> it(h.getGroupes()); 
    Groupe g;     
    for(it.reset();!it.end();it++){
        g = (Groupe)it;
        ajouteTupleTableGroupes(g.Tuple());
    }
}


void ApplicHoraireWindow::ResetLocaux(){

    videTableLocaux();
    Iterateur<Local> it(h.getLocaux());
    Local l;    
    for(it.reset();!it.end();it++){
        l = (Local)it;    
        ajouteTupleTableLocaux(l.Tuple());
    }
}


void ApplicHoraireWindow::ResetCourss(){

    videTableCourss();
    Iterateur<Cours> it(h.getCourss());
    Cours c;
    for(it.reset();!it.end();it++){
        c = (Cours)it;
        ajouteTupleTableCourss(h.getTuple(c));
    }

}


void ApplicHoraireWindow::ResetFields(){
    setNomProfesseur("");
    setPrenomProfesseur("");
    videNumeroGroupe();
    setNomLocal("");
    videHeuresDebut();
    videMinutesDebut();
    videDuree();
    setIntitule("");
}