#include  <fstream>
#include <vector>
#include <sstream>
#include "utilitaire.h"
#include "type_def.h"


u_int16_t genererID(){
    static int lastID = 0; //Retiens le dernier ID générer
    lastID ++;
    return lastID-1;
}


void ecritureRecursif(Personne * jean, ofstream &fichier){
    if (jean == nullptr)
    {
        return;
    }

    // Récupérer les IDs ou mettre -1 si le pointeur est nul
    int idC = (jean->conjoint) ? jean->conjoint->id : 65535;
    int idPH = (jean->ParentH) ? jean->ParentH->id : 65535;
    int idPF = (jean->ParentF) ? jean->ParentF->id : 65535;

    fichier << jean->id << ";"
            << jean->nom << ";"
            << jean->prenom << ";" 
            << jean->annee << ";"
            << (int)jean->sexe << ";" 
            << idC << ";" << idPH << ";" << idPF << endl;


    ecritureRecursif(jean->ParentF,fichier);
    ecritureRecursif(jean->ParentH,fichier);
}

void enregistrerArbre(Personne * jean, string filname){

    ofstream fichier(filname);
    if (fichier.is_open()){
        ecritureRecursif(jean, fichier);
        fichier.close();
    }

}


Personne* lireArbre(string filname) {
    ifstream fichier(filname);
    string ligne;
    if (!fichier.is_open()) return nullptr;

    // 1. Ton "repertoire" de données temporaires lues du fichier
    vector<PersonneWithID*> repertoire;

    while (getline(fichier, ligne)) {
        stringstream ss(ligne);
        string cellule;
        int id, annee, sexe, idC, idPH, idPF;
        string nom, prenom;
    
        getline(ss, cellule, ';'); id = stoi(cellule);
        getline(ss, nom, ';');
        getline(ss, prenom, ';');
        getline(ss, cellule, ';'); annee = stoi(cellule);
        getline(ss, cellule, ';'); sexe = stoi(cellule);
        getline(ss, cellule, ';'); idC = stoi(cellule);
        getline(ss, cellule, ';'); idPH = stoi(cellule);
        getline(ss, cellule, ';'); idPF = stoi(cellule);

        if (repertoire.size() <= id) { // Correction: <= pour inclure l'index id
            repertoire.resize(id + 1, nullptr);
        }

        PersonneWithID* p = new PersonneWithID;
        p->id = id;
        p->nom = nom;
        p->prenom = prenom;
        p->annee = annee;
        p->sexe = (sexType)sexe;//Conversion de type
        p->conjointId = idC;
        p->ParentFId = idPF;
        p->ParentHId = idPH;
        repertoire[id] = p;
    }

    // 2. Création du tableau final de "vraies" Personnes
    // On crée d'abord tous les objets pour qu'ils existent en mémoire
    vector<Personne*> vraiArbre(repertoire.size(), nullptr);
    for (int i = 0; i < repertoire.size(); i++) {
        if (repertoire[i] != nullptr) {
            vraiArbre[i] = creerPersonne(repertoire[i]->nom, repertoire[i]->prenom, 
                                         repertoire[i]->annee, repertoire[i]->sexe,repertoire[i]->id);
        }
    }

    // Raccordement des pointeurs 
    for (int i = 0; i < repertoire.size(); i++) {
        if (repertoire[i] != nullptr) {
            //SI il a un père sinon on met son id 
            if (repertoire[i]->ParentHId != 65535) 
                vraiArbre[i]->ParentH = vraiArbre[repertoire[i]->ParentHId];
            
            //SI il a une mère on met son id 
            if (repertoire[i]->ParentFId != 65535) 
                vraiArbre[i]->ParentF = vraiArbre[repertoire[i]->ParentFId];

            //SI il a un conjoint on met son id 
            if (repertoire[i]->conjointId != 65535) 
                vraiArbre[i]->conjoint = vraiArbre[repertoire[i]->conjointId];
        }
    }

    //Nettoyage de la structure temporaire (PersonneWithID)
    for (auto p : repertoire) delete p;
    fichier.close();

    // 5. Retourner la racine (Adan, ID 0)
    return vraiArbre[0]; 
}