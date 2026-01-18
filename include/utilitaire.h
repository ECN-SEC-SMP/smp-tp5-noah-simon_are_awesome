#pragma once
#include <iostream>
#include "type_def.h"

/// \brief Crée une nouvelle personne avec identifiant et liens vides.
/// \param new_nom Nom de famille.
/// \param new_prenom Prénom.
/// \param new_annee Année de naissance.
/// \param new_sexe Sexe de la personne.
/// \param ID Identifiant unique.
Personne* creerPersonne(string new_nom, string new_prenom, int new_annee, sexType new_sexe,u_int16_t ID);

/// \brief Maries deux personnes si les conditions sont remplies.
/// \param jean1 Première personne.
/// \param jean2 Seconde personne.
void mariagePersonne(Personne * jean1, Personne *jean2);

/// \brief Affiche les informations détaillées d'une personne.
/// \param jean Personne à afficher.
void afficherPersonne(Personne * jean);

/// \brief Vérifie si deux personnes représentent le même individu.
/// \param jean1 Première personne.
/// \param jean2 Seconde personne.
bool isMemePersonne(Personne * jean1, Personne *jean2);

/// \brief Détermine si une personne est ancêtre d'une autre.
/// \param JeanCible Personne dont on explore les ancêtres.
/// \param JeanChercher Personne recherchée comme ancêtre.
bool Ancetre(Personne * JeanCible, Personne * JeanChercher);

/// \brief Teste si un mariage entre deux personnes est autorisé.
/// \param jean1 Première personne.
/// \param jean2 Seconde personne.
bool isMariagePossible(Personne * jean1, Personne *jean2);

/// \brief Calcule récursivement la hauteur de l'arbre familial.
/// \param jeanArbre Racine de l'arbre.
int calculHauteurArbre_rec(Personne * jeanArbre);

/// \brief Indique si deux personnes sont frère et sœur.
/// \param jean1 Première personne.
/// \param jean2 Seconde personne.
bool isFrereSoeur(Personne * jean1, Personne *jean2);

/// \brief Affiche récursivement un arbre familial simple.
/// \param jean1 Racine à afficher.
void afficherArbre_rec(Personne * jean1);

// Le = "" et = true permettent d'appeler la fonction sans préciser ces paramètres
/// \brief Affiche l'arbre familial sous forme graphique.
/// \param jean Racine à afficher.
/// \param indent Préfixe visuel cumulatif.
/// \param estDernier Indique si le nœud est le dernier enfant.
void afficherArbreGraphique(Personne * jean, std::string indent = "", bool estDernier = true);