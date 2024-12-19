#ifndef BDD_AVIS
#define BDD_AVIS

typedef struct {
	int id_avis;
	int id_citoyen;
	int id_parking;
	float note;
	char comment[100];
	int dr_jour;
	int dr_mois;
	int dr_annee;
	char motif[20];
	char type[3];
	char sexe;	
} Avis;
typedef struct{
	int id_parking;
	float note;
	int n;	
} tAvis;

int ajouter_avis(char * fileName, Avis c);
int modifier_avis(char *fileName, int id_m, Avis c_new);
int supprimer_avis(char *fileName, int id_s);
Avis chercher_avis(char * fileName,int id);
int trier_par_note(char* filename,char* filename2);
int super_chercher_avis(char *fileName, char *fileName2, int id_avis, int bid_avis, int id_citoyen, int bid_citoyen, int id_parking, int bid_parking);


#endif // BDD_AVIS
