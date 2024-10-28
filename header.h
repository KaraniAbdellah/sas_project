#ifndef TASK
#define TASK


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
		struct Liste* prev;
	} Liste;
	


	// Les prototypes des fonctions
	
	




#endif

