#ifndef PARKING_H
#define PARKING_H


typedef struct
{
    int j;
    int m;
    int a;
} date;                              

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
} agent;
typedef struct
{
	int id;
	int id_agent;
	char nom[100];
	char region[100];
	char adresse[100];
	int nbetages;
	int numero_de_telephone;
	int tarif;
	char est_couvert;
	char supporte_pour_handicappe;
	int capacite;
	int place_disponible;
}Parking;


void ajouterParking(const char* filename, Parking p);
void afficherParkings(const char* filename);
void modifierParking(const char* filename, int id, Parking p);
void supprimerParking(const char* filename, int id);
int genererID(const char* counterFile);
Parking rechercherParking(const char* filename, int id);
void rechercherParkingParRegion(const char* filename, const char* region);
void rechercherParkingParNom(const char* filename, const char* nom);
void afficherParkings(const char* filename);
void rechercherParkingParNometRegion(const char* filename, const char* nom,const char* region);
void affecteragent(const char* filenamep, char* filenamea,int idparking,int cinagent);




//agent
int ajouter_agent(char * fileName, agent a);
int afficher_agent(char * filename, int cin_a);
int modifier_agent(char * fileName, agent m);
int supprimer_agent(char * fileName, int cin_a);
agent rechercher_agent(char * fileName, int cin_a);
int historique_reservation(char * fileName, int cin_a);

#endif

