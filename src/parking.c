#include <stdio.h>
#include <string.h>
#include "parking.h"
#include "crud.h"
#include <ctype.h>
#include <gtk/gtk.h>


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
        printf("Erreur : Impossible d'ouvrir '%s' pour lire le dernier ID.\n", counterFile);
    }

    file = fopen(counterFile, "w");
    if (file != NULL)
    {
        fprintf(file, "%d", id);
        fclose(file);
    }
    else
    {
        printf("Erreur : Impossible d'ouvrir '%s' pour écrire le nouvel ID.\n", counterFile);
    }
    return id;
}

void ajouterParking(const char* filename, Parking p)
{
    char countertxt[] = "counter.txt";
    p.id = genererID(countertxt);
    p.id_agent=0;
    p.place_disponible=p.capacite;
    
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Erreur : Impossible d'ouvrir le fichier '%s' en mode ajout.\n", filename);
        return;
    }

    fprintf(file, "%d,%d,%s,%s,%s,%d,%d,%d,%c,%c,%d,%d\n", p.id, p.id_agent, p.nom, p.region, p.adresse, 
            p.nbetages, p.numero_de_telephone, p.tarif, p.est_couvert, p.supporte_pour_handicappe, p.capacite, p.place_disponible);


    

    fclose(file);
}





/*
void afficherParkings(const char* filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Erreur: Impossible d'ouvrir le fichier '%s' en lecture.\n", filename);
        return;
    }

    Parking p;

   printf("ID | ID Agent | Nom | Region | Adresse | Nb Etages | Tel | Tarif | Couvert | Handicap | Capacite | Places Dispo | Services\n");
    printf("\n");

    while (fscanf(file, "%d,%d,%99[^,],%99[^,],%99[^,],%d,%d,%d,%c,%c,%d,%d\n", 
                   &p.id, &p.id_agent, p.nom, p.region, p.adresse, &p.nbetages, 
                   &p.numero_de_telephone, &p.tarif, &p.est_couvert, &p.supporte_pour_handicappe, 
                   &p.capacite, &p.place_disponible) != EOF)
    {

        

        printf("%d | %d | %s | %s | %s | %d | %d | %d | %c | %c | %d | %d\n", 
                p.id, p.id_agent, p.nom, p.region, p.adresse, p.nbetages, 
                p.numero_de_telephone, p.tarif, p.est_couvert, p.supporte_pour_handicappe, 
                p.capacite, p.place_disponible);
	
    }

    fclose(file);
}
*/










void modifierParking(const char* filename, int id, Parking p)
{
    FILE *file = fopen(filename, "r+");
    if (!file)
    {
        printf("Erreur : Impossible d'ouvrir le fichier '%s' en mode lecture/écriture.\n", filename);
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp)
    {
        printf("Erreur : Impossible d'ouvrir le fichier temporaire pour l'écriture.\n");
        fclose(file);
        return;
    }

    Parking ptemp;
    int found = 0;

    while (fscanf(file, "%d,%d,%99[^,],%99[^,],%99[^,],%d,%d,%d,%c,%c,%d,%d\n", &ptemp.id, &ptemp.id_agent, 
                ptemp.nom, ptemp.region, ptemp.adresse, &ptemp.nbetages, &ptemp.numero_de_telephone, &ptemp.tarif, 
                &ptemp.est_couvert, &ptemp.supporte_pour_handicappe, &ptemp.capacite, &ptemp.place_disponible) != EOF)
    {
        

        if (ptemp.id == id)
        {
            found = 1;
            fprintf(temp, "%d,%d,%s,%s,%s,%d,%d,%d,%c,%c,%d,%d\n", ptemp.id, p.id_agent, p.nom, p.region, p.adresse, 
                    p.nbetages, p.numero_de_telephone, p.tarif, p.est_couvert, p.supporte_pour_handicappe, p.capacite, p.place_disponible);
        
        }
        else
        {
            fprintf(temp, "%d,%d,%s,%s,%s,%d,%d,%d,%c,%c,%d,%d\n", ptemp.id, ptemp.id_agent, ptemp.nom, ptemp.region, 
                    ptemp.adresse, ptemp.nbetages, ptemp.numero_de_telephone, ptemp.tarif, ptemp.est_couvert, 
                    ptemp.supporte_pour_handicappe, ptemp.capacite, ptemp.place_disponible);
            
        }
    }

    fclose(file);
    fclose(temp);

    if (found)
    {
        remove(filename);
        printf(" Le parking %d a été modifié avec succès.\n", id);
        rename("temp.txt", filename);
    }
    else
    {
        printf("Erreur : Le parking %d est introuvable.\n", id);
        remove("temp.txt");
    }
}

void supprimerParking(const char* filename, int id)
{
    
    FILE *file = fopen(filename, "r+");
    if (!file)
    {
        printf("Erreur : Impossible d'ouvrir le fichier '%s' en mode lecture/écriture.\n", filename);
        return;
    }

    FILE *temp1 = fopen("temp1.txt", "w");
    if (!temp1)
    {
        printf("Erreur : Impossible d'ouvrir le fichier temporaire pour l'écriture.\n");
        fclose(file);
        return;
    }

    Parking ptemp;
    int found = 0;

    while (fscanf(file, "%d,%d,%99[^,],%99[^,],%99[^,],%d,%d,%d,%c,%c,%d,%d\n", &ptemp.id, &ptemp.id_agent, 
                ptemp.nom, ptemp.region, ptemp.adresse, &ptemp.nbetages, &ptemp.numero_de_telephone, &ptemp.tarif, 
                &ptemp.est_couvert, &ptemp.supporte_pour_handicappe, &ptemp.capacite, &ptemp.place_disponible) != EOF)
    {
       

        if (ptemp.id != id)
        {
            fprintf(temp1, "%d,%d,%s,%s,%s,%d,%d,%d,%c,%c,%d,%d\n", ptemp.id, ptemp.id_agent, ptemp.nom, ptemp.region, 
                    ptemp.adresse, ptemp.nbetages, ptemp.numero_de_telephone, ptemp.tarif, ptemp.est_couvert, 
                    ptemp.supporte_pour_handicappe, ptemp.capacite, ptemp.place_disponible);
            
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
        printf("Erreur : Parking avec ID %d introuvable.\n", id);
        remove("temp1.txt");
	
    }
}

Parking rechercherParking(const char* filename, int id)
{
    FILE *file = fopen(filename, "r+");
    FILE *f2 = fopen("parid.txt", "w");
    Parking p;
    if (file == NULL)
    {
        printf("Erreur : Impossible d'ouvrir le fichier '%s' en mode lecture.\n", filename);
        Parking empty = {0};
        return empty;
    }

    while (fscanf(file, "%d,%d,%99[^,],%99[^,],%99[^,],%d,%d,%d,%c,%c,%d,%d\n", &p.id, &p.id_agent, p.nom, p.region, 
                   p.adresse, &p.nbetages, &p.numero_de_telephone, &p.tarif, &p.est_couvert, &p.supporte_pour_handicappe, 
                   &p.capacite, &p.place_disponible) != EOF)
    {
        

        if (p.id == id)
        {
	    fprintf(f2, "%d,%d,%s,%s,%s,%d,%d,%d,%c,%c,%d,%d\n", p.id, p.id_agent, p.nom, p.region, p.adresse, 
                    p.nbetages, p.numero_de_telephone, p.tarif, p.est_couvert, p.supporte_pour_handicappe, p.capacite, p.place_disponible);
           
	    fclose(file);
            fclose(f2);
	    return p;

        }
    }

    fclose(file);
    fclose(f2);
    
    printf("Erreur : Parking avec ID %d introuvable.\n", id);
    Parking empty = {-1};
    return empty;
}

void rechercherParkingParRegion(const char* filename, const char* region)
{
    FILE *file = fopen(filename, "r+");
    FILE *par_region = fopen("parregion.txt", "w");
    Parking p;
    if (file == NULL)
    {
        printf("Erreur : Impossible d'ouvrir le fichier '%s' en mode lecture.\n", filename);
        return;
    }
    if (!par_region)
    {
        printf("Erreur : Impossible d'ouvrir le fichier temporaire pour l'écriture.\n");
        fclose(file);
        return;
    }

    while (fscanf(file, "%d,%d,%99[^,],%99[^,],%99[^,],%d,%d,%d,%c,%c,%d,%d\n", &p.id, &p.id_agent, p.nom, p.region, 
                   p.adresse, &p.nbetages, &p.numero_de_telephone, &p.tarif, &p.est_couvert, &p.supporte_pour_handicappe, 
                   &p.capacite, &p.place_disponible) != EOF)
    {
        

        if (strcmp(p.region, region) == 0)
        {
            fprintf(par_region, "%d,%d,%s,%s,%s,%d,%d,%d,%c,%c,%d,%d\n", p.id, p.id_agent, p.nom, p.region, p.adresse, 
                    p.nbetages, p.numero_de_telephone, p.tarif, p.est_couvert, p.supporte_pour_handicappe, p.capacite, p.place_disponible);
            
        }
    }

    fclose(file);
    fclose(par_region);
    printf("Recherche terminée pour la région '%s'. Les résultats sont dans 'parregion.txt'.\n", region);
}



void rechercherParkingParNom(const char* filename, const char* nom)
{



	FILE *file=fopen(filename,"r+");
	FILE *par_nom=fopen("parnom.txt","w");
	Parking p;
	if (file==NULL)
	{
		printf("Erreur : Impossible d'ouvrir le fichier '%s' en mode lecture.\n", filename);
		return;
        	
	}
	if (!par_nom)
    	{
        	printf("Erreur : Impossible d'ouvrir le fichier temporaire pour l'écriture.\n");
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
	printf("Recherche terminée pour le nom '%s'. Les résultats sont dans 'parnom.txt'.\n", nom);
}

void rechercherParkingParNometRegion(const char* filename, const char* nom,const char* region)
{
	rechercherParkingParNom(filename,nom);
	rechercherParkingParRegion("parnom.txt",region);
	remove("parnom.txt");
        rename("parregion.txt","parnometregion.txt");
}


void affecteragent(const char* filenamep,char* filenamea,int idparking,int cinagent)
{
	Parking p ;
	p=rechercherParking(filenamep,idparking);
	if (p.id!=0)
	{
		p.id_agent=cinagent;
		modifierParking(filenamep,idparking, p);
	} else return;
	agent a;

	a=rechercher_agent(filenamea,cinagent);
	if(a.cin_a!=-1)
	{
		a.parking=p.id;
		modifier_agent1(filenamea,a);
	}
}







void vider(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    
    char id[10], id_agent[10], nom[100], region[100], adresse[100];
    char nbetages[10], numero_de_telephone[10], tarif[10];
    char est_couvert, supporte_pour_handicappe;
    char capacite[10], place_disponible[10];

    // Open the parking file
    FILE *f = fopen("parking.txt", "r");
    if (!f) {
        perror("Error opening file");
        return;
    }

    // Get the model for the tree view
    store = gtk_tree_view_get_model(liste);
    if (store == NULL) {
        
        // Set up columns for the tree view
	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID_AGENT", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("NOM", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("REGION", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ADRESSE", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("NB_ETAGES", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("NUMERO_DE_TELEPHONE", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("TARIF", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("COUVERT", renderer, "text", 8, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("SUPPORTE_POUR_HANDICAPE", renderer, "text", 9, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("CAPACITE", renderer, "text", 10, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("PLACES_DISPONIBLES", renderer, "text", 11, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    }




        store = gtk_list_store_new(12, 
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_BOOLEAN, G_TYPE_BOOLEAN, 
                                   G_TYPE_STRING, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));

}









void afficher_parking(const char* filename, GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;


    int id, id_agent, nbetages, numero_de_telephone, tarif, capacite, place_disponible;
    char nom[100], region[100], adresse[100];
    char est_couvert, supporte_pour_handicappe;


    char id_str[10], id_agent_str[10], nbetages_str[10], numero_de_telephone_str[15];
    char tarif_str[10], capacite_str[10], place_disponible_str[10];

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

    if (store == NULL) {

        store = gtk_list_store_new(12, 
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_BOOLEAN, G_TYPE_BOOLEAN, 
                                   G_TYPE_STRING, G_TYPE_STRING);


        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID_AGENT", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("NOM", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("REGION", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ADRESSE", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("NB_ETAGES", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("NUMERO_DE_TELEPHONE", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("TARIF", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("COUVERT", renderer, "text", 8, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("SUPPORTE_POUR_HANDICAPE", renderer, "text", 9, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("CAPACITE", renderer, "text", 10, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("PLACES_DISPONIBLES", renderer, "text", 11, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);


        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    }


    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        g_print("Erreur lors de l'ouverture du fichier: %s\n", filename);
        return;
    }


    while (fscanf(f, "%d,%d,%99[^,],%99[^,],%99[^,],%d,%d,%d,%c,%c,%d,%d\n",
                  &id, &id_agent, nom, region, adresse,
                  &nbetages, &numero_de_telephone, &tarif,
                  &est_couvert, &supporte_pour_handicappe,
                  &capacite, &place_disponible) == 12) {


        sprintf(id_str, "%d", id);
        sprintf(id_agent_str, "%d", id_agent);
        sprintf(nbetages_str, "%d", nbetages);
        sprintf(numero_de_telephone_str, "%d", numero_de_telephone);
        sprintf(tarif_str, "%d", tarif);
        sprintf(capacite_str, "%d", capacite);
        sprintf(place_disponible_str, "%d", place_disponible);


        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, id_str,
                           1, id_agent_str,
                           2, nom,
                           3, region,
                           4, adresse,
                           5, nbetages_str,
                           6, numero_de_telephone_str,
                           7, tarif_str,
                           8, (est_couvert == '1'),
                           9, (supporte_pour_handicappe == '1'),
                           10, capacite_str,
                           11, place_disponible_str,
                           -1);
    }

    fclose(f);
}

void afficher_parkingsansagent(const char* filename, GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;


    int id, id_agent, nbetages, numero_de_telephone, tarif, capacite, place_disponible;
    char nom[100], region[100], adresse[100];
    char est_couvert, supporte_pour_handicappe;


    char id_str[10], id_agent_str[10], nbetages_str[10], numero_de_telephone_str[15];
    char tarif_str[10], capacite_str[10], place_disponible_str[10];

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

    if (store == NULL) {

        store = gtk_list_store_new(12, 
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_BOOLEAN, G_TYPE_BOOLEAN, 
                                   G_TYPE_STRING, G_TYPE_STRING);


        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID_AGENT", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("NOM", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("REGION", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ADRESSE", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("NB_ETAGES", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("NUMERO_DE_TELEPHONE", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("TARIF", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("COUVERT", renderer, "text", 8, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("SUPPORTE_POUR_HANDICAPE", renderer, "text", 9, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("CAPACITE", renderer, "text", 10, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("PLACES_DISPONIBLES", renderer, "text", 11, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);


        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    }


    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        g_print("Erreur lors de l'ouverture du fichier: %s\n", filename);
        return;
    }


    while (fscanf(f, "%d,%d,%99[^,],%99[^,],%99[^,],%d,%d,%d,%c,%c,%d,%d\n",
                  &id, &id_agent, nom, region, adresse,
                  &nbetages, &numero_de_telephone, &tarif,
                  &est_couvert, &supporte_pour_handicappe,
                  &capacite, &place_disponible) == 12) {
	if (id_agent==0){


		sprintf(id_str, "%d", id);
		sprintf(id_agent_str, "%d", id_agent);
		sprintf(nbetages_str, "%d", nbetages);
		sprintf(numero_de_telephone_str, "%d", numero_de_telephone);
		sprintf(tarif_str, "%d", tarif);
		sprintf(capacite_str, "%d", capacite);
		sprintf(place_disponible_str, "%d", place_disponible);


		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter,
		                   0, id_str,
		                   1, id_agent_str,
		                   2, nom,
		                   3, region,
		                   4, adresse,
		                   5, nbetages_str,
		                   6, numero_de_telephone_str,
		                   7, tarif_str,
		                   8, (est_couvert == '1'),
		                   9, (supporte_pour_handicappe == '1'),
		                   10, capacite_str,
		                   11, place_disponible_str,
    			                   -1);
    	}
    }

    fclose(f);
}






































/*

void vider_agent(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;

    store = gtk_tree_view_get_model(GTK_TREE_VIEW(liste));
    if (!store) {

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Prénom", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Adresse", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Salaire", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Expérience", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Parking", renderer, "text", 8, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date de Naissance", renderer, "text", 9, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }


    store = gtk_list_store_new(10, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
}

void afficheragent(const char* filename, GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeIter iter;
    GtkListStore *store;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
    if (!store) {
        vider(liste);  
        store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
    }

    FILE *f = fopen(filename, "r");
    if (!f) {
        g_print("Erreur lors de l'ouverture du fichier: %s\n", filename);
        return;
    }

    char line[512];
    agent a;
    char naissance_str[20];

    while (fgets(line, sizeof(line), f)) {
        sscanf(line, "%d %49s %49s %d:%d:%d %99s %99s %f %d %d %d",
               &a.cin_a, a.nom, a.prenom, &a.naissance.j, &a.naissance.m, &a.naissance.a,
               a.adresse, a.e_mail, &a.salaire, &a.sexe, &a.experience, &a.parking);

        sprintf(naissance_str, "%02d/%02d/%04d", a.naissance.j, a.naissance.m, a.naissance.a);

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, g_strdup_printf("%d", a.cin_a),
                           1, a.nom,
                           2, a.prenom,
                           3, a.adresse,
                           4, a.e_mail,
                           5, g_strdup_printf("%.2f", a.salaire),
                           6, (a.sexe == 1 ? "Homme" : "Femme"),
                           7, g_strdup_printf("%d", a.experience),
                           8, g_strdup_printf("%d", a.parking),
                           9, naissance_str,
                           -1);
    }

    fclose(f);
}


*/





