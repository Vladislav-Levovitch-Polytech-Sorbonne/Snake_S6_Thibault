#include "Projet_info_ARENE.h"
#include "Projet_info_SERPENT.h"
#include <stdio.h>
#include <stdlib.h>

//Prototypes des fonctions
void arene_preparation (Cellule*** arene_p, int Longueur_Arene_p, int Hauteur_Arene_p);
void verification_cellule (Cellule ***arene, int Longueur_Arene_f, int Hauteur_Arene_f);
void arene_muraille (Cellule **arene_m, int *Muraille_m, int Stock_Muraille_m);
void verification_muraille (int * Muraille_v, int Stock_Muraille_v);
void maj_coordonne(int* x_c, int* y_c, int direction_c);
int  eviter_les_obstacles (int direction_e, Cellule **arene_e, int Longueur_Arene_e, int Hauteur_Arene_e, Serpant** Tete_Queu_Moi_e, int Profondeur);
void avance_ligne_droite (int direction_d, int distance_d, int* taille_serpent_d, int* tour_d, t_return_code* adversaire_d, t_return_code* moi_d, t_move* move_adv_d, Cellule **arene_d, int Longueur_Arene_d, int Hauteur_Arene_d, Serpant* serpent_Moi_d, Serpant** Tete_Queu_Moi_d, Serpant* serpent_adv_d, Serpant** Tete_Queu_adv_d, int Placement_a_DROITE_d);
void affichage_arene (Cellule **arene_a, int Longueur_Arene_a, int Hauteur_Arene_a);
void maj_arene_serpant_position (Cellule **arene_p, int Longueur_Arene_p, int Hauteur_Arene_p, int direction_p, int* tour_p, Serpant* Serpant_p, Serpant **Tete_Queu_p);
void liberation_serpent(Serpant* Serpant_l);
void liberation_memoire(Cellule **arene_l, int Hauteur_Arene_l, int *Muraille_l, Serpant *Serpant_Moi_l, Serpant *Serpant_Adv_l, Serpant **Tete_Queu_Moi_l, Serpant **Tete_Queu_Adv_l);


int main (void)
	{
	printf("\nTest Main Debut fonctionnel\n");
	
	//Initialisation des variables + + + + + - - - - - + + + + + - - - - - + + + + + 
	int Longueur_Arene = 0; //sizeX
	int Hauteur_Arene = 0; //sizeY
	int Stock_Muraille = 0; //nbWalls

	Cellule ** arene = NULL;

	char gameName;
	int taille_serpent = 2;
	
	t_return_code adversaire = 0; 
	t_return_code moi = 0;
	t_move move_adv;
	int tour = 0;
	
	/*Ressource pour comprendre liste doublement chainee utilise ici pour representer les serpants 

	Schema d une double liste - Pour notre cas assez similaire a la difference que la queue et la tete se reboucle
	https://chgi.developpez.com/dblist/liste.gif

	Rappel pour double liste
	https://forums.commentcamarche.net/forum/affich-37604399-liste-doublement-chainee
	*/
	
	int it = 0;
	printf("\nTest Main Milieu %d fonctionnel\n", it);
	it ++;

//PARTIE INITIALISATION DE L ENVIRONNEMENT DE JEU
	connectToServer("localhost", 1234,"Vlad");
	waitForSnakeGame(	"TRAINING SUPER_PLAYER difficulty=2 timeout=10 seed=2000 start=1",
	 					&gameName, &Longueur_Arene, &Hauteur_Arene, &Stock_Muraille);

	//Muraille
		printf("L = %d H = %d nr_mur = %d %s \n", Longueur_Arene, Hauteur_Arene, Stock_Muraille, &gameName);
		int * Muraille = (int*) malloc(Stock_Muraille* 4 * sizeof(int));
		int Placement_a_DROITE = getSnakeArena(Muraille); //Merci Aymen Ahmed FILALI DARAI : explication getSnakeArena
		printf("\nLe serpent joue commence a droite : %d\n",Placement_a_DROITE);

	//Creation Serpant
		Serpant * Serpant_Moi = (Serpant *) malloc (1*sizeof(Serpant));
        Serpant * Serpant_Adv = (Serpant *) malloc (1*sizeof(Serpant));
        
		if ( Placement_a_DROITE == 1 )
        {
			(*Serpant_Moi).Coordonnee_Portion_Serpant.x = Longueur_Arene-3;
			(*Serpant_Adv).Coordonnee_Portion_Serpant.x = 2;
		}
		else if ( Placement_a_DROITE == 0 )
        {
			(*Serpant_Moi).Coordonnee_Portion_Serpant.x = 2;
			(*Serpant_Adv).Coordonnee_Portion_Serpant.x = Longueur_Arene-3;
		}
        (*Serpant_Moi).Coordonnee_Portion_Serpant.y = Hauteur_Arene/2;
        (*Serpant_Moi).Remonter_vers_serpant_tete = Serpant_Moi;
        (*Serpant_Moi).Redescendre_vers_serpant_queu = Serpant_Moi;
        
        (*Serpant_Adv).Coordonnee_Portion_Serpant.y = Hauteur_Arene/2;
        (*Serpant_Adv).Remonter_vers_serpant_tete = Serpant_Adv;
        (*Serpant_Adv).Redescendre_vers_serpant_queu = Serpant_Adv;
        
        Serpant **Tete_Queu_Moi = (Serpant **) malloc(2 * sizeof(Serpant*));
        Serpant **Tete_Queu_Adv = (Serpant **) malloc(2 * sizeof(Serpant*));
        
        Tete_Queu_Moi[0] = (Serpant *) malloc (1*sizeof(Serpant));
        Tete_Queu_Moi[1] = (Serpant *) malloc (1*sizeof(Serpant));
        Tete_Queu_Adv[0] = (Serpant *) malloc (1*sizeof(Serpant));
        Tete_Queu_Adv[1] = (Serpant *) malloc (1*sizeof(Serpant));
        
        Tete_Queu_Moi[0] = Serpant_Moi; Tete_Queu_Moi[1] = Serpant_Moi;
        Tete_Queu_Adv[0] = Serpant_Adv; Tete_Queu_Adv[1] = Serpant_Adv;
        
        printf ("y = %d\n", (*Tete_Queu_Adv[1]).Coordonnee_Portion_Serpant.y);
        printf ("x = %d\n", (*((*Tete_Queu_Moi[1]).Remonter_vers_serpant_tete)).Coordonnee_Portion_Serpant.x);

	verification_muraille (Muraille, Stock_Muraille);
	printf("\nTest Main Milieu %d fonctionnel\n", it);it ++;
	
	sendComment("Bonne chance mon copain ^^");

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

//PARTIE DEPLACEMENT DANS LE JEU

	avance_ligne_droite(0, (1), &taille_serpent, &tour, &adversaire, &moi, &move_adv,arene, Longueur_Arene, Hauteur_Arene,Serpant_Moi, Tete_Queu_Moi, Serpant_Adv, Tete_Queu_Adv, Placement_a_DROITE); //printArena(); //Test unitaire de deplacement
	avance_ligne_droite(3, (1), &taille_serpent, &tour, &adversaire, &moi, &move_adv,arene, Longueur_Arene, Hauteur_Arene,Serpant_Moi, Tete_Queu_Moi, Serpant_Adv, Tete_Queu_Adv, Placement_a_DROITE); //printArena(); //Test unitaire de deplacement

	int direction_manuel_cylage_petit = 2;
	for ( int iii = 0; iii<6; iii++)
	{
		for ( int ii = 0; ii<4; ii++)
		{
			for ( int i = 0; i<2; i++)
			{
				avance_ligne_droite(direction_manuel_cylage_petit, 1, &taille_serpent, &tour, &adversaire, &moi, &move_adv,arene, Longueur_Arene, Hauteur_Arene,Serpant_Moi, Tete_Queu_Moi, Serpant_Adv, Tete_Queu_Adv, Placement_a_DROITE); //All in one : Affiche l arene + Met a jour l arene et les serpants + deplace le serpant
				//printArena();
				printf ("Cycle %d - %d - %d\n",iii, ii, i);
			}
			direction_manuel_cylage_petit--;
			if (direction_manuel_cylage_petit<0) {direction_manuel_cylage_petit=3;} 
		}
	}

int joker_pass = 0; //Variable utile pour passer les 1eres rotation si on commence a Gauche.
	if ( Placement_a_DROITE == 1 ) 
        {	//Coup speciaux si on joue par la Droite
			avance_ligne_droite(2, (2), &taille_serpent, &tour, &adversaire, &moi, &move_adv,arene, Longueur_Arene, Hauteur_Arene,Serpant_Moi, Tete_Queu_Moi, Serpant_Adv, Tete_Queu_Adv, Placement_a_DROITE);
			avance_ligne_droite(1, (3), &taille_serpent, &tour, &adversaire, &moi, &move_adv,arene, Longueur_Arene, Hauteur_Arene,Serpant_Moi, Tete_Queu_Moi, Serpant_Adv, Tete_Queu_Adv, Placement_a_DROITE);
			avance_ligne_droite(0, (Hauteur_Arene/2)+1, &taille_serpent, &tour, &adversaire, &moi, &move_adv,arene, Longueur_Arene, Hauteur_Arene,Serpant_Moi, Tete_Queu_Moi, Serpant_Adv, Tete_Queu_Adv, Placement_a_DROITE);
			joker_pass = 1;
		}
	else if ( Placement_a_DROITE == 0 )
        {	//Coup speciaux si on joue par la Gauche
			avance_ligne_droite(3, (1), &taille_serpent, &tour, &adversaire, &moi, &move_adv,arene, Longueur_Arene, Hauteur_Arene,Serpant_Moi, Tete_Queu_Moi, Serpant_Adv, Tete_Queu_Adv, Placement_a_DROITE);
			avance_ligne_droite(2, (Hauteur_Arene/2)+1, &taille_serpent, &tour, &adversaire, &moi, &move_adv,arene, Longueur_Arene, Hauteur_Arene,Serpant_Moi, Tete_Queu_Moi, Serpant_Adv, Tete_Queu_Adv, Placement_a_DROITE);
			joker_pass = 0;
		}
	
	while ( moi == 0 && adversaire == 0) //Pensez a couper la machine si le jeu est fini dans avance_ligne_droite aussi
	{	
		if ( joker_pass == 1) //Si on joue a Gauche on commence a tourner par le bas, ici on tourne par le haut
			{
				avance_ligne_droite(3, (Longueur_Arene- 1), &taille_serpent, &tour, &adversaire, &moi, &move_adv,arene, Longueur_Arene, Hauteur_Arene,Serpant_Moi, Tete_Queu_Moi, Serpant_Adv, Tete_Queu_Adv, Placement_a_DROITE);
				avance_ligne_droite(2, (Hauteur_Arene - 1), &taille_serpent, &tour, &adversaire, &moi, &move_adv,arene, Longueur_Arene, Hauteur_Arene,Serpant_Moi, Tete_Queu_Moi, Serpant_Adv, Tete_Queu_Adv, Placement_a_DROITE);
			}
			joker_pass = 1; //Sauvegarder la 1er passage
			avance_ligne_droite(1, (Longueur_Arene- 1), &taille_serpent, &tour, &adversaire, &moi, &move_adv,arene, Longueur_Arene, Hauteur_Arene,Serpant_Moi, Tete_Queu_Moi, Serpant_Adv, Tete_Queu_Adv, Placement_a_DROITE);
			avance_ligne_droite(0, (Hauteur_Arene - 1), &taille_serpent, &tour, &adversaire, &moi, &move_adv,arene, Longueur_Arene, Hauteur_Arene,Serpant_Moi, Tete_Queu_Moi, Serpant_Adv, Tete_Queu_Adv, Placement_a_DROITE);
	}

//FIN de Partie
	printf ("coup_Moi : %d\t coup_adverse : %d\t mon serpent est de taille : %d\n",moi, adversaire, taille_serpent );	

	if (moi == -1)
		{printf ("\nNotre serpant a perdu mais il fera mieux la prochaine fois : )");}
	else if (adversaire == -1)
		{
			sendComment("Mon serpant a gagner emogie confetie ^^ Merci mon copain ^^");
			printf ("\nNotre serpant a gagner emogie confetie ^^");}
	
	closeConnection(); printf("\nFermeture Connection"); //Merci Quentin GODÉREAUX : rappel liberation memoire 

	//Partie liberation de la memoire alloue
	liberation_memoire(arene, Hauteur_Arene, Muraille, Serpant_Moi, Serpant_Adv, Tete_Queu_Moi, Tete_Queu_Adv);

	printf("\nTest Main Fin fonctionnel\n");

	return 0; //Attention,  si l on return 1 c'est un signe d erreur le compilateur le signifiera
}
