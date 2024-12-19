#include "avis.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#define MAX_RECORDS 100

int ajouter_avis(char * fileName, Avis c){
    int id=1;
    FILE *f=fopen(fileName,"a+");
    Avis t;
    if(f!=NULL){
        while(fscanf(f,"%d %d %d %f %s %d %d %d %s %s %c\n",&t.id_avis,&t.id_citoyen,&t.id_parking,&t.note,t.comment,&t.dr_jour,&t.dr_mois,&t.dr_annee,t.motif,t.type,&t.sexe)!=EOF){
            id=t.id_avis+1;
        }
    }
    fclose(f);
    f=fopen(fileName,"a");
    if(f!=NULL){
        fprintf(f,"%d %d %d %f %s %d %d %d %s %s %c\n",id,c.id_citoyen,c.id_parking,c.note,c.comment,c.dr_jour,c.dr_mois,c.dr_annee,c.motif,c.type,c.sexe);
        fclose(f);
        return 1;
    }
    else return 0;
}

int modifier_avis(char *fileName, int id_m, Avis c_new){
    int success=0;
    Avis c;
    FILE *f1=fopen(fileName,"r");
    FILE *f2=fopen("temp.avis.modifier","w");
    if(f1!=NULL && f2!=NULL){
        while(fscanf(f1,"%d %d %d %f %s %d %d %d %s %s %c\n",&c.id_avis,&c.id_citoyen,&c.id_parking,&c.note,c.comment,&c.dr_jour,&c.dr_mois,&c.dr_annee,c.motif,c.type,&c.sexe)!=EOF){
            if (c.id_avis==id_m){
                fprintf(f2,"%d %d %d %f %s %d %d %d %s %s %c\n",c.id_avis,c_new.id_citoyen,c_new.id_parking,c_new.note,c_new.comment,c_new.dr_jour,c_new.dr_mois,c_new.dr_annee,c_new.motif,c_new.type,c_new.sexe);
                success++;
            }
            else {
                fprintf(f2,"%d %d %d %f %s %d %d %d %s %s %c\n",c.id_avis,c.id_citoyen,c.id_parking,c.note,c.comment,c.dr_jour,c.dr_mois,c.dr_annee,c.motif,c.type,c.sexe);
            }
        }
    }
    fclose(f1);
    fclose(f2);
    remove(fileName);
    rename("temp.avis.modifier", fileName);
    return success;
}

int supprimer_avis(char *fileName, int id_s){
    int success=0;
    Avis c;
    FILE *f1=fopen(fileName,"r");
    FILE *f2=fopen("temp.avis.supprimer","w");
    if(f1!=NULL && f2!=NULL){
        while(fscanf(f1,"%d %d %d %f %s %d %d %d %s %s %c\n",&c.id_avis,&c.id_citoyen,&c.id_parking,&c.note,c.comment,&c.dr_jour,&c.dr_mois,&c.dr_annee,c.motif,c.type,&c.sexe)!=EOF){
            if (c.id_avis==id_s){
                success++;
            }
            else {
                fprintf(f2,"%d %d %d %f %s %d %d %d %s %s %c\n",c.id_avis,c.id_citoyen,c.id_parking,c.note,c.comment,c.dr_jour,c.dr_mois,c.dr_annee,c.motif,c.type,c.sexe);
            }
        }
    }
    fclose(f1);
    fclose(f2);
    remove(fileName);
    rename("temp.avis.supprimer", fileName);
    return success;
}

Avis chercher_avis(char * fileName,int id_c){
    Avis c;
    int success=0;
    FILE *f=fopen(fileName,"r");
    if(f!=NULL){
        while (success==0 && fscanf(f,"%d %d %d %f %s %d %d %d %s %s %c\n",&c.id_avis,&c.id_citoyen,&c.id_parking,&c.note,c.comment,&c.dr_jour,&c.dr_mois,&c.dr_annee,c.motif,c.type,&c.sexe)!=EOF){
            if(c.id_avis == id_c) success=1;
        }
    }
    fclose(f);
    if(success==0){
        c.id_avis=-1;
    }
    return c;
}


int tribulles(tAvis T[],int n){//tri a bulles pour les parking selon les notes
	int i,permut;
	tAvis aux;
	do
	{
		permut= 0;
		for(i=0;i<n-1;i++)
		{
			if(T[i].note<T[i+1].note)
			{
				aux=T[i];
				T[i]=T[i+1];
				T[i+1]=aux;
				permut=1;
			}
		}
	} while(permut==1);
	return 1;
}

int longuer_bdd(char* filename)//calculer le nombres d'avis total dans la base de donnees
{
	int l=0;
    FILE *f=fopen(filename,"a+");
    Avis t;
    if(f!=NULL){
        while(fscanf(f,"%d %d %d %f %s %d %d %d %s %s %c\n",&t.id_avis,&t.id_citoyen,&t.id_parking,&t.note,t.comment,&t.dr_jour,&t.dr_mois,&t.dr_annee,t.motif,t.type,&t.sexe)!=EOF){
            l++;
        }
    }
    else return -1;
    fclose(f);
	return l;
	
}

int trier_par_note(char* filename,char* filename2)
{
int i,j,t;
int n2=0;//longueur T2
int n=longuer_bdd(filename);//longueur T

tAvis a;

Avis *T=malloc(n*sizeof(Avis));//tableau des avis (vide)
tAvis *T2=malloc(n*sizeof(tAvis));//tableau a manipuler (vide)

FILE *f=fopen(filename,"a+");
    if(f!=NULL){
        for (i=0;i<n;i++){//remplissage des avis dans T
        	fscanf(f,"%d %d %d %f %s %d %d %d %s %s %c\n",&T[i].id_avis,&T[i].id_citoyen, &T[i].id_parking,&T[i].note,T[i].comment,&T[i].dr_jour, &T[i].dr_mois,&T[i].dr_annee,T[i].motif, T[i].type, &T[i].sexe);
        	}
        }
    else return -1;
    fclose(f);
    
	for (i=0;i<n;i++){//remplissage de T vers T2 sans redoublant et avec sommation des notes et nombres
		t=0;
		for (j=0;j<n2&&t==0;j++){//si l'element existe addition de note et nombre
			if(T[i].id_parking==T2[j].id_parking){
				T2[j].note+=T[i].note;
				T2[j].n++;
				t=1;
			}
		}
		if(t==0){//si l'element n'existe pas creation d'une nouvelle case dans T2
			a.note=T[i].note;
			a.id_parking=T[i].id_parking;
			a.n=1;
			T2[n2]=a;
			n2++;
		}
	}
	for (j=0;j<n2;j++){//calcule de la note finale par division de la somme des notes par le nombre de notes
		T2[j].note/=T2[j].n;
	}
	tribulles(T2,n2);//tri par la fonction pour afficher les parking selon les notes
	f=fopen(filename2,"w");//remplissage d'un nouveau fichier
    	for (j=0;j<n2;j++){
    		fprintf(f,"%d %d %f\n",T2[j].id_parking,T2[j].n,T2[j].note);
    	}
    	fclose(f);
	free(T);
	free(T2);
}
int super_chercher_avis(char *fileName, char *fileName2, int id_avis, int bid_avis, int id_citoyen, int bid_citoyen, int id_parking, int bid_parking)
{
    Avis c;
    char temp[50],temp2[150];
    FILE *f=fopen(fileName,"r");
    FILE *f2=fopen(fileName2,"w");
    int res;
    if(f!=NULL){
        while (fscanf(f,"%d %d %d %f %s %d %d %d %s %s %c\n",&c.id_avis,&c.id_citoyen,&c.id_parking,&c.note,c.comment,&c.dr_jour,&c.dr_mois,&c.dr_annee,c.motif,c.type,&c.sexe)!=EOF){
            printf("%d %d %d %f %s %d %d %d %s %s %c\n",c.id_avis,c.id_citoyen,c.id_parking,c.note,c.comment,c.dr_jour,c.dr_mois,c.dr_annee,c.motif,c.type,c.sexe);
            res=1;
            if(bid_avis)
            {
                sprintf(temp,"%d",id_avis);
                sprintf(temp2,"%d",c.id_avis);
                if(strstr(temp2,temp)==NULL) res=0;
            }
            if(bid_citoyen)
            {
                sprintf(temp,"%d",id_citoyen);
                sprintf(temp2,"%d",c.id_citoyen);
                if(strstr(temp2,temp)==NULL) res=0;
            }
            if(bid_parking)
            {
                sprintf(temp,"%d",id_parking);
                sprintf(temp2,"%d",c.id_parking);
                if(strstr(temp2,temp)==NULL) res=0;
            }
            if(res==1) fprintf(f2,"%d %d %d %f %s %d %d %d %s %s %c\n",c.id_avis,c.id_citoyen,c.id_parking,c.note,c.comment,c.dr_jour,c.dr_mois,c.dr_annee,c.motif,c.type,c.sexe);
        }
        fclose(f);
        fclose(f2);
    }
}//*/

