#ifndef __API_Projet_Info_SERPENT__
#define __API_Projet_Info_SERPENT__

#include "Snake-EI3-2024/snakeAPI.h"
#include "Snake-EI3-2024/clientAPI.h"
#include <stdlib.h>

typedef struct _Coordonnee_struct
{
    int x;
    int y;
} Coordonnee;

typedef struct _Serpant_struct
{
    Coordonnee Coordonnee_Portion_Serpant;
    struct _Serpant_struct *Remonter_vers_serpant_tete;
    struct _Serpant_struct *Redescendre_vers_serpant_queu;
} Serpant;

typedef struct _Cellule_struct
{
    int N;
    int S;
    int E;
    int W;
	
    int Occupation;
} Cellule;

#include "Projet_info_SERPENT.h"

void affichage_arene(Cellule **arene_a, int Longueur_Arene_a, int Hauteur_Arene_a);
void arene_preparation(Cellule ***arene_p, int Longueur_Arene_p, int Hauteur_Arene_p);
void verification_cellule(Cellule ***arene_v, int Longueur_Arene_p, int Hauteur_Arene_p);
void verification_muraille(int *Muraille_v, int Stock_Muraille_v);
void arene_muraille(Cellule **arene_m, int *Muraille_m, int Stock_Muraille_m);
void liberation_memoire(Cellule **arene_l, int Hauteur_Arene_l, int *Muraille_l, Serpant *Serpant_Moi_l, Serpant *Serpant_Adv_l, Serpant **Tete_Queu_Moi_l, Serpant **Tete_Queu_Adv_l);

#endif