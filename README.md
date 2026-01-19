# Rapport de TP5 - Arbre généalogique

**Nom :** PERRET Noah & L'HINGUERAT Simon 

**Groupe :** SEC28

**Date :** 18 Janvier 2026  

## Compilation et exécution

```bash
# Compilation
make

# Exécution du binaire principal
./main

# Nettoyage
make clean
```

## Préambule : objectifs du projet

L'application construit et manipule un arbre généalogique :
- création de personnes et gestion des mariages
- vérification de liens de parenté (ancêtre, frère/sœur)
- calcul de la hauteur d'arbre
- affichage textuel et graphique (style « tree »)
- sauvegarde / chargement sur disque.

# 1 - Structures de données

### `sexType`
```cpp
enum sexType { homme = 0, femme = 1 };
```

### `Personne`
```cpp
struct Personne {
    string nom;
    string prenom;
    int annee;
    u_int16_t id;
    sexType sexe;
    Personne* conjoint;
    Personne* ParentH;
    Personne* ParentF;
};
```
Utilisée en mémoire pour représenter chaque individu et ses liens (parents/pacsé).

### `PersonneWithID`
```cpp
struct PersonneWithID {
    string nom;
    string prenom;
    int annee;
    u_int16_t id;
    sexType sexe;
    u_int16_t conjointId;
    u_int16_t ParentHId;
    u_int16_t ParentFId;
};
```
Format sérialisable pour la sauvegarde/chargement des arbres (références par identifiants).

# 2 - Utilitaires (personnes)

Fichier : `include/utilitaire.h` — implémentation dans `src/utilitaire.cpp`.

#### Prototypes principaux
```cpp
Personne* creerPersonne(string nom, string prenom, int annee, sexType sexe, u_int16_t id);
void mariagePersonne(Personne* p1, Personne* p2);
void afficherPersonne(Personne* p);
bool isMemePersonne(Personne* p1, Personne* p2);
bool Ancetre(Personne* cible, Personne* chercher);
bool isMariagePossible(Personne* p1, Personne* p2);
int  calculHauteurArbre_rec(Personne* racine);
bool isFrereSoeur(Personne* p1, Personne* p2);
void afficherArbre_rec(Personne* racine);
void afficherArbreGraphique(Personne* racine, std::string indent = "", bool estDernier = true);
```

#### Résumé des rôles
- `creerPersonne` : alloue et initialise une personne avec liens vides.
- `mariagePersonne` : lie deux personnes si l'union est autorisée (majorité, pas d'ancêtre commun direct ni fratrie).
- `afficherPersonne` : affiche civilité, parents et conjoint.
- `isMemePersonne` : comparaison stricte des champs identité.
- `Ancetre` : détecte récursivement si une personne est l'ancêtred'une autre personne.    
- `isMariagePossible` : règle de mariage (majorité, pas de consanguinité directe ni fratrie).
- `calculHauteurArbre_rec` : hauteur maximale de l'arbre (profondeur).
- `isFrereSoeur` : vrai si mêmes deux parents connus.
- `afficherArbre_rec` : parcours et affichage simple.
- `afficherArbreGraphique` : rendu arborescent ASCII façon commande `tree`.

# 3 - Utilitaires (fichiers)

Fichier : `include/utilitaire_fichier.h` — implémentation dans `src/utilitaire_fichier.cpp`.

#### Prototypes principaux
```cpp
void ecritureRecursif(Personne* racine, std::ofstream& fichier);
void enregistrerArbre(Personne* racine, std::string filename);
Personne* lireArbre(std::string filename);
u_int16_t genererID();
```

#### Résumé des rôles
- `ecritureRecursif` : sérialise l'arbre en profondeur dans un flux ouvert.
- `enregistrerArbre` : exporte l'arbre complet vers un fichier texte.
- `lireArbre` : recharge un arbre depuis un fichier sauvegardé (reconstruction des liens).
- `genererID` : fournit un identifiant unique simple pour chaque personne créée.

# 4 - Jeux d'essais / Résultats

L'exécution de `./main` réalise une séquence de tests automatiques :
- création d'un arbre familial d'exemple
- tests d'affichage (personne puis arbre complet)
- vérification frère/sœur et ancêtres
- calcul de hauteur d'arbre
- vérification de la possibilité de mariage
- sauvegarde dans `arbreEcriture.txt` puis rechargement et affichage.

Extrait de sortie attendue :
```
Nous célébrons aujourd'hui l'union entre JeanDupontetAnnePetit
... (tests intermédiaires) ...
Hauteur de l'arbre de Lucas : 3 (Attendu: 3)
=== Affichage de l'arbre complet (Style Linux) ===
└── Lucas Dupont (1980)
    ├── Anne Petit (1955)
    └── Jean Dupont (1950)
        ├── Marie Petit (1927)
        └── Henri Petit (1922)

Arbre enregistre dans 'arbreEcriture.txt'
Arbre charge avec succes. Apercu :
└── Lucas Dupont (1980)
    ├── Anne Petit (1955)
    └── Jean Dupont (1950)
        ├── Marie Petit (1927)
        └── Henri Petit (1922)
```

# 5 - Points clés / limites
- Consanguinité contrôlée uniquement via ancêtres directs et fratrie.
- Les parents inconnus sont laissés à `nullptr` et affichés comme « INCONNU ».
- La génération d'ID est locale au run (pas de persistance d'un compteur externe).
