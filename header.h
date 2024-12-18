
/* **********************************************************************************************/
/*                                                                                   			*/
/*                                  	::::::::  ::::     ::  :::::::::::   :::::::::::		*/ 
/*                                      :+:       :: ::	   ::  ::	    ::	 ::		  ::		*/ 
/*                                      :+:       ::  ::   ::  ::		::	 ::		  ::		*/ 
/* By: Abdellah Karani                  ::::::::  ::   ::  ::  :+:+:+:+:+:	 :+:+:+:+:+:		*/ 
/*                                      :+:       ::    :: ::  ::		::	 ::		  ::		*/ 
/* Started: 2024/10/28          		:+:       ::     ::::  ::		::	 ::		  ::		*/ 
/* Finiched: 2024/10/30           		::::::::  ::  	   ::  ::		::	 ::		  ::		*/
/*           	                                                                       			*/ 
/* **********************************************************************************************/


#ifndef TASK
#define TASK

	// Coleurs
	#define RED "\033[1;31m"
	#define GREEN "\033[1;32m"
	#define WARNING "\033[1;33m"
	#define RESET "\033[0m"
	#define MENU_COLOR "\033[1;36m"
	#define GRAY "\033[1;90m"
	#define BLUE "\033[1;34m"


	// Les definitions des structures
	
	typedef struct Date {
		int jour;
		int mois;
		int annes;
	} Date;
	
	typedef struct Tache {
		char titre[20];
		char description[200];
		char status[20];
		char priorite[20];
		Date date;
	} Tache;
	
	typedef struct Liste {
		Tache data;
		struct Liste* next;
	} Liste;
	


	// Les prototypes des fonctions
	void message();
	void menu();
	void affiche_info(Liste *tache);
	void afficher_taches(Liste *head);
	int saisir_et_verifier_chaine(char *message, char *resultat, char *option1, char *option2);
	
	void remplacer_spaces(char *str);
	void remplacer_underscore(char *str);
	void obtenir_taches(Liste **head);
	void ajouter_taches_fichier(Liste *head);
	
	void demander_info(Liste *n_node);
	void ajouter_liste(Liste **head, Liste *n_node);
	Liste *cree_node();
	void ajouter_tache(Liste **head);
	
	Liste *trouver_tache(Liste **head, int n_tache);
	void menu_modification();
	void modifier_tache(Liste **head);
	
	void supprimer_tache(Liste **head);
	
	void filtrage_titre(Liste *head);
	void filtrage_status(Liste *head);
	void filtrage_priorite(Liste *head);
	void filtrage_date(Liste *head);
	void menu_filtrage();
	void filtrer_taches(Liste *head);
	
	void tri_tache(Liste **head);
	void tri_tache_croissant(Liste **head);
	void tri_tache_croissant(Liste **head);
	



#endif







