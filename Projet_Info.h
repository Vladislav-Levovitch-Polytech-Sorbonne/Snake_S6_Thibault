#ifndef __API_Projet_Info__
#define __API_Projet_Info__
#include "snakeAPI.h"
//Test git 
typedef struct _Coordonnee_struct
	{
	    int x;
	    int y;
	} Coordonnee;
	
typedef struct _Serpant_struct //Serpant doublement chainee
	{
	Coordonnee Coordonnee_Portion_Serpant;
	
	struct _Serpant_struct * Remonter_vers_serpant_tete;
	struct _Serpant_struct * Redescendre_vers_serpant_queu;
	
	} Serpant;

typedef struct _Cellule_struct
	{
	    	int N;
		int S;
		int E;
		int W;
		
	    	int Occupation;
	} Cellule;



void arene_preparation (Cellule*** arene_p, int Longueur_Arene_p, int Hauteur_Arene_p)
	{
	*arene_p = (Cellule **)malloc(Hauteur_Arene_p * sizeof(Cellule *)); //Demande d aide pour le cast par Chatgpt (le nb d etoile a mettre et ce qu il fallait mettre dedans) 
	for (int h = 0; h < Hauteur_Arene_p; h++) 
		{
        (*arene_p)[h] = (Cellule *)malloc(Longueur_Arene_p * sizeof(Cellule));
		}
	    if (*arene_p == NULL) {
        printf("test");}
	//Initialisation classique des cellules
	for (int hh = 0; hh < Hauteur_Arene_p; hh++) 
		{
        for (int ll = 0; ll < Longueur_Arene_p; ll++) 
        	{
            (*arene_p)[hh][ll].N = 0;
            (*arene_p)[hh][ll].S = 0;
            (*arene_p)[hh][ll].E = 0;
            (*arene_p)[hh][ll].W = 0;
            (*arene_p)[hh][ll].Occupation = 0;
        	}	
    	}
    //Rajout des bordures	
    for (int i = 0; i < Longueur_Arene_p; i++) 
		{
		(*arene_p)[0][i].N = 1;
		(*arene_p)[Hauteur_Arene_p-1][i].S = 1;
		}
	
	for (int ii = 0; ii < Hauteur_Arene_p; ii++) 
		{
		(*arene_p)[ii][0].W = 1;
		(*arene_p)[ii][Longueur_Arene_p-1].E = 1;
		}
		
	//Rajout des occupations initiales
	
	(*arene_p)[Hauteur_Arene_p/2][2].Occupation=1;
	(*arene_p)[Hauteur_Arene_p/2][Longueur_Arene_p-3].Occupation=1;	
	}
	
void verification_cellule (Cellule ***arene_v, int Longueur_Arene_p, int Hauteur_Arene_p) 
	{
	//Cette fonction sert a verifier le bon fonctionnement des murs (et a terme pourrat etre utile a les afficher)
    for (int h = 0; h < Hauteur_Arene_p; h++) 
    	{
        for (int l = 0; l < Longueur_Arene_p; l++) 
        	{
            printf("Cellule [%d][%d] - N: %d, S: %d, E: %d, W: %d, Occupation: %d\n",
            h, l, (*arene_v)[h][l].N, (*arene_v)[h][l].S, (*arene_v)[h][l].E, (*arene_v)[h][l].W, (*arene_v)[h][l].Occupation);
        	}
    	}
	}
	
void verification_muraille (int *Muraille_v, int Stock_Muraille_v) 
	{
	//Cette fonction sert a verifier le bon fonctionnement du tableau de mur
    for (int m = 0; m<Stock_Muraille_v ;m++)
		{
		printf ("\n %d : ", m+1);
		for (int m4 = 0; m4<4 ;m4++)
			{
			printf ("%d ",Muraille_v[4*m+m4]);
			}
		}
	}

void arene_muraille(Cellule **arene_m, int *Muraille_m, int Stock_Muraille_m) 
	{
    for (int mur = 0; mur < Stock_Muraille_m; mur++) 
    	{
        int x1 = Muraille_m[4 * mur + 0];
        int y1 = Muraille_m[4 * mur + 1];
        int x2 = Muraille_m[4 * mur + 2];
        int y2 = Muraille_m[4 * mur + 3];

        if (y1 == y2) 
        	{
            if (x1 > x2) 
            	{
                arene_m[y1][x1].W = 1;
                arene_m[y2][x2].E = 1;
            	} 
            else 
            	{
                arene_m[y1][x1].E = 1;
                arene_m[y2][x2].W = 1;
            	}
        	} 
        else if (x1 == x2) 
        	{
            if (y1 > y2) 
            	{
                arene_m[y1][x1].N = 1;
                arene_m[y2][x2].S = 1;
            	} 
            else 
            	{
                arene_m[y1][x1].S = 1;
                arene_m[y2][x2].N = 1;
            	}
            }
        }
    }

	
//void avance_ligne_droite (int direction, int distance, int* taille_serpent_d, int* tour_d, t_return_code* adversaire_d, t_return_code* moi_d, t_move* move_adv_d)//Version sans la mise a jour
void avance_ligne_droite (int direction_d, int distance_d, int* taille_serpent_d, int* tour_d, t_return_code* adversaire_d, t_return_code* moi_d, t_move* move_adv_d, Cellule **arene_d, int Longueur_Arene_d, int Hauteur_Arene_d, Serpant* serpent_moi_d, Serpant** Tete_Queu_moi_d, Serpant* serpent_adv_d, Serpant** Tete_Queu_adv_d)
	{
    for (int v = 0; v < distance_d; v++)   //PASS
    	{
        *adversaire_d = getMove(move_adv_d);
        *moi_d = sendMove(direction_d);
	maj_arene_serpant_position(arene_d, Longueur_Arene_d, Hauteur_Arene_d, direction_d, tour_d, serpent_moi_d, Tete_Queu_moi_d);
        maj_arene_serpant_position(arene_d, Longueur_Arene_d, Hauteur_Arene_d, *move_adv_d, tour_d, serpent_adv_d, Tete_Queu_adv_d);
	affichage_arene (arene_d, Longueur_Arene_d, Hauteur_Arene_d);
        //printArena();

        if (((*tour_d) % 10) == 0)
        	{
			(*taille_serpent_d)++;
			}; 
		printf ("coup_moi : %d\t coup_adverse : %d\t mon serpent est de taille : %d\n",*moi_d, *adversaire_d, *taille_serpent_d );	
		printf (" + + + + le coup adverse est %d + + + + ", *move_adv_d); 
		(*tour_d)++; 
		printf (" + - + tours numéro : %d + - + \n", *tour_d);
		}	
	}

void affichage_arene (Cellule **arene_a, int Longueur_Arene_a, int Hauteur_Arene_a)
    {
    int v = 0;
    //Affichage 1er ligne
    printf("\x1b[36m ┏━━");
    for (int h = 0; h < Longueur_Arene_a-2; h++) 
        {
        printf ("\x1b[0m━\x1b[36m━\x1b[0m━");
        }
    printf("━━┓\n \x1b[0m");
    
    for (int h = 0; h < Hauteur_Arene_a; h++) 
        {
        if (h==0){}
		else {
			printf ("\x1b[36m\n ┃  \x1b[0m");	
			for (int l = 1; l < Longueur_Arene_a-1; l++) 
				{
				if (arene_a[h][l].N == 1 && arene_a[h][l].W == 0 && arene_a[h-1][l].W == 0)	
				    {printf("━━━");}
				else if (arene_a[h][l].W == 1 && arene_a[h][l].N == 0 && arene_a[h][l-1].N == 0 && arene_a[h-1][l].W == 1)
				    {printf("\x1b[0m┃  \x1b[0m");}    
				else if (arene_a[h][l].W == 1 && arene_a[h][l].N == 1 && arene_a[h][l-1].N == 1 && arene_a[h-1][l].W == 1)
				    {printf("\x1b[35m╋\x1b[0m━━");}
				
				else if (arene_a[h][l].N == 1 && arene_a[h][l].W == 1 && arene_a[h][l-1].N == 0 && arene_a[h-1][l].W == 0)
				    {printf("\x1b[32m┏\x1b[0m━━");}
				else if (arene_a[h][l].N == 1 && arene_a[h][l].W == 0 && arene_a[h][l-1].N == 0 && arene_a[h-1][l].W == 1)
				    {printf("\x1b[32m┗\x1b[0m━━");}
				else if (arene_a[h][l].N == 0 && arene_a[h][l].W == 1 && arene_a[h][l-1].N == 1 && arene_a[h-1][l].W == 0)
				    {printf("\x1b[32m┓  \x1b[0m");}
				else if (arene_a[h][l].N == 0 && arene_a[h][l].W == 0 && arene_a[h][l-1].N == 1 && arene_a[h-1][l].W == 1)
				    {printf("\x1b[32m┛  \x1b[0m");}
				
				else if (arene_a[h][l].N == 1 && arene_a[h][l].W == 1 && arene_a[h][l-1].N == 0 && arene_a[h-1][l].W == 1)
				    {printf("\x1b[33m┣\x1b[0m━━");}
				else if (arene_a[h][l].N == 1 && arene_a[h][l].W == 0 && arene_a[h][l-1].N == 1 && arene_a[h-1][l].W == 1)
				    {printf("\x1b[33m┻\x1b[0m━━");}
				else if (arene_a[h][l].N == 0 && arene_a[h][l].W == 1 && arene_a[h][l-1].N == 1 && arene_a[h-1][l].W == 1)
				    {printf("\x1b[33m┫  \x1b[0m");}
				else if (arene_a[h][l].N == 1 && arene_a[h][l].W == 1 && arene_a[h][l-1].N == 1 && arene_a[h-1][l].W == 0)
				    {printf("\x1b[33m┳\x1b[0m━━");}
				    			    
				else if (arene_a[h][l].W == 1 && arene_a[h][l].N == 0 && arene_a[h][l-1].N == 0)
				    {printf("\x1b[94m╻  \x1b[0m");}
				else if (arene_a[h-1][l].W == 1 && arene_a[h][l].N == 0 && arene_a[h][l-1].N == 0)
				    {printf("\x1b[34m╹  \x1b[0m");}
				    
				else 
				    {printf("   ");}
				}
				
        //Affichage derniere colonne
        if ( v == 0)
        	{printf("\x1b[36m  ┃\x1b[0m"); v = 1;}
        else
        	{printf("\x1b[0m  ┃\x1b[36m"); v = 0;}
            }
        if (h==0){}
		else {printf ("\n ");}
		
		//Affichage ligne mur horizontaux
        for (int l = 0; l < Longueur_Arene_a-1; l++) 
            {
            if (arene_a[h][l].Occupation == 1 && arene_a[h][l].W == 0)
                {printf(" ■ ");}
            //else if (h==0 && l==0){printf("test");}
            else if (arene_a[h][l].Occupation == 1 && arene_a[h][l].W == 1)
                {printf("┃\x1b[36m■\x1b[0m ");}
                //{printf("┃■ ");}
            else if (arene_a[h][l].Occupation == 0 && arene_a[h][l].W == 1)
                {printf("┃. ");}
            else 
                {printf(" . ");}
            }
        //Affichage derniere colonne    
        if (arene_a[h][Longueur_Arene_a-1].Occupation == 1)
                    {printf("\x1b[36m ■┃\x1b[0m");}
        else 
        	{printf("\x1b[36m .┃\x1b[0m");}  
        }
        
    printf ("\n");
    
    //Affichage derniere ligne
    printf("\x1b[36m ┗━━");
    for (int h = 0; h < Longueur_Arene_a-2; h++) 
        {
        printf ("\x1b[0m━\x1b[36m━\x1b[0m━");
        }
    printf("━━┛\x1b[0m\n\n");
    
    /*
    for (int ll= 0; ll < Longueur_Arene_a; ll++) 
        {
        if (arene_a[Hauteur_Arene_a-1][ll].S == 1 && arene_a[Hauteur_Arene_a-1][ll].E == 0 && arene_a[Hauteur_Arene_a-1][ll].W == 0)
            {printf("━━━");}
        else if (arene_a[Hauteur_Arene_a-1][ll].S == 1 && arene_a[Hauteur_Arene_a-1][ll].E == 1 && arene_a[Hauteur_Arene_a-1][ll].W == 0)
            {printf("━━┛ ");}
        else if (arene_a[Hauteur_Arene_a-1][ll].S == 1 && arene_a[Hauteur_Arene_a-1][ll].E == 0 && arene_a[Hauteur_Arene_a-1][ll].W == 1)
            {printf(" ┗━━");}
        else if (arene_a[Hauteur_Arene_a-1][ll].S == 1 && arene_a[Hauteur_Arene_a-1][ll].E == 1 && arene_a[Hauteur_Arene_a-1][ll].W == 1)
            {printf("┗━┛");} //Doute ici
        else 
            {printf("   ");} //Doute ici
        }
    */    
    }

void maj_arene_serpant_position (Cellule **arene_p, int Longueur_Arene_p, int Hauteur_Arene_p, int direction_p, int* tour_p, Serpant* Serpant_p,Serpant **Tete_Queu_p) //On pourrat ajouter le serpant de qui est ce pour ensuite faire la maj pour les couleurs et triangle.
    {
    //Maj des coordonnes
    int x_new = ((*Tete_Queu_p[0]).Coordonnee_Portion_Serpant.x);
    int y_new = ((*Tete_Queu_p[0]).Coordonnee_Portion_Serpant.y);
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
        arene_p[y_new][x_new].Occupation = 1;
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
        arene_p[y_new][x_new].Occupation = 1;
        }
    }
#endif


/*

Les Papas des Elec Thibault HILAIRE Yann DOUZE Benoit FABRE Annick ALEXANDRE IFitep Michel REDON 
Ei Eise Eili Eist 
Les ST etait premier avec EI 
Ifitep avant Polytech
 
*/
