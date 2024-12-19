#ifndef PARKING_H
#define PARKING_H


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

#endif

