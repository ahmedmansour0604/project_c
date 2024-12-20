#ifndef CRUD_H
#define CRUD_H
#include <gtk/gtk.h>

typedef struct
{
    int id_sc;
    char nom_sc[100];
    char description[255];
    int tarif_sc;
    char parking_associe[255] ;
    char disponibilte[5];  
    int hh;
    int mm ; 
    int ss ;
}service;


//76int ajouter_sc_reservation(char * fileName, reservation p );
int ajouter_service(char * fileName, service s) ; 
int modifier_service(char * fileName, service m);
int supprimer_service(char * fileName, int id_sc) ;
service rechercher_service(char * fileName, int id_sc);
//int afficher_service(char * fileName, int id_sc);
int affecter_service( char * fileName, char * fileName1, int id_res, int id_sc);
void afficher_servicee(const char* filename, GtkWidget *liste);
void vider_service(GtkWidget *liste);


typedef struct
{
    int j;
    int m;
    int a;
}date;                              

typedef struct
{
    int cin_a;
    char nom[50];
    char prenom[50];
    char adresse[100]; // Changed from char to char array
    char e_mail[100];  // Changed from char to char array
    float salaire;
    int sexe;  // Fixed typo from sex to sexe
    int experience;
    int parking;
    date naissance;  // Corrected Date to date
}agent;


int ajouter_agent(char * fileName, agent a);
void afficheragent(const char* filename, GtkWidget *liste);
void vider_agent(GtkWidget *liste);
//int afficher_agent(char * filename, int cin_a);
int modifier_agent(char *fileName, int id_a, agent m);

int supprimer_agent(char * fileName, int cin_a);
agent rechercher_agent(char * fileName, int cin_a);
void afficherhistorique(char *filename,char *filename2,int cin_a, int j, int m, int a);
void afficheragentsansparking(const char* filename, GtkWidget *liste);
int modifier_agent1(char *fileName, agent m);


#endif // BDD_CITOYEN



