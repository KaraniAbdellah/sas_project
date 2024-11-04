#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <time.h>


/* **********************************************************************************************/
/*                                                                                   			*/
/*                                  	::::::::  ::::     ::  :::::::::::   :::::::::::		*/ 
/*                                      :+:       :: ::	   ::  ::	    ::	 ::		  ::		*/ 
/*                                      :+:       ::  ::   ::  ::		::	 ::		  ::		*/ 
/* By: Abdellah Karani                  ::::::::  ::   ::  ::  :+:+:+:+:+:	 :+:+:+:+:+:		*/ 
/*                                      :+:       ::    :: ::  ::		::	 ::		  ::		*/ 
/* Started: 2024/10/28          		:+:       ::     ::::  ::		::	 ::		  ::		*/ 
/* Finiched: 2024/10/31          		::::::::  ::  	   ::  ::		::	 ::		  ::		*/
/*           	                                                                       			*/ 
/* **********************************************************************************************/



// Message
void message() {
	printf(RED "\n-------------------------\n");
	printf(RED "Aucun Tache");
	printf("\n-------------------------\n" RESET);
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

// Menu
void menu() {
	
	printf(MENU_COLOR "\n========================== MENU ==========================\n\n" RESET);
	printf("1. 📜  Ajouter une Tache\n");
	printf("2. 📋  Afficher des Taches\n");
	printf("3. 🖊️  Modifier une Tache\n");
	printf("4. 🗑️  Supprimer une Tache\n");
	printf("5. 🔍  Filtrer les Taches \n");
	printf("6. 🔍  Trier les Taches \n");
	printf("7. 🚪  Quitter\n");
	
}


// Affiches Des Information sur la tache
void affiche_info(Liste *tache) {

	printf("titre: %s\n", tache->data.titre);
	printf("description: %s\n", tache->data.description);
	printf("status: %s\n", tache->data.status);
	printf("priorite: %s\n", tache->data.priorite);
	printf("Date: %d/%d/%d\n", tache->data.date.jour, tache->data.date.mois, tache->data.date.annes);
	printf(BLUE "-------------------------\n" RESET);
	
}


// Affiches Les Taches
void afficher_taches(Liste *head) {
	
	if (head == NULL) {
		message(); return;
	}
	
	Liste *temp = head;
	printf(BLUE "\n-------------------------\n" RESET);
	while (temp != NULL) {
		affiche_info(temp);
		temp = temp->next;
	}
	
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

// Verfier la chaine qui lit par utilisateur
int saisir_et_verifier_chaine(char *message, char *resultat, char *option1, char *option2) {
    printf("%s", message);
    scanf("%19[^\n]", resultat);
    getchar();
    if (strcmp(resultat, option1) != 0 && strcmp(resultat, option2) != 0) {
        return 0;
    }
    return 1;
}

// demander des information
void demander_info(Liste *n_node) {

	printf("Enter le titre: ");
	scanf("%[^\n]", n_node->data.titre); n_node->data.titre[19] = '\0';
	getchar();
	printf("Enter la description: ");
	scanf("%[^\n]", n_node->data.description); n_node->data.description[199] = '\0';
	getchar();
	
	int check;
	
	do {
		check = saisir_et_verifier_chaine("Enter status (complet/incomplet): ",
		n_node->data.status, "incomplet", "complet");
	} while(check == 0);
	
	do {
		check = saisir_et_verifier_chaine("Enter le priorite (low/high): ",
		n_node->data.priorite, "low", "high");
	} while(check == 0);
	
	do {
		printf("Enter la date (jour): ");
		scanf("%d", &n_node->data.date.jour);
	} while (n_node->data.date.jour < 0 || n_node->data.date.jour > 31);
	
	do {
		printf("Enter la date (moin): ");
		scanf("%d", &n_node->data.date.mois);
	} while (n_node->data.date.mois < 0 || n_node->data.date.mois > 12);
    
	time_t now = time(NULL); // get the nbr of second since 1 Jan 1970
    struct tm *t = localtime(&now); // localtime return addrese of struct
	int annes = t->tm_year + 1900; // get the actual year
    
	do {
		printf("Enter la date (annes): ");
		scanf("%d", &n_node->data.date.annes);
	} while (n_node->data.date.annes < 0 || n_node->data.date.annes < annes);
	

}

// Cree une node dans la liste
Liste *cree_node() {

	Liste *n_node = (Liste *) malloc(sizeof(Liste));
	if (n_node == NULL) {
		printf("peut pas ajouter ce node\n");
		exit(1);
	}
	n_node->next = NULL;
	return n_node;
	
}

// Ajouter Dans La Liste
void ajouter_liste(Liste **head, Liste *n_node) {
	
	if (*head == NULL) {
		*head = n_node;
	} else {
		Liste *temp = *head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = n_node;
	}
	
}

// Ajouter Les Taches
void ajouter_tache(Liste **head) {

	// Cree un node dans la liste
	Liste *n_node = cree_node();
	
	// Demande des information sur la tache
	demander_info(n_node);

	// Ajouter node dans la liste
	ajouter_liste(head, n_node);
	
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

// Trouver la tache qui doit modifier_tache
Liste* trouver_tache(Liste **head, int n_tache) {
	
	Liste *temp = *head;
	int index = 1;
	while (temp != NULL && index < n_tache) {
		temp = temp->next;
		index++;
	}
	if (temp == NULL) return NULL;
	else return temp;
	
}

// Menu de modification
void menu_modification() {
	printf("1. titre \n");
	printf("2. description\n");
	printf("3. status\n");
	printf("4. priorite\n");
	printf("5. Date\n");
	printf("6. Quitter Session de modification\n");
}

// Modifier les taches
void modifier_tache(Liste **head) {
	
	if (*head == NULL) {
		message(); return;
	}
	
	int n_tache;
	printf("Enter numero de la tache: ");
	scanf("%d", &n_tache);
	
	// Trouver le node du tache choisit
	Liste *tache_modfier = trouver_tache(head, n_tache);
	if (tache_modfier == NULL) {
		message(); return;
	}
	
	int choix_mod, check;
	do {
		menu_modification();
		printf("Veillez enterez le champ de modification: ");
		scanf("%d", &choix_mod); // new line
		getchar();
		
		if (choix_mod == 1) {
			printf("Enter neuveau titre de tache: ");
			scanf("%[^\n]", tache_modfier->data.titre);
		} 
		else if (choix_mod == 2) {
			printf("Enter neuveau description de tache: ");
			scanf("%[^\n]", tache_modfier->data.description);
		} 
		else if (choix_mod == 3) {
			do {
				check = saisir_et_verifier_chaine("Enter neuveau status (complet/incomplet): ",
				tache_modfier->data.status, "incomplet", "complet");
			} while(check == 0);
		} 
		else if (choix_mod == 4) {
			do {
				check = saisir_et_verifier_chaine("Enter neuveau priorite (low/hight): ",
				tache_modfier->data.priorite, "incomplet", "complet");
			} while(check == 0);
		} 
		else if (choix_mod == 5) {
			do {
				printf("Enterz le neuveau jour: ");
				scanf("%d", &tache_modfier->data.date.jour);
			} while (tache_modfier->data.date.jour < 0 || tache_modfier->data.date.jour > 31);
			
			do {
				printf("Enterz le neuveau moin: ");
				scanf("%d", &tache_modfier->data.date.mois);
			} while (tache_modfier->data.date.mois < 0 || tache_modfier->data.date.mois > 12);
			
			time_t now = time(NULL);
			struct tm *t = localtime(&now);
			int annes = t->tm_year + 1900;
			
			do {
				printf("Enterz le neuveau annes: ");
				scanf("%d", &tache_modfier->data.date.annes);
			} while (tache_modfier->data.date.annes < 0 || tache_modfier->data.date.annes < annes);
			
		} 
		else {
			continue;
		}
	} while(choix_mod != 6);
	
	printf(GREEN "\n✅ Tache bien modifier\n" RESET);
		
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

// Supprimer une taches
void supprimer_tache(Liste **head) {
	
	if (*head == NULL) {
		message(); return;
	}
	
	int n_tache;
	printf("Enterz tache a supprimer: ");
	scanf("%d", &n_tache);
	
	Liste *temp = *head;
	Liste *prev;
	int index = 1;
	while (temp != NULL) { 
		if (index == n_tache) {
			if (temp == *head) {
				*head = temp->next;
			} else {
				prev->next = temp->next;
			}
			free(temp);
			printf(GREEN "\n✅ Tache bien supprimer\n" RESET);
			return;
		}
		prev = temp;
		temp = temp->next;
		index++;
	}
	
	if (temp == NULL) {
		message(); return;
	}
	
}									

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

// filtrage des information par le nom
void filtrage_titre(Liste *head) {
	
	char *titre = (char *) malloc(sizeof(char) * 20);
	printf("Enter le titre: ");
	scanf("%[^\n]s", titre); titre[19] = '\0';
	
	Liste *temp = head;
	int check = 0;
	printf(BLUE "-------------------------\n");
	printf("Les taches filtrer par le titre: \n");
	printf("-------------------------\n" RESET);
	while(temp != NULL) {
		if (strcmp(temp->data.titre, titre) == 0) {
			check = 1;
			affiche_info(temp);
		}
		temp = temp->next;
	}
	if (check == 0) {
		message();
	}	
	printf("\n");
	
}


// filtrage des information par le status
void filtrage_status(Liste *head) {

	char *status = (char *) malloc(sizeof(char) * 20);
	printf("Enter le status: ");
	scanf("%[^\n]s", status); status[19] = '\0';
	
	Liste *temp = head;
	int check = 0;
	printf(BLUE "-------------------------\n");
	printf("Les taches filtrer par le status: \n");
	printf("-------------------------\n" RESET);
	while(temp != NULL) {
		if (strcmp(temp->data.status, status) == 0) {
			check = 1;
			affiche_info(temp);
		}
		temp = temp->next;
	}
	if (check == 0) {
		message();
	}	
	printf("\n");
	
	
}


// filtrage des information par le priorite
void filtrage_priorite(Liste *head) {
	
	char *priorite = (char *) malloc(sizeof(char) * 20);
	printf("Enter le priorite: ");
	scanf("%[^\n]s", priorite); priorite[19] = '\0';
	
	Liste *temp = head;
	int check = 0;
	printf(BLUE "-------------------------\n");
	printf("Les taches filtrer par le priorite: \n");
	printf("-------------------------\n" RESET);
	while(temp != NULL) {
		if (strcmp(temp->data.priorite, priorite) == 0) {
			check = 1;
			affiche_info(temp);
		}
		temp = temp->next;
	}
	if (check == 0) {
		message();
	}	
	printf("\n");
	
}


// filtrage des information par la date
void filtrage_date(Liste *head) {
	
	int jour;
	int mois;
	int annes;
	printf("Enter Le jour: ");
	scanf("%d", &jour);
	printf("Enter Le mois: ");
	scanf("%d", &mois);
	printf("Enter Le annes: ");
	scanf("%d", &annes);
	
	Liste *temp = head;
	int check = 0;
	printf(BLUE "-------------------------\n");
	printf("Les taches filtrer par la date: \n");
	printf("-------------------------\n" RESET);
	while(temp != NULL) {
		if (temp->data.date.jour == jour && temp->data.date.mois == mois && temp->data.date.annes == annes) {
			check = 1;
			affiche_info(temp);
		}
		temp = temp->next;
	}
	if (check == 0) {
		message();
	}
	printf("\n");
	
}


// Menu de filtrage
void menu_filtrage() {

	printf("1. titre \n");
	printf("2. status\n");
	printf("3. priorite\n");
	printf("4. date\n");
	printf("5. Quitter Session de Filtrage\n");
	
}


//  Filtrer les Taches
void filtrer_taches(Liste *head) {
	
	if (head == NULL) {
		message(); return;
	}
	
	int choix;
	do {
		menu_filtrage();
		printf("Enter votre choix: ");
		scanf("%d", &choix);
		getchar();
		switch(choix) {
			case 1: {
				filtrage_titre(head);
				break;
			}
			case 2: {
				filtrage_status(head);
				break;
			}
			case 3: {
				filtrage_priorite(head);
				break;
			}
			case 4: {
				filtrage_date(head);
				break;
			}
			default: break;
		}
	} while(choix != 5);
	
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

// Remplacer les spaces d'un string
void remplacer_spaces(char *str) {
	
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == ' ') str[i] = '_';
	}
	
}

// Remplacer les underscores d'un string 
void remplacer_underscore(char *str) {
	
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '_') str[i] = ' ';
	}
	
}

// Ajouter les informations dans un fichier
void ajouter_taches_fichier(Liste *head) {

	FILE *p_file = fopen("tache.txt", "w");
	if (p_file == NULL) {
		printf("Error d'ouvrir a un fichier\n");
		return;
	}

	Liste *temp = head;
	while (temp != NULL) {
		
		remplacer_spaces(temp->data.titre);
		remplacer_spaces(temp->data.description);
		
		fprintf(p_file, "titre: %s\ndescription: %s\npriorite: %s\nstatus: %s\ndate: %d:%d:%d\n\n", temp->data.titre, temp->data.description,
		   temp->data.status, temp->data.priorite, temp->data.date.jour, temp->data.date.mois, temp->data.date.annes);

		temp = temp->next;
		
	}

	fclose(p_file);
	
}

// obtenir les tache a partir du fihier
void obtenir_taches(Liste **head) {
	
	FILE *p_file = fopen("tache.txt", "r");
	if (p_file == NULL) {
		printf("Error d'ouvrir le fichier\n");
		return;
	}
	
	while (1) {
	
		Liste *n_node = cree_node();
		
		int result = fscanf(p_file, "titre: %s\ndescription: %s\npriorite: %s\nstatus: %s\ndate: %d:%d:%d\n\n", 
			n_node->data.titre, n_node->data.description, n_node->data.status, n_node->data.priorite,
			&n_node->data.date.jour, &n_node->data.date.mois, &n_node->data.date.annes);

		remplacer_underscore(n_node->data.description);
		remplacer_underscore(n_node->data.titre);
				
		if (result != 7) break;
		
		ajouter_liste(head, n_node);
		
	}
		
	fclose(p_file);
	
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void tri_tache_croissant(Liste **head) {
    
    Liste *p1 = *head;
    while (p1 != NULL) {
		Liste *p2 = p1->next;
		Liste *minEle = p1;
		while (p2 != NULL) {
			if (p2->data.date.annes < minEle->data.date.annes) {
				minEle = p2;
			} else if (p2->data.date.annes == minEle->data.date.annes) {
				if (p2->data.date.mois < minEle->data.date.mois) {
				    minEle = p2;
				} else if (p2->data.date.mois == minEle->data.date.mois) {
				    if (p2->data.date.jour < minEle->data.date.jour) {
				        minEle = p2;
				    }
				}
			}
			p2 = p2->next;
		}

		
		if (minEle != p1) {
			Tache temp = p1->data;
            p1->data = minEle->data;
            minEle->data = temp;
		}
				
		p1 = p1->next;
	}
    
}


void tri_tache_decroissant(Liste **head) {
	
	Liste *p1 = *head;
    while (p1 != NULL) {
		Liste *p2 = p1->next;
		Liste *minEle = p1;
		while (p2 != NULL) {
			if (p2->data.date.annes > minEle->data.date.annes) {
				minEle = p2;
			} else if (p2->data.date.annes == minEle->data.date.annes) {
				if (p2->data.date.mois > minEle->data.date.mois) {
				    minEle = p2;
				} else if (p2->data.date.mois == minEle->data.date.mois) {
				    if (p2->data.date.jour > minEle->data.date.jour) {
				        minEle = p2;
				    }
				}
			}
			p2 = p2->next;
		}

		if (minEle != p1) {
			Tache temp = p1->data;
		    p1->data = minEle->data;
		    minEle->data = temp;
		}

		p1 = p1->next;

	}
	
}

void tri_tache(Liste **head) {
	
	char choix;
	do {
		printf("Enterz order de tri, croissant(c) || decroissant(d): ");
		scanf("%c", &choix);
		getchar();
	} while(choix != 'c' && choix != 'd');
	
	if (choix == 'c') {
		tri_tache_croissant(head);
	} else {
		tri_tache_decroissant(head);
	}
	printf(GREEN "\n✅ Tache bien tries\n" RESET);
	
}








