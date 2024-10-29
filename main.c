#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <time.h>

/*
	pour acceder a les champs avec un pointeur en utliser des fleches
*/


// Message
void message() {
	printf("\n-------------------------\n");
	printf("Aucun Tache");
	printf("\n-------------------------\n");
}


// Menu
void menu() {

	printf("\n========================== MENU ==========================\n\n");
	printf("1. 📜  Ajouter une Tache\n");
	printf("2. 📋  Afficher des Taches\n");
	printf("3. 🖊️  Modifier une Tache\n");
	printf("4. 🗑️  Supprimer une Tache\n");
	printf("5. 🔍  Filtrer les Taches \n");
	printf("6. 🚪  Quitter\n");
	
}

// Affiches Des Information sur la tache
void affiche_info(Liste *tache) {
	printf("titre: %s\n", tache->data.titre);
	printf("description: %s\n", tache->data.description);
	printf("status: %s\n", tache->data.status);
	printf("priorite: %s\n", tache->data.priorite);
	printf("Date: %d/%d/%d\n", tache->data.date.jour, tache->data.date.mois, tache->data.date.annes);
	printf("-------------------------\n");
}


// Affiches Les Taches
void afficher_taches(Liste *head) {
	
	if (head == NULL) {
		message(); return;
	}
	
	Liste *temp = head;
	printf("\n-------------------------\n");
	while (temp != NULL) {
		affiche_info(temp);
		temp = temp->next;
	}
	
}


// Remplacer les spaces d'un string
void remplacer_spaces(char *str) {
	
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == ' ') str[i] = '_';
	}
	
}

// Ajouter les informations dans un fichier
void ajouter_tache_fichier(Liste *tache) {
	
	FILE *p_file = fopen("tache.txt", "a");
	if (p_file == NULL) {
		printf("Error d'ajout a un fichier\n");
		return;
	}
	
	remplacer_spaces(tache->data.titre);
	remplacer_spaces(tache->data.description);
	remplacer_spaces(tache->data.status);
	remplacer_spaces(tache->data.priorite);
	
	fprintf(p_file, "%s %s %s %s %d %d %d", tache->data.titre, tache->data.description,
	tache->data.status, tache->data.priorite, tache->data.date.jour, tache->data.date.mois, tache->data.date.annes);
	
}

// Ajouter Les Taches
void ajouter_tache(Liste **head) {
	
	// cree un node dans la liste
	Liste *n_node = (Liste *) malloc(sizeof(Liste));
	if (n_node == NULL) {
		printf("peut pas ajouter ce node\n");
		return;
	}
	n_node->next = n_node->prev = NULL;
	
	printf("Enter le titre: ");
	scanf("%[^\n]", n_node->data.titre); n_node->data.titre[19] = '\0';
	getchar();
	printf("Enter la description: ");
	scanf("%[^\n]", n_node->data.description); n_node->data.description[19] = '\0';
	getchar();
	printf("Enter le status: ");
	scanf("%[^\n]", n_node->data.status); n_node->data.status[19] = '\0';
	getchar();
	printf("Enter le priorite: ");
	scanf("%[^\n]", n_node->data.priorite); n_node->data.priorite[19] = '\0';
	getchar();
	printf("Enter la date (jour): ");
	scanf("%d", &n_node->data.date.jour);

	// get the year
	time_t now = time(NULL);
    struct tm *t = localtime(&now);
    
	int annes = t->tm_year + 1970;
    int mois = t->tm_mon + 1;
	
	do {
		printf("Enter la date (moin): ");
		scanf("%d", &n_node->data.date.mois);
	} while (n_node->data.date.mois < mois || n_node->data.date.mois <= 0);
    
	do {
		printf("Enter la date (annes): ");
		scanf("%d", &n_node->data.date.annes);
	} while (n_node->data.date.annes < annes);
	
	if (*head == NULL) {
		*head = n_node;
		return;
	}
	
	Liste *temp = *head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	n_node->prev = temp;
	temp->next = n_node;
	
	// Ajouter la tache a un fichier
	ajouter_tache_fichier(n_node);
	
}


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
	
	int choix_mod;
	do {
		menu_modification();
		printf("Veillez enterez le champ de modification: ");
		scanf("%d", &choix_mod);
		getchar();
		if (choix_mod == 1) {
			printf("Enter neuveau titre de tache: ");
			scanf("%[^\n]", tache_modfier->data.titre);
		} else if (choix_mod == 2) {
			printf("Enter neuveau description de tache: ");
			scanf("%[^\n]", tache_modfier->data.description);
		} else if (choix_mod == 3) {
			printf("Enter neuveau status de tache: ");
			scanf("%[^\n]", tache_modfier->data.status);
		} else if (choix_mod == 4) {
			printf("Enter neuveau titre de tache: ");
			scanf("%[^\n]", tache_modfier->data.priorite);
		} else if (choix_mod == 5) {
			printf("Enterz le neuveau jour: "); scanf("%d", &tache_modfier->data.date.jour);
			printf("Enterz le neuveau moin: "); scanf("%d", &tache_modfier->data.date.mois);
			printf("Enterz le neuveau annes: "); scanf("%d", &tache_modfier->data.date.annes);
		} else {
			continue;
		}
	} while(choix_mod != 6);
		
}

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
			if (temp != *head) {
				prev->next = temp->next;
				if (temp->next != NULL) temp->next->prev = prev;
			} else {
				*head = temp->next;
				if (temp->next != NULL) temp->next->prev = NULL;
			}
			free(temp);
			printf("✅ Tache bien supprimer\n");
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


// filtrage des information par le nom
void filtrage_titre(Liste *head) {
	
	char *titre = (char *) malloc(sizeof(char) * 20);
	printf("Enter le titre: ");
	scanf("%[^\n]s", titre); titre[19] = '\0';
	
	Liste *temp = head;
	int check = 0;
	printf("-------------------------\n");
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
	printf("-------------------------\n");
	while(temp != NULL) {
		if (strcmp(temp->data.status, status) == 0) {
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
	printf("-------------------------\n");
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
	printf("-------------------------\n");
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
void  filtrer_taches(Liste *head) {
	
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


int main() {
	
	Liste *head = NULL;
	int choix;
	do {
		menu();
		printf("Veillez enterez votre choix: ");
		scanf("%d", &choix);
		getchar();
		if (choix == 1) {
			ajouter_tache(&head);
		} else if (choix == 2) {
			afficher_taches(head);
		} else if (choix == 3) {
			modifier_tache(&head);
		} else if (choix == 4) {
			supprimer_tache(&head);
		} else if (choix == 5) {
			filtrer_taches(head);
		} else if (choix != 6) {
			printf("Veillez Saiser Votre Operation\n");
		}
		
	} while(choix != 6);
		
	return 0;
}






// explination 
/*
	// gets the current time in seconds since January 1, 1970
	time_t now = time(NULL);
	// line converts the time_t value now into a tm structure
    struct tm *t = localtime(&now);
    int year = t->tm_year + 1900;
    // on ajouter 1900 car tm_year reprsent annes depuis 1900
    // tm_year countr from 1900
*/



// Custom the date condition & storage in file
















