#include "Projet_info_ARENE.h"

void affichage_arene(Cellule **arene_a, int Longueur_Arene_a, int Hauteur_Arene_a);
void liberation_serpent(Serpant *Serpant_l);

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
	
	(*arene_p)[Hauteur_Arene_p/2][2].Occupation = 10; //Serpant de Gauche Base 10
	(*arene_p)[Hauteur_Arene_p/2][Longueur_Arene_p-3].Occupation = 20; //Serpant de Droite base 20
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
		else 
    {
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
            if (arene_a[h][l].Occupation >= 1 && (arene_a[h][l].W == 0||arene_a[h][l].W == 1) )
            {// Echantillons ◀ ▶ ▲ ▼ ■
                if (arene_a[h][l].Occupation<20 && arene_a[h][l].Occupation>=10) //Ouverture de la couleur GAUCHE = ROUGE, DROITE = BLEU
                    {printf("\x1b[31m");}
                else 
                    {printf("\x1b[36m");}
                
                if (arene_a[h][l].W == 0){printf(" ");}
                else if (arene_a[h][l].W == 1){printf("┃");}

                if      ((((arene_a[h][l].Occupation)-1)%10)==0) {printf("▲");} //Dehachage_dechiffrement de l occupation
                else if ((((arene_a[h][l].Occupation)-1)%10)==1) {printf("▶");}
                else if ((((arene_a[h][l].Occupation)-1)%10)==2) {printf("▼");}
                else if ((((arene_a[h][l].Occupation)-1)%10)==3) {printf("◀");}
                else 
                    {printf("■");}

                printf("\x1b[0m ");//Reset de la couleur
            }

            else if (arene_a[h][l].Occupation == 0 && arene_a[h][l].W == 1)
                {printf("┃. ");}
            else 
                {printf(" . ");}
        }
        //Affichage derniere colonne    
        if (arene_a[h][Longueur_Arene_a-1].Occupation >= 1)
        {// Echantillons ◀ ▶ ▲ ▼ ■
            if (arene_a[h][Longueur_Arene_a-1].Occupation<20 && arene_a[h][Longueur_Arene_a-1].Occupation>=10) //Ouverture de la couleur GAUCHE = ROUGE, DROITE = BLEU
                {printf("\x1b[31m ");}
            else 
                {printf("\x1b[36m ");}

            if      ((((arene_a[h][Longueur_Arene_a-1].Occupation)-1)%10)==0) {printf("▲");} //Dehachage_dechiffrement de l occupation
            else if ((((arene_a[h][Longueur_Arene_a-1].Occupation)-1)%10)==1) {printf("▶");}
            else if ((((arene_a[h][Longueur_Arene_a-1].Occupation)-1)%10)==2) {printf("▼");}
            else if ((((arene_a[h][Longueur_Arene_a-1].Occupation)-1)%10)==3) {printf("◀");}
            else 
                {printf("■");}
                
            printf("\x1b[0m┃");//Reset de la couleur
        }
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
}

void liberation_memoire(Cellule **arene_l, int Hauteur_Arene_l, int *Muraille_l, Serpant *Serpant_Moi_l, Serpant *Serpant_Adv_l, Serpant **Tete_Queu_Moi_l, Serpant **Tete_Queu_Adv_l)
{
    //Liberation memoire arene
    for (int h = 0; h < Hauteur_Arene_l; h++) 
    {
        free(arene_l[h]);
    }
    free(arene_l);
    printf("\nLiberation memoire arene effectuee");
    
    //Liberation memoire muraille
    free(Muraille_l);
    printf("\nLiberation memoire muraille effectuee");

    //Liberation memoire Serpants
    liberation_serpent(Serpant_Moi_l);
    liberation_serpent(Serpant_Adv_l);
    printf("\nLiberation memoire muraille effectuee");

    //Liberation memoire tetes et queues serpents
    free(Tete_Queu_Moi_l);
    free(Tete_Queu_Adv_l);
    printf("\nLiberation memoire tete_queue effectuee\n");
}

/*

Les Papas des Elec Thibault HILAIRE Yann DOUZE Benoit FABRE Annick ALEXANDRE IFitep Michel REDON 
Ei Eise Eili Eist 
Les ST etait premier avec EI 
Ifitep avant Polytech
 
*/
