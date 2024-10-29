#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


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


// Affiches Les Taches
void afficher_taches(Liste *head) {
	
	if (head == NULL) {
		message(); return;
	}
	
	Liste *temp = head;
	printf("\n-------------------------\n");
	while (temp != NULL) {
		printf("titre: %s\n", temp->data.titre);
		printf("description: %s\n", temp->data.description);
		printf("status: %s\n", temp->data.status);
		printf("priorite: %s\n", temp->data.priorite);
		printf("Date: %d/%d/%d\n", temp->data.date.jour, temp->data	.date.mois, temp->data.date.annes);
		printf("-------------------------\n");
		temp = temp->next;
	}
	
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
	scanf("%[^\n]", n_node->data.titre);
	getchar();
	printf("Enter la description: ");
	scanf("%[^\n]", n_node->data.description);
	getchar();
	printf("Enter le status: ");
	scanf("%[^\n]", n_node->data.status);
	getchar();
	printf("Enter le priorite: ");
	scanf("%[^\n]", n_node->data.priorite);
	getchar();
	printf("Enter la date (jour): ");
	scanf("%d", &n_node->data.date.jour);
	printf("Enter la date (moin): ");
	scanf("%d", &n_node->data.date.mois);
	printf("Enter la date (annes): ");
	scanf("%d", &n_node->data.date.annes);
	
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
		} else if (choix_mod != 6) {
			printf("Veillez Saiser Votre Operation\n");
		} else {
			
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
	printf("Enter le titre");
	scanf("%[^\n]s", titre); titre[19] = '\0';
	
	Liste *temp = head;
	while(temp != NULL) {
		if (strcmp(temp->titre, titre) == 0) {
			printf("titre: %s\n", temp->data.titre);
			printf("description: %s\n", temp->data.description);
			printf("status: %s\n", temp->data.status);
			printf("priorite: %s\n", temp->data.priorite);
			printf("Date: %d/%d/%d\n", temp->data.date.jour, temp->data	.date.mois, temp->data.date.annes);
			printf("-------------------------\n");
		}
		
		temp = temp->next;
	}
	
}

// filtrage des information par le status
void filtrage_status(Liste *head) {
	
	printf("Not Implemented yet\n");
	
}

// filtrage des information par le priorite
void filtrage_priorite(Liste *head) {
	
	printf("Not Implemented yet\n");
	
}

// Menu de filtrage
void menu_filtrage() {

	printf("1. titre \n");
	printf("2. status\n");
	printf("3. priorite\n");
	printf("4. Quitter Session de Filtrage\n");
	
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
			default: break;
		}
	} while(choix != 4);
	
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











