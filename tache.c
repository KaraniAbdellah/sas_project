#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <time.h>


/* ********************************************************************************* 	*/
/*                                                                                   	*/
/*                                  	::::::::     									*/ 
/*                                      :+:          									*/ 
/*                                      :+:            									*/ 
/* By: Abdellah Karani                  ::::::::            							*/ 
/*                                      :+:            									*/ 
/* Created: 2024/10/30           		:+:             								*/ 
/*            							::::::::   										*/
/*           	                                                                       	*/ 
/* ********************************************************************************* */



// Message
void message() {
	printf("\n-------------------------\n");
	printf("Aucun Tache");
	printf("\n-------------------------\n");
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

// Menu
void menu() {

	printf("\n========================== MENU ==========================\n\n");
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

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

// Remplacer les spaces d'un string
void remplacer_spaces(char *str) {
	
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == ' ') str[i] = '_';
	}
	
}

// Ajouter les informations dans un fichier
void ajouter_taches_fichier(Liste *head) {

	FILE *p_file = fopen("tache.txt", "w");
	if (p_file == NULL) {
		printf("Error d'ajouter a un fichier\n");
		return;
	}

	Liste *temp = head;
	while (temp != NULL) {
		
		remplacer_spaces(temp->data.titre);
		remplacer_spaces(temp->data.description);
		remplacer_spaces(temp->data.status);
		remplacer_spaces(temp->data.priorite);
		
		fprintf(p_file, "%s %s %s %s %d %d %d\n", temp->data.titre, temp->data.description,
		   temp->data.status, temp->data.priorite, temp->data.date.jour, temp->data.date.mois, temp->data.date.annes);
	
		temp = temp->next;		
		
	}	

	fclose(p_file);
	
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

// demander des information
void demander_info(Liste *n_node) {

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
	
	// obtenu actual year
	time_t now = time(NULL);
    struct tm *t = localtime(&now);
	int annes = t->tm_year + 1900;
    int mois = t->tm_mon + 1;
	
	do {
		printf("Enter la date (jour): ");
		scanf("%d", &n_node->data.date.jour);
	} while (n_node->data.date.jour < 0 || n_node->data.date.jour > 31);
	
	do {
		printf("Enter la date (moin): ");
		scanf("%d", &n_node->data.date.mois);
	} while (n_node->data.date.mois < mois || n_node->data.date.mois > 12);
    
	do {
		printf("Enter la date (annes): ");
		scanf("%d", &n_node->data.date.annes);
	} while (n_node->data.date.annes < annes);
	

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
		n_node->prev = temp;
		temp->next = n_node;
	}
	
}

// Cree une node dans la liste
Liste *cree_node() {

	Liste *n_node = (Liste *) malloc(sizeof(Liste));
	if (n_node == NULL) {
		printf("peut pas ajouter ce node\n");
		exit(1);
	}
	n_node->next = n_node->prev = NULL;
	return n_node;
	
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

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

// obtenir les tache a partir du fihier
void obtenir_taches(Liste **head) {
	
	FILE *p_file = fopen("tache.txt", "r");
	if (p_file == NULL) {
		printf("Error d'ouvrir le fichier\n");
		return;
	}
	
	while (1) {
	
		Liste *n_node = cree_node();

		int result = fscanf(p_file, "%s %s %s %s %d %d %d\n", n_node->data.titre, n_node->data.description,
		   n_node->data.status, n_node->data.priorite, &n_node->data.date.jour, &n_node->data.date.mois, &n_node->data.date.annes);
		
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
	
}

/*
Liste *p1 = *head;

    while (p1 != NULL) {
        Liste *p2 = p1->next;
        while (p2 != NULL) {
            if (p2->data.date.annes < p1->data.date.annes) {
				changment(&p1, &p2);
			} else if (p2->data.date.annes == p1->data.date.annes) {
				if (p2->data.date.mois < p1->data.date.mois) {
					changment(&p1, &p2);
				} else if (p2->data.date.mois == p1->data.date.mois) {
					if (p2->data.date.jour < p1->data.date.jour) {
						changment(&p1, &p2);
					}
				}
			}
            p2 = p2->next;
        }
        p1 = p1->next;
    }
*/

/*
Liste *temp1 = *p1;
    Liste *temp2 = *p2;

    if (temp1->prev != NULL) {
        temp1->prev->next = temp2;
    }
    if (temp2->next != NULL) {
        temp2->next->prev = temp1;
    }

    temp1->next = temp2->next;
    temp2->next = temp1;
    
    temp1->prev = temp2->prev;
    temp2->prev = temp1;

    if (temp1->prev != NULL) {
        temp1->prev->next = temp1;
    }
    if (temp2->next != NULL) {
        temp2->next->prev = temp2;
    }
*/







