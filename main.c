#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <time.h>




int main() {
	
	Liste *head = NULL;
	
	// obtenir les infomation sur les taches
	obtenir_taches(&head);
	
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
		} else if (choix == 6) {
			tri_tache(&head);
		} else if (choix == 7) {
			ajouter_taches_fichier(head);
			break;
		} else {
			continue;
		}
		
	} while(choix != 7);
		
	return 0;
	
}









