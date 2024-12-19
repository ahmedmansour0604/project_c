#include <stdio.h>
#include "reservation.h"


int ajouter_reservation(char * fileName, reservation p )
{
    FILE * f=fopen(fileName, "a");
    if(f!=NULL)
    {
        fprintf(f,"%d %d %d %s %c %d %d %d %d %d %c %d\n",p.id_res, p.id_cl, p.id_pk, p.nep, p.h_f, p.id_mt, p.jdr, p.mdr, p.adr, p.drr, p.mdp, p.id_ser);
        fclose(f);
        return 1;
    }
    else return 0;
}

int affichier_reservation(char * fileName, reservation p)//cbon
{
    FILE * f=fopen(fileName, "a");
    if(f!=NULL)
    {
        printf("%d %d %d %s %c %d %d %d %d %d %c %d\n",p.id_res, p.id_cl, p.id_pk, p.nep, p.h_f, p.id_mt, p.jdr, p.mdr, p.adr, p.drr, p.mdp, p.id_ser);
        fclose(f);
        return 1;
    }
    else return 0;
}



int modifier_reservation(char *fileName, int id_res,reservation p_n){
    int success=0;
    reservation p;
    FILE *f1=fopen(fileName,"r");
    FILE *f2=fopen("modifier_resveration.txt","w");
    if(f1!=NULL && f2!=NULL){
        while(fscanf(f1,"%d %d %d %s %c %d %d %d %d %d %c %d\n",&p.id_res, &p.id_cl, &p.id_pk, p.nep, &p.h_f, &p.id_mt, &p.jdr, &p.mdr, &p.adr, &p.drr, &p.mdp, &p.id_ser)!=EOF){
            if (p.id_res==id_res){
                fprintf(f2,"%d %d %d %s %c %d %d %d %d %d %c %d\n",p.id_res, p_n.id_cl, p_n.id_pk, p_n.nep, p_n.h_f, p_n.id_mt, p_n.jdr, p_n.mdr, p_n.adr, p_n.drr, p_n.mdp, p_n.id_ser);
                success++;
            }
            else {
                fprintf(f2,"%d %d %d %s %c %d %d %d %d %d %c %d\n",p.id_res, p.id_cl, p.id_pk, p.nep, p.h_f, p.id_mt, p.jdr, p.mdr, p.adr, p.drr, p.mdp, p.id_ser);
            }
        }
    }
    fclose(f1);
    fclose(f2);
    remove(fileName);
    rename("modifier_resveration.txt", fileName);
    return success;
}


reservation rechercher_reservation(char * fileName,int id_res){
    FILE *f;
    reservation p;
    int success=0;
    f=fopen(fileName,"r");
    
    if(f!=NULL){
        while (success==0 && fscanf(f,"%d %d %d %s %c %d %d %d %d %d %c %d\n",&p.id_res, &p.id_cl, &p.id_pk, p.nep, &p.h_f, &p.id_mt, &p.jdr, &p.mdr, &p.adr, &p.drr, &p.mdp, &p.id_ser)!=EOF){
            if(p.id_res == id_res){

 success=1;
        }
    }
}
    fclose(f);
    if(success==0){
        p.id_res=-1;
    }
    return p;
}



int supprimer_reservation(char * fileName, int id_res)
{
    int tr=0;
    reservation p;
    FILE * f=fopen(fileName, "r");
    FILE * f2=fopen("supprimer.txt", "a");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%d %d %d %s %c %d %d %d %d %d %c %d\n",&p.id_res, &p.id_cl, &p.id_pk, p.nep, &p.h_f,&p.id_mt, &p.jdr, &p.mdr, &p.adr, &p.drr, &p.mdp, &p.id_ser)!=EOF)
        {
            if(p.id_res == id_res)
                tr=1;
            else
                fprintf(f2,"%d %d %d %s %c %d %d %d %d %d %c %d\n",p.id_res, p.id_cl, p.id_pk, p.nep, p.h_f, p.id_mt, p.jdr, p.mdr, p.adr, p.drr, p.mdp, p.id_ser);
        }
    }
else printf("ERREUR\n");
    fclose(f);
    fclose(f2);
    remove(fileName);
    rename("supprimer.txt", fileName);
    return tr;
}



