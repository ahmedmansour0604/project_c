
#ifndef SERVICE_H_INCLUDED
#define SERVICE_H_INCLUDED
#include <stdio.h>

typedef struct
{
    int id_sc;
    char nom[100];
    char description[255];
    float tarif;
    int disponibilte; // nb de place pour verifier la disponibilité de service 
    int duree ;
}service;

int ajouter_service(char * fileName, service s) ; //
int modifier_service(char * fileName, service m );//
int supprimer_service(char * fileName, int id_sc) ;//
service rechercher_service(char * fileName, int id_sc);//
//int reservation_service (char * fileName, int id_res);//
#endif
