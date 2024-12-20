#include "crud.h"
#include "reservation.h"
#include "parking.h"
#include <gtk/gtk.h>
#include <stdio.h>


//fonction ajout
int ajouter_service(char * fileName, service s )
{
    
    FILE * f=fopen(fileName, "a+");

		printf("test 2\n");
    if(f!=NULL)
    {
        fprintf(f,"%d %s %s %d %s %s %d %d %d\n",s.id_sc, s.nom_sc, s.description, s.tarif_sc, s.parking_associe, s.disponibilte, s.hh, s.mm, s.ss);
        fclose(f);

		printf("test 3\n");        return s.id_sc;
    }
    else return -1;
}

//fonction modifier
int modifier_service( char * fileName, service m)
{
    int tr=0;
    service s;
    FILE * f=fopen(fileName, "r");
    FILE * f2=fopen("temp.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%d %s %s %d %s %s %d %d %d\n",&s.id_sc, s.nom_sc, s.description, &s.tarif_sc, s.parking_associe, s.disponibilte, &s.hh, &s.mm, &s.ss)!=EOF)
        {
            if(s.id_sc != m.id_sc)
            {
		printf("test0");
                fprintf(f2,"%d %s %s %d %s %s %d %d %d\n",s.id_sc, s.nom_sc, s.description, s.tarif_sc, s.parking_associe, s.disponibilte, s.hh, s.mm, s.ss);
                tr=1;
            }
            else
                fprintf(f2,"%d %s %s %d %s %s %d %d %d\n",s.id_sc, m.nom_sc, m.description, m.tarif_sc, m.parking_associe, m.disponibilte, m.hh, m.mm, m.ss);
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

        while(fscanf(f,"%d %s %s %d %s %s %d %d %d\n",&s.id_sc, s.nom_sc, s.description, &s.tarif_sc, s.parking_associe, s.disponibilte, &s.hh, &s.mm, &s.ss)!=EOF)
        {
		printf("test");
            if(s.id_sc == id_sc/* || strcmp(s.nom_sc, nom_sc) == 0*/)
                tr=1;
            else
                fprintf(f2,"%d %s %s %d %s %s %d %d %d\n",s.id_sc, s.nom_sc, s.description, s.tarif_sc, s.parking_associe, s.disponibilte, s.hh, s.mm, s.ss);
		
        }
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
    FILE * f=fopen(fileName, "r+");
    if(f!=NULL)
    {
        while(tr==0 && fscanf(f,"%d %s %s %d %s %s %d %d %d\n",&s.id_sc, s.nom_sc, s.description, &s.tarif_sc, s.parking_associe, s.disponibilte, &s.hh, &s.mm, &s.ss)!=EOF)
        {
		
            if(s.id_sc== id_sc )
                tr=1;
		
		//printf("%d",x);
		//break;
        }
    }
    fclose(f);
    if(tr==0) s.id_sc=-1;
    return s;
}


//fonction affecter un service 
int affecter_service( char * fileName, char * fileName1,  int id_res, int id_sc)
{
    int trs = 0;
    int trp = 0;
    reservation p; 
    service s;
    FILE * f=fopen(fileName, "a+");
    FILE * f2=fopen(fileName1, "r");
    if(f!=NULL && f2!=NULL)
    {
       while(fscanf(f,"%d ",&p.id_res)==1)
        {//printf("id reservation trouvée\n");
         if(p.id_res = id_res){
	printf("id reservation trouvée");		
	trp=1;
	return p.id_res; }
	else return 0;
	}
	while(fscanf(f2,"%d %s %s %d %s %s %d %d %d\n",&s.id_sc, s.nom_sc, s.description, &s.tarif_sc, s.parking_associe, s.disponibilte, &s.hh, &s.mm, &s.ss)!=EOF)
        {//printf("id service trouvée");
	if(s.id_sc = id_sc){
	printf("id service  trouvée");		
	trs=1;
	return s.id_sc; }
	else return 0;
	}
    if (trp == 1 && trs == 1)
    fprintf(f,"%s\n",p.ser);
    fclose(f);
    fclose(f2);
	}    
	return 0;
}


void vider_service(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;

    store = gtk_tree_view_get_model(GTK_TREE_VIEW(liste));
    if (!store) {
        // Define columns only once
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom Service", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Description", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Tarif", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Parking Associé", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Disponibilité", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Heure", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    // Initialize an empty list store with appropriate column types
    store = gtk_list_store_new(7, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
}

void afficher_servicee(const char* filename, GtkWidget *liste) {
    GtkTreeIter iter;
    GtkListStore *store;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
    if (!store) {
        vider_service(liste); // Initialize the tree view columns if not already initialized
        store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
    }

    FILE *f = fopen(filename, "r");
    if (!f) {
        g_print("Erreur lors de l'ouverture du fichier: %s\n", filename);
        return;
    }

    service s;
    char line[512];
    char heure_formatee[10]; // To store formatted hour (hh:mm:ss)

    while (fgets(line, sizeof(line), f)) {
        // Parse the line and fill the service structure
        sscanf(line, "%d %99s %254s %d %254s %4s %d %d %d",
               &s.id_sc, s.nom_sc, s.description, &s.tarif_sc, 
               s.parking_associe, s.disponibilte, &s.hh, &s.mm, &s.ss);

        // Format the hour
        sprintf(heure_formatee, "%02d:%02d:%02d", s.hh, s.mm, s.ss);

        // Append data to the GtkListStore
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, g_strdup_printf("%d", s.id_sc),
                           1, s.nom_sc,
                           2, s.description,
                           3, g_strdup_printf("%d", s.tarif_sc),
                           4, s.parking_associe,
                           5, s.disponibilte,
                           6, heure_formatee,
                           -1);
    }

    fclose(f);
}



//Agent

// Function to add an agent
int ajouter_agent(char * fileName, agent a)
{
    FILE * f = fopen(fileName, "a");
    a.parking = 0;
    if (f != NULL)
    {
        fprintf(f, "%d %s %s %d:%d:%d %s %s %f %d %d %d\n", a.cin_a, a.nom, a.prenom, a.naissance.j, a.naissance.m, a.naissance.a, a.adresse, a.e_mail, a.salaire, a.sexe, a.experience, a.parking);
        fclose(f);
        return 1;
    }
    else return 0;
}



// Function to modify an agent
int modifier_agent(char *fileName, int id_a, agent m)
{
    int tr = 0;
    agent a;
    m.parking=0;
    FILE * f = fopen(fileName, "r");
    FILE * f2 = fopen("temp.txt", "w");
    if (f != NULL && f2 != NULL)
    {
        while (fscanf(f, "%d %s %s %d:%d:%d %s %s %f %d %d %d\n", &a.cin_a, a.nom, a.prenom, &a.naissance.j, &a.naissance.m, &a.naissance.a, a.adresse, a.e_mail, &a.salaire, &a.sexe, &a.experience, &a.parking) != EOF)
        {
            if (id_a != a.cin_a)
            {
                fprintf(f2, "%d %s %s %d:%d:%d %s %s %f %d %d %d\n", a.cin_a, a.nom, a.prenom, a.naissance.j, a.naissance.m, a.naissance.a, a.adresse, a.e_mail, a.salaire, a.sexe, a.experience, a.parking);
            }
            else
            {
                fprintf(f2, "%d %s %s %d:%d:%d %s %s %f %d %d %d\n", a.cin_a, m.nom, m.prenom, m.naissance.j, m.naissance.m, m.naissance.a, m.adresse, m.e_mail, m.salaire, m.sexe, m.experience, m.parking);
                tr = 1;
            }
        }
    }
    fclose(f);
    fclose(f2);
    remove(fileName);
    rename("temp.txt", fileName);
    return tr;
}

// Function to delete an agent
int supprimer_agent(char *fileName, int cin_a)
{
    int tr = 0;
    agent a;
    FILE * f = fopen(fileName, "r");
    FILE * f2 = fopen("corbeille.txt", "w");
    if (f != NULL && f2 != NULL)
    {
        while (fscanf(f, "%d %s %s %d:%d:%d %s %s %f %d %d %d\n", &a.cin_a, a.nom, a.prenom, &a.naissance.j, &a.naissance.m, &a.naissance.a, a.adresse, a.e_mail, &a.salaire, &a.sexe, &a.experience, &a.parking) != EOF)
        {
            if (a.cin_a == cin_a)
                tr = 1;
            else
                fprintf(f2, "%d %s %s %d:%d:%d %s %s %f %d %d %d\n", a.cin_a, a.nom, a.prenom, a.naissance.j, a.naissance.m, a.naissance.a, a.adresse, a.e_mail, a.salaire, a.sexe, a.experience, a.parking);
        }
    }
    fclose(f);
    fclose(f2);
    remove(fileName);
    rename("corbeille.txt", fileName);
    return tr;
}

// Function to search for an agent
agent rechercher_agent(char *fileName, int cin_a)
{
    agent a;
    int tr = 0;
    FILE * f = fopen(fileName, "r");
    if (f != NULL)
    {
        while (tr == 0 && fscanf(f, "%d %s %s %d:%d:%d %s %s %f %d %d %d\n", &a.cin_a, a.nom, a.prenom, &a.naissance.j, &a.naissance.m, &a.naissance.a, a.adresse, a.e_mail, &a.salaire, &a.sexe, &a.experience, &a.parking) != EOF)
        {
            if (a.cin_a == cin_a)
            {
                tr = 1;
                fclose(f);
                return a;
            }
        }
        fclose(f);
    }
    if (tr == 0)
        a.cin_a = -1;
    return a;
}


void afficherhistorique(char *filename,char *filename2, int cin_a, int j, int m, int a) {
    FILE *f = fopen(filename,"r");
    FILE *f2 = fopen(filename2, "r");
    Parking ptemp;
    int idp;
    if (f == NULL) {
        printf("Error opening file %s for reading.\n", filename);
        return;
    }
    if (f2 == NULL) {
    	printf("Error opening file %s for reading.\n", filename2);
    	return;
    } 
	while (fscanf(f, "%d,%d,%99[^,],%99[^,],%99[^,],%d,%d,%d,%c,%c,%d,%d\n", &ptemp.id, &ptemp.id_agent, 
                ptemp.nom, ptemp.region, ptemp.adresse, &ptemp.nbetages, &ptemp.numero_de_telephone, &ptemp.tarif, 
                &ptemp.est_couvert, &ptemp.supporte_pour_handicappe, &ptemp.capacite, &ptemp.place_disponible) != EOF)
  	{
		if (ptemp.id_agent==cin_a)
		{
			idp=ptemp.id;
			g_warning("test1");
			break;


			
		}
	}


    FILE *f3=fopen("Historiquedereservation.txt","w");
    if (f3 == NULL) {
        printf("Error opening file Historiquedereservation.txt for writing.\n");
        fclose(f);  
        return;
    }

    reservation p;
    while (fscanf(f2, "%d %d %s %c %d %d %d %d %d %d %c %d\n",&p.id_res, &p.id_cl, p.nep, &p.h_f, &p.id_mt, &p.id_pk, &p.jdr, &p.mdr, &p.adr, &p.drr, &p.mdp, &p.ser) == 12){
        if ((p.jdr == j) && (p.mdr == m) && (p.adr == a) && (p.id_pk==idp)) {
		printf("id : %d\n",p.id_res);
		fprintf(f3,"%d %d %s %c %d %d %d %d %d %d %c %d\n", p.id_res, p.id_cl, p.nep, p.h_f, p.id_mt, p.id_pk, p.jdr, p.mdr, p.adr, p.drr, p.mdp, p.ser);

		g_warning("test3");

        }
    }

    fclose(f);
    fclose(f2);
    fclose(f3);
}



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
        vider_agent(liste);  
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
                           6, (a.sexe == 0 ? "Homme" : "Femme"),
                           7, g_strdup_printf("%d", a.experience),
                           8, g_strdup_printf("%d", a.parking),
                           9, naissance_str,
                           -1);
    }

    fclose(f);
}

void afficheragentsansparking(const char* filename, GtkWidget *liste) {
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
	if (a.parking==0){

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
    }

    fclose(f);
}

int modifier_agent1(char *fileName, agent m)
{
    int tr = 0;
    agent a;
    FILE * f = fopen(fileName, "r");
    FILE * f2 = fopen("temp.txt", "w");
    if (f != NULL && f2 != NULL)
    {
        while (fscanf(f, "%d %s %s %d:%d:%d %s %s %f %d %d %d\n", &a.cin_a, a.nom, a.prenom, &a.naissance.j, &a.naissance.m, &a.naissance.a, a.adresse, a.e_mail, &a.salaire, &a.sexe, &a.experience, &a.parking) != EOF)
        {
            if (a.cin_a != m.cin_a)
            {
                fprintf(f2, "%d %s %s %d:%d:%d %s %s %f %d %d %d\n", a.cin_a, a.nom, a.prenom, a.naissance.j, a.naissance.m, a.naissance.a, a.adresse, a.e_mail, a.salaire, a.sexe, a.experience, a.parking);
            }
            else
            {
                fprintf(f2, "%d %s %s %d:%d:%d %s %s %f %d %d %d\n", m.cin_a, m.nom, m.prenom, m.naissance.j, m.naissance.m, m.naissance.a, m.adresse, m.e_mail, m.salaire, m.sexe, m.experience, m.parking);
                tr = 1;
            }
        }
    }
    fclose(f);
    fclose(f2);
    remove(fileName);
    rename("temp.txt", fileName);
    return tr;
}















