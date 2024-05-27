//#include <stdio.h> //Deja inclu dans le ClientAPI.h <- SnakeAPI.h <- Projet_Info.h
#include "Projet_Info.h"

void arene_preparation (Cellule*** arene_p, int Longueur_Arene_p, int Hauteur_Arene_p);
void verification_cellule (Cellule ***arene, int Longueur_Arene_f, int Hauteur_Arene_f);
void arene_muraille (Cellule **arene_m, int *Muraille_m, int Stock_Muraille_m);
//void arene_muraille (Cellule ***arene_m,int ** Muraille_m, int Stock_Muraille_m);
void verification_muraille (int * Muraille_v, int Stock_Muraille_v);
void avance_ligne_droite (int direction, int distance, int* taille_serpent_d, int* tour_d, t_return_code* adversaire_d, t_return_code* moi_d,t_move* move_adv_d);
void affichage_arene (Cellule **arene_a, int Longueur_Arene_a, int Hauteur_Arene_a);
void maj_arene_serpant_position (Cellule **arene_p, int Longueur_Arene_p, int Hauteur_Arene_p, int direction_p, int* tour_p, Serpant* Serpant_p,Serpant **Tete_Queu_p);

int main (void)
	{
	printf("\nTest Main Debut fonctionnel\n");
	
	//Initialisation des variables + + + + + - - - - - + + + + + - - - - - + + + + + 
	int Longueur_Arene = 0; //sizeX
	int Hauteur_Arene = 0; //sizeY
	int Stock_Muraille = 0; //nbWalls

	Cellule ** arene = NULL;

	char gameName;
	int start = 1; //Pour transmettre l information si l on est a Droite ou non
	int taille_serpent = 2;
	
	t_return_code adversaire; 
	t_return_code moi;
	t_move move_adv;
	int tour = 0;
	
	
	/*Ressource pour comprendre liste doublement chainee utilise ici pour representer les serpants 

	Schema d une double liste - Pour notre cas assez similaire


	Rappel pour double liste
	https://forums.commentcamarche.net/forum/affich-37604399-liste-doublement-chainee


	*/
	
	int it = 0;
	printf("\nTest Main Milieu %d fonctionnel\n", it);
	it ++;
	
	connectToServer("localhost", 1234,"Vlad");
	waitForSnakeGame(	"TRAINING SUPER_PLAYER difficulty=3 timeout=10 seed=2002 start=1",
	 			&gameName, &Longueur_Arene, &Hauteur_Arene, &Stock_Muraille);

	//Creation Serpant
	Serpant * Serpant_Moi = (Serpant *) malloc (1*sizeof(Serpant));
        Serpant * Serpant_Adv = (Serpant *) malloc (1*sizeof(Serpant));
        
        (*Serpant_Moi).Coordonnee_Portion_Serpant.x = Longueur_Arene-3;
        (*Serpant_Moi).Coordonnee_Portion_Serpant.y = Hauteur_Arene/2;
        (*Serpant_Moi).Remonter_vers_serpant_tete = Serpant_Moi;
        (*Serpant_Moi).Redescendre_vers_serpant_queu = Serpant_Moi;
        
        (*Serpant_Adv).Coordonnee_Portion_Serpant.x = 2;
        (*Serpant_Adv).Coordonnee_Portion_Serpant.y = Hauteur_Arene/2;
        (*Serpant_Adv).Remonter_vers_serpant_tete = Serpant_Adv;
        (*Serpant_Adv).Redescendre_vers_serpant_queu = Serpant_Adv;
        
        Serpant **Tete_Queu_Moi = (Serpant **) malloc(2 * sizeof(Serpant*));
        Serpant **Tete_Queu_Adv = (Serpant **) malloc(2 * sizeof(Serpant*));
        
        Tete_Queu_Moi[0] = (Serpant *) malloc (1*sizeof(Serpant));
        Tete_Queu_Moi[1] = (Serpant *) malloc (1*sizeof(Serpant));
        Tete_Queu_Adv[0] = (Serpant *) malloc (1*sizeof(Serpant));
        Tete_Queu_Adv[1] = (Serpant *) malloc (1*sizeof(Serpant));
        
        *((Tete_Queu_Moi)[0]) = *Serpant_Moi; *((Tete_Queu_Moi)[1]) = *Serpant_Moi;
        *((Tete_Queu_Adv)[0]) = *Serpant_Adv; *((Tete_Queu_Adv)[1]) = *Serpant_Adv;
        
        printf ("y = %d\n", (*Tete_Queu_Adv[1]).Coordonnee_Portion_Serpant.y);
        printf ("x = %d\n", (*((*Tete_Queu_Moi[1]).Remonter_vers_serpant_tete)).Coordonnee_Portion_Serpant.x);
	
	//Muraille
	printf("L = %d H = %d nr_mur = %d %s \n", Longueur_Arene, Hauteur_Arene, Stock_Muraille, &gameName);
	int * Muraille = (int*) malloc(Stock_Muraille* 4 * sizeof(int));
	getSnakeArena(Muraille);
	verification_muraille (Muraille, Stock_Muraille);
	printf("\nTest Main Milieu %d fonctionnel\n", it);it ++;
	
	//Arene
	arene_preparation (&arene, Longueur_Arene, Hauteur_Arene);
	printf("\n\nTest Main Milieu fonctionnel %d   %d   %d\n\n", arene[0][0].N, arene[3][6].W, arene[Hauteur_Arene-1][4].S );
	//verification_cellule (&arene, Longueur_Arene, Hauteur_Arene);
	//arene[1][0].Occupation = 1; arene[0][0].Occupation = 1; //Sert a tester l affichage des occupations
	affichage_arene (arene, Longueur_Arene, Hauteur_Arene);
	
	arene_muraille(arene, Muraille, Stock_Muraille);
	printf("\n\n\n + + + + + Muraillage + + + + +\n\n\n");
	
	//verification_cellule (&arene, Longueur_Arene, Hauteur_Arene);
	affichage_arene (arene, Longueur_Arene, Hauteur_Arene);
	
	printf("\nTest Main Milieu %d fonctionnel\n", it);
	it ++;
	
	printArena();
	printf("\nTest Main Milieu %d fonctionnel\n", it);
	it ++;
	printf ("Mon serpent est de taille : %d\n", taille_serpent );
	printf (" + - + tours numéro : %d + - + \n", tour); tour++;
	
	//1er Coup manuel pour tester et apprehender la gestion du jeu
	adversaire = getMove( &move_adv );
	moi = sendMove(0);
	maj_arene_serpant_position (arene, Longueur_Arene, Hauteur_Arene, 0       , &tour, Serpant_Moi, Tete_Queu_Moi);
	maj_arene_serpant_position (arene, Longueur_Arene, Hauteur_Arene, move_adv, &tour, Serpant_Adv, Tete_Queu_Adv);
	affichage_arene (arene, Longueur_Arene, Hauteur_Arene);
	printArena();
	printf (" + - + tours numéro : %d + - + \n", tour); tour++;
	printf ("coup_moi : %d\t coup_adverse : %d\t mon serpent est de taille : %d\n",moi, adversaire, taille_serpent );
	
	//2eme Coup manuel pour tester et apprehender la gestion du jeu
	adversaire = getMove( &move_adv );
	moi = sendMove(3);
	maj_arene_serpant_position (arene, Longueur_Arene, Hauteur_Arene, 3       , &tour, Serpant_Moi, Tete_Queu_Moi);
	maj_arene_serpant_position (arene, Longueur_Arene, Hauteur_Arene, move_adv, &tour, Serpant_Adv, Tete_Queu_Adv);
	affichage_arene (arene, Longueur_Arene, Hauteur_Arene);
	printArena();
	printf ("coup_moi : %d\t coup_adverse : %d\t mon serpent est de taille : %d\n",moi, adversaire, taille_serpent );
	printf (" + - + tours numéro : %d + - + \n", tour);tour++;
	
	int tour_manuel_cylage_petit = 2;
	for ( int iii = 0; iii<6; iii++)
		{
		for ( int ii = 0; ii<4; ii++)
			{
			for ( int i = 0; i<2; i++)
				{
				avance_ligne_droite(tour_manuel_cylage_petit, 1, &taille_serpent, &tour, &adversaire, &moi, &move_adv);
				maj_arene_serpant_position (arene, Longueur_Arene, Hauteur_Arene, tour_manuel_cylage_petit, &tour, Serpant_Moi, Tete_Queu_Moi);
				maj_arene_serpant_position (arene, Longueur_Arene, Hauteur_Arene, move_adv, &tour, Serpant_Adv, Tete_Queu_Adv);
				affichage_arene (arene, Longueur_Arene, Hauteur_Arene);
				void printArena();
				printf ("Cycle %d - %d - %d\n",iii, ii, i);
				}
			tour_manuel_cylage_petit--;
			if (tour_manuel_cylage_petit<0) {tour_manuel_cylage_petit=3;} 
			}
		}

	avance_ligne_droite(2, (2), &taille_serpent, &tour, &adversaire, &moi, &move_adv);
	avance_ligne_droite(1, (3), &taille_serpent, &tour, &adversaire, &moi, &move_adv);
	avance_ligne_droite(0, (Hauteur_Arene/2)+1, &taille_serpent, &tour, &adversaire, &moi, &move_adv);
	
while (1) 
	{
	avance_ligne_droite(3, (Longueur_Arene- 1), &taille_serpent, &tour, &adversaire, &moi, &move_adv);
	avance_ligne_droite(2, (Hauteur_Arene - 1), &taille_serpent, &tour, &adversaire, &moi, &move_adv);
	avance_ligne_droite(1, (Longueur_Arene- 1), &taille_serpent, &tour, &adversaire, &moi, &move_adv);
	avance_ligne_droite(0, (Hauteur_Arene - 1), &taille_serpent, &tour, &adversaire, &moi, &move_adv);
	}
	closeConnection();

	printf("\nTest Main Fin fonctionnel\n");

	return 0; //Attention,  si l on return 1 c'est un signe d erreur le compilateur le signifiera
	}