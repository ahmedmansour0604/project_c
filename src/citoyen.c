#include "citoyen.h"

#include <stdio.h>
#include <string.h>

#include "reservation.h"
#include "parking.h"
#include "service.h"
//*/

int rep_space_udnder(char *p){
    while(*p!='\0'){
        if(*p==' '){
            *p='_';
        }
        p++;
    }
    return 0;
}

int rep_under_space(char *p){
    while(*p!='\0'){
        if(*p=='_'){
            *p=' ';
        }
        p++;
    }
    return 0;
}

int str_is_int(char * str){
	int i = 0;
	while(str[i]!='\0'){
		if(!(str[i]-'0'<10 && str[i]-'0'>=0)) return 0;
		i++;
	}
	return 1;
}

int str_to_int(char * str){
	int i = 0;
	int n = 0;
	while(str[i]!='\0'){
		n*=10;
		n+=str[i]-'0';
		i++;
	}
	return n;
}

int dernier_id_citoyen(char *filename)
{
    int id=1,temp;
    FILE *f=fopen(filename,"a+");
    Citoyen t;
    if(f!=NULL){
        do
        {
            temp=fscanf(f,"%d %s %s %s %d %s %c %d %d %d %s\n",&id,t.nom,t.prenom,t.email,&t.tele,t.adresse,&t.sexe,&t.dn_jour,&t.dn_mois,&t.dn_annee,t.municipalite);
            if(temp==0)
            {
                printf("Warning : Error while finding latest id!");
                return -1;
            }
        } while (temp!=EOF);
        fclose(f);
    }
    return id;
}

int ajouter_citoyen(char * fileName, Citoyen c){
    int id=dernier_id_citoyen(fileName)+1;
    FILE *f=fopen(fileName,"a");
    if(f!=NULL){
        fprintf(f,"%d %s %s %s %d %s %c %d %d %d %s\n",id,c.nom,c.prenom,c.email,c.tele,c.adresse,c.sexe,c.dn_jour,c.dn_mois,c.dn_annee,c.municipalite);
        fclose(f);
        return id;
    }
    else return 0;
}

int modifier_citoyen(char *fileName, int id_m, Citoyen c_new){
    int success=0;
    Citoyen c;
    FILE *f1=fopen(fileName,"r");
    FILE *f2=fopen("temp.citoyen.modifier","w");
    if(f1!=NULL && f2!=NULL){
        while(fscanf(f1,"%d %s %s %s %d %s %c %d %d %d %s\n",&c.id,c.nom,c.prenom,c.email,&c.tele,c.adresse,&c.sexe,&c.dn_jour,&c.dn_mois,&c.dn_annee,c.municipalite)!=EOF){
            if (c.id==id_m){
                fprintf(f2,"%d %s %s %s %d %s %c %d %d %d %s\n",c_new.id,c_new.nom,c_new.prenom,c_new.email,c_new.tele,c_new.adresse,c_new.sexe,c_new.dn_jour,c_new.dn_mois,c_new.dn_annee,c_new.municipalite);
                success=id_m;
            }
            else {
                fprintf(f2,"%d %s %s %s %d %s %c %d %d %d %s\n",c.id,c.nom,c.prenom,c.email,c.tele,c.adresse,c.sexe,c.dn_jour,c.dn_mois,c.dn_annee,c.municipalite);
            }
        }
    }
    fclose(f1);
    fclose(f2);
    remove(fileName);
    rename("temp.citoyen.modifier", fileName);
    return success;
}

int supprimer_citoyen(char *fileName, int id_s){
    int success=0;
    Citoyen c;
    FILE *f1=fopen(fileName,"r");
    FILE *f2=fopen("temp.citoyen.supprimer","w");
    if(f1!=NULL && f2!=NULL){
        while(fscanf(f1,"%d %s %s %s %d %s %c %d %d %d %s\n",&c.id,c.nom,c.prenom,c.email,&c.tele,c.adresse,&c.sexe,&c.dn_jour,&c.dn_mois,&c.dn_annee,c.municipalite)!=EOF){
            if (c.id==id_s){
                success=id_s;
            }
            else {
                fprintf(f2,"%d %s %s %s %d %s %c %d %d %d %s\n",c.id,c.nom,c.prenom,c.email,c.tele,c.adresse,c.sexe,c.dn_jour,c.dn_mois,c.dn_annee,c.municipalite);
            }
        }
    }
    fclose(f1);
    fclose(f2);
    remove(fileName);
    rename("temp.citoyen.supprimer", fileName);
    return success;
}

Citoyen chercher_citoyen(char * fileName,int id_c){
    FILE *f;
    Citoyen c;
    int success=0;
    f=fopen(fileName,"r");
    if(f!=NULL){
        while (success==0 && fscanf(f,"%d %s %s %s %d %s %c %d %d %d %s\n",&c.id,c.nom,c.prenom,c.email,&c.tele,c.adresse,&c.sexe,&c.dn_jour,&c.dn_mois,&c.dn_annee,c.municipalite)!=EOF){
            if(c.id == id_c) success=1;
        }
    }
    fclose(f);
    if(success==0){
        c.id=-1;
    }
    return c;
}

int super_chercher_citoyen(char *fileName, char *fileName2, int id, int bid, char nom[], int bnom, char prenom[], int bprenom, char email[], int bemail, int tele, int btele, char adresse[],int badresse)
{
    Citoyen c;
    char temp[50],temp2[150];
    FILE *f=fopen(fileName,"r");
    FILE *f2=fopen(fileName2,"w");
    int res;
    if(f!=NULL){
        while (fscanf(f,"%d %s %s %s %d %s %c %d %d %d %s\n",&c.id,c.nom,c.prenom,c.email,&c.tele,c.adresse,&c.sexe,&c.dn_jour,&c.dn_mois,&c.dn_annee,c.municipalite)!=EOF){
            printf("%d %s %s %s %d %s %c %d %d %d %s\n",c.id,c.nom,c.prenom,c.email,c.tele,c.adresse,c.sexe,c.dn_jour,c.dn_mois,c.dn_annee,c.municipalite);
            res=1;
            if(bid)
            {
                sprintf(temp,"%d",id);
                sprintf(temp2,"%d",c.id);
                if(strstr(temp2,temp)==NULL) res=0;
            }
            printf("%d %s %d %s %d %d\n",bid,temp,id,temp2,c.id,res);
            if(bnom)
            {
                if(strstr(c.nom,nom)==NULL) res=0;
            }
            if(bprenom)
            {
                if(strstr(c.prenom,prenom)==NULL) res=0;
            }
            if(bemail)
            {
                if(strstr(c.email,email)==NULL) res=0;
            }
            if(btele)
            {
                sprintf(temp,"%d",tele);
                sprintf(temp2,"%d",c.tele);
                if(strstr(temp2,temp)==NULL) res=0;
            }
            if(badresse)
            {
                if(strstr(c.adresse,adresse)==NULL) res=0;
            }
            if(res==1) fprintf(f2,"%d %s %s %s %d %s %c %d %d %d %s\n",c.id,c.nom,c.prenom,c.email,c.tele,c.adresse,c.sexe,c.dn_jour,c.dn_mois,c.dn_annee,c.municipalite);
        }
        fclose(f);
        fclose(f2);
    }
}


float calculer_facture_citoyen(char * basereservation,char * baseparking,char * baseservice,char * facture,int id_c,int mois,int annee){
	FILE *f = fopen(basereservation,"a+");
	/*FILE *fr = fopen("temp.facture.mois","w");
	fclose(fr);*/
	remove("temp.facture.mois");
	if (f==NULL /*|| fr==NULL*/) return -1;
	reservation p;
	float total=0;
    FILE *f2=fopen(facture,"w");
    if (f2==NULL) return -1;
	while(fscanf(f,"%d %d %d %s %c %d %d %d %d %d %c %d\n",&p.id_res, &p.id_cl, &p.id_pk, p.nep, &p.h_f, &p.id_mt, &p.jdr, &p.mdr, &p.adr, &p.drr, &p.mdp, &p.id_ser)!=EOF)
	{
		//printf("%d %d %d\n",p.id_cl==id_c, p.mdr==mois, p.adr==annee);
		if (p.id_cl==id_c && p.mdr==mois && p.adr==annee)
		{
			Parking par=rechercherParking(baseparking, p.id_pk);
			//printf("%d\n",par.tarif);
			total+=par.tarif*p.drr;
            fprintf(f2,"p %d %s %f\n",par.id,par.nom,(float)par.tarif);
			//ajouter_reservation("temp.facture.mois",p);
			if(p.id_ser!=0) {
				service s=rechercher_service(baseservice, p.id_ser);
				fprintf(f2,"s %d %s %f\n",s.id_sc,s.nom,s.tarif);
                //ajouter_service("temp.facture.mois",s) ;
				total+=s.tarif; 
			}
		}
	}
	fclose(f);
    fclose(f2);
	return total;
}


