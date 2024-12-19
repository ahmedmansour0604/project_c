#include "service.h"
#include <string.h>
#include <stdio.h>

//fonction ajout
int ajouter_service(char * fileName, service s )
{
    FILE * f=fopen(fileName, "a");
    if(f!=NULL)
    {
        fprintf(f,"%d %s %s %f %d %d\n",s.id_sc, s.nom, s.description, s.tarif, s.disponibilte, s.duree);
        fclose(f);
        return 1;
    }
    else return 0;
}

//fonction modifier
int modifier_service( char * fileName, service m )
{
    int tr=0;
    service s;
    FILE * f=fopen(fileName, "r");
    FILE * f2=fopen("temp.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%d %s %s %f %d %d\n",&s.id_sc, s.nom, s.description, &s.tarif, &s.disponibilte, &s.duree)!=EOF)
        {
            if(s.id_sc != m.id_sc)
            {
		printf("test0");
                fprintf(f2,"%d %s %s %f %d %d\n",s.id_sc, s.nom, s.description, s.tarif, s.disponibilte, s.duree);
                tr=1;
            }
            else
                fprintf(f2,"%d %s %s %f %d %d \n",m.id_sc, m.nom, m.description, m.tarif, m.disponibilte, m.duree);
        }
    }
    fclose(f);
    fclose(f2);
    remove(fileName);
    rename("temp.txt", fileName);
    return tr;
}

//fonction supprimer
int supprimer_service(char * fileName, int id_sc)
{
    int tr=0;
    service s;
    FILE * f=fopen(fileName, "r");
    FILE * f2=fopen("corbeille.txt", "w");
    if(f!=NULL && f2!=NULL)
    {

        while(fscanf(f,"%d %s %s %f %d %d\n",&s.id_sc, s.nom, s.description, &s.tarif, &s.disponibilte, &s.duree)!=EOF)
        {
		printf("test");
            if(s.id_sc == id_sc)
                tr=1;
            else
                fprintf(f2,"%d %s %s %f %d %d\n",s.id_sc, s.nom, s.description, s.tarif, s.disponibilte, s.duree);
		
        }
/*for(int i=0 ;i<20;i++){
	printf("%d",fscanf(f,"%d %s %s %f %d %d\n",&s.id_sc, s.nom, s.description, &s.tarif, &s.disponibilte, &s.duree)==EOF);
}*/
    }
    fclose(f);
    fclose(f2);
    remove(fileName);
    rename("corbeille.txt", fileName);
    return tr;
}

  // fonction recherche
service rechercher_service(char * fileName, int id_sc) 
{
service s;
    int tr = 0;
    FILE * f=fopen(fileName, "r");
    if(f!=NULL)
    {
        while(tr==0 && fscanf(f,"%d %s %s %f %d %d\n",&s.id_sc, s.nom, s.description, &s.tarif, &s.disponibilte, &s.duree)!=EOF)
        {

		//printf("test_recherce");
            if(s.id_sc== id_sc)
                tr=1;
		//printf("test_recherce");
        }
    }
    fclose(f);
    if(tr==0)
	s.id_sc=0;
    return s;
}
