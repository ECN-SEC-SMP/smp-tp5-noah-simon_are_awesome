#pragma once
#include <iostream>
using namespace std;


enum sexType{
    homme = 0,
    femme = 1,
};

struct Personne
{
    string nom;
    string prenom;
    int annee;
    u_int16_t id;
    sexType sexe; 
    Personne * conjoint;
    Personne* ParentH;
    Personne* ParentF;
};


struct PersonneWithID
{
    string nom;
    string prenom;
    int annee;
    u_int16_t id;
    sexType sexe; 
    u_int16_t conjointId;
    u_int16_t ParentHId;
    u_int16_t ParentFId;
};

