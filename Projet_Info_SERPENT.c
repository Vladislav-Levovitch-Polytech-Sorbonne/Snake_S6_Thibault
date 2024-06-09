#include "Projet_Info_ARENE.h"
#include "Projet_Info_SERPENT.h"

void maj_arene_serpant_position(Cellule **arene_p, int Longueur_Arene_p, int Hauteur_Arene_p, int direction_p, int* tour_p, Serpant* Serpant_p, Serpant **Tete_Queu_p);

int eviter_les_obstacles (Cellule **arene_e, int direction_e, Serpant** Tete_Queu_Moi_e)
    {
        int x_0 = ((*Tete_Queu_Moi_e[0]).Coordonnee_Portion_Serpant.x);
        int y_0 = ((*Tete_Queu_Moi_e[0]).Coordonnee_Portion_Serpant.y);

        Cellule current_cell = arene_e [y_0][x_0];
        int cycle[4] = {current_cell.N, current_cell.E, current_cell.S, current_cell.W}; //Tableau repertoriant les informations dans l'ordre
        
        int direction_anti_cyclique = direction_e;
        for (int t_4 = 0; t_4 <4; t_4++)
            {
                int y_1 = y_0;
                int x_1 = x_0;

                if (direction_anti_cyclique == 0) {y_1 = y_0 - 1;} // Haut
                else if (direction_anti_cyclique == 2) {y_1 = y_0 + 1;} //Bas
                else if (direction_anti_cyclique == 3) {x_1 = x_0 - 1;} //Gauche
                else if (direction_anti_cyclique == 1) {x_1 = x_0 + 1;} //Droite

                if (cycle[direction_anti_cyclique] == 0 && arene_e[y_1][x_1].Occupation == 0) //Si la case est accesible ET qu il n y a pas d occupation
                    {return direction_anti_cyclique;}
                direction_anti_cyclique +=1;
                if (direction_anti_cyclique == 4) {direction_anti_cyclique = 0;}
            }
        return direction_anti_cyclique;
    }

void avance_ligne_droite (int direction_d, int distance_d, int* taille_serpent_d, int* tour_d, t_return_code* adversaire_d, t_return_code* moi_d, t_move* move_adv_d, Cellule **arene_d, int Longueur_Arene_d, int Hauteur_Arene_d, Serpant* serpent_moi_d, Serpant** Tete_Queu_moi_d, Serpant* serpent_adv_d, Serpant** Tete_Queu_adv_d, int Placement_a_DROITE_d)
{
    for (int v = 0; v < distance_d; v++)   //PASS
    {
        int direction_prioritaire = eviter_les_obstacles (arene_d, direction_d, Tete_Queu_moi_d);
        if (*adversaire_d != 0 || *moi_d != 0 ) {return;} //Protection supplementaire
            if (Placement_a_DROITE_d == 1)
                {*adversaire_d = getMove(move_adv_d);}
            else if (Placement_a_DROITE_d == 0)
                {*moi_d = sendMove(direction_prioritaire);}
        if (*adversaire_d != 0 || *moi_d != 0 ) {return;}
            if (Placement_a_DROITE_d == 0)
                {*adversaire_d = getMove(move_adv_d);}
            else if (Placement_a_DROITE_d == 1)
                {*moi_d = sendMove(direction_prioritaire);}
        if (*adversaire_d != 0 || *moi_d != 0 ) {return;}
	    maj_arene_serpant_position(arene_d, Longueur_Arene_d, Hauteur_Arene_d, direction_prioritaire, tour_d, serpent_moi_d, Tete_Queu_moi_d);
        maj_arene_serpant_position(arene_d, Longueur_Arene_d, Hauteur_Arene_d, *move_adv_d, tour_d, serpent_adv_d, Tete_Queu_adv_d);
	    affichage_arene (arene_d, Longueur_Arene_d, Hauteur_Arene_d);
        //printArena();

        if (((*tour_d) % 10) == 0)
        {
			(*taille_serpent_d)++;
		}; 
		printf ("coup_moi : %d\t coup_adverse : %d\t mon serpent est de taille : %d\n",*moi_d, *adversaire_d, *taille_serpent_d );	
		printf (" + + + + le coup adverse est %d + + + + ", *move_adv_d); 
		printf (" + - + tours numéro : %d + - + \n", *tour_d);
        (*tour_d)++;
    direction_prioritaire = direction_d; //On remet en priorite la distance de parcourt en longueur de l arene
	}	
}

void maj_arene_serpant_position (Cellule **arene_p, int Longueur_Arene_p, int Hauteur_Arene_p, int direction_p, int* tour_p, Serpant* Serpant_p,Serpant **Tete_Queu_p) //On pourrat ajouter le serpant de qui est ce pour ensuite faire la maj pour les couleurs et triangle.
{
    //Maj des coordonnes
    int x_new = ((*Tete_Queu_p[0]).Coordonnee_Portion_Serpant.x);
    int y_new = ((*Tete_Queu_p[0]).Coordonnee_Portion_Serpant.y);

    int y_old = y_new;
    int x_old = x_new;
    arene_p [y_old][x_old].Occupation -= (arene_p [y_old][x_old].Occupation)%10;

    if (direction_p == 0) // Haut
    {
        y_new -= 1;
    }
        
    else if (direction_p == 2) // Bas
    {
        y_new += 1;
    }
    
    else if (direction_p == 3) // Gauche
    {
        x_new -= 1;
	}
    
    else if (direction_p == 1) // Droite
    {
        x_new += 1;
	}
    
    if (x_new<0 || y_new<0 || x_new>=Longueur_Arene_p || y_new>=Hauteur_Arene_p ) 
	{
	printf("Out of rang mais bon ... les coups interdits sont interdits : )\n");
	return; //Par securite
	}
    
    //Maj serpant et arene
    if (((*tour_p-1)%10)==0) //Decalage du a l incrementation de tour avant la maj de serpant 
    {
        //Partie creation nouvelle_tete_serpant
        Serpant * Nouvelle_tete_Serpant = (Serpant *) malloc (1*sizeof(Serpant));
        (* Nouvelle_tete_Serpant).Remonter_vers_serpant_tete = Tete_Queu_p[1];
        (* Nouvelle_tete_Serpant).Redescendre_vers_serpant_queu = Tete_Queu_p[0];
        (* Nouvelle_tete_Serpant).Coordonnee_Portion_Serpant.x = x_new;
        (* Nouvelle_tete_Serpant).Coordonnee_Portion_Serpant.y = y_new;

        //Partie insertion de la nouvelle tete
        (*Tete_Queu_p[0]).Remonter_vers_serpant_tete = Nouvelle_tete_Serpant;		//Ancienne tete relie la nouvelle
        (*Tete_Queu_p[1]).Redescendre_vers_serpant_queu = Nouvelle_tete_Serpant;	//La queu change son raccordement

        //Partie Mise a jour de la sauvegarde tete_queu
        Tete_Queu_p[0] = Nouvelle_tete_Serpant;
        
        //Partie Mise a jour arene
        arene_p[y_new][x_new].Occupation = arene_p [y_old][x_old].Occupation+1+direction_p;
    }

    else 
    {
        //Partie Mise a jour de la sauvegarde tete_queu
        arene_p[(*(Tete_Queu_p[1])).Coordonnee_Portion_Serpant.y][(*(Tete_Queu_p[1])).Coordonnee_Portion_Serpant.x].Occupation = 0; //Liberation de la case
        (*(Tete_Queu_p[1])).Coordonnee_Portion_Serpant.y = y_new;
        (*(Tete_Queu_p[1])).Coordonnee_Portion_Serpant.x = x_new;
        
        Tete_Queu_p[0] = (*(Tete_Queu_p[0])).Remonter_vers_serpant_tete;
        Tete_Queu_p[1] = (*(Tete_Queu_p[1])).Remonter_vers_serpant_tete;
        
        //Partie Mise a jour arene
        arene_p[y_new][x_new].Occupation = arene_p [y_old][x_old].Occupation+1+direction_p;
    }
}

void liberation_serpent(Serpant* Serpant_l) 
{
    if (Serpant_l == NULL) 
        {return;}

    Serpant* current = Serpant_l;
    Serpant* Portion_suivante;

    do //On libere au moins un element qui est la tete
    {
        Portion_suivante = (*current).Redescendre_vers_serpant_queu;
        free(current);
        current = Portion_suivante;
    } while (current != Serpant_l);
}

/*

Les Papas des Elec Thibault HILAIRE Yann DOUZE Benoit FABRE Annick ALEXANDRE IFitep Michel REDON 
Ei Eise Eili Eist 
Les ST etait premier avec EI 
Ifitep avant Polytech
 
*/
