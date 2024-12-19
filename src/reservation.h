#ifndef RESERVATION_H_INCLUDED
#define RESERVATION_H_INCLUDED
#include <stdio.h>

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
    char mdp;//e = espece ou c = cash
    int id_ser;
}reservation;

int ajouter_reservation(char * fileName, reservation p) ; // cbon
int affichier_reservation(char * fileName, reservation p) ;//
int modifier_reservation(char * fileName, int id_res ,reservation p_n);//
int supprimer_reservation(char * fileName, int id_res) ;//cbon²
reservation rechercher_reservation(char * fileName, int id_res);//cbon
// int ajecter_reservation(char * file name, int id_res);

//void ajouter_service();   
//int verifIDs(int id_sc);//
//int verifIDp(int id_pk);//


#endif

