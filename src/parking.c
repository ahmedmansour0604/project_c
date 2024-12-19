#include <stdio.h>
#include <string.h>
#include "parking.h"

int genererID(const char* counterFile)
{
    FILE *file = fopen(counterFile, "r");
    int id = 1;
    if (file != NULL)
    {
        fscanf(file, "%d", &id);
        fclose(file);
        id++;
    }
    else
    {
        printf("Error: Could not open '%s' to read the last ID.\n", counterFile);
    }

    file = fopen(counterFile, "w");
    if (file != NULL)
    {
        fprintf(file, "%d", id);
        fclose(file);
    }
    else
    {
        printf("Error: Could not open '%s' to write the new ID.\n", counterFile);
    }
    return id;
}

void ajouterParking(const char *filename, Parking p)
{
    char countertxt[] = "counter.txt";
    p.id = genererID(countertxt);
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Error: Could not open the file '%s' for appending.\n", filename);
        return;
    }

    fprintf(file, "%d,%d,%s,%s,%s,%d,%d,%d,%c,%c,%d,%d\n", p.id,p.id_agent,p.nom,p.region, p.adresse, p.nbetages, p.numero_de_telephone, p.tarif, p.est_couvert, p.supporte_pour_handicappe, p.capacite, p.place_disponible);
    fclose(file);
}


void modifierParking(const char *filename, int id, Parking p)
{
    FILE *file = fopen(filename, "r+");
    if (!file)
    {
        printf("Error: Could not open the file '%s' for reading and writing.\n", filename);
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp)
    {
        printf("Error: Could not open the temporary file for writing.\n");
        fclose(file);
        return;
    }

    Parking ptemp;
    int found = 0;

    while (fscanf(file, "%d,%d,%99[^,],%99[^,],%99[^,],%d,%d,%d,%c,%c,%d,%d\n", &ptemp.id, &ptemp.id_agent,ptemp.nom, ptemp.region, ptemp.adresse, &ptemp.nbetages, &ptemp.numero_de_telephone, &ptemp.tarif, &ptemp.est_couvert, &ptemp.supporte_pour_handicappe, &ptemp.capacite, &ptemp.place_disponible) != EOF)
    {
        if (ptemp.id == id)
        {
            found = 1;
            fprintf(temp, "%d,%d,%s,%s,%s,%d,%d,%d,%c,%c,%d,%d\n",ptemp.id,p.id_agent,p.nom, p.region, p.adresse, p.nbetages, p.numero_de_telephone, p.tarif, p.est_couvert, p.supporte_pour_handicappe, p.capacite, p.place_disponible);
        }
        else
        {
            fprintf(temp, "%d,%d,%s,%s,%s,%d,%d,%d,%c,%c,%d,%d\n", ptemp.id,ptemp.id_agent,ptemp.nom, ptemp.region, ptemp.adresse, ptemp.nbetages, ptemp.numero_de_telephone, ptemp.tarif, ptemp.est_couvert, ptemp.supporte_pour_handicappe, ptemp.capacite, ptemp.place_disponible);
        }
    }

    fclose(file);
    fclose(temp);

    if (found)
    {
        remove(filename);
        rename("temp.txt", filename);
    }
    else
    {
        printf("Error: Parking with ID %d not found.\n", id);
        remove("temp.txt");
    }
}


void supprimerParking(const char *filename, int id)
{
    FILE *file = fopen(filename, "r+");
    if (!file)
    {
        printf("Error: Could not open the file '%s' for reading and writing.\n", filename);
        return;
    }

    FILE *temp1 = fopen("temp1.txt", "w");
    if (!temp1)
    {
        printf("Error: Could not open the temporary file for writing.\n");
        fclose(file);
        return;
    }

    Parking ptemp;
    int found = 0;

    while (fscanf(file, "%d,%d,%99[^,],%99[^,],%99[^,],%d,%d,%d,%c,%c,%d,%d\n", &ptemp.id,&ptemp.id_agent,ptemp.nom, ptemp.region, ptemp.adresse, &ptemp.nbetages, &ptemp.numero_de_telephone, &ptemp.tarif, &ptemp.est_couvert, &ptemp.supporte_pour_handicappe, &ptemp.capacite, &ptemp.place_disponible) != EOF)
    {
        if (ptemp.id != id)
        {
            fprintf(temp1, "%d,%d,%s,%s,%s,%d,%d,%d,%c,%c,%d,%d\n", ptemp.id,ptemp.id_agent,ptemp.nom, ptemp.region, ptemp.adresse, ptemp.nbetages, ptemp.numero_de_telephone, ptemp.tarif, ptemp.est_couvert, ptemp.supporte_pour_handicappe, ptemp.capacite, ptemp.place_disponible);
        }
        else
        {
            found = 1;
        }
    }

    fclose(temp1);
    fclose(file);

    if (found)
    {
        remove(filename);
        rename("temp1.txt", filename);
    }
    else
    {
        printf("Error: Parking with ID %d not found.\n", id);
        remove("temp1.txt");
    }
}









Parking rechercherParking(const char* filename, int id)
{
	FILE *file=fopen(filename,"r+");
	Parking p;
	if (file==NULL)
	{
		printf("Error: Could not open the file '%s' for reading.\n", filename);
        	Parking empty = {0};
        	return empty;
	}
	while (fscanf(file,"%d,%d,%99[^,],%99[^,],%99[^,],%d,%d,%d,%c,%c,%d,%d\n", &p.id, &p.id_agent,p.nom, p.region, p.adresse, &p.nbetages, &p.numero_de_telephone, &p.tarif, &p.est_couvert, 			   &p.supporte_pour_handicappe, &p.capacite, &p.place_disponible)!=EOF)
	{
		if (p.id==id)
		{
			fclose(file);
            		return p;
		}
	}
	fclose(file);
    	printf("Error: Parking with ID %d not found.\n", id);
    	Parking empty = {0};
    	return empty;



}








void rechercherParkingParRegion(const char* filename, const char* region)
{
	FILE *file=fopen(filename,"r+");
	FILE *par_region=fopen("parregion.txt","a");
	Parking p;
	if (file==NULL)
	{
		printf("Error: Could not open the file '%s' for reading.\n", filename);
        	
	}
	if (!par_region)
    	{
        	printf("Error: Could not open the temporary file for writing.\n");
        	fclose(file);
        	return;
   	}
	while (fscanf(file, "%d,%d,%99[^,],%99[^,],%99[^,],%d,%d,%d,%c,%c,%d,%d\n", &p.id, &p.id_agent,p.nom, p.region, p.adresse, &p.nbetages, &p.numero_de_telephone, &p.tarif, &p.est_couvert, &p.supporte_pour_handicappe, &p.capacite, &p.place_disponible) != EOF)
    	{
        	if (strcmp(p.region, region) == 0)
        	{
            		fprintf(par_region, "%d,%d,%s,%s,%s,%d,%d,%d,%c,%c,%d,%d\n", p.id, p.id_agent,p.nom, p.region, p.adresse, p.nbetages, p.numero_de_telephone, p.tarif, p.est_couvert, p.supporte_pour_handicappe, p.capacite, p.place_disponible);
        	}
    	}

	
	fclose(file);
    	fclose(par_region);
    	
    	
}




void rechercherParkingParNom(const char* filename, const char* nom)
{



	FILE *file=fopen(filename,"r+");
	FILE *par_nom=fopen("parnom.txt","a");
	Parking p;
	if (file==NULL)
	{
		printf("Error: Could not open the file '%s' for reading.\n", filename);
        	
	}
	if (!par_nom)
    	{
        	printf("Error: Could not open the temporary file for writing.\n");
        	fclose(file);
        	return;
   	}
	while (fscanf(file, "%d,%d,%99[^,],%99[^,],%99[^,],%d,%d,%d,%c,%c,%d,%d\n", &p.id, &p.id_agent,p.nom, p.region, p.adresse, &p.nbetages, &p.numero_de_telephone, &p.tarif, &p.est_couvert, &p.supporte_pour_handicappe, &p.capacite, &p.place_disponible) != EOF)
    	{
        	if (strcmp(p.nom,nom) == 0)
        	{
            		fprintf(par_nom, "%d,%d,%s,%s,%s,%d,%d,%d,%c,%c,%d,%d\n", p.id, p.id_agent,p.nom, p.region, p.adresse, p.nbetages, p.numero_de_telephone, p.tarif, p.est_couvert, p.supporte_pour_handicappe, p.capacite, p.place_disponible);
        	}
    	}

	
	fclose(file);
    	fclose(par_nom);
    	
    	
}













