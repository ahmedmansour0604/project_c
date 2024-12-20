#ifndef RESERVATION_H_INCLUDED
#define RESERVATION_H_INCLUDED
#include <stdio.h>
#include <gtk/gtk.h>
#include "parking.h"

typedef struct
{
    int id_res;
    int id_cl;
    char nep[50];
    char h_f;
    int id_mt;
    int id_pk;
    int jdr;
    int mdr;
    int adr;
    int drr;
    char mdp;//e = espece ou c = carte
    int ser;
}reservation;

//int generation_idres(const char* counter_Res_File) ;
int ajouter_reservation(char * fileName, reservation p) ;
int ajouter_reservation2(char * fileName, reservation p );
int affichier_reservation( reservation p) ;
int modifier_reservation(char *fileName, int id_res ,reservation p_n);
int supprimer_reservation(char * fileName, int id_res) ;
reservation rechercher_reservation(char * fileName, int d);
void trier_parkings(Parking T[], int n);
//void affecter_reservation(char*filenamep, char*filenamer, int idparking ,int idres);
void afficher_reservation(const char *filename, GtkWidget *liste);
void ajouterParkingReservation(const char* filename, Parking p);

#endif
