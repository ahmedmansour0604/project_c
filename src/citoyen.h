#ifndef BDD_CITOYEN
#define BDD_CITOYEN

typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    char email[50];
    int tele;
    char adresse[150];
    char sexe;
    int dn_jour,dn_mois,dn_annee;
    char municipalite[50];
} Citoyen;

int ajouter_citoyen(char * fileName, Citoyen c);
int modifier_citoyen(char *fileName, int id_m, Citoyen c_new);
int supprimer_citoyen(char *fileName, int id_s);
int dernier_id_citoyen(char *filename);
Citoyen chercher_citoyen(char * fileName,int id);
int super_chercher_citoyen(char *fileName,char *fileName2, int id, int bid, char nom[], int bnom, char prenom[], int bprenom, char email[], int bemail, int tele, int btele, char adresse[],int badresse);

float calculer_facture_citoyen(char * basereservation,char * baseparking,char * baseservice,char * facture,int id_c,int mois,int annee);
int rep_space_udnder(char *p);
int rep_under_space(char *p);
int str_is_int(char * str);
int str_to_int(char * str);

#endif // BDD_CITOYEN
