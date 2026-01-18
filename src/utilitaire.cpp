#include <iostream>
#include "utilitaire.h"


const unsigned int anneeActuelle = 2026;

Personne* creerPersonne(string new_nom, string new_prenom, int new_annee, sexType new_sexe,u_int16_t ID){
   Personne * jean = new Personne;

   jean->nom = new_nom;
   jean->prenom = new_prenom;
   jean->annee = new_annee;
   jean->sexe = new_sexe;

   jean->conjoint = nullptr;
   jean->ParentF = nullptr;
   jean->ParentH = nullptr;

   jean->id = ID;

   return jean; 
}




void mariagePersonne(Personne * jean1, Personne *jean2){
    if (isMariagePossible(jean1,jean2))
    {
        jean1->conjoint = jean2;
        jean2->conjoint = jean1;
        cout << "Nous célébrons aujourd'hui l'union entre " 
             << jean1->prenom << jean1->nom << "et"
             << jean2->prenom << jean2->nom << endl;
    }else {
        cout << "Mariage impossible : conditions legales non remplies." << endl;
    }   
}

void afficherPersonne(Personne *jean)
{
    cout << "-----------------------------" << endl;
    if (jean->sexe == homme)
    {
        cout << "Monsieur ";
        cout << jean->nom << " " << jean->prenom <<endl;
        //gestion conjoint
        if (jean->conjoint != nullptr)
            cout << " époux de " << jean->conjoint->prenom << " " << jean->conjoint->nom << endl;
        //gestion parents
        if (jean->ParentH != nullptr)
            cout << "De père : " << jean->ParentH->prenom << " " << jean->ParentH->nom << endl;
        else
            cout << "de père : INCONNU" << endl;

        if (jean->ParentF != nullptr){
            cout << "De mère : " << jean->ParentF->prenom << " " << jean->ParentF->nom ;
            if (jean->ParentH != nullptr)
                cout << " épouse de M." << jean->ParentH->nom << endl;
            else 
                cout << "épouse d'un INCONNU";

        }else
            cout << "De mère : INCONNUE" << endl;

        
    }
    else
    {
        cout << "Madame ";
        cout << jean->nom << " " << jean->prenom;
        //gestion conjoint
        if (jean->conjoint != nullptr)
            cout << " épouse de " << jean->conjoint->prenom << " " << jean->conjoint->nom << endl;
        //gestion parents
        if (jean->ParentH != nullptr)
            cout << "De père : " << jean->ParentH->prenom << " " << jean->ParentH->nom << endl;
        else
            cout << "de père : INCONNU" << endl;

        if (jean->ParentF != nullptr){
            cout << "De mère : " << jean->ParentF->prenom << " " << jean->ParentF->nom ;
            if (jean->ParentH != nullptr)
                cout << " épouse de M." << jean->ParentH->nom << endl;
            else 
                cout << "épouse d'un INCONNU";

        }else
            cout << "De mère : INCONNUE" << endl;

        
    }
    cout << "-----------------------------" << endl;

    


}



//return true si c'est les même personne
bool isMemePersonne(Personne * jean1, Personne *jean2){
    return jean1->nom == jean2->nom && 
           jean1->prenom == jean2->prenom &&
           jean1->annee == jean2->annee &&
           jean1->sexe == jean2->sexe;
} 

//return si c'est les 2 personnes sont frère et soeur
bool isFrereSoeur(Personne * jean1, Personne *jean2){
    //Vérifier si jean1 et jean2 sexiste
    if (jean1 == nullptr || jean2 == nullptr)
    {
        return false;
    }

    Personne * J1PF = jean1->ParentF;
    Personne * J2PF = jean2->ParentF;
    Personne * J1PH = jean1->ParentH;
    Personne * J2PH = jean2->ParentH;

    //Vérifier si ce n'est pas de père inconnus
    if (J1PF == nullptr || J2PF == nullptr || J1PH == nullptr || J2PH ==nullptr )
    {
        return false;
    }

    //Vérifie si ils ont les mêmes parents
    return (isMemePersonne(J1PF,J2PF) && isMemePersonne(J1PH,J2PH));
}

bool Ancetre(Personne * JeanCible, Personne * JeanChercher){
    
    if ((JeanCible->ParentF != nullptr)){
        if (isMemePersonne(JeanCible->ParentF, JeanChercher))  return true;
    } 

    if (JeanCible->ParentF != nullptr){
        if (isMemePersonne(JeanCible->ParentH, JeanChercher)) return true;
    } 

    if ((JeanCible->ParentF == nullptr) && (JeanCible->ParentF == nullptr)) return false;
    
    //condition ? valeur_si_vrai : valeur_si_faux

    else return (JeanCible->ParentF == nullptr ? false : Ancetre(JeanCible->ParentF, JeanChercher)) 
                || (JeanCible->ParentH == nullptr ? false : Ancetre(JeanCible->ParentH, JeanChercher));
    

}


int calculHauteurArbre_rec(Personne * jeanArbre){
    if (jeanArbre == nullptr){   
        //Si l'abre est vide
        return 0;
    } else {
        //Chosie la hauteur max entre le noeud gauche et droit 
        return 1 + max(calculHauteurArbre_rec(jeanArbre->ParentF),calculHauteurArbre_rec(jeanArbre->ParentH));
    }
}

bool isMariagePossible(Personne * jean1, Personne *jean2){
    //Vérifie si les 2 sont majeurs
    if (((anneeActuelle - jean1->annee)<18 || (anneeActuelle - jean2->annee)<18) ){
        return false;
    }
    
    //Vérifie si ils 
    return !Ancetre(jean1,jean2)&&
           !Ancetre(jean2,jean1)&&
           !isFrereSoeur(jean1,jean2);
}



void afficherArbre_rec(Personne * jean1){
    if (jean1 == nullptr){   
        //Si l'abre est vide
        return;
    } else {
        //Affiche la personne
        afficherPersonne(jean1);
        cout << endl;
        afficherArbre_rec(jean1->ParentF);
        afficherArbre_rec(jean1->ParentH);
        
    }
}


void afficherArbreGraphique(Personne * jean, string prefixe, bool estDernier) {
    if (jean == nullptr) return;

    // Affiche le trait de la branche actuelle
    // └── pour le dernier enfant, ├── pour ceux d'avant
    cout << prefixe << (estDernier ? "└── " : "├── ") 
         << jean->prenom << " " << jean->nom << " (" << jean->annee << ")" << endl;

    // On ajuste le préfixe pour les générations suivantes
    // Si c'est le dernier, on met des espaces, sinon on continue le trait vertical "|"
    string nouveauPrefixe = prefixe + (estDernier ? "    " : "│   ");

    // On prépare une liste de parents pour itérer
    // Ici, la mère puis le père
    if (jean->ParentF != nullptr || jean->ParentH != nullptr) {
        
        // On affiche la mère. Est-elle la dernière à afficher ? 
        // Oui, seulement si le père est inconnu.
        bool mereEstDerniere = (jean->ParentH == nullptr);
        
        if (jean->ParentF != nullptr) {
            afficherArbreGraphique(jean->ParentF, nouveauPrefixe, mereEstDerniere);
        } else {
            cout << nouveauPrefixe << (mereEstDerniere ? "└── " : "├── ") << "Mère: INCONNUE" << endl;
        }

        // Le père est toujours le dernier affiché dans notre logique
        if (jean->ParentH != nullptr) {
            afficherArbreGraphique(jean->ParentH, nouveauPrefixe, true);
        } else if (!mereEstDerniere) { // Si la mère n'était pas dernière, on signale le père inconnu
            cout << nouveauPrefixe << "└── " << "Père: INCONNU" << endl;
        }
    }
}