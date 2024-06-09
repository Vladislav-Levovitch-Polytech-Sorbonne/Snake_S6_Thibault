#ifndef __API_Projet_Info_SERPENT__
#define __API_Projet_Info_SERPENT__

#include "Snake-EI3-2024/clientAPI.h"
#include "Snake-EI3-2024/snakeAPI.h"

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

#include "Projet_info_ARENE.h"

void maj_coordonne(int* x_c, int* y_c, int direction_c);
int eviter_les_obstacles (int direction_e, int x_0_e, int y_0_e, Cellule **arene_e, int Longueur_Arene_e, int Hauteur_Arene_e, Serpant** Tete_Queu_Moi_e, int Profondeur);
void maj_arene_serpant_position (Cellule **arene_p, int Longueur_Arene_p, int Hauteur_Arene_p, int direction_p, int *tour_p, Serpant *Serpant_p, Serpant **Tete_Queu_p);
void avance_ligne_droite (int direction_d, int distance_d, int* taille_serpent_d, int* tour_d, t_return_code* adversaire_d, t_return_code* moi_d, t_move* move_adv_d, Cellule **arene_d, int Longueur_Arene_d, int Hauteur_Arene_d, Serpant* serpent_Moi_d, Serpant** Tete_Queu_Moi_d, Serpant* serpent_adv_d, Serpant** Tete_Queu_adv_d, int Placement_a_DROITE_d);
void liberation_serpent (Serpant *Serpant_l);

#endif