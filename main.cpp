

#include <iostream>
#include "type_def.h"
#include "utilitaire.h"
#include "utilitaire_fichier.h"

using namespace std;

// prototypes:
void testComplet();

int main()
{
    
    // /*-------------------------------------début setup-------------------------------------*/
    // Personne *adan = creerPersonne("ADAN", "Adan", 2000, homme, genererID());

    // // ===== Parents =====
    // Personne *baptiste = creerPersonne("BAPTISTE", "Baptiste", 1975, homme, genererID());
    // Personne *bella = creerPersonne("BELLA", "Bella", 1978, femme, genererID());

    // adan->ParentH = baptiste;
    // adan->ParentF = bella;


    // // ===== Grands-parents côté père (Baptiste) =====
    // Personne *christian = creerPersonne("CHRISTIAN", "Christian", 1950, homme, genererID());
    // Personne *claire = creerPersonne("CLAIRE", "Claire", 1952, femme, genererID());

    // baptiste->ParentH = christian;
    // baptiste->ParentF = claire;

   
    // // ===== Grands-parents côté mère (Bella) =====
    // Personne *david = creerPersonne("DAVID", "David", 1948, homme, genererID());
    // Personne *diane = creerPersonne("DIANE", "Diane", 1951, femme, genererID());

    // bella->ParentH = david;
    // bella->ParentF = diane;


    // // ===== Deuxième branche: parents des grands-parents =====

    // // Parents de Christian
    // Personne *eric = creerPersonne("ERIC", "Eric", 1925, homme, genererID());
    // Personne *emma = creerPersonne("EMMA", "Emma", 1927, femme, genererID());

    // christian->ParentH = eric;
    // christian->ParentF = emma;


    // // Parents de Claire
    // Personne *felix = creerPersonne("FELIX", "Felix", 1923, homme, genererID());
    // Personne *flora = creerPersonne("FLORA", "Flora", 1926, femme, genererID());

    // claire->ParentH = felix;
    // claire->ParentF = flora;

    

    // // Parents de David
    // Personne *georges = creerPersonne("GEORGES", "Georges", 1920, homme, genererID());
    // Personne *helene = creerPersonne("HELENE", "Helene", 1924, femme, genererID());

    // david->ParentH = georges;
    // david->ParentF = helene;

    

    // // Parents de Diane
    // Personne *henri = creerPersonne("HENRI", "Henri", 1922, homme, genererID());
    // Personne *irene = creerPersonne("IRENE", "Irene", 1925, femme, genererID());

    // diane->ParentH = henri;
    // diane->ParentF = irene;



    // mariagePersonne(baptiste, bella);
    // mariagePersonne(christian, claire);
    // mariagePersonne(david, diane);
    // mariagePersonne(eric, emma);
    // mariagePersonne(felix, flora);
    // mariagePersonne(georges, helene);
    // mariagePersonne(henri, irene);

    // /*-------------------------------------fin setup-------------------------------------*/

    

  
   

    // //testA ffichage graphique :
    // afficherArbreGraphique(adan);

    // //test enregistrement :
    // enregistrerArbre(adan,"arbreEcriure.txt");

    // //Test lecture :
    //afficherArbreGraphique(lireArbre("arbreLecture.txt"));
    // //enregistrerArbre(p,"arbre2.txt");
    // afficherArbreGraphique(adan);

    
    testComplet();

    
}



void testComplet(){
    // Créations d'une famille sur 3 générations
    //Enfants
    Personne* fils = creerPersonne("Dupont", "Lucas", 1980, homme, genererID());
    Personne* fille = creerPersonne("Dupont", "Emma", 1985, femme, genererID());
    //Parents
    Personne* père = creerPersonne("Dupont", "Jean", 1950, homme, genererID());
    Personne* mère = creerPersonne("Petit", "Anne", 1955, femme, genererID());
    mariagePersonne(père, mère);
    //Grand parent
    Personne* g_père1 = creerPersonne("Dupont", "Henri", 1920, homme, genererID());
    Personne* g_mère1 = creerPersonne("Martin", "Marie", 1925, femme, genererID());
    mariagePersonne(g_père1, g_mère1);
    Personne* g_père2 = creerPersonne("Petit", "Henri", 1922, homme, genererID());
    Personne* g_mère2 = creerPersonne("Petit", "Marie", 1927, femme, genererID());
    mariagePersonne(g_père2, g_mère2);


    //On définit les parents de père
    père->ParentH = g_père1;
    père->ParentF = g_mère1;

    //On définit les parents de mère
    père->ParentH = g_père2;
    père->ParentF = g_mère2;

    // On définit les parents des enfants
    fils->ParentH = père; fils->ParentF = mère;
    fille->ParentH = père; fille->ParentF = mère;

    // --- 3. TESTS DES FONCTIONS DE BASE ---
    cout << "=== Test Affichage Personne ===" << endl;
    afficherPersonne(fils);
    cout << endl;

    cout << "=== Test Frère/Soeur ===" << endl;
    if (isFrereSoeur(fils, fille)) cout << "Lucas et Emma sont bien frere et soeur." << endl;
    else cout << "Erreur dans isFrereSoeur" << endl;

    // --- 4. TESTS DE GÉNÉALOGIE (Récursion) ---
    cout << "\n=== Test Ancêtres ===" << endl;
    if (Ancetre(fils, g_père1)) cout << "Henri est bien l'ancetre de Lucas." << endl;
    
    cout << "\n=== Test Hauteur Arbre ===" << endl;
    cout << "Hauteur de l'arbre de Lucas : " << calculHauteurArbre_rec(fils) << " (Attendu: 3)" << endl;

    // --- 5. TESTS DE MARIAGE POSSIBLE ---
    cout << "\n=== Test Mariage Possible ===" << endl;
    cout << "Mariage Lucas + Emma ? " << (isMariagePossible(fils, fille) ? "OUI" : "NON (Consanguinité)") << endl;
    
    Personne* inconnu = creerPersonne("Inconnu", "X", 1980, femme, 99);
    cout << "Mariage Lucas + Inconnu ? " << (isMariagePossible(fils, inconnu) ? "OUI" : "NON") << endl;

    // --- 6. TEST AFFICHAGE GRAPHIQUE ---
    cout << "\n=== Affichage de l'arbre complet (Style Linux) ===" << endl;
    afficherArbreGraphique(fils);

    // --- 7. TEST SAUVEGARDE ET CHARGEMENT ---
    cout << "\n=== Test Sauvegarde ===" << endl;
    enregistrerArbre(fils, "arbreEcriture.txt");
    cout << "Arbre enregistre dans 'arbreEcriture.txt'" << endl;

    cout << "\n=== Test Chargement ===" << endl;
    cout << "Arbre charge avec succes. Apercu :" << endl;
    afficherArbreGraphique(lireArbre("arbreEcriture.txt"));

}