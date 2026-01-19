#pragma once

#include "type_def.h"
#include "fstream"

/// \brief Écrit récursivement un arbre généalogique dans un fichier.
/// \param jean Racine à sérialiser.
/// \param fichier Flux de sortie ouvert.
void ecritureRecursif(Personne * jean, ofstream &fichier);

/// \brief Sérialise l'arbre complet dans un fichier donné.
/// \param jean Racine de l'arbre.
/// \param filname Nom du fichier cible.
void enregistrerArbre(Personne * jean, string filname);

/// \brief Charge un arbre généalogique depuis un fichier.
/// \param filname Nom du fichier source.
Personne* lireArbre(string filname);

/// \brief Génère un identifiant unique pour une personne.
u_int16_t genererID();

 