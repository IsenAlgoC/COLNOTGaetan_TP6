#include <stdio.h>   /* pour les entrées-sorties */
#include <string.h>  /* pour les manipulations de chaînes de caractères */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/* Compléter votre nom ici                                                */
/*   Nom : Colnot              Prénom : Gaëtan                            */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le répertoire stocké en mémoire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire* rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compléter code ici pour tableau
	int idx;
	if (rep->nb_elts < MAX_ENREG)
	{
		idx = rep->nb_elts;
		rep->tab[idx] = enr;
		modif = true;
		rep->nb_elts++;

	}
	else {
		return(ERROR);
	}

#else
#ifdef IMPL_LIST
	int compteur = 0;

	bool inserted = false;
	if (rep->nb_elts == 0) {
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = true;
			return(OK);
		}

	}
	else {
		SingleLinkedListElem* comparateur = rep->liste->head;
		while (!est_sup(comparateur->pers, enr) && comparateur->next != NULL) {//on parcourt la liste en comparant à chaque fois l'enregistrement et le comparateur et si l'enregistrement se trouve avant dans l'ordre alphabétique, on le place avant l'enregistrement
			compteur++;
			comparateur = comparateur->next;
		}

		if (!est_sup(comparateur->pers, enr) && comparateur->next == NULL) { 		//on regarde si il n'y a pas d'anomalie au bout de la liste
			compteur++;
		}

		if (InsertElementAt(rep->liste, compteur, enr) != 0) {

			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = true;
		}
		return(OK);
	}



#endif

#endif


	return(OK);

}
 /* fin ajout */
  /**********************************************************************/
  /* supprime du répertoire l'enregistrement dont l'indice est donné en */
  /*   paramètre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB

void supprimer_un_contact_dans_rep(Repertoire * rep, int indice){
	// compléter code ici pour tableau
	if (rep->nb_elts >= 1){		/* s'il y a au moins un element ds le tableau */
		if ((indice > -1) || (indice < rep->nb_elts)) { /* et que l'indice pointe a l'interieur */
			for (int i = indice; i < rep->nb_elts - 1; ++i) {
				*rep->tab->nom=(rep->tab + i) - (rep->tab + i + 1);
			}
			rep->nb_elts -= 1;		/* ds ts les cas, il y a un element en moins */
			modif = true;
		}
		else {
			modif = false;
		}
	}
	return;
}/* fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du répertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif à vrai                              */
  /************************************************************************/
  // complet

	int supprimer_un_contact_dans_rep_liste(Repertoire *rep, SingleLinkedListElem *elem) {
	
	int ret=DeleteLinkedListElem(rep->liste, elem);
	if (ret == 1) {
		rep->nb_elts--;
		modif = true;
	}

	return (0); 
	}
#endif
#endif


  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement sur une ligne à l'écran  */
  /* ex Dupont, Jean                 0320304050                         */
  /**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	// code à compléter ici
	printf("%s", enr.nom);
	printf(", ");
	printf("%s", enr.prenom);
	printf("            ");
	printf("%s\n", enr.tel);


} /* fin affichage_enreg */
  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	// code à compléter ici
	// comme fonction affichage_enreg, mais avec présentation alignées des infos
	int a = 0;
	int b = 0;
	while (enr.nom[a] != 0) { //taille nom
		a++;
	}
	while (enr.prenom[b] != 0) { //taille prenom
		b++;
	}
	int ecart1 = MAX_NOM - a; //moyen d'avoir l'écart entre prenom et nom 2 fois
	int ecart2 = MAX_NOM - b; 
	printf("\n");
	printf("|%s", enr.nom);
	for (int i = 0; i < ecart1; i++) {
		printf(" ");
	}

	printf("|%s", enr.prenom);
	for (int i = 0; i < ecart2; i++) {
		printf(" ");
	}

	printf("|");
	printf("%s", enr.tel);

	} /* fin affichage_enreg */


  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)
{
	// code à compléter ici
	for (int i = 0; i < MAX_NOM; ++i) {
		int ascii1 = (int)enr1.nom[i];
		int ascii2 = (int)enr2.nom[i];
		if (ascii1 < ascii2) {
			return true;
		}
		if (ascii1 = ascii2) {
			int asciiprenom1 = (int)enr1.prenom[1];
			int asciiprenom2 = (int)enr2.prenom[1];
			if (asciiprenom1 < asciiprenom2) {
				return true;
			}
		}
		return(false);
	}
	return -1;
}
 
/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire *rep)
{

#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	int numberOfSwaps = 0;
	int i = 0;
	char tmp;

	do
	{
		numberOfSwaps = 0;
		for (i = 0; i <= rep->nb_elts; i++)
		{
			if (rep->tab[i].nom[i] > rep->tab[i].nom[i + 1])
			{
				tmp = rep->tab[i].nom[i];
				rep->tab[i].nom[i] = rep->tab[i].nom[i + 1];
				rep->tab[i].nom[i + 1] = tmp;
				numberOfSwaps++;
			}
		}


	} while (numberOfSwaps > 0);


	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien à faire !
	// la liste est toujours triée
#endif
#endif


	rep->est_trie = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le répertoire d'un enregistrement correspondant au  */
  /*   nom à partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au critère ou*/
  /*   un entier négatif si la recherche est négative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire *rep, char nom[], int ind)
{
	int i = ind;		    /* position (indice) de début de recherche dans tableau/liste rep */
	int ind_fin;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;		

#ifdef IMPL_TAB				// ajouter code ici pour tableau
	ind_fin = rep->nb_elts - 1; // indice de fin à ne pas dépasser
	strncpy_s(tmp_nom, _countof(tmp_nom), nom, _TRUNCATE);

	while ((i <= ind_fin) && (!trouve))
	{
		for (int j = 0; tmp_nom[j] != '\0'; j++) {

			if (tmp_nom[j] >= 'a' && tmp_nom[j] <= 'z') {
				tmp_nom[j] = tmp_nom[j] - 32;
			}
		}
		strncpy_s(tmp_nom2, _countof(tmp_nom2), rep->tab[i].nom, _TRUNCATE);
		if (strcmp(tmp_nom, tmp_nom2) == 0)
			trouve = true;
		else
			i++;
	}
	
#else
#ifdef IMPL_LIST
							// ajouter code ici pour Liste
	for (int u = 0; u < MAX_NOM; u++) {
		tmp_nom[u] = toupper(nom[u]);
	}
	while (trouve == false && ind_fin != 0) {  /*on bouge la tête de liste*/
		if (rep->liste == NULL) {
			return 0;
		}
		else {

			for (int j = 0; j < MAX_NOM; j++) {
				tmp_nom2[j] = toupper((rep->liste->head->pers).nom[j]);
			}

			if (strcmp(tmp_nom, tmp_nom2) == 0) {
				trouve = true;
			}

			ind_fin--;
		}
		if (trouve == false && ind_fin != 0) { /*on bouge la tête de liste*/
			rep->liste->head->pers = rep->liste->head->next->pers;
		}

	}
	
#endif
#endif

	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non numériques de la chaines        */
  /*********************************************************************/
size_t myStrLen(const char* string) {
	size_t size = 0;

	while (*string != '\0') {
		string++;    // On déplace le pointeur sur le caractère suivant
		size++;
	}
	return size;
}
void compact(char *s)
{
	// compléter code ici
	
	for (int i = 0; i = myStrLen(s); ++i) {
		int ascii = (int)s[i];
		if (ascii < 48 || ascii >57) { remove (&s[i]); };
	}
	return;
}

/**********************************************************************/
/* sauvegarde le répertoire dans le fichier dont le nom est passé en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionné ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire* rep, char nom_fichier[])
{
	FILE* fic_rep;					/* le fichier */
	errno_t err = fopen_s(&fic_rep, nom_fichier, "w"); /*ouverture du fichier*/
#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	if (err != 0) {
		return ERROR;
	}
	else {

		for (int i = 0; i < rep->nb_elts; i++) {
			fputs(rep->tab[i].nom, fic_rep);
			fputc(';', fic_rep);
			fputs(rep->tab[i].prenom, fic_rep);
			fputc(';', fic_rep);
			fputs(rep->tab[i].tel, fic_rep);
			fputc('\n', fic_rep);

		}

		fclose(fic_rep);
	}
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	if (err != 0) {
		return ERROR;
	}
	else {


		for (int i = 0; i < rep->nb_elts; i++) {      //on prend l'enregistrement et on écrit
			fprintf(fic_rep, "%s%c", GetElementAt(rep->liste, i)->pers.nom, SEPARATEUR);
			fprintf(fic_rep, "%s%c", GetElementAt(rep->liste, i)->pers.prenom, SEPARATEUR);
			fprintf(fic_rep, "%s", GetElementAt(rep->liste, i)->pers.tel);
		}

		fclose(fic_rep); //fermeture du fichier
	}
	
#endif
#endif
	return (OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le répertoire le contenu du fichier dont le nom est  */
  /*   passé en argument                                                */
  /*   retourne OK si le chargement a fonctionné et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char *char_nw_line;
	
	_set_errno(0);
	if ( ((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL) )
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element à priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
														// ajouter code implemention liste
				if (lire_champ_suivant(buffer, &idx, tmp.nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							
					if (lire_champ_suivant(buffer, &idx, tmp.prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, tmp.tel, MAX_TEL, SEPARATEUR) == OK) {
							num_rec++;	

						}
					}
			}

			ajouter_un_contact_dans_rep(rep, tmp); //pour garder le contact à chaque chargement

#endif
#endif




			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */