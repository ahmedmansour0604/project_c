#include <stdio.h>
#include <string.h>
#include "reservation.h"
#include <gtk/gtk.h>
#include "parking.h"

int gen_id_res(const char* idgenresfile)
{
    FILE *file = fopen(idgenresfile, "r");
    int id_res = 1;
    if (file != NULL)
    {
        fscanf(file, "%d", &id_res);
        fclose(file);
        (id_res)++;
    }
    else
    {
        printf("Error: Could not open '%s' to read the last ID.\n", idgenresfile);
    }

    file = fopen(idgenresfile, "w");
    if (file != NULL)
    {
        fprintf(file, "%d", id_res);
        fclose(file);
    }
    else
    {
        printf("Error: Could not open '%s' to write the new ID.\n", idgenresfile);
    }
    return id_res;
}

int ajouter_reservation(char * fileName, reservation p )
{

    FILE * f=fopen(fileName, "a");
    if(f!=NULL)
    {
	p.id_pk=0;
    	p.id_res=gen_id_res("compteur_reservation.txt");
    	//strcpy(p.ser,"null");
	p.ser=-1;
	//p.h_f='h';
        fprintf(f,"%d %d %s %c %d %d %d %d %d %d %c %d\n", p.id_res, p.id_cl, p.nep, p.h_f, p.id_mt, p.id_pk, p.jdr, p.mdr, p.adr, p.drr, p.mdp, p.ser);
        fclose(f);
        return 1;
    }
    else return 0;
}
int ajouter_reservation2(char * fileName, reservation p )
{

    FILE * f=fopen(fileName, "a");
    if(f!=NULL)
    {
    	fprintf(f,"%d %d %s %c %d %d %d %d %d %d %c %d\n", p.id_res, p.id_cl, p.nep, p.h_f, p.id_mt, p.id_pk, p.jdr, p.mdr, p.adr, p.drr, p.mdp, p.ser);
        fclose(f);
        return 1;
    }
    else return 0;
}


int affichier_reservation(reservation p)
{
        printf("%d %d %s %c %d %d %d %d %d %d %c %d\n", p.id_res, p.id_cl, p.nep, p.h_f, p.id_mt, p.id_pk, p.jdr, p.mdr, p.adr, p.drr, p.mdp, p.ser);
}


int modifier_reservation(char *fileName, int id_res ,reservation p_n) {
    int success = 0;
    reservation p;

    FILE *f1 = fopen(fileName, "r");
    if (f1 == NULL) {
        perror("Error opening input file");
        return 0; // Return 0 to indicate failure
    }

    FILE *f2 = fopen("modifier_reservation.txt", "w");
    if (f2 == NULL) {
        perror("Error opening temporary file");
        fclose(f1);
        return 0; // Return 0 to indicate failure
    }

    // Read from original file and write to temporary file
    while (fscanf(f1, "%d %d %s %c %d %d %d %d %d %d %c %d\n",
                  &p.id_res, &p.id_cl, p.nep, &p.h_f, &p.id_mt, &p.id_pk,
                  &p.jdr, &p.mdr, &p.adr, &p.drr, &p.mdp, &p.ser) == 12) {
        if (p.id_res == id_res) {
            // Write updated record
            fprintf(f2, "%d %d %s %c %d %d %d %d %d %d %c %d\n",
                    p_n.id_res, p_n.id_cl, p_n.nep, p_n.h_f, p_n.id_mt,
                    p_n.id_pk, p_n.jdr, p_n.mdr, p_n.adr, p_n.drr, p_n.mdp,
                    p_n.ser);
            success = 1;
        } else {
            // Write unmodified record
            fprintf(f2, "%d %d %s %c %d %d %d %d %d %d %c %d\n",
                    p.id_res, p.id_cl, p.nep, p.h_f, p.id_mt, p.id_pk,
                    p.jdr, p.mdr, p.adr, p.drr, p.mdp, p.ser);
        }
    }

    fclose(f1);
    fclose(f2);

    // Replace original file only if successful
    if (success) {
        if (remove(fileName) != 0) {
            perror("Error removing original file");
            return 0; // Return 0 to indicate failure
        }
        if (rename("modifier_reservation.txt", fileName) != 0) {
            perror("Error renaming temporary file");
            return 0; // Return 0 to indicate failure
        }
    } else {
        // If no modification was made, delete the temporary file
        remove("modifier_reservation.txt");
    }

    return success; // Return 1 if the modification was successful
}


reservation rechercher_reservation(char *fileName, int id_res)
{
	FILE *file=fopen(fileName,"r+");
	reservation p;
	if (file==NULL)
	{
		printf("Error: Could not open the file '%s' for reading.\n", fileName);
        	reservation empty = {0};
        	return empty;
	}
	while (fscanf(file, "%d %d %s %c %d %d %d %d %d %d %c %d\n",
                  &p.id_res, &p.id_cl, p.nep, &p.h_f, &p.id_mt, &p.id_pk,
                  &p.jdr, &p.mdr, &p.adr, &p.drr, &p.mdp, &p.ser)==12)
	{	
		if (p.id_res==id_res)
		{
			fclose(file);
            		return p;
		}
	}
	fclose(file);
    	printf("Error: Reservation with ID %d not found.\n", id_res);
    	reservation empty = {0};
    	return empty;



















/*
    reservation p;
    p.id_res=-1;
    FILE *f = fopen(fileName, "r");
	printf("testingerruer1");
    if (f != NULL)
    {
      
	printf("testingerruer2");
	int x = fscanf(f, "%d %d %s %c %d %d %d %d %d %d %c %d\n", &p.id_res, &p.id_cl, p.nep, &p.h_f, &p.id_mt, &p.id_pk, &p.jdr, &p.mdr, &p.adr, &p.drr, &p.mdp, &p.ser);
    while(x!= EOF)
    	{
	printf("%d\n",x);
        if (p.id_res == id_res)
        	{
            fclose(f); 
            return p;  
        	}
x = fscanf(f, "%d %d %s %c %d %d %d %d %d %d %c %d\n", &p.id_res, &p.id_cl, p.nep, &p.h_f, &p.id_mt, &p.id_pk, &p.jdr, &p.mdr, &p.adr, &p.drr, &p.mdp, &p.ser);
	if (x==0){
fclose(f);
    reservation vide = {0};
    return vide;}
	}
    }
	printf("testingerruer4");

    fclose(f);

    
    reservation vide = {0};
    return vide;*/
}




int supprimer_reservation(char * fileName, int id_res)
{
    int tr=0;
    reservation p;
    FILE * f=fopen(fileName, "r");
    FILE * f2=fopen("supprimer.txt", "a");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%d %d %s %c %d %d %d %d %d %d %c %d\n",&p.id_res, &p.id_cl, p.nep, &p.h_f, &p.id_mt, &p.id_pk, &p.jdr, &p.mdr, &p.adr, &p.drr, &p.mdp, &p.ser)!=EOF)
        {
            if(p.id_res == id_res)
                tr=1;
            else
                fprintf(f2,"%d %d %s %c %d %d %d %d %d %d %c %d\n",
        p.id_res, p.id_cl, p.nep, p.h_f, p.id_mt, p.id_pk, p.jdr, p.mdr, p.adr, p.mdp, p.ser);

        }
    }
else printf("ERREUR\n");
    fclose(f);
    fclose(f2);
    remove(fileName);
    rename("supprimer.txt", fileName);
    return tr;
}


/*void affecter_reservation( char* filenamep,char *filenamer, int idparking ,int idres)
{
	Parking p;
	reservation r;
	p=rechercherParking(filenamep,idparking);
	if (p.id!=0)
	{
		p.place_disponible--;
		modifierParking(filenamep,idparking,p);
	}
	else return;
	r=rechercher_reservation(filenamer,idres);
	if(r.id_res!=-1)

	{
		r.id_pk=idparking;
		modifier_reservation(filenamer,idres,r);
		
	}

}*/


void trier_parkings(Parking T[], int n) {
	int i,permut;
	Parking aux;
	do
	{
		permut= 0;
		for(i=0;i<n-1;i++)
		{
			if(T[i].place_disponible<T[i+1].place_disponible)
			{
				aux=T[i];
				T[i]=T[i+1];
				T[i+1]=aux;
				permut=1;
			}
		}
	} while(permut==1);
}

/*
	n=0;
	Parking ptemp;
	FILE *f = fopen("parking.txt","r");
	while(fscanf(f, "%d,%d,%99[^,],%99[^,],%99[^,],%d,%d,%d,%c,%c,%d,%d\n", &ptemp.id, &ptemp.id_agent,ptemp.nom, ptemp.region, ptemp.adresse, &ptemp.nbetages, &ptemp.numero_de_telephone, &ptemp.tarif, &ptemp.est_couvert, &ptemp.supporte_pour_handicappe, &ptemp.capacite, &ptemp.place_disponible) != EOF){
		parkings[n]=ptemp;
		n++;
	}
	fclose(f);
 FILE *fichier = fopen("trie_parking.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (parkings[j].place_disponible < parkings[j + 1].place_disponible) {
                Parking temp = parkings[j];
                parkings[j] = parkings[j + 1];
                parkings[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        fprintf(fichier, "%d %d %s %s %s %d %d %d %c %c %d %d\n",
                parkings[i].id, parkings[i].id_agent, parkings[i].nom, parkings[i].region,
                parkings[i].adresse, parkings[i].nbetages, parkings[i].numero_de_telephone,
                parkings[i].tarif, parkings[i].est_couvert, parkings[i].supporte_pour_handicappe,
                parkings[i].capacite, parkings[i].place_disponible);
    }

    fclose(fichier);
    printf("Les données triées ont été enregistrées dans %s.\n", nom_fichier);
return parkings;
}*/


void vider_reservation(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;

    store = gtk_tree_view_get_model(GTK_TREE_VIEW(liste));
    if (!store) {

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID Reservation", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID Client", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom et Prenom", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Heure/Date", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID Matricule", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID Parking", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date Debut", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date Fin", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Mode Paiement", renderer, "text", 8, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Service", renderer, "text", 9, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    store = gtk_list_store_new(10, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT,
                               G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
}

void afficher_reservation(const char *filename, GtkWidget *liste) 
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	reservation p;

	char id_res[50];
    	char id_cl[50];
    	char nom[50];
    	char sex[50];
    	char mat[50];
    	char id_par[50];
    	char date[50];
    	char duree[50];
    	char mode_pay[50];
    	char service[50];	
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID",renderer,"text",0,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("CLIENT",renderer,"text",1,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("NOM",renderer,"text",2,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("SEXE",renderer,"text",3,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("MATRICULE",renderer,"text",4,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("PARKING",renderer,"text",5,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("DATE",renderer,"text",6,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("DUREE",renderer,"text",7,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("MODE",renderer,"text",8,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("SERVICE",renderer,"text",9,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
	}
	
	store=gtk_list_store_new(10, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	
	FILE *f = fopen(filename,"a+");
	if(f==NULL) return;
	while(fscanf(f, "%d %d %s %c %d %d %d %d %d %d %c %d\n",
                  &p.id_res, &p.id_cl, p.nep, &p.h_f, &p.id_mt, &p.id_pk,
                  &p.jdr, &p.mdr, &p.adr, &p.drr, &p.mdp, &p.ser) == 12)
	{
		//printf("hafedh testing\n");
		sprintf(id_res,"%d",p.id_res);
		sprintf(id_cl,"%d",p.id_cl);
		strcpy(nom,p.nep);
		if(p.h_f=='m') strcpy(sex,"Male");
		else strcpy(sex,"Femelle");
		sprintf(mat,"%d",p.id_mt);
		sprintf(id_par,"%d",p.id_pk);
		sprintf(date,"%d/%d/%d",p.jdr,p.mdr,p.adr);
		sprintf(duree,"%d",p.drr);
		if(p.mdp=='c') strcpy(mode_pay,"Carte");
		else strcpy(mode_pay,"Espece");
		sprintf(service,"%d",p.ser);
		
		gtk_list_store_append(store,&iter);
		gtk_list_store_set(store,&iter,0,id_res,1,id_cl,2,nom,3,sex,4,mat,5,id_par,6,date,7,duree,8,mode_pay,9,service,-1);
	
	}
	fclose(f);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
	g_object_unref(store);





    /*GtkCellRenderer *renderer;
    GtkTreeIter iter;
    GtkListStore *store;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
    if (!store) {
        vider_reservation(liste);
        store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
    }

    FILE *f = fopen(filename, "r");
    if (!f) {
        g_print("Erreur lors de l'ouverture du fichier: %s\n", filename);
        return;
    }

    char line[512];
    reservation p;
    char date_debut[20], date_fin[20];

    while (fgets(line, sizeof(line), f)) {
        sscanf(line, "%d %d %s %c %d %d %d %d %d %d %c %d",
               &p.id_res, &p.id_cl, p.nep, &p.h_f, &p.id_mt, &p.id_pk, &p.jdr, &p.mdr, &p.adr, &p.drr, &p.mdp, &p.ser);

        sprintf(date_debut, "%02d/%02d/%04d", p.jdr, p.mdr, p.adr);
        sprintf(date_fin, "%02d/%02d/%04d", p.drr, p.mdr, p.adr);

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, p.id_res,
                           1, p.id_cl,
                           2, p.nep,
                           3, g_strdup_printf("%c", p.h_f),
                           4, p.id_mt,
                           5, p.id_pk,
                           6, date_debut,
                           7, date_fin,
                           8, (p.mdp == 'e' ? "Espece" : "Cash"),
                           9, p.ser,
                           -1);
    }

    fclose(f);//*/
}

void ajouterParkingReservation(const char* filename, Parking p)
{
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Erreur : Impossible d'ouvrir le fichier '%s' en mode ajout.\n", filename);
        return;
    }
	printf("%d,%d,%s,%s,%s,%d,%d,%d,%c,%c,%d,%d\n", p.id, p.id_agent, p.nom, p.region, p.adresse, 
            p.nbetages, p.numero_de_telephone, p.tarif, p.est_couvert, p.supporte_pour_handicappe, p.capacite, p.place_disponible);
    fprintf(file, "%d,%d,%s,%s,%s,%d,%d,%d,%c,%c,%d,%d\n", p.id, p.id_agent, p.nom, p.region, p.adresse, 
            p.nbetages, p.numero_de_telephone, p.tarif, p.est_couvert, p.supporte_pour_handicappe, p.capacite, p.place_disponible);
    fclose(file);
}






