#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include "citoyen.h"
#include <stdlib.h>
#include <string.h>
#include "avis.h"
#include "parking.h"
#include "crud.h"
#include "reservation.h"

#define bdd_citoyen "citoyen.txt"
#define bdd_avis "avis.txt"

Citoyen c;

char sexe = 'm';

void
on_citoyen_ajouter_confirmer_clicked   (GtkWidget       *ajout,
                                        gpointer         user_data)
{
	GtkWidget* input ;
	GtkWidget* output ;
	
	char tmp[150];
	
	output = lookup_widget(ajout, "citoyen_ajouter_affichage") ;
	gtk_label_set_text(GTK_LABEL(output),"(Resultat)");
	
	//id
	c.id=1;
	//nom
	input = lookup_widget(ajout, "citoyen_ajouter_nom");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	//printf("%ld %d\n",strlen(tmp),strlen(tmp)==0);
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) strcpy(c.nom,tmp);
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Nom invalide!");
		return;
	}
	//printf("%s\n",tmp);
	//prenom
	input = lookup_widget(ajout, "citoyen_ajouter_prenom");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	//printf("%ld %d\n",strlen(tmp),strlen(tmp)==0);
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) strcpy(c.prenom,tmp);
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Prenom invalide!");
		return;
	}
	//email
	input = lookup_widget(ajout, "citoyen_ajouter_email");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	//printf("%ld %d\n",strlen(tmp),strlen(tmp)==0);
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) strcpy(c.email,tmp);
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Email invalide!");
		return;
	}
	//telephone
	input = lookup_widget(ajout, "citoyen_ajouter_telephone");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0) c.tele=str_to_int(tmp);
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Numero de Telephone invalide!");
		return;
	}
	//sexe
	c.sexe=sexe;
	//adresse
	input = lookup_widget(ajout, "citoyen_ajouter_adresse");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	//printf("%ld %d\n",strlen(tmp),strlen(tmp)==0);
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) strcpy(c.adresse,tmp);
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Email invalide!");
		return;
	}
	//date
	input=lookup_widget(ajout,"citoyen_ajouter_jour");
	c.dn_jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(ajout,"citoyen_ajouter_mois");
	c.dn_mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(ajout,"citoyen_ajouter_annee");
	c.dn_annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	//printf("%d/%d/%d\n",c.dn_jour,c.dn_mois,c.dn_annee);
	//municipalite
	input=lookup_widget(ajout,"citoyen_ajouter_combobox");
	//gtk_combo_box_append_text(GTK_COMBO_BOX(input),"test ajout"); //test ajout au combo box
	if(gtk_combo_box_get_active_text(GTK_COMBO_BOX(input))!=NULL) strcpy(c.municipalite,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input)));
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Municipalité invalide!");
		return;
	}
	rep_space_udnder(c.municipalite);
	//ajout
	int res=ajouter_citoyen(bdd_citoyen,c);
	if(res==0){
		gtk_label_set_text(GTK_LABEL(output),"Erreur lors de l'ajout!");
		return;
	}
	printf("%d\n",res);
	sprintf(tmp, "Ajout du Citoyen avec success! (ID=%d)", res);
	gtk_label_set_text(GTK_LABEL(output),"Ajout du Citoyen avec success!");
	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(ajout)),
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_INFO,
		GTK_BUTTONS_OK,
		tmp);	
	gtk_dialog_run(GTK_DIALOG(dialog));	
	gtk_widget_destroy(dialog);
}

/*

	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_ERROR,
		GTK_BUTTONS_OK,
		"Veuillez saisir un tarif valide !");	
	gtk_dialog_run(GTK_DIALOG(dialog));	
	gtk_widget_destroy(dialog);

	GTK_MESSAGE_INFO ou GTK_MESSAGE_ERROR

    int id;
    char nom[50];
    char prenom[50];
    char email[50];
    int tele;
    char adresse[150];
    char sexe;
    int dn_jour,dn_mois,dn_annee;
    char municipalite[50];
*/

void
on_citoyen_ajouter_male_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	sexe='m';
}


void
on_citoyen_ajouter_femelle_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	sexe='f';
}


void
on_citoyen_afficher_bouton_clicked     (GtkWidget       *affiche,
                                        gpointer         user_data)
{
	GtkWidget* input ;
	GtkWidget* output ;
	
	char tmp[150];
	
	//id
	input = lookup_widget(affiche, "citoyen_afficher_id");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0) c=chercher_citoyen(bdd_citoyen,str_to_int(tmp));
	else {
	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(affiche)),
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_ERROR,
		GTK_BUTTONS_OK,
		"ID invalide!");	
	gtk_dialog_run(GTK_DIALOG(dialog));	
	gtk_widget_destroy(dialog);

	return;
	}
	if(c.id==-1){
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(affiche)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			"ID inexistant!");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);

		return;
	}
	
	//nom
	rep_under_space(c.nom);
	output = lookup_widget(affiche, "citoyen_afficher_nom") ;
	gtk_label_set_text(GTK_LABEL(output),c.nom);
	output = lookup_widget(affiche, "citoyen_modifier_nom") ;
	gtk_entry_set_text(GTK_ENTRY(output),c.nom);
	//prenom
	rep_under_space(c.prenom);
	output = lookup_widget(affiche, "citoyen_afficher_prenom") ;
	gtk_label_set_text(GTK_LABEL(output),c.prenom);
	output = lookup_widget(affiche, "citoyen_modifier_prenom") ;
	gtk_entry_set_text(GTK_ENTRY(output),c.prenom);
	//email
	rep_under_space(c.email);
	output = lookup_widget(affiche, "citoyen_afficher_email") ;
	gtk_label_set_text(GTK_LABEL(output),c.email);
	output = lookup_widget(affiche, "citoyen_modifier_email") ;
	gtk_entry_set_text(GTK_ENTRY(output),c.email);
	//telephone
	sprintf(tmp,"%d",c.tele);
	output = lookup_widget(affiche, "citoyen_afficher_telephone") ;
	gtk_label_set_text(GTK_LABEL(output),tmp);
	output = lookup_widget(affiche, "citoyen_modifier_telephone") ;
	gtk_entry_set_text(GTK_ENTRY(output),tmp);
	//adresse
	rep_under_space(c.adresse);
	output = lookup_widget(affiche, "citoyen_afficher_adresse") ;
	gtk_label_set_text(GTK_LABEL(output),c.adresse);
	output = lookup_widget(affiche, "citoyen_modifier_adresse") ;
	gtk_entry_set_text(GTK_ENTRY(output),c.adresse);
	//sexe
	output = lookup_widget(affiche, "citoyen_afficher_sexe") ;
	if (c.sexe=='m') {
		gtk_label_set_text(GTK_LABEL(output),"Male");
		output = lookup_widget(affiche, "citoyen_modifier_male") ;
		gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),TRUE);
	}
	else {
		gtk_label_set_text(GTK_LABEL(output),"Femelle");
		output = lookup_widget(affiche, "citoyen_modifier_femelle") ;
		gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),TRUE);
	}
	//date naissance
	output = lookup_widget(affiche, "citoyen_afficher_dn") ;
	sprintf(tmp,"%d/%d/%d",c.dn_jour,c.dn_mois,c.dn_annee);
	gtk_label_set_text(GTK_LABEL(output),tmp);
	output=lookup_widget(affiche,"citoyen_modifier_jour");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(output),c.dn_jour);
	output=lookup_widget(affiche,"citoyen_modifier_mois");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(output),c.dn_mois);
	output=lookup_widget(affiche,"citoyen_modifier_annee");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(output),c.dn_annee);
	//municipalite
	rep_under_space(c.municipalite);
	output = lookup_widget(affiche, "citoyen_afficher_municipalite") ;
	gtk_label_set_text(GTK_LABEL(output),c.municipalite);
	output = lookup_widget(affiche, "citoyen_modifier_combobox");
	gtk_combo_box_set_active(GTK_COMBO_BOX(output),0);
	int i=0;//gtk_combo_box_get_active_text(GTK_COMBO_BOX(input))
	while (i<24&&(strcmp(c.municipalite,gtk_combo_box_get_active_text(GTK_COMBO_BOX(output)))!=0)){
		gtk_combo_box_set_active(GTK_COMBO_BOX(output),i);
		i++;
	}
	//entry22
	/*output = lookup_widget(affiche, "entry22") ;
	gtk_entry_set_text(GTK_ENTRY(output),"test");*/
	
}


void
on_citoyen_modifier_bouton_clicked     (GtkWidget       *modif,
                                        gpointer         user_data)
{
	GtkWidget* input ;
	GtkWidget* output ;
	
	char tmp[150];
	
	output = lookup_widget(modif, "citoyen_modifier_affichage") ;
	gtk_label_set_text(GTK_LABEL(output),"(Resultat)");
	
	input = lookup_widget(modif, "citoyen_afficher_id");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0){
		if (c.id!=str_to_int(tmp)){
	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(modif)),
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_ERROR,
		GTK_BUTTONS_OK,
		"Il faut clicker sur Afficher!");	
	gtk_dialog_run(GTK_DIALOG(dialog));	
	gtk_widget_destroy(dialog);

	return;
	}}
	//id deja fait
	
	//nom
	input = lookup_widget(modif, "citoyen_modifier_nom");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	//printf("%ld %d\n",strlen(tmp),strlen(tmp)==0);
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) strcpy(c.nom,tmp);
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Nom invalide!");
		return;
	}
	//printf("%s\n",tmp);
	//prenom
	input = lookup_widget(modif, "citoyen_modifier_prenom");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	//printf("%ld %d\n",strlen(tmp),strlen(tmp)==0);
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) strcpy(c.prenom,tmp);
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Prenom invalide!");
		return;
	}
	//email
	input = lookup_widget(modif, "citoyen_modifier_email");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	//printf("%ld %d\n",strlen(tmp),strlen(tmp)==0);
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) strcpy(c.email,tmp);
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Email invalide!");
		return;
	}
	//telephone
	input = lookup_widget(modif, "citoyen_modifier_telephone");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0) c.tele=str_to_int(tmp);
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Numero de Telephone invalide!");
		return;
	}
	//sexe
	c.sexe=sexe;
	//adresse
	input = lookup_widget(modif, "citoyen_modifier_adresse");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	//printf("%ld %d\n",strlen(tmp),strlen(tmp)==0);
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) strcpy(c.adresse,tmp);
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Email invalide!");
		return;
	}
	//date
	input=lookup_widget(modif,"citoyen_modifier_jour");
	c.dn_jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(modif,"citoyen_modifier_mois");
	c.dn_mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(modif,"citoyen_modifier_annee");
	c.dn_annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	//printf("%d/%d/%d\n",c.dn_jour,c.dn_mois,c.dn_annee);
	//municipalite
	input=lookup_widget(modif,"citoyen_modifier_combobox");
	//gtk_combo_box_append_text(GTK_COMBO_BOX(input),"test modif"); //test modif au combo box
	if(gtk_combo_box_get_active_text(GTK_COMBO_BOX(input))!=NULL) strcpy(c.municipalite,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input)));
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Municipalité invalide!");
		return;
	}
	int res=modifier_citoyen(bdd_citoyen,c.id,c);
	if(res==0){
		gtk_label_set_text(GTK_LABEL(output),"Erreur lors de l'modif!");
		return;
	}
	printf("%d\n",res);
	sprintf(tmp, "Modification du Citoyen avec success! (ID=%d)", res);
	gtk_label_set_text(GTK_LABEL(output),"modif du Citoyen avec success!");
	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(modif)),
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_INFO,
		GTK_BUTTONS_OK,
		tmp);	
	gtk_dialog_run(GTK_DIALOG(dialog));	
	gtk_widget_destroy(dialog);

}


void
on_citoyen_modifier_femelle_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	sexe='f';
}


void
on_citoyen_modifier_male_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	sexe='m';
}


void
on_citoyen_supprimer_bouton_clicked    (GtkWidget       *supp,
                                        gpointer         user_data)
{
	GtkWidget* input ;
	GtkWidget* output ;
	char tmp[150];
	
	Citoyen c;	
	
	//id
	input = lookup_widget(supp, "citoyen_supprimer_id");
	output = lookup_widget(supp, "citoyen_supprimer_message");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0) c=chercher_citoyen(bdd_citoyen,str_to_int(tmp));
	else {
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(supp)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			"ID invalide!");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		gtk_entry_set_text(GTK_ENTRY(output),"ID invalide!");
		return;
	}
	if(c.id!=-1) {
		sprintf(tmp,"Voulez-vous vraiment supprimer le citoyen N°%d ?",c.id);
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(supp)),
        	                            GTK_DIALOG_MODAL,
            	                        GTK_MESSAGE_QUESTION,
                	                    GTK_BUTTONS_YES_NO,
                    	                tmp);

    	int result = gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		
		if (result == GTK_RESPONSE_YES){
			supprimer_citoyen(bdd_citoyen,c.id);

			sprintf(tmp,"Citoyen N°%d supprimé!",c.id);
			gtk_label_set_text(GTK_LABEL(output),tmp);
			dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(supp)),
				GTK_DIALOG_MODAL,
				GTK_MESSAGE_INFO,
				GTK_BUTTONS_OK,
				tmp);	
			gtk_dialog_run(GTK_DIALOG(dialog));	
			gtk_widget_destroy(dialog);
			}
	} else {
		sprintf(tmp,"Citoyen N°%d introuvable!",str_to_int(tmp));
		gtk_label_set_text(GTK_LABEL(output),tmp);
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(supp)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			tmp);	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		gtk_entry_set_text(GTK_ENTRY(output),tmp);
		return;
	}
	on_citoyen_supprimer_afficher_clicked  (supp,user_data);
}


void
on_citoyen_supprimer_afficher_clicked  (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *liste = lookup_widget(button, "citoyen_supprimer_treeview");
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	int id_max,i;

	Citoyen c;

	char id[10];
    char nom[50];
    char prenom[50];
    char email[50];
    char tele[10];
    char adresse[150];
    char csexe[10];
    char dn[10];
    char municipalite[50];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID",renderer,"text",0,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("NOM",renderer,"text",1,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("PRENOM",renderer,"text",2,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("EMAIL",renderer,"text",3,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("TELEPHONE",renderer,"text",4,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ADRESSE",renderer,"text",5,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("SEXE",renderer,"text",6,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("DATE NAISSANCE",renderer,"text",7,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("MUNICIPALITE",renderer,"text",8,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
	}
	
	store=gtk_list_store_new(9, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	
	id_max=dernier_id_citoyen(bdd_citoyen);
	for (i=1;i<=id_max;i++)
	{
		c=chercher_citoyen(bdd_citoyen,i);
		//printf("%d %s %s %s %d %s %c %d %d %d %s\n",c.id,c.nom,c.prenom,c.email,c.tele,c.adresse,c.sexe,c.dn_jour,c.dn_mois,c.dn_annee,c.municipalite);
		if (c.id!=-1)
		{
			sprintf(id,"%d",c.id);
			strcpy(nom,c.nom);
			rep_under_space(nom);
			strcpy(prenom,c.prenom);
			rep_under_space(prenom);
			strcpy(email,c.email);
			rep_under_space(email);
			sprintf(tele,"%d",c.tele);
			strcpy(adresse,c.adresse);
			rep_under_space(adresse);
			if (c.sexe=='m') strcpy(csexe,"Male"); else strcpy(csexe,"Femelle");
			sprintf(dn,"%d/%d/%d",c.dn_jour,c.dn_mois,c.dn_annee);
			strcpy(municipalite,c.municipalite);
			rep_under_space(municipalite);
			printf("%s %s %s %s %s %s %s %s %s\n",id,nom,prenom,email,tele,adresse,csexe,dn,municipalite);
			


			gtk_list_store_append(store,&iter);
			gtk_list_store_set(store,&iter,0,id,1,nom,2,prenom,3,email,4,tele,5,adresse,6,csexe,7,dn,8,municipalite,-1);
		}
	}
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
	g_object_unref(store);
}


void
on_citoyen_supprimer_treeview_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	gchar* id;
    gchar* nom;
    gchar* prenom;
    gchar* email;
    gchar* tele;
    gchar* adresse;
    gchar* csexe;
    gchar* dn;
    gchar* municipalite;
	
	GtkWidget* output;
	output = lookup_widget(treeview, "citoyen_supprimer_id") ;

	GtkTreeModel *model = gtk_tree_view_get_model(treeview);

	if(gtk_tree_model_get_iter(model,&iter,path))
	{
		gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,1,&nom,2,&prenom,3,&email,4,&tele,5,&adresse,6,&csexe,7,&dn,8,&municipalite,-1);
		gtk_entry_set_text(GTK_ENTRY(output),id);
		on_citoyen_supprimer_bouton_clicked(treeview,user_data);
	}
}


void
on_citoyen_rechercher_bouton_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
	int bid=0,bnom=0,bprenom=0,bemail=0,btele=0,badresse=0;
	int id,tele;
	char nom[50],prenom[50],email[50],adresse[150];
	GtkWidget* input;

	char tmp[150];

	char res_rech[]="resultat.txt";

	input = lookup_widget(button, "citoyen_rechercher_id");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	input = lookup_widget(button, "checkbutton1");
	if(str_is_int(tmp)&&strlen(tmp)!=0) id=str_to_int(tmp);
	else gtk_toggle_button_set_active(input,FALSE);
	bid=gtk_toggle_button_get_active(input);
	
	input = lookup_widget(button, "citoyen_rechercher_nom");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	input = lookup_widget(button, "checkbutton2");
	if(strlen(tmp)!=0) strcpy(nom,tmp);
	else gtk_toggle_button_set_active(input,FALSE);
	bnom=gtk_toggle_button_get_active(input);
	
	input = lookup_widget(button, "citoyen_rechercher_prenom");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	input = lookup_widget(button, "checkbutton3");
	if(strlen(tmp)!=0) strcpy(prenom,tmp);
	else gtk_toggle_button_set_active(input,FALSE);
	bprenom=gtk_toggle_button_get_active(input);
	
	input = lookup_widget(button, "citoyen_rechercher_email");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	input = lookup_widget(button, "checkbutton4");
	if(strlen(tmp)!=0) strcpy(email,tmp);
	else gtk_toggle_button_set_active(input,FALSE);
	bemail=gtk_toggle_button_get_active(input);

	input = lookup_widget(button, "citoyen_rechercher_telephone");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	input = lookup_widget(button, "checkbutton5");
	if(str_is_int(tmp)&&strlen(tmp)!=0) tele=str_to_int(tmp);
	else gtk_toggle_button_set_active(input,FALSE);
	btele=gtk_toggle_button_get_active(input);
	
	input = lookup_widget(button, "citoyen_rechercher_adresse");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	input = lookup_widget(button, "checkbutton6");
	if(strlen(tmp)!=0) strcpy(adresse,tmp);
	else gtk_toggle_button_set_active(input,FALSE);
	badresse=gtk_toggle_button_get_active(input);

	super_chercher_citoyen(bdd_citoyen,res_rech, id, bid, nom, bnom, prenom, bprenom, email, bemail, tele, btele, adresse, badresse);

	//citoyen_rechercher_treeview
	GtkWidget *liste = lookup_widget(button, "citoyen_rechercher_treeview");
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	int id_max,i;

	Citoyen c;

	char idt[10];
    char nomt[50];
    char prenomt[50];
    char emailt[50];
    char telet[10];
    char adresset[150];
    char csexet[10];
    char dnt[10];
    char municipalitet[50];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID",renderer,"text",0,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("NOM",renderer,"text",1,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("PRENOM",renderer,"text",2,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("EMAIL",renderer,"text",3,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("TELEPHONE",renderer,"text",4,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ADRESSE",renderer,"text",5,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("SEXE",renderer,"text",6,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("DATE NAISSANCE",renderer,"text",7,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("MUNICIPALITE",renderer,"text",8,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
	}
	
	store=gtk_list_store_new(9, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	id_max=dernier_id_citoyen(res_rech);
	for (i=1;i<=id_max;i++)
	{
		c=chercher_citoyen(res_rech,i);
		//printf("%d %s %s %s %d %s %c %d %d %d %s\n",c.id,c.nom,c.prenom,c.email,c.tele,c.adresse,c.sexe,c.dn_jour,c.dn_mois,c.dn_annee,c.municipalite);
		if (c.id!=-1)
		{
			sprintf(idt,"%d",c.id);
			strcpy(nomt,c.nom);
			rep_under_space(nomt);
			strcpy(prenomt,c.prenom);
			rep_under_space(prenomt);
			strcpy(emailt,c.email);
			rep_under_space(emailt);
			sprintf(telet,"%d",c.tele);
			strcpy(adresset,c.adresse);
			rep_under_space(adresset);
			if (c.sexe=='m') strcpy(csexet,"Male"); else strcpy(csexet,"Femelle");
			sprintf(dnt,"%d/%d/%d",c.dn_jour,c.dn_mois,c.dn_annee);
			strcpy(municipalitet,c.municipalite);
			rep_under_space(municipalitet);
			
			gtk_list_store_append(store,&iter);
			gtk_list_store_set(store,&iter,0,idt,1,nomt,2,prenomt,3,emailt,4,telet,5,adresset,6,csexet,7,dnt,8,municipalitet,-1);
		}
	}
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
	g_object_unref(store);//*/
}


void
on_citoyen_calculer_button_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget* input ;
	GtkWidget* output ;
	
	char tmp[150];
	Citoyen c;
	int mois,annee;
	char facture[]="facture.txt";
	//id
	input = lookup_widget(button, "citoyen_calculer_id");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0) c=chercher_citoyen(bdd_citoyen,str_to_int(tmp));
	else {
	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_ERROR,
		GTK_BUTTONS_OK,
		"ID invalide!");	
	gtk_dialog_run(GTK_DIALOG(dialog));	
	gtk_widget_destroy(dialog);

	return;
	}
	if(c.id==-1){
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			"ID inexistant!");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		return;
	}
	input=lookup_widget(button,"citoyen_calculer_mois");
	mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(button,"citoyen_calculer_annee");
	annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	//printf("%d %d %d\n",c.id,mois,annee);
	float total = calculer_facture_citoyen("reservation.txt","parking.txt","service.txt",facture,c.id, mois, annee);
	GtkWidget *ptr=lookup_widget(button,"citoyen_calculer_prix");
	sprintf(tmp,"%.3f",total);
	gtk_label_set_text(GTK_LABEL(ptr),tmp);
	GtkWidget *liste = lookup_widget(button, "citoyen_calculer_treeview");
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	char typet;
	int idt;
	float tarift;
    char type[50];
    char id[50];
	char nom[100];
	char tarif[50];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("TYPE",renderer,"text",0,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID",renderer,"text",1,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("NOM",renderer,"text",2,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("PRIX",renderer,"text",3,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
	}
	
	store=gtk_list_store_new(4, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	
	FILE *f = fopen(facture,"a+");
	if(f==NULL) return;
	while(fscanf(f,"%c %d %s %f\n",&typet,&idt,nom,&tarift)!=EOF)
	{
		if (typet=='p') strcpy(type,"Parking");
		else strcpy(type,"Service");
		sprintf(id,"%d",idt);
		sprintf(tarif,"%f",tarift);
		printf("%s %s %s %s\n",type,id,nom,tarif);
		gtk_list_store_append(store,&iter);
		gtk_list_store_set(store,&iter,0,type,1,id,2,nom,3,tarif,-1);
	
	}
	fclose(f);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
	g_object_unref(store);//*/
}


void // ajouter avis
on_button23_clicked                    (GtkWidget       *button,
                                        gpointer         user_data)
{
	Avis a;
	GtkWidget* input ;
	GtkWidget* output ;
	
	char tmp[100];
	
	output = lookup_widget(button, "label355") ;
	gtk_label_set_text(GTK_LABEL(output),"(Resultat)");

	//id citoyen
	input = lookup_widget(button, "entry46");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0) a.id_citoyen=str_to_int(tmp);
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"ID Citoyen invalide!");
		return;
	}
	//id parking
	input = lookup_widget(button, "entry47");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0) a.id_parking=str_to_int(tmp);
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"ID Parking invalide!");
		return;
	}
	//Note
	input = lookup_widget(button, "spinbutton21");
	a.note=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	//commentaire
	input = lookup_widget(button, "entry48");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) strcpy(a.comment,tmp);
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Commentaire invalide!");
		return;
	}
	//date
	input=lookup_widget(button,"spinbutton22");
	a.dr_jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(button,"spinbutton23");
	a.dr_mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(button,"spinbutton24");
	a.dr_annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	//motif
	input=lookup_widget(button,"combobox10");
	if(gtk_combo_box_get_active_text(GTK_COMBO_BOX(input))!=NULL) strcpy(a.motif,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input)));
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Motif invalide!");
		return;
	}
	rep_space_udnder(a.motif);
	//type
	strcpy(a.type,"nn");
	input=lookup_widget(button,"checkbutton13");
	if (gtk_toggle_button_get_active(input)) a.type[0]='o';
    else a.type[0]='n';
	input=lookup_widget(button,"checkbutton12");
	if (gtk_toggle_button_get_active(input)) a.type[1]='o';
    else a.type[1]='n';
	//sexe
	input=lookup_widget(button,"radiobutton23");
	if (gtk_toggle_button_get_active(input)) a.sexe='h';
    else a.sexe='f';
	//printf("%d %d %d %f %s %d %d %d %s %s %c\n",1,a.id_citoyen,a.id_parking,a.note,a.comment,a.dr_jour,a.dr_mois,a.dr_annee,a.motif,a.type,a.sexe);
	//ajout
	int res=ajouter_avis(bdd_avis,a);
	if(res==0){
		gtk_label_set_text(GTK_LABEL(output),"Erreur lors de l'ajout!");
		return;
	}
	sprintf(tmp, "Ajout d'Avis avec success!");
	gtk_label_set_text(GTK_LABEL(output),"Ajout d'Avis avec success!");
	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_INFO,
		GTK_BUTTONS_OK,
		tmp);	
	gtk_dialog_run(GTK_DIALOG(dialog));	
	gtk_widget_destroy(dialog);
}


void//afficher
on_button68_clicked                    (GtkButton       *affiche,
                                        gpointer         user_data)
{
	Avis a;
	GtkWidget* input ;
	GtkWidget* output ;
	
	char tmp[150];
	
	//id
	input = lookup_widget(affiche, "entry58");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0) a=chercher_avis(bdd_avis,str_to_int(tmp));
	else {
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(affiche)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			"ID invalide!");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);

		return;
	}
	if(c.id==-1){
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(affiche)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			"ID inexistant!");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);

		return;
	}
	//id_avis
	sprintf(tmp,"%d",a.id_avis);
	output = lookup_widget(affiche, "label357") ;
	gtk_label_set_text(GTK_LABEL(output),tmp);
	output = lookup_widget(affiche, "entry52") ;
	gtk_entry_set_text(GTK_ENTRY(output),tmp);
	//id_citoyen
	sprintf(tmp,"%d",a.id_citoyen);
	output = lookup_widget(affiche, "label358") ;
	gtk_label_set_text(GTK_LABEL(output),tmp);
	output = lookup_widget(affiche, "entry55") ;
	gtk_entry_set_text(GTK_ENTRY(output),tmp);
	//id_parking
	sprintf(tmp,"%d",a.id_parking);
	output = lookup_widget(affiche, "label359") ;
	gtk_label_set_text(GTK_LABEL(output),tmp);
	output = lookup_widget(affiche, "entry56") ;
	gtk_entry_set_text(GTK_ENTRY(output),tmp);
	//note
	sprintf(tmp,"%.2f",a.note);
	output = lookup_widget(affiche, "label360") ;
	gtk_label_set_text(GTK_LABEL(output),tmp);
	output = lookup_widget(affiche, "spinbutton28") ;
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(output),(int)a.note);
	//commentaire
	rep_under_space(a.comment);
	output = lookup_widget(affiche, "label361") ;
	gtk_label_set_text(GTK_LABEL(output),a.comment);
	output = lookup_widget(affiche, "entry57") ;
	gtk_entry_set_text(GTK_ENTRY(output),a.comment);
	//dr
	output = lookup_widget(affiche, "label362") ;
	sprintf(tmp,"%d/%d/%d",a.dr_jour,a.dr_mois,a.dr_annee);
	gtk_label_set_text(GTK_LABEL(output),tmp);
	output=lookup_widget(affiche,"spinbutton30");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(output),a.dr_jour);
	output=lookup_widget(affiche,"spinbutton31");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(output),a.dr_mois);
	output=lookup_widget(affiche,"spinbutton32");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(output),a.dr_annee);
	//motif
	rep_under_space(a.motif);
	output = lookup_widget(affiche, "label363") ;
	gtk_label_set_text(GTK_LABEL(output),a.motif);
	output = lookup_widget(affiche, "combobox11");
	gtk_combo_box_set_active(GTK_COMBO_BOX(output),0);
	int i=0;//gtk_combo_box_get_active_text(GTK_COMBO_BOX(input))
	while (i<2&&(strcmp(a.motif,gtk_combo_box_get_active_text(GTK_COMBO_BOX(output)))!=0)){
		gtk_combo_box_set_active(GTK_COMBO_BOX(output),i);
		i++;
	}
	//type Reclamation Remerciment
	strcpy(tmp,"Reclamation : ");
	output = lookup_widget(affiche, "checkbutton16") ;
	if(a.type[0]=='o') 
	{
		strcat(tmp,"Oui");
		gtk_toggle_button_set_active(output,TRUE);
	} 
	else 
	{
		strcat(tmp,"Non");
		gtk_toggle_button_set_active(output,FALSE);
	}
	strcat(tmp,"   Remerciment : ");
	output = lookup_widget(affiche, "checkbutton17") ;
	if(a.type[1]=='o') 
	{
		strcat(tmp,"Oui");
		gtk_toggle_button_set_active(output,TRUE);
	} 
	else 
	{
		strcat(tmp,"Non");
		gtk_toggle_button_set_active(output,FALSE);
	}
	output = lookup_widget(affiche, "label364");
	gtk_label_set_text(GTK_LABEL(output),tmp);
	//sexe
	output = lookup_widget(affiche, "label365") ;
	if (a.sexe=='h') {
		gtk_label_set_text(GTK_LABEL(output),"Homme");
		output = lookup_widget(affiche, "radiobutton27") ;
		gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),TRUE);
	}
	else {
		gtk_label_set_text(GTK_LABEL(output),"Femme");
		output = lookup_widget(affiche, "radiobutton28") ;
		gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),TRUE);
	}
}


void//modifier
on_button25_clicked                    (GtkWidget       *button,
                                        gpointer         user_data)
{
	Avis a;
	GtkWidget* input ;
	GtkWidget* output ;
	
	char tmp[100];
	
	output = lookup_widget(button, "label367") ;
	gtk_label_set_text(GTK_LABEL(output),"(Resultat)");
	//id avis
	input = lookup_widget(button, "entry52");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0) a.id_avis=str_to_int(tmp);
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"ID Citoyen invalide!");
		return;
	}
	//id citoyen
	input = lookup_widget(button, "entry55");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0) a.id_citoyen=str_to_int(tmp);
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"ID Citoyen invalide!");
		return;
	}
	//id parking
	input = lookup_widget(button, "entry56");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0) a.id_parking=str_to_int(tmp);
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"ID Parking invalide!");
		return;
	}
	//Note
	input = lookup_widget(button, "spinbutton28");
	a.note=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	//commentaire
	input = lookup_widget(button, "entry57");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) strcpy(a.comment,tmp);
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Commentaire invalide!");
		return;
	}
	//date
	input=lookup_widget(button,"spinbutton30");
	a.dr_jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(button,"spinbutton31");
	a.dr_mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(button,"spinbutton32");
	a.dr_annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	//motif
	input=lookup_widget(button,"combobox11");
	if(gtk_combo_box_get_active_text(GTK_COMBO_BOX(input))!=NULL) strcpy(a.motif,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input)));
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Motif invalide!");
		return;
	}
	rep_space_udnder(a.motif);
	//type
	strcpy(a.type,"nn");
	input=lookup_widget(button,"checkbutton16");
	if (gtk_toggle_button_get_active(input)) a.type[0]='o';
    else a.type[0]='n';
	input=lookup_widget(button,"checkbutton17");
	if (gtk_toggle_button_get_active(input)) a.type[1]='o';
    else a.type[1]='n';
	//sexe
	input=lookup_widget(button,"radiobutton27");
	if (gtk_toggle_button_get_active(input)) a.sexe='h';
    else a.sexe='f';
	//printf("%d %d %d %f %s %d %d %d %s %s %c\n",1,a.id_citoyen,a.id_parking,a.note,a.comment,a.dr_jour,a.dr_mois,a.dr_annee,a.motif,a.type,a.sexe);
	//ajout
	int res=modifier_avis(bdd_avis,a.id_avis,a);
	if(res==0){
		gtk_label_set_text(GTK_LABEL(output),"Erreur lors du modification!");
		return;
	}
	sprintf(tmp, "Modification d'Avis avec success!");
	gtk_label_set_text(GTK_LABEL(output),"Modification d'Avis avec success!");
	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_INFO,
		GTK_BUTTONS_OK,
		tmp);	
	gtk_dialog_run(GTK_DIALOG(dialog));	
	gtk_widget_destroy(dialog);
}


void//treeview23
on_button70_clicked                    (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *liste = lookup_widget(button, "treeview23");
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	Avis t;

	char id_avis[50];
    char id_citoyen[50];
    char id_parking[50];
    char note[50];
    char comment[100];
    char dr[50];
    char motif[50];
    char type[50];
    char sex[50];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID AVIS",renderer,"text",0,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID CITOYEN",renderer,"text",1,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID PARKING",renderer,"text",2,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("NOTE",renderer,"text",3,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("COMMENT",renderer,"text",4,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("DATE",renderer,"text",5,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("MOTIF",renderer,"text",6,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("TYPE",renderer,"text",7,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("SEXE",renderer,"text",8,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
	}
	
	store=gtk_list_store_new(9, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	
	FILE *f = fopen(bdd_avis,"a+");
	if(f==NULL) return;
	while(fscanf(f,"%d %d %d %f %s %d %d %d %s %s %c\n",&t.id_avis,&t.id_citoyen,&t.id_parking,&t.note,t.comment,&t.dr_jour,&t.dr_mois,&t.dr_annee,t.motif,t.type,&t.sexe)!=EOF)
	{
		sprintf(id_avis,"%d",t.id_avis);
		sprintf(id_citoyen,"%d",t.id_citoyen);
		sprintf(id_parking,"%d",t.id_parking);
		sprintf(note,"%d",(int)t.note);
		strcpy(comment,t.comment);
		rep_under_space(t.comment);
		sprintf(dr,"%d/%d/%d",t.dr_jour,t.dr_mois,t.dr_annee);
		strcpy(motif,t.motif);
		rep_under_space(motif);
		if (t.type[0]=='o')
		{
			strcpy(type,"Rec");
			if (t.type[0]=='o')strcat(type," Rem");
		}
		else if (t.type[0]=='o')strcpy(type,"Rem");
		else strcpy(type,"None");
		if (t.sexe=='h') strcpy(sex,"Homme"); else strcpy(sex,"Femme");

		gtk_list_store_append(store,&iter);
		gtk_list_store_set(store,&iter,0,id_avis,1,id_citoyen,2,id_parking,3,note,4,comment,5,dr,6,motif,7,type,8,sex,-1);
	
	}
	fclose(f);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
	g_object_unref(store);
}


void//supprimer
on_button26_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget* input ;
	GtkWidget* output ;
	char tmp[150];
	
	Avis a;	
	
	//id
	input = lookup_widget(button, "entry59");
	output = lookup_widget(button, "label173");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0) a=chercher_avis(bdd_avis,str_to_int(tmp));
	else {
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			"ID invalide!");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		gtk_entry_set_text(GTK_ENTRY(output),"ID invalide!");
		return;
	}
	if(a.id_avis!=-1) {
		sprintf(tmp,"Voulez-vous vraiment supprimer l'avis N°%d ?",a.id_avis);
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
        	                            GTK_DIALOG_MODAL,
            	                        GTK_MESSAGE_QUESTION,
                	                    GTK_BUTTONS_YES_NO,
                    	                tmp);

    	int result = gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		
		if (result == GTK_RESPONSE_YES){
			supprimer_avis(bdd_avis,a.id_avis);

			sprintf(tmp,"Avis N°%d supprimé!",a.id_avis);
			gtk_label_set_text(GTK_LABEL(output),tmp);
			dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
				GTK_DIALOG_MODAL,
				GTK_MESSAGE_INFO,
				GTK_BUTTONS_OK,
				tmp);	
			gtk_dialog_run(GTK_DIALOG(dialog));	
			gtk_widget_destroy(dialog);
			}
	} else {
		sprintf(tmp,"Avis N°%d introuvable!",str_to_int(tmp));
		gtk_label_set_text(GTK_LABEL(output),tmp);
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			tmp);	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		gtk_entry_set_text(GTK_ENTRY(output),tmp);
		return;
	}
	on_button70_clicked  (button,user_data);
}


void
on_treeview23_row_activated            (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	gchar* id;
    gchar* nom;
    gchar* prenom;
    gchar* email;
    gchar* tele;
    gchar* adresse;
    gchar* csexe;
    gchar* dn;
    gchar* municipalite;
	
	GtkWidget* output;
	output = lookup_widget(treeview, "entry59") ;

	GtkTreeModel *model = gtk_tree_view_get_model(treeview);

	if(gtk_tree_model_get_iter(model,&iter,path))
	{
		gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,1,&nom,2,&prenom,3,&email,4,&tele,5,&adresse,6,&csexe,7,&dn,8,&municipalite,-1);
		gtk_entry_set_text(GTK_ENTRY(output),id);
		on_button26_clicked(treeview,user_data);
	}//*/
}

void//treeview10
on_button64_clicked                    (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *liste = lookup_widget(button, "treeview10");
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	tAvis t;
	char tri[]="tris_parking.txt";
	trier_par_note(bdd_avis,tri);

    char id_parking[50];
    char note[50];
	char n[50];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID PARKING",renderer,"text",0,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("NOTE",renderer,"text",1,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("NOMBRE D'AVIS",renderer,"text",2,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
	}
	
	store=gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	
	FILE *f = fopen(tri,"a+");
	if(f==NULL) return;
	while(fscanf(f,"%d %d %f\n",&t.id_parking,&t.n,&t.note)!=EOF)
	{
		sprintf(id_parking,"%d",t.id_parking);
		sprintf(note,"%f",t.note);
		sprintf(n,"%d",t.n);
		
		gtk_list_store_append(store,&iter);
		gtk_list_store_set(store,&iter,0,id_parking,1,note,2,n,-1);
	
	}
	fclose(f);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
	g_object_unref(store);
}


void//recherche par id avis
on_button75_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	int id_avist;
	
	GtkWidget* input;

	char tmp[150];

	char res_rech[]="result.txt";

	input = lookup_widget(button, "entry120");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0) id_avist=str_to_int(tmp);
	else return;
	super_chercher_avis(bdd_avis,res_rech,id_avist,1,0,0,0,0);

	GtkWidget *liste = lookup_widget(button, "treeview24");
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	Avis t;

	char id_avis[50];
    char id_citoyen[50];
    char id_parking[50];
    char note[50];
    char comment[100];
    char dr[50];
    char motif[50];
    char type[50];
    char sex[50];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID AVIS",renderer,"text",0,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID CITOYEN",renderer,"text",1,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID PARKING",renderer,"text",2,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("NOTE",renderer,"text",3,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("COMMENT",renderer,"text",4,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("DATE",renderer,"text",5,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("MOTIF",renderer,"text",6,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("TYPE",renderer,"text",7,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("SEXE",renderer,"text",8,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
	}
	
	store=gtk_list_store_new(9, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	
	FILE *f = fopen(res_rech,"a+");
	if(f==NULL) return;
	while(fscanf(f,"%d %d %d %f %s %d %d %d %s %s %c\n",&t.id_avis,&t.id_citoyen,&t.id_parking,&t.note,t.comment,&t.dr_jour,&t.dr_mois,&t.dr_annee,t.motif,t.type,&t.sexe)!=EOF)
	{
		sprintf(id_avis,"%d",t.id_avis);
		sprintf(id_citoyen,"%d",t.id_citoyen);
		sprintf(id_parking,"%d",t.id_parking);
		sprintf(note,"%d",(int)t.note);
		strcpy(comment,t.comment);
		rep_under_space(t.comment);
		sprintf(dr,"%d/%d/%d",t.dr_jour,t.dr_mois,t.dr_annee);
		strcpy(motif,t.motif);
		rep_under_space(motif);
		if (t.type[0]=='o')
		{
			strcpy(type,"Rec");
			if (t.type[0]=='o')strcat(type," Rem");
		}
		else if (t.type[0]=='o')strcpy(type,"Rem");
		else strcpy(type,"None");
		if (t.sexe=='h') strcpy(sex,"Homme"); else strcpy(sex,"Femme");

		gtk_list_store_append(store,&iter);
		gtk_list_store_set(store,&iter,0,id_avis,1,id_citoyen,2,id_parking,3,note,4,comment,5,dr,6,motif,7,type,8,sex,-1);
	
	}
	fclose(f);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
	g_object_unref(store);//*/
}


void//recherche par id citoyen
on_button76_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	int id_citoyent;
	
	GtkWidget* input;

	char tmp[150];

	char res_rech[]="result.txt";

	input = lookup_widget(button, "entry121");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0) id_citoyent=str_to_int(tmp);
	else return;
	super_chercher_avis(bdd_avis,res_rech,0,0,id_citoyent,1,0,0);

	GtkWidget *liste = lookup_widget(button, "treeview24");
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	Avis t;

	char id_avis[50];
    char id_citoyen[50];
    char id_parking[50];
    char note[50];
    char comment[100];
    char dr[50];
    char motif[50];
    char type[50];
    char sex[50];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID AVIS",renderer,"text",0,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID CITOYEN",renderer,"text",1,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID PARKING",renderer,"text",2,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("NOTE",renderer,"text",3,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("COMMENT",renderer,"text",4,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("DATE",renderer,"text",5,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("MOTIF",renderer,"text",6,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("TYPE",renderer,"text",7,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("SEXE",renderer,"text",8,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
	}
	
	store=gtk_list_store_new(9, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	
	FILE *f = fopen(res_rech,"a+");
	if(f==NULL) return;
	while(fscanf(f,"%d %d %d %f %s %d %d %d %s %s %c\n",&t.id_avis,&t.id_citoyen,&t.id_parking,&t.note,t.comment,&t.dr_jour,&t.dr_mois,&t.dr_annee,t.motif,t.type,&t.sexe)!=EOF)
	{
		sprintf(id_avis,"%d",t.id_avis);
		sprintf(id_citoyen,"%d",t.id_citoyen);
		sprintf(id_parking,"%d",t.id_parking);
		sprintf(note,"%d",(int)t.note);
		strcpy(comment,t.comment);
		rep_under_space(t.comment);
		sprintf(dr,"%d/%d/%d",t.dr_jour,t.dr_mois,t.dr_annee);
		strcpy(motif,t.motif);
		rep_under_space(motif);
		if (t.type[0]=='o')
		{
			strcpy(type,"Rec");
			if (t.type[0]=='o')strcat(type," Rem");
		}
		else if (t.type[0]=='o')strcpy(type,"Rem");
		else strcpy(type,"None");
		if (t.sexe=='h') strcpy(sex,"Homme"); else strcpy(sex,"Femme");

		gtk_list_store_append(store,&iter);
		gtk_list_store_set(store,&iter,0,id_avis,1,id_citoyen,2,id_parking,3,note,4,comment,5,dr,6,motif,7,type,8,sex,-1);
	
	}
	fclose(f);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
	g_object_unref(store);//*/
}


void//recherche par id parking
on_button74_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	int id_parkingt;
	
	GtkWidget* input;

	char tmp[150];

	char res_rech[]="result.txt";

	input = lookup_widget(button, "entry122");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0) id_parkingt=str_to_int(tmp);
	else return;
	super_chercher_avis(bdd_avis,res_rech,0,0,0,0,id_parkingt,1);

	GtkWidget *liste = lookup_widget(button, "treeview24");
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	Avis t;

	char id_avis[50];
    char id_citoyen[50];
    char id_parking[50];
    char note[50];
    char comment[100];
    char dr[50];
    char motif[50];
    char type[50];
    char sex[50];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID AVIS",renderer,"text",0,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID CITOYEN",renderer,"text",1,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID PARKING",renderer,"text",2,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("NOTE",renderer,"text",3,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("COMMENT",renderer,"text",4,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("DATE",renderer,"text",5,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("MOTIF",renderer,"text",6,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("TYPE",renderer,"text",7,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("SEXE",renderer,"text",8,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
	}
	
	store=gtk_list_store_new(9, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	
	FILE *f = fopen(res_rech,"a+");
	if(f==NULL) return;
	while(fscanf(f,"%d %d %d %f %s %d %d %d %s %s %c\n",&t.id_avis,&t.id_citoyen,&t.id_parking,&t.note,t.comment,&t.dr_jour,&t.dr_mois,&t.dr_annee,t.motif,t.type,&t.sexe)!=EOF)
	{
		sprintf(id_avis,"%d",t.id_avis);
		sprintf(id_citoyen,"%d",t.id_citoyen);
		sprintf(id_parking,"%d",t.id_parking);
		sprintf(note,"%d",(int)t.note);
		strcpy(comment,t.comment);
		rep_under_space(t.comment);
		sprintf(dr,"%d/%d/%d",t.dr_jour,t.dr_mois,t.dr_annee);
		strcpy(motif,t.motif);
		rep_under_space(motif);
		if (t.type[0]=='o')
		{
			strcpy(type,"Rec");
			if (t.type[0]=='o')strcat(type," Rem");
		}
		else if (t.type[0]=='o')strcpy(type,"Rem");
		else strcpy(type,"None");
		if (t.sexe=='h') strcpy(sex,"Homme"); else strcpy(sex,"Femme");

		gtk_list_store_append(store,&iter);
		gtk_list_store_set(store,&iter,0,id_avis,1,id_citoyen,2,id_parking,3,note,4,comment,5,dr,6,motif,7,type,8,sex,-1);
	
	}
	fclose(f);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
	g_object_unref(store);//*/
}


/*
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "parking.h"
#include "support.h"
#include <ctype.h>*/


int recherche_par[3]={0,0,0}; // 0:id 1:nom: 2:region
int id_parking_affecter=-1;
int id_agent_affecter=-1;
int etat=0;
int id_p_a_modif=-1;

int is_only_digits(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

int is_only_alpha(const char *str) {
    while (*str) {
        if (!isalpha(*str)) {
            return 0;
        }
        str++;
    }
    return 1; 
}

int is_file_empty(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {

        return -1; 
    }


    fseek(file, 0, SEEK_END);
    long size = ftell(file); 
    fclose(file);

    return (size == 0); 
}

char est_couvert='N';
char supporte_pour_handicappe ='N';
char m_est_couvert='N';
char m_supporte_pour_handicappe ='N';


void
on_checkbutton_pcouvert_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
	{
		est_couvert ='Y';
	}

}
void
on_checkbutton_pnoncouvert_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
	{
		est_couvert ='N';
	}

}



void on_button_p_ajouter_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
	GtkWidget *nom;
	GtkWidget *adresse;
	GtkWidget *region;
	GtkWidget *places;
	GtkWidget *nbetages;
	GtkWidget *couvert;
	GtkWidget *numero;
	GtkWidget *tarif;
	Parking p;

	nom=lookup_widget(objet_graphique,"p_nomtextentry");
	adresse=lookup_widget(objet_graphique,"p_adressetextentry");
	region=lookup_widget(objet_graphique,"combobox_p_regionentry");
	places=lookup_widget(objet_graphique,"spinbutton_pplacesentry");
	nbetages=lookup_widget(objet_graphique,"spinbutton_pnbetageentry");

	numero=lookup_widget(objet_graphique,"p_numero_textentry");
	tarif=lookup_widget(objet_graphique,"p_tariftextentry");

	strcpy(p.nom,gtk_entry_get_text(GTK_ENTRY(nom)));
	strcpy(p.adresse,gtk_entry_get_text(GTK_ENTRY(adresse)));
	const char *tarif_text = gtk_entry_get_text(GTK_ENTRY(tarif));
    
        if (tarif_text != NULL && tarif_text[0] != '\0') 
	{
        	p.tarif = atoi(tarif_text); 
    	} else  {
        		p.tarif = 0; 
    		}

	const char *numero_text = gtk_entry_get_text(GTK_ENTRY(numero));
    
        if (numero_text != NULL && numero_text[0] != '\0') 
	{
        	p.numero_de_telephone = atoi(numero_text); 
    	} 
	else  
	{
        	p.numero_de_telephone = 0; 
    	}
	

	strcpy(p.region,gtk_combo_box_get_active_text(GTK_COMBO_BOX(region)));
	p.capacite=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(places));
	p.nbetages=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(nbetages));
	p.est_couvert=est_couvert;
	p.supporte_pour_handicappe=supporte_pour_handicappe;





	
	if (strlen(p.nom) == 0) {
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                               "Le champ 'Nom' est obligatoire !");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		return;
	}
	if (!is_only_alpha(p.nom)) {
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Le champ 'Nom' doit contenir uniquement des lettres !");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		return;
	}

	if (gtk_combo_box_get_active(GTK_COMBO_BOX(region)) == -1) {
    		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                               	GTK_DIALOG_MODAL,
                                               	GTK_MESSAGE_ERROR,
                                               	GTK_BUTTONS_OK,
                                               	"Veuillez sélectionner une région !");
		gtk_dialog_run(GTK_DIALOG(dialog));
                gtk_widget_destroy(dialog);
                return;
	}



	if (strlen(p.adresse) == 0) {
        	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Le champ 'Adresse' est obligatoire !");
        	gtk_dialog_run(GTK_DIALOG(dialog));
        	gtk_widget_destroy(dialog);
        	return;
	}

	if (!is_only_digits(tarif_text)) {
            		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Le champ 'tarif' doit contenir uniquement des chiffres !");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
			return;

	}



	if (p.tarif <= 0) 
	{
	    	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
	                                               GTK_DIALOG_MODAL,
	                                               GTK_MESSAGE_ERROR,
	                                               GTK_BUTTONS_OK,
	                                               "Veuillez saisir un tarif valide !");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
    		return;
	}

	
	if(strlen(numero_text)!=8  ) {
            		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Le champ 'Numero de telephone' doit contenir 8  chiffres !");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
			return;
	
	
	}
	
	if (numero_text != NULL && strlen(numero_text)==8) {
        	if (!is_only_digits(numero_text)) {
            		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Le champ 'Numero de telephone' doit contenir uniquement des chiffres !");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
			return;
        }









	char msg [100];
	sprintf(msg,"Parking ajouté avec succès  !");
	ajouterParking("parking.txt",p);
	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               msg);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	}


	
	

}
void
on_non_supp_radio_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	{
		supporte_pour_handicappe='N';
	}

}




void on_radiobutton_psupportepourhandicappe_toggled(GtkToggleButton *togglebutton, gpointer user_data)
   

{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	{
		supporte_pour_handicappe='Y';
	}

}









void on_modifier_selectbutton_clicked(GtkWidget *objet_graphique, gpointer user_data) {
    GtkWidget* id;
    GtkWidget* nom;
    GtkWidget* adresse;
    GtkWidget* region;
    GtkWidget* capacite;
    GtkWidget* nbetages;
    GtkWidget* couvert;
    GtkWidget* supp;
    GtkWidget* numero;
    GtkWidget* tarif;
    int idr;
    char capacite_str[20];
    char nbetages_str[20];
    char numero_str[20];
    char tarif_str[20];
    char msg[50];

    id = lookup_widget(objet_graphique, "modifier_id");
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(id));

    if (!is_only_digits(id_text)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Le champ 'id' doit contenir uniquement des chiffres !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    } else {
        idr = atoi(id_text);
    }

    Parking p = rechercherParking("parking.txt", idr);
    if (p.id==-1) {

	
	sprintf(msg,"parking %d introuvable",idr);
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   msg);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
	return;

   }
    id_p_a_modif=idr;

    sprintf(capacite_str, "%d", p.capacite);
    sprintf(nbetages_str, "%d", p.nbetages);
    sprintf(tarif_str, "%d", p.tarif); 
    sprintf(numero_str, "%d", p.numero_de_telephone);

    char* couvert_str = (p.est_couvert == 'Y') ? "Oui" : "Non";
    char* supp_str = (p.supporte_pour_handicappe == 'Y') ? "Oui" : "Non";

    nom = lookup_widget(objet_graphique, "nomlabel");
    region = lookup_widget(objet_graphique, "regionlabel");
    adresse = lookup_widget(objet_graphique, "adresselabel");
    tarif = lookup_widget(objet_graphique, "tariflabel");
    capacite = lookup_widget(objet_graphique, "placeslabel");
    supp = lookup_widget(objet_graphique, "supplabel");
    numero = lookup_widget(objet_graphique, "numerolabel");
    nbetages = lookup_widget(objet_graphique, "nbetagelabel");
    couvert = lookup_widget(objet_graphique, "couvertlabel");

    gtk_label_set_text(GTK_LABEL(nom), p.nom);
    gtk_label_set_text(GTK_LABEL(region), p.region);
    gtk_label_set_text(GTK_LABEL(adresse), p.adresse);
    gtk_label_set_text(GTK_LABEL(capacite), capacite_str);
    gtk_label_set_text(GTK_LABEL(nbetages), nbetages_str);
    gtk_label_set_text(GTK_LABEL(couvert), couvert_str);
    gtk_label_set_text(GTK_LABEL(supp), supp_str);
    gtk_label_set_text(GTK_LABEL(tarif), tarif_str);
    gtk_label_set_text(GTK_LABEL(numero), numero_str);




	GtkWidget *mnom;
	GtkWidget *mid;
	GtkWidget *madresse;
	GtkWidget *mregion;
	GtkWidget *mplaces;
	GtkWidget *mnbetages;
	GtkWidget *mcouvert;
	GtkWidget *mnumero;
	GtkWidget *mtarif;
	GtkWidget *output;
	mnom=lookup_widget(objet_graphique,"modifier_pnom");
	madresse=lookup_widget(objet_graphique,"modifier_padresse");
	mregion=lookup_widget(objet_graphique,"combobox_modifier_pregion");
	mplaces=lookup_widget(objet_graphique,"modifier_pplaces");
	mnbetages=lookup_widget(objet_graphique,"modifier_pnbetages");

	mnumero=lookup_widget(objet_graphique,"modifier_pnumero");
	mtarif=lookup_widget(objet_graphique,"modifier_ptarif");
	gtk_entry_set_text(GTK_ENTRY(mnom),p.nom);
	gtk_entry_set_text(GTK_ENTRY(madresse),p.adresse);
	gtk_entry_set_text(GTK_ENTRY(mnumero),numero_str);
	gtk_entry_set_text(GTK_ENTRY(mtarif),tarif_str);
	if (p.est_couvert=='Y') {
		output = lookup_widget(objet_graphique, "check_modifier_pcouvert") ;
		
		gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),TRUE);
	}
	else {
		
		output = lookup_widget(objet_graphique, "check_modifier_pnoncouvert") ;
		gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),TRUE);
	}
	if (p.supporte_pour_handicappe=='Y') {
		output = lookup_widget(objet_graphique, "radiobutton_modifier_psup") ;
		
		gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),TRUE);
	}
	else {
		
		output = lookup_widget(objet_graphique, "radiobutton_modifier_psup") ;
		gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),TRUE);
	}
	
	
	
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(mplaces),p.capacite);

	gtk_spin_button_set_value(GTK_SPIN_BUTTON(mnbetages),p.nbetages);

	
	
	gtk_combo_box_set_active(GTK_COMBO_BOX(mregion),0);
	int i=0;//gtk_combo_box_get_active_text(GTK_COMBO_BOX(input))
	while (i<24&&(strcmp(p.region,gtk_combo_box_get_active_text(GTK_COMBO_BOX(mregion)))!=0)){
		gtk_combo_box_set_active(GTK_COMBO_BOX(mregion),i);
		i++;
	}
	
	
}






void
on_radiobutton_modifier_pnonsup_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	{
		m_supporte_pour_handicappe='N';
	}

}
void
on_radiobutton_modifier_psup_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	{
		m_supporte_pour_handicappe='Y';
	}
}


void
on_check_modifier_pcouvert_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
	{
		m_est_couvert ='Y';
	}


}








void
on_modfier_p_annuler_clicked           (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	
	    GtkWidget *dialog;
            GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique));

            dialog = gtk_message_dialog_new(
                parent_window,
                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_QUESTION,
                GTK_BUTTONS_YES_NO,
                "Êtes-vous sûr de vouloir annuler la modification ?"
            );

            gtk_message_dialog_format_secondary_text(
                GTK_MESSAGE_DIALOG(dialog),
                "Cette action est irréversible."
            );

            gint response = gtk_dialog_run(GTK_DIALOG(dialog));

            if (response == GTK_RESPONSE_YES) {


		gtk_widget_destroy(dialog);
                GtkWidget *success_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    "Modification annuleé."
                );
                gtk_dialog_run(GTK_DIALOG(success_dialog));
                gtk_widget_destroy(success_dialog);

            } else if (response == GTK_RESPONSE_NO) {

		gtk_widget_destroy(dialog);
                GtkWidget *cancel_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    "Annulation annulée."
                );
                gtk_dialog_run(GTK_DIALOG(cancel_dialog));
                gtk_widget_destroy(cancel_dialog);
		return;
            }



	



    GtkWidget* id;
    GtkWidget* nom;
    GtkWidget* adresse;
    GtkWidget* region;
    GtkWidget* capacite;
    GtkWidget* nbetages;
    GtkWidget* couvert;
    GtkWidget* supp;
    GtkWidget* numero;
    GtkWidget* tarif;
    int idr;
    char capacite_str[20];
    char nbetages_str[20];
    char numero_str[20];
    char tarif_str[20];

    id = lookup_widget(objet_graphique, "modifier_id");
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(id));

    if (!is_only_digits(id_text)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Le champ 'id' doit contenir uniquement des chiffres !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    } else {
        idr = atoi(id_text);

    }

    Parking p = rechercherParking("parking.txt", idr);
    char msg[100];

 




    nom = lookup_widget(objet_graphique, "nomlabel");
    region = lookup_widget(objet_graphique, "regionlabel");
    adresse = lookup_widget(objet_graphique, "adresselabel");
    tarif = lookup_widget(objet_graphique, "tariflabel");
    capacite = lookup_widget(objet_graphique, "placeslabel");
    supp = lookup_widget(objet_graphique, "supplabel");
    numero = lookup_widget(objet_graphique, "numerolabel");
    nbetages = lookup_widget(objet_graphique, "nbetagelabel");
    couvert = lookup_widget(objet_graphique, "couvertlabel");

    gtk_label_set_text(GTK_LABEL(nom), "");
    gtk_label_set_text(GTK_LABEL(region), "");
    gtk_label_set_text(GTK_LABEL(adresse), "");
    gtk_label_set_text(GTK_LABEL(capacite), "");
    gtk_label_set_text(GTK_LABEL(nbetages), "");
    gtk_label_set_text(GTK_LABEL(couvert), "");
    gtk_label_set_text(GTK_LABEL(supp), "");
    gtk_label_set_text(GTK_LABEL(tarif), "");
    gtk_label_set_text(GTK_LABEL(numero), "");




	GtkWidget *mnom;
	GtkWidget *mid;
	GtkWidget *madresse;
	GtkWidget *mregion;
	GtkWidget *mplaces;
	GtkWidget *mnbetages;
	GtkWidget *mcouvert;
	GtkWidget *mnumero;
	GtkWidget *mtarif;
	GtkWidget *output;
	mnom=lookup_widget(objet_graphique,"modifier_pnom");
	madresse=lookup_widget(objet_graphique,"modifier_padresse");
	mregion=lookup_widget(objet_graphique,"combobox_modifier_pregion");
	mplaces=lookup_widget(objet_graphique,"modifier_pplaces");
	mnbetages=lookup_widget(objet_graphique,"modifier_pnbetages");

	mnumero=lookup_widget(objet_graphique,"modifier_pnumero");
	mtarif=lookup_widget(objet_graphique,"modifier_ptarif");
	gtk_entry_set_text(GTK_ENTRY(mnom),"");
	gtk_entry_set_text(GTK_ENTRY(madresse),"");
	gtk_entry_set_text(GTK_ENTRY(mnumero),"");
	gtk_entry_set_text(GTK_ENTRY(mtarif),"");

	output = lookup_widget(objet_graphique, "check_modifier_pcouvert") ;
		
	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),FALSE);
	
	
	output = lookup_widget(objet_graphique, "check_modifier_pnoncouvert") ;
	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),FALSE);
	

	output = lookup_widget(objet_graphique, "radiobutton_modifier_psup") ;
		
	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),FALSE);
	
		
	output = lookup_widget(objet_graphique, "radiobutton_modifier_psup") ;
	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),FALSE);
	
	
	
	
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(mplaces),0.0);

	gtk_spin_button_set_value(GTK_SPIN_BUTTON(mnbetages),0.0);

	
	
	gtk_combo_box_set_active(GTK_COMBO_BOX(mregion),-1);
	
	














}














void
on_modifier_p_button_clicked (GtkWidget *objet_graphique, gpointer user_data)



{ 
	if(id_p_a_modif==-1){
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Utilisez le boutton 'Selectioner' au premier lieux");
        	gtk_dialog_run(GTK_DIALOG(dialog));
        	gtk_widget_destroy(dialog);
		return;
		
	}	
	
	GtkWidget *nom;
	GtkWidget *id;
	GtkWidget *adresse;
	GtkWidget *region;
	GtkWidget *places;
	GtkWidget *nbetages;
	GtkWidget *couvert;
	GtkWidget *numero;
	GtkWidget *tarif;
	Parking p;
	int idr;
	id = lookup_widget(objet_graphique, "modifier_id");
	const char *id_text = gtk_entry_get_text(GTK_ENTRY(id));

	if (!is_only_digits(id_text)) {
        	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Le champ 'id' doit contenir uniquement des chiffres !");
        	gtk_dialog_run(GTK_DIALOG(dialog));
        	gtk_widget_destroy(dialog);
        	return;
	} else {
        	idr = atoi(id_text);
    	}

	nom=lookup_widget(objet_graphique,"modifier_pnom");
	adresse=lookup_widget(objet_graphique,"modifier_padresse");
	region=lookup_widget(objet_graphique,"combobox_modifier_pregion");
	places=lookup_widget(objet_graphique,"modifier_pplaces");
	nbetages=lookup_widget(objet_graphique,"modifier_pnbetages");

	numero=lookup_widget(objet_graphique,"modifier_pnumero");
	tarif=lookup_widget(objet_graphique,"modifier_ptarif");

	strcpy(p.nom,gtk_entry_get_text(GTK_ENTRY(nom)));
	strcpy(p.adresse,gtk_entry_get_text(GTK_ENTRY(adresse)));
	const char *tarif_text = gtk_entry_get_text(GTK_ENTRY(tarif));
    
        if (tarif_text != NULL && tarif_text[0] != '\0') 
	{
        	p.tarif = atoi(tarif_text); 
    	} else  {
        		p.tarif = 0; 
    		}

	const char *numero_text = gtk_entry_get_text(GTK_ENTRY(numero));
    
        if (numero_text != NULL && numero_text[0] != '\0') 
	{
        	p.numero_de_telephone = atoi(numero_text); 
    	} 
	else  
	{
        	p.numero_de_telephone = 0; 
    	}
	

	strcpy(p.region,gtk_combo_box_get_active_text(GTK_COMBO_BOX(region)));
	p.capacite=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(places));
	p.nbetages=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(nbetages));
	p.est_couvert=m_est_couvert;
	p.supporte_pour_handicappe=m_supporte_pour_handicappe;





	
	if (strlen(p.nom) == 0) {
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                               "Le champ 'Nom' est obligatoire !");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		return;
	}
	if (!is_only_alpha(p.nom)) {
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Le champ 'Nom' doit contenir uniquement des lettres !");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		return;
	}

	if (gtk_combo_box_get_active(GTK_COMBO_BOX(region)) == -1) {
    		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                               	GTK_DIALOG_MODAL,
                                               	GTK_MESSAGE_ERROR,
                                               	GTK_BUTTONS_OK,
                                               	"Veuillez sélectionner une région !");
		gtk_dialog_run(GTK_DIALOG(dialog));
                gtk_widget_destroy(dialog);
                return;
	}



	if (strlen(p.adresse) == 0) {
        	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Le champ 'Adresse' est obligatoire !");
        	gtk_dialog_run(GTK_DIALOG(dialog));
        	gtk_widget_destroy(dialog);
        	return;
	}




	if (p.tarif <= 0) 
	{
	    	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
	                                               GTK_DIALOG_MODAL,
	                                               GTK_MESSAGE_ERROR,
	                                               GTK_BUTTONS_OK,
	                                               "Veuillez saisir un tarif valide !");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
    		return;
	}

	
	
	if (numero_text != NULL && strlen(numero_text)==8) {
        	if (!is_only_digits(numero_text)) {
            		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Le champ 'Numero de telephone' doit contenir uniquement des chiffres !");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
			return;
        }





	    char msg [120];
	    GtkWidget *dialog;
            GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique));
	    sprintf(msg,"Êtes-vous sûr de vouloir modifier le Parking %d ?",idr);
            dialog = gtk_message_dialog_new(
                parent_window,
                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_QUESTION,
                GTK_BUTTONS_YES_NO,
                msg
            );

            gtk_message_dialog_format_secondary_text(
                GTK_MESSAGE_DIALOG(dialog),
                "Cette action est irréversible."
            );

            gint response = gtk_dialog_run(GTK_DIALOG(dialog));

            if (response == GTK_RESPONSE_YES) {

		modifierParking("parking.txt", idr, p);
		id_p_a_modif=-1;
		sprintf(msg,"Parking %d modifié avec succès.",idr);
		gtk_widget_destroy(dialog);
                GtkWidget *success_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    msg
                );
                gtk_dialog_run(GTK_DIALOG(success_dialog));
                gtk_widget_destroy(success_dialog);

            } else if (response == GTK_RESPONSE_NO) {

		gtk_widget_destroy(dialog);
                GtkWidget *cancel_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    "modification annulée."
                );
                gtk_dialog_run(GTK_DIALOG(cancel_dialog));
                gtk_widget_destroy(cancel_dialog);
            }







	}


	
	

}





void
on_check_modifier_pnoncouvert_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
	{
		m_est_couvert ='N';
	}

}


void
on_suppreimer_p_button_clicked(GtkWidget *objet_graphique, gpointer user_data) {
    int idr;
    GtkWidget *id;
    id = lookup_widget(objet_graphique, "supprimer_p_identry");
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(id));
    char msg[100];


    if (!is_only_digits(id_text)) {
        GtkWidget *dialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Le champ 'id' doit contenir uniquement des chiffres !"
        );
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    } else {
        idr = atoi(id_text); 
        Parking p = rechercherParking("parking.txt", idr); 

        if (p.id == -1) { 
	    sprintf(msg,"Parking %d introuvable",idr);
            GtkWidget *dialog = gtk_message_dialog_new(
                GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_ERROR,
                GTK_BUTTONS_OK,
                msg
            );
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;


        } else {
	    sprintf(msg,"Êtes-vous sûr de vouloir supprimer le Parking %d ?",idr);
            GtkWidget *dialog;
            GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique));

            dialog = gtk_message_dialog_new(
                parent_window,
                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_QUESTION,
                GTK_BUTTONS_YES_NO,
                msg
            );

            gtk_message_dialog_format_secondary_text(
                GTK_MESSAGE_DIALOG(dialog),
                "Cette action est irréversible."
            );

            gint response = gtk_dialog_run(GTK_DIALOG(dialog));

            if (response == GTK_RESPONSE_YES) {

                supprimerParking("parking.txt", idr);
		gtk_widget_destroy(dialog);
                GtkWidget *success_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    "Parking supprimé avec succès."
                );
                gtk_dialog_run(GTK_DIALOG(success_dialog));
                gtk_widget_destroy(success_dialog);

            } else if (response == GTK_RESPONSE_NO) {

		gtk_widget_destroy(dialog);
                GtkWidget *cancel_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    "Suppression annulée."
                );
                gtk_dialog_run(GTK_DIALOG(cancel_dialog));
                gtk_widget_destroy(cancel_dialog);
            }


            
        }
    }
}







void on_rechercher_p_button_clicked(GtkWidget *objet_graphique, gpointer user_data) {
    
    int empty ;
    char msg[120];

    GtkWidget *treeview_chercher_parking;
    treeview_chercher_parking = lookup_widget(objet_graphique, "treeview_p_rechercher");


    if (!treeview_chercher_parking) {
        g_warning("Treeview not found!");
        return;
    }


    vider(treeview_chercher_parking);

    if ((recherche_par[0] == 1) && (recherche_par[2] == 0) &&(recherche_par[1]==0)) {

        GtkWidget *id;
	GtkWidget *output;
	output=lookup_widget(objet_graphique,"check_rechercher_p_id");
        id = lookup_widget(objet_graphique, "rechercher_p_id");
	int idr;

        if (!id) {
            g_warning("Nom entry not found!");
            return;
        }

        char id_str[100];
        g_strlcpy(id_str, gtk_entry_get_text(GTK_ENTRY(id)), sizeof(id_str));

        if (strlen(id_str) > 0) {
	    idr=atoi(id_str);
            rechercherParking("parking.txt", idr);

            afficher_parking("parid.txt", treeview_chercher_parking);
        }

        recherche_par[0] = 0;
	//gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),FALSE);
        empty = is_file_empty("parid.txt");
	if (empty==1){
		sprintf(msg,"Parking %d introuvble ",idr);
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                               msg);
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
	}
		
 
        return;
    }

    if ((recherche_par[1] == 1) && (recherche_par[2] == 0)) {

        GtkWidget *nom;
        nom = lookup_widget(objet_graphique, "rechercher_p_nom");

        if (!nom) {
            g_warning("Nom entry not found!");
            return;
        }

        char nom_str[100];
        g_strlcpy(nom_str, gtk_entry_get_text(GTK_ENTRY(nom)), sizeof(nom_str));

        if (strlen(nom_str) > 0) {
            rechercherParkingParNom("parking.txt", nom_str);

            afficher_parking("parnom.txt", treeview_chercher_parking);
        }

        //recherche_par[1] = 0;
	GtkWidget *output;
	output=lookup_widget(objet_graphique,"check_rechercher_p_nom");
	//gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),FALSE); 
	empty = is_file_empty("parnom.txt");
	if (empty==1){
		sprintf(msg,"Pas de parking avec le nom '%s' ",nom_str);
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                               msg);
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
	} 
        return;

    }

    if ((recherche_par[2] == 1) && (recherche_par[1] == 0)) {

        GtkWidget *region;
        region = lookup_widget(objet_graphique, "rechercher_p_region");

        if (!region) {
            g_warning("Region entry not found!");
            return;
        }

        char region_str[100];
        g_strlcpy(region_str, gtk_entry_get_text(GTK_ENTRY(region)), sizeof(region_str));

        if (strlen(region_str) > 0) {
            rechercherParkingParRegion("parking.txt", region_str);

            afficher_parking("parregion.txt", treeview_chercher_parking);
        }

        //recherche_par[2] = 0;
	GtkWidget *output;
	output=lookup_widget(objet_graphique,"check_rechercher_p_region");
	//gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),FALSE);
	empty = is_file_empty("parregion.txt");
	if (empty==1){
		sprintf(msg,"Pas de parkings dans '%s'",region_str);
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                               msg);
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
	} 
	 
        return;
    }

    if ((recherche_par[2] == 1) && (recherche_par[1] == 1)){
        GtkWidget *nom, *region;
        nom = lookup_widget(objet_graphique, "rechercher_p_nom");
        region = lookup_widget(objet_graphique, "rechercher_p_region");

        if (!nom || !region) {
            g_warning("Required entry widget(s) not found!");
            return;
        }

        char nom_str[100], region_str[100];
        g_strlcpy(nom_str, gtk_entry_get_text(GTK_ENTRY(nom)), sizeof(nom_str));
        g_strlcpy(region_str, gtk_entry_get_text(GTK_ENTRY(region)), sizeof(region_str));

        if (strlen(nom_str) > 0 && strlen(region_str) > 0) {
            rechercherParkingParNometRegion("parking.txt", nom_str, region_str);

            afficher_parking("parnometregion.txt", treeview_chercher_parking);
        }

        //recherche_par[1] = 0;
        //recherche_par[2] = 0;
	/*GtkWidget *output;
	output=lookup_widget(objet_graphique,"check_rechercher_p_nom");
	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),FALSE);
	output=lookup_widget(objet_graphique,"check_rechercher_p_region");
	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),FALSE);*/
	empty = is_file_empty("parnometregion.txt");
	if (empty==1){
		sprintf(msg,"Pas de parkings avec le nom '%s' dans '%s'",nom_str,region_str);
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                               msg);
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
	}
        return;
    }




}





void
on_check_rechercher_p_id_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	GtkWidget *output;
	output=lookup_widget(togglebutton,"check_rechercher_p_nom");
	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),FALSE);
	output=lookup_widget(togglebutton,"check_rechercher_p_region");
	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),FALSE);
 

	recherche_par[0]=1;
	if (!gtk_toggle_button_get_active(togglebutton)) {
		recherche_par[0]=0;;
	}



}


void
on_check_rechercher_p_region_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{


	if (etat==1) return;
	if (recherche_par[0]==1){
		etat=1;
		GtkWidget *output;
		output=lookup_widget(togglebutton,"check_rechercher_p_nom");
		gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),FALSE);
		output=lookup_widget(togglebutton,"check_rechercher_p_region");
		gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),FALSE);
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(togglebutton)),
	                                               GTK_DIALOG_MODAL,
	                                               GTK_MESSAGE_ERROR,
	                                               GTK_BUTTONS_OK,
	                                               "Vous ne pouvez pas selctioner ce critere lorsque le critere 'id' est selectionne");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		etat=0;
		return;
	}

	recherche_par[2]=1;
	if (!gtk_toggle_button_get_active(togglebutton)) {
		recherche_par[2]=0;;
	}
		
		

}


void
on_check_rechercher_p_nom_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{


	if (etat==1) return;
	if (recherche_par[0]==1){
		etat=1;
		GtkWidget *output;
		output=lookup_widget(togglebutton,"check_rechercher_p_nom");
		gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),FALSE);
		output=lookup_widget(togglebutton,"check_rechercher_p_region");
		gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),FALSE);
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(togglebutton)),
	                                               GTK_DIALOG_MODAL,
	                                               GTK_MESSAGE_ERROR,
	                                               GTK_BUTTONS_OK,
	                                               "Vous ne pouvez pas selctioner ce critere lorsque le critere 'id' est selectionne");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		etat=0;
		return;
	}

	recherche_par[1]=1;
		if (!gtk_toggle_button_get_active(togglebutton)) {
		recherche_par[1]=0;;
	}

}

void
on_treeview_p_rechercher_row_activated (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data) {
    GtkTreeIter iter;
    gchar *id_str;
    int id;

    GtkTreeModel *model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path)) {

        gtk_tree_model_get(GTK_LIST_STORE(model), &iter,
                           0, &id_str,  
                           -1);

        
        id = atoi(id_str);
	char msg [120];
	    GtkWidget *dialog;
            GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_toplevel(treeview));
	    sprintf(msg,"Êtes-vous sûr de vouloir supprimer le Parking %d ?",id);
            dialog = gtk_message_dialog_new(
                parent_window,
                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_QUESTION,
                GTK_BUTTONS_YES_NO,
                msg
            );

            gtk_message_dialog_format_secondary_text(
                GTK_MESSAGE_DIALOG(dialog),
                "Cette action est irréversible."
            );

            gint response = gtk_dialog_run(GTK_DIALOG(dialog));

            if (response == GTK_RESPONSE_YES) {

        	supprimerParking("parking.txt", id);
		/*vider(treeview);
        	afficher_parking("parking.txt", treeview);*/
		on_rechercher_p_button_clicked(treeview,user_data);

		sprintf(msg,"Parking %d supprime avec succès.",id);
		gtk_widget_destroy(dialog);
                GtkWidget *success_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(gtk_widget_get_toplevel(treeview)),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    msg
                );
                gtk_dialog_run(GTK_DIALOG(success_dialog));
                gtk_widget_destroy(success_dialog);

            } else if (response == GTK_RESPONSE_NO) {

		gtk_widget_destroy(dialog);
                GtkWidget *cancel_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(gtk_widget_get_toplevel(treeview)),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    "suprission annulée."
                );
                gtk_dialog_run(GTK_DIALOG(cancel_dialog));
                gtk_widget_destroy(cancel_dialog);
            }
	




  
    }
}



void
on_treeview_afficher_parking_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	    GtkTreeIter iter;
    gchar *id_str;
    int id;

    GtkTreeModel *model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path)) {

        gtk_tree_model_get(GTK_LIST_STORE(model), &iter,
                           0, &id_str,  
                           -1);


        id = atoi(id_str);
            GtkWidget *dialog;
            GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_toplevel(treeview));

            dialog = gtk_message_dialog_new(
                parent_window,
                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_QUESTION,
                GTK_BUTTONS_YES_NO,
                "Êtes-vous sûr de vouloir supprimer ?"
            );

            gtk_message_dialog_format_secondary_text(
                GTK_MESSAGE_DIALOG(dialog),
                "Cette action est irréversible."
            );

            gint response = gtk_dialog_run(GTK_DIALOG(dialog));

            if (response == GTK_RESPONSE_YES) {

                supprimerParking("parking.txt", id);
		gtk_widget_destroy(dialog);
                GtkWidget *success_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(gtk_widget_get_toplevel(treeview)),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    "Parking supprimé avec succès."
                );
                gtk_dialog_run(GTK_DIALOG(success_dialog));
                gtk_widget_destroy(success_dialog);

            } else if (response == GTK_RESPONSE_NO) {

		gtk_widget_destroy(dialog);
                GtkWidget *cancel_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(gtk_widget_get_toplevel(treeview)),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    "Suppression annulée."
                );
                gtk_dialog_run(GTK_DIALOG(cancel_dialog));
                gtk_widget_destroy(cancel_dialog);
            }
  


        //supprimerParking("parking.txt", id);


	vider(treeview);
        afficher_parking("parking.txt", treeview);  
    }

}


void
on_aficher_parking_clicked (GtkWidget *objet_graphique, gpointer user_data)
{
	GtkWidget *treeview_aff_parking;
	treeview_aff_parking = lookup_widget(objet_graphique, "treeview_afficher_parking");


	if (!treeview_aff_parking) {
        	g_warning("Treeview not found!");
        	return;
	}


	vider(treeview_aff_parking);
	afficher_parking("parking.txt",treeview_aff_parking );
	

	

}


void on_affecter_agent_button_clicked(GtkWidget  *objet_graphique,gpointer user_data)
{
	
	GtkWidget *idparking,*idagent;
	idparking=lookup_widget(GTK_WIDGET(objet_graphique), "id_p_affecter_entry");
	idagent=lookup_widget(GTK_WIDGET(objet_graphique), "id_a_affecter_entry");
	int id_a,id_p;
	const char *id_text = gtk_entry_get_text(GTK_ENTRY(idparking));
	if (!is_only_digits(id_text)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Le champ 'id parking' doit contenir uniquement des chiffres !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
        } else {
        	id_p= atoi(id_text);
        }
	id_text = gtk_entry_get_text(GTK_ENTRY(idagent));
	if (!is_only_digits(id_text)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Le champ 'id agent' doit contenir uniquement des chiffres !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
        } else {
        	id_a= atoi(id_text);
        }
	
        Parking p = rechercherParking("parking.txt", id_p);
	if (p.id==-1) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "parking introuvable");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
	return;
	}
	agent a =rechercher_agent("agent.txt",id_a);
	if (a.cin_a==-1) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Agent introuvable");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
	return;
	}
//yesno
		
	    GtkWidget *dialog;
            GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique));
	    char msg [100];
	    sprintf(msg,"Êtes-vous sûr de vouloir affecter agent '%d' au parking '%d' ",id_a,id_p);

            dialog = gtk_message_dialog_new(
                parent_window,
                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_QUESTION,
                GTK_BUTTONS_YES_NO,
                msg
            );

            gtk_message_dialog_format_secondary_text(
                GTK_MESSAGE_DIALOG(dialog),
                ""
            );

            gint response = gtk_dialog_run(GTK_DIALOG(dialog));

            if (response == GTK_RESPONSE_YES) {
	    sprintf(msg,"Agent '%d'affecte au parking '%d' ",id_a,id_p);
	    affecteragent("parking.txt","agent.txt",id_p,id_a);


		gtk_widget_destroy(dialog);
                GtkWidget *success_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    msg
                );
                gtk_dialog_run(GTK_DIALOG(success_dialog));
                gtk_widget_destroy(success_dialog);

            } else if (response == GTK_RESPONSE_NO) {

		gtk_widget_destroy(dialog);
                GtkWidget *cancel_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    "Affectation annulée."
                );
                gtk_dialog_run(GTK_DIALOG(cancel_dialog));
                gtk_widget_destroy(cancel_dialog);
		return;
            }

	


	

}


void
on_affecter_treeview_parking_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
    GtkTreeIter iter;
    gchar *id_str;
    
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path)) {

        gtk_tree_model_get(GTK_LIST_STORE(model), &iter,
                           0, &id_str,  
                           -1);

        
	char idp_text[20];
        id_parking_affecter = atoi(id_str);
	sprintf(idp_text, "%d" ,id_parking_affecter);
	GtkWidget *entry = lookup_widget(GTK_WIDGET(treeview), "id_p_affecter_entry");
	gtk_entry_set_text(GTK_ENTRY(entry),idp_text);


        

        


        g_free(id_str);
    }
}



void
on_affecte_treeview_agent_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
    GtkTreeIter iter;
    gchar *id_str;

    
    

    GtkTreeModel *model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path)) {

        gtk_tree_model_get(GTK_LIST_STORE(model), &iter,
                           0, &id_str,  
                           -1);

        id_agent_affecter =atoi(id_str);
	char ida_text[20];

	sprintf(ida_text, "%d" ,id_agent_affecter);
	GtkWidget *entry = lookup_widget(GTK_WIDGET(treeview), "id_a_affecter_entry");
	gtk_entry_set_text(GTK_ENTRY(entry),ida_text);

	
	g_free(id_str);
	

	}
}


void
on_affecteragent_afficherbutton_clicked
                                        (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *treeview_affecter_parking;
	treeview_affecter_parking = lookup_widget(objet_graphique, "affecter_treeview_parking");


	if (!treeview_affecter_parking) {
        	g_warning("Treeview not found!");
        	return;
	}


	vider(treeview_affecter_parking);
	afficher_parkingsansagent("parking.txt",treeview_affecter_parking );




	GtkWidget *treeview_affecter_agent;
	treeview_affecter_agent = lookup_widget(objet_graphique, "affecte_treeview_agent");


	if (!treeview_affecter_agent) {
        	g_warning("Treeview not found!");
        	return;
	}


	vider_agent(treeview_affecter_agent);
	afficheragentsansparking("agent.txt",treeview_affecter_agent );

}



//zaab

void
on_annul_ajout_button_clicked          (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
	

	GtkWidget *dialog;
            GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique));

            dialog = gtk_message_dialog_new(
                parent_window,
                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_QUESTION,
                GTK_BUTTONS_YES_NO,
                "Êtes-vous sûr de vouloir annuler l´ajout de ce parking ?"
            );

            gtk_message_dialog_format_secondary_text(
                GTK_MESSAGE_DIALOG(dialog),
                "Cette action est irréversible."
            );

            gint response = gtk_dialog_run(GTK_DIALOG(dialog));

            if (response == GTK_RESPONSE_YES) {


		gtk_widget_destroy(dialog);
                GtkWidget *success_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    "Ajout annuleé."
                );
                gtk_dialog_run(GTK_DIALOG(success_dialog));
                gtk_widget_destroy(success_dialog);

            } else if (response == GTK_RESPONSE_NO) {

		gtk_widget_destroy(dialog);
                GtkWidget *cancel_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    "Annulation annulée."
                );
                gtk_dialog_run(GTK_DIALOG(cancel_dialog));
                gtk_widget_destroy(cancel_dialog);
		return;
            }
	



	GtkWidget *nom;
	GtkWidget *adresse;
	GtkWidget *region;
	GtkWidget *places;
	GtkWidget *nbetages;
	GtkWidget *couvert;
	GtkWidget *numero;
	GtkWidget *tarif;


	nom=lookup_widget(objet_graphique,"p_nomtextentry");
	adresse=lookup_widget(objet_graphique,"p_adressetextentry");
	region=lookup_widget(objet_graphique,"combobox_p_regionentry");
	places=lookup_widget(objet_graphique,"spinbutton_pplacesentry");
	nbetages=lookup_widget(objet_graphique,"spinbutton_pnbetageentry");

	numero=lookup_widget(objet_graphique,"p_numero_textentry");
	tarif=lookup_widget(objet_graphique,"p_tariftextentry");
	gtk_entry_set_text(GTK_ENTRY(nom),"");
	gtk_entry_set_text(GTK_ENTRY(adresse),"");
	gtk_entry_set_text(GTK_ENTRY(numero),"");
	gtk_entry_set_text(GTK_ENTRY(tarif),"");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(places),0.0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(nbetages),0.0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(region),-1);
	GtkWidget *check_b;
	check_b=lookup_widget(objet_graphique,"checkbutton_pcouvert");
	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(check_b),FALSE);
	check_b=lookup_widget(objet_graphique,"checkbutton_pnoncouvert");
	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(check_b),FALSE);
	    
	



}


/*
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include "crud.h"
#include <stdlib.h>
#include <string.h>*/
#define base_service "service.txt"
#define AgentBDD "agent.txt"

service s;

char disponibilite[5] = "Oui";
char disponibilite0[5] = "Oui";
int id_m = -1 , i = -1 , e = -2;


void
on_radiobutton_a_oui_sv_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

    strcpy(disponibilite, "Oui");
	
}


void
on_radiobutton_a_d_sv_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    strcpy(disponibilite, "Non");
}


void
on_button_a_sv_clicked                 (GtkWidget       *ajout_sv,
                                        gpointer         user_data)
{
   	GtkWidget* input ;
	GtkWidget* output ;
	
	char tmp[150];
	
	output = lookup_widget(ajout_sv, "labela_sv") ;
	gtk_label_set_text(GTK_LABEL(output),"Vous pouvez commencez l'ajout");

    //id entry_a_id_sv
	
    input = lookup_widget(ajout_sv, "entry_a_id_sv");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0){
         s.id_sc=str_to_int(tmp);}
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Id non valide!");
		return;
	} 

    //nom entry_a_nom_sv


    input = lookup_widget(ajout_sv, "entry_a_nom_sv");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) {
	strcpy(s.nom_sc, tmp); }
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Nom invalide!");
		return;
	}
	//printf("%s\n",s.nom_sc);

    //description entry_a_des_sv

    input = lookup_widget(ajout_sv, "entry_a_des_sv");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) {
	strcpy(s.description,tmp); }
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"description invalide!");
		return;
	}


    // tarif  entry_a_ta_sv
    input = lookup_widget(ajout_sv, "entry_a_ta_sv");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0){
         s.tarif_sc=str_to_int(tmp);}
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Tarif invalide!");
		return;
	}
printf("%s\n",tmp);

    //parking associe combobox_pa_sv


    input=lookup_widget(ajout_sv,"combobox_pa_sv");
	if(gtk_combo_box_get_active_text(GTK_COMBO_BOX(input))!=NULL){
         strcpy(s.parking_associe,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input)));
    }else 
	{
		gtk_label_set_text(GTK_LABEL(output),"parking non invalide!");
		return;
	}
	printf("%s\n",s.parking_associe);

	 //diponibilite 
	/*
	if (disponibilite == "Oui"){
	s.disponibilte = 1 ; }
	else { s.disponibilte = 0 ;
		}
			*/		
	strcpy(s.disponibilte,disponibilite);


	//duree spinbutton
	
	input=lookup_widget(ajout_sv,"spinbuttonhh_sv");
	s.hh=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	//printf("hh %d\n",s.hh);
	input=lookup_widget(ajout_sv,"spinbuttonmm_sv");
	s.mm=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(ajout_sv,"spinbuttonss_sv");
	s.ss=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));

	
	int res = ajouter_service(base_service, s);
	if(res==-1){
		output = lookup_widget(ajout_sv, "labela_sv");
		gtk_label_set_text(GTK_LABEL(output),"Erreur lors de l'ajout!");
		return;
	}
	
	sprintf(tmp, "Ajout du service effectuer avec success! (ID=%d)", s.id_sc);
	printf("%s\n",tmp);
		gtk_label_set_text(GTK_LABEL(output),"Ajout du Service avec success!");
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(ajout_sv)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			tmp);	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);

    	


}


void
on_button_sup_aj_sv_clicked            (GtkWidget       *suppajt,
                                        gpointer         user_data)
{
	GtkWidget* input ;
	GtkWidget* output ;
	
	char tmp[150];
	
	output = lookup_widget(suppajt, "labela_sv") ;
	gtk_label_set_text(GTK_LABEL(output),"Vous pouvez recommencez l'ajout");

    //id entry_a_id_sv
	
    input = lookup_widget(suppajt, "entry_a_id_sv");
	gtk_entry_set_text(GTK_ENTRY(input),"");

    //nom entry_a_nom_sv

    input = lookup_widget(suppajt, "entry_a_nom_sv");
	gtk_entry_set_text(GTK_ENTRY(input),"");

    //description entry_a_des_sv

    input = lookup_widget(suppajt, "entry_a_des_sv");
	gtk_entry_set_text(GTK_ENTRY(input),"");
	
    // tarif  entry_a_ta_sv
    input = lookup_widget(suppajt, "entry_a_ta_sv");
	gtk_entry_set_text(GTK_ENTRY(input),"");
	
    //parking associe combobox_pa_sv


	input=lookup_widget(suppajt,"combobox_pa_sv");
        gtk_combo_box_set_active(GTK_COMBO_BOX(input),0);

	 //diponibilite 
			
	//strcpy(s.disponibilte,disponibilite);


	//duree spinbutton
	
	input=lookup_widget(suppajt,"spinbuttonhh_sv");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(input),0.0);

	input=lookup_widget(suppajt,"spinbuttonmm_sv");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(input),0.0);

	input=lookup_widget(suppajt,"spinbuttonss_sv");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(input),0.0);

	
	sprintf(tmp, "Recommencer l'ajout");
		gtk_label_set_text(GTK_LABEL(output),"Vous pouvez recommencer votre ajout");
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(suppajt)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			tmp);	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);

}


void
on_button_modif_sv_clicked             (GtkWidget       *mod,
                                        gpointer         user_data)
{
	service m;
	GtkWidget* input ;
	GtkWidget* output ;
	
	char tmp[150];
	
	output = lookup_widget(mod, "label_m_sv") ;
	gtk_label_set_text(GTK_LABEL(output),"Vous pouvez commencez la modification");

   
    //nom entry_a_nom_sv


    input = lookup_widget(mod, "entry_n_sv_m");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) {
	strcpy(m.nom_sc, tmp); }
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Nom invalide!");
		return;
	}
	//printf("%s\n",s.nom_sc);

    //description entry_a_des_sv

    input = lookup_widget(mod, "entry_d_sv_m");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) {
	strcpy(m.description,tmp); }
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"description invalide!");
		return;
	}


    // tarif  entry_a_ta_sv
    input = lookup_widget(mod, "entry_t_sv_m");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0){
	
         m.tarif_sc=str_to_int(tmp);}
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Tarif invalide!");
		return;
	}

    //parking associe combobox_pa_sv


    input=lookup_widget(mod,"combobox_m_sv");
	if(gtk_combo_box_get_active_text(GTK_COMBO_BOX(input))!=NULL){
         strcpy(m.parking_associe,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input)));
    }else 
	{
		gtk_label_set_text(GTK_LABEL(output),"parking non invalide!");
		return;
	}

	 //diponibilite 
	
	/*
	if (disponibilite == "Oui"){
	s.disponibilte = 1 ; }
	else { s.disponibilte = 0 ;
		}
			*/		
	strcpy(m.disponibilte,disponibilite0);
	m.id_sc=id_m;
	//duree spinbutton
	
	input=lookup_widget(mod,"spinbutton_hh_m");
	m.hh=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(mod,"spinbutton_mm_m");
	m.mm=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(mod,"spinbutton_ss_m");
	m.ss=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));

	
	int res = modifier_service(base_service, m);
	if(res==-1){
		output = lookup_widget(mod, "label_m_sv");
		gtk_label_set_text(GTK_LABEL(output),"Erreur lors de modification!");
		return;
	}
	
	sprintf(tmp, "Modification du service effectuer avec success! (ID=%d)", id_m);
		gtk_label_set_text(GTK_LABEL(output),"Modification du Service effectuer avec success!");
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(mod)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			tmp);	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
id_m = -1;

}


void
on_button_a_modif_sv_clicked           (GtkWidget       *smod,
                                        gpointer         user_data)
{
	char tmp[150];
	GtkWidget* input ;
	GtkWidget* output ;
	
	
	
	output = lookup_widget(smod, "label_m_sv") ;
	gtk_label_set_text(GTK_LABEL(output),"Vous pouvez recommencez la modification");

    //id entry_a_id_sv
	
    input = lookup_widget(smod, "entry_id_s_m");
	gtk_entry_set_text(GTK_ENTRY(input),"");

    //nom entry_a_nom_sv

    input = lookup_widget(smod, "entry_n_sv_m");
	gtk_entry_set_text(GTK_ENTRY(input),"");

    //description entry_a_des_sv

    input = lookup_widget(smod, "entry_d_sv_m");
	gtk_entry_set_text(GTK_ENTRY(input),"");
	
    // tarif  entry_a_ta_sv
    input = lookup_widget(smod, "entry_t_sv_m");
	gtk_entry_set_text(GTK_ENTRY(input),"");
	
    //parking associe combobox_pa_sv

	input=lookup_widget(smod,"combobox_m_sv");
	printf("00");
        gtk_combo_box_set_active(GTK_COMBO_BOX(input),-1);
	printf("001");

	 //diponibilite 
			
	//strcpy(s.disponibilte,disponibilite);


	//duree spinbutton
	
	input=lookup_widget(smod,"spinbutton_hh_m");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(input),0.0);

	input=lookup_widget(smod,"spinbutton_mm_m");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(input),0.0);

	input=lookup_widget(smod,"spinbutton_ss_m");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(input),0.0);
	
	sprintf(tmp,"Recommencer la modification");
		gtk_label_set_text(GTK_LABEL(output),"Vous pouvez recommencer la modification");
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(smod)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			tmp);	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);


}


void
on_checkbutton_o_m_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))strcpy(disponibilite0, "Oui");
}


void
on_checkbutton_n_m_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))strcpy(disponibilite0, "Non");
}


void
on_button_r_id_sv_m_clicked            (GtkWidget       *ridmod,
                                        gpointer         user_data)
{

	char tmp[150];
	GtkWidget* input ;
	GtkWidget* output ;
	service m;
	
	input = lookup_widget(ridmod, "entry_id_s_m");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0){
        	s.id_sc=str_to_int(tmp);
		id_m = s.id_sc;
		m =rechercher_service(base_service, id_m);

	}else {
		gtk_label_set_text(GTK_LABEL(output),"Id non valide!");
		return;
	}
	if (m.id_sc==-1){
		gtk_label_set_text(GTK_LABEL(output),"service introuvable");
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(ridmod)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			"service introuvable");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		return;
	}
	id_m = s.id_sc;
	

    //nom entry_a_nom_sv

    input = lookup_widget(ridmod, "entry_n_sv_m");
	gtk_entry_set_text(GTK_ENTRY(input),m.nom_sc);

    //description entry_a_des_sv

    input = lookup_widget(ridmod, "entry_d_sv_m");
	gtk_entry_set_text(GTK_ENTRY(input),m.description);
	
    // tarif  entry_a_ta_sv
    input = lookup_widget(ridmod, "entry_t_sv_m");
	sprintf(tmp, "%d", m.tarif_sc);
	gtk_entry_set_text(GTK_ENTRY(input),tmp);
	
    //parking associe combobox_pa_sv


	input=lookup_widget(ridmod,"combobox_m_sv");
	printf("01");
        gtk_combo_box_set_active(GTK_COMBO_BOX(input),0);
	printf("0");
	int i;
	while(i<24 && (strcmp(m.parking_associe,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input)))!=0)){
		gtk_combo_box_set_active(GTK_COMBO_BOX(input),i);
		i++;                                                                                     }

	 //diponibilite 
	/*		
	strcpy(s.disponibilte,disponibilite);*/
	if (strcmp(m.disponibilte,"Oui")==0) {
		output = lookup_widget(ridmod, "checkbutton_o_m") ;
		gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),TRUE);
		output = lookup_widget(ridmod, "checkbutton_n_m") ;
		gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),FALSE);
	}
	else {
		output = lookup_widget(ridmod, "checkbutton_n_m") ;
		gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),TRUE);
		output = lookup_widget(ridmod, "checkbutton_o_m") ;
		gtk_toggle_button_set_active(GTK_RADIO_BUTTON(output),FALSE);
	}


	//duree spinbutton
	
	input=lookup_widget(ridmod,"spinbutton_hh_m");
	sprintf(tmp, "%d", m.hh);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(input),m.hh);
	

	input=lookup_widget(ridmod,"spinbutton_mm_m");
	sprintf(tmp, "%d", m.mm);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(input),m.mm);

	input=lookup_widget(ridmod,"spinbutton_ss_m");
	sprintf(tmp, "%d", m.ss);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(input),m.ss);


	sprintf(tmp, "Vous pouvez commencer la modification (ID=%d)", id_m);

		gtk_label_set_text(GTK_LABEL(output),"Vous pouvez commencer la modification");
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(ridmod)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			tmp);	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
	

}


void
on_button_aff_sv_clicked               (GtkWidget       *afficher_sv,
                                        gpointer         user_data)
{

	GtkWidget *treeview ;
	treeview = lookup_widget(afficher_sv, "treeview_aff_sv");


	if (!treeview) {
        	g_warning("Treeview non trouvée !");
        	return;
	}
	vider_service(treeview);
	afficher_servicee(base_service, treeview);

}


void
on_button_supprimmer_sv_clicked        (GtkWidget       *supp_sv,
                                        gpointer         user_data)
{

	GtkWidget* input ;
	GtkWidget* output ;
	
	char tmp[150];
	
	int i;	
	
	//id
	input = lookup_widget(supp_sv, "entry_id_supp");
	output = lookup_widget(supp_sv, "label_supp_sv");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0) 	
	i=supprimer_service(base_service,str_to_int(tmp));
	else {
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(supp_sv)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			"ID invalide!");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		gtk_entry_set_text(GTK_ENTRY(output),"ID invalide!");
		return;
	}
	if(i!=0) {
		sprintf(tmp,"Service N°%d supprimé!",str_to_int(tmp));
		gtk_label_set_text(GTK_LABEL(output),tmp);
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(supp_sv)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			tmp);	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
	} else {
		sprintf(tmp,"Service N°%d introuvable!",str_to_int(tmp));
		gtk_label_set_text(GTK_LABEL(output),tmp);
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(supp_sv)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			tmp);	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		gtk_entry_set_text(GTK_ENTRY(output),"ID invalide!");
		return;

	}
	

}


void
on_button_rch_sv_clicked               (GtkWidget       *r_sv,
                                        gpointer         user_data)
{

	char tmp[10];
    	int id ;
	GtkWidget *treeview;
	treeview = lookup_widget(r_sv, "treeview_r_sv");
	printf("1");
	
	vider_service(treeview);
	printf("2");

        GtkWidget *input;
	GtkWidget *output;
	output=lookup_widget(r_sv,"label_rech_sv");
        input = lookup_widget(r_sv, "entry_id_re_sv");

        strcpy(tmp, gtk_entry_get_text(GTK_ENTRY(input)));
	printf("3");
	

        if (strlen(tmp) > 0) {
	    id=atoi(tmp);
            service s1 =rechercher_service(base_service,id);
	    if(s1.id_sc==-1) return;
	    printf("4");
	    ajouter_service("base_r_sv.txt", s1);
	    printf("5");
	    vider_service(treeview);
            afficher_servicee("base_r_sv.txt", treeview);
            printf("2"); 
	    remove("base_r_sv.txt");

	}
}


void
on_button_rech_affect_clicked          (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_button_affect_clicked               (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_button_a_agent_clicked              (GtkWidget       *a_ag,
                                        gpointer         user_data)
{
	agent a;

//label_aj_a int

	GtkWidget* input ;
	GtkWidget* output ;
	
	char tmp[150];
	
	output = lookup_widget(a_ag, "label_aj_a") ;
	gtk_label_set_text(GTK_LABEL(output),"Vous pouvez commencez l'ajout");

 
//cin entry_c_a_a int
	
    input = lookup_widget(a_ag, "entry_c_a_a");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0){
         a.cin_a=str_to_int(tmp);}
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Numero de CIN invalide!");
		return;
	} 


//nom entry_n_a_a  char

    input = lookup_widget(a_ag, "entry_n_a_a");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) {
	strcpy(a.nom, tmp); }
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Nom invalide!");
		return;
	}	
 
//prenom entr_p_a_a char

	input = lookup_widget(a_ag, "entry_p_a_a");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) {
	strcpy(a.prenom, tmp); }
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Prenom invalide!");
		return;
	}

//date naissance spin 3x

	//duree spinbutton
	
	input=lookup_widget(a_ag,"spinbutton_m_a_a");
	a.naissance.m=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(a_ag,"spinbutton_a_a_a");
	a.naissance.a=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(a_ag,"spinbutton_j_a_a");
	a.naissance.j=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));

	
	

//adress entry_adr_a_a char

	input = lookup_widget(a_ag, "entry_adr_a_a");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) {
	strcpy(a.adresse, tmp); }
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Adresse invalide!");
		return;
	}

//email entry_e_a_a char

	input = lookup_widget(a_ag, "entry_e_a_a");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) {
	strcpy(a.e_mail, tmp); }
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"E-mail invalide!");
		return;
	}

//salaire entry_sa_a_a float


	input = lookup_widget(a_ag, "entry_sa_a_a");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	int f=atof(tmp);
	if(str_is_int(tmp)&&strlen(tmp)!=0){
         a.salaire=f;}
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Salaire invalide!");
		return;
	}


//radiobutton sex int
	//sexe
	input=lookup_widget(a_ag,"radiobutton_a_h_agen");
	if (gtk_toggle_button_get_active(input)) a.sexe=0;
    	else a.sexe=1;	
	//a.sexe = i ;

//experience checkbox experience int

	//a.experience = e ;
	input=lookup_widget(a_ag,"checkbutton_o_m_a");
	e=gtk_toggle_button_get_active(input);
	printf("%d\n",e);
	if(e==0){a.experience=1;}
	else{a.experience=-2;}

	//parking affecter combobox_a_a
/*
 	input=lookup_widget(a_ag,"combobox_a_a");
	if(gtk_combo_box_get_active_text(GTK_COMBO_BOX(input))!=NULL){
         strcpy(a.parking,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input)));
    }else 
	{
		gtk_label_set_text(GTK_LABEL(output),"parking non invalide!");
		return;
	}*/

	


int res = ajouter_agent(AgentBDD, a);
	if(res==-1){
		output = lookup_widget(a_ag, "label_aj_a");
		gtk_label_set_text(GTK_LABEL(output),"Erreur lors de l'ajout!");
		return;
	}
	
	sprintf(tmp, "Ajout d'agent effectuer avec success! (ID=%d)", a.cin_a);
		gtk_label_set_text(GTK_LABEL(output),"Ajout d'agent avec success!");
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(a_ag)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			tmp);	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);

}


void
on_radiobutton_a_h_agen_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	i=0 ;
}


void
on_radiobutton_a_f_age_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	i=1;
}


void
on_checkbutton_a_e_n_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	e=0;
}


void
on_checkbutton_a_e_o_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	e=1;
}


void
on_button_aff_ag_clicked               (GtkWidget       *aff_ajt,
                                        gpointer         user_data)
{
	agent a;
	GtkWidget *treeview ;
	treeview = lookup_widget(aff_ajt, "treeviewaff_a");


	if (!treeview) {
        	g_warning("Treeview non trouvée !");
        	return;
	}
	vider_agent(treeview);
	afficheragent(AgentBDD, treeview);

}


void
on_button_modifier_agent_clicked       (GtkWidget       *a_agm,
                                        gpointer         user_data)
{
	agent a;
	GtkWidget* input ;
	GtkWidget* output ;
	
	char tmp[150];
	input = lookup_widget(a_agm, "entry_c_m_a");
	output = lookup_widget(a_agm, "label_m_ag") ;
	a.cin_a=atoi(gtk_entry_get_text(GTK_ENTRY(input)));

	


        input = lookup_widget(a_agm, "entry_n_m_a");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) {
	strcpy(a.nom, tmp); }
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Nom invalide!");
		return;
	}	
 


	input = lookup_widget(a_agm, "entry_p_m_a");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) {
	strcpy(a.prenom, tmp); }
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Prenom invalide!");
		return;
	}


	
	input=lookup_widget(a_agm,"spinbutton_m_m_a");
	a.naissance.m=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(a_agm,"spinbutton_a_m_a");
	a.naissance.a=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(a_agm,"spinbutton_j_m_a");
	a.naissance.j=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));

	
	

	input = lookup_widget(a_agm, "entry_adr_m_a");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) {
	strcpy(a.adresse, tmp); }
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Adresse invalide!");
		return;
	}



	input = lookup_widget(a_agm, "entry_e_m_a");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	rep_space_udnder(tmp);
	if(strlen(tmp)!=0) {
	strcpy(a.e_mail, tmp); }
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"E-mail invalide!");
		return;
	}

	input = lookup_widget(a_agm, "entry_s_m_a");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	int f=atof(tmp);
	if(str_is_int(tmp)&&strlen(tmp)!=0){
         a.salaire=f;}
	else 
	{
		gtk_label_set_text(GTK_LABEL(output),"Salaire invalide!");
		return;
	}


//radiobutton sex int

	a.sexe = i ;

//experience checkbox experience int

	a.experience = e ;



	


int res = modifier_agent(AgentBDD, a.cin_a, a);
	if(res==-1){
		output = lookup_widget(a_agm, "label_m_ag");
		gtk_label_set_text(GTK_LABEL(output),"Erreur lors de la modification!");
		return;
	}
	
	sprintf(tmp, "Modification d'agent effectuer avec success! (ID=%d)", a.cin_a);
		gtk_label_set_text(GTK_LABEL(output),"Modification d'agent avec success!");
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(a_agm)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			tmp);	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);

}


void
on_button_r_id_ag_clicked              (GtkWidget       *rida,
                                        gpointer         user_data)
{

	agent a;
	char tmp[150];
	GtkWidget* input ;
	GtkWidget* output ;



	input = lookup_widget(rida, "entry_c_m_a");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0){
        	a=rechercher_agent(AgentBDD, str_to_int(tmp));
	}else {
		gtk_label_set_text(GTK_LABEL(output),"Id non valide!");
		return;
	}
	if (a.cin_a==-1){
		gtk_label_set_text(GTK_LABEL(output),"Agent introuvable");
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(rida)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			"Agent introuvable");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		return;
	}
	

	//entrybox
	input = lookup_widget(rida, "entry_n_m_a");
	gtk_entry_set_text(GTK_ENTRY(input),a.nom);

	input = lookup_widget(rida, "entry_p_m_a");
	gtk_entry_set_text(GTK_ENTRY(input),a.prenom);

	input = lookup_widget(rida, "entry_adr_m_a");
	gtk_entry_set_text(GTK_ENTRY(input),a.adresse);
	
	input = lookup_widget(rida, "entry_e_m_a");
	gtk_entry_set_text(GTK_ENTRY(input),a.e_mail);
	
	input = lookup_widget(rida, "entry_s_m_a");
	sprintf(tmp,"%f",a.salaire);
	gtk_entry_set_text(GTK_ENTRY(input),tmp);
	
   
	//duree spinbutton
	
	input=lookup_widget(rida,"spinbutton_m_m_a");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(input),a.naissance.m);

	input=lookup_widget(rida,"spinbutton_a_m_a");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(input),a.naissance.a);

	input=lookup_widget(rida,"spinbutton_j_m_a");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(input),a.naissance.j);
	
	sprintf(tmp,"Recommencer la modification");
		gtk_label_set_text(GTK_LABEL(output),"Vous pouvez recommencer la modification");
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(rida)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			tmp);	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);


}


void
on_checkbutton_o_m_a_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	e=1;
}


void
on_checkbutton_n_m_a_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	e=0;
}


void
on_radiobutton_h_m_a_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	i=0;
}


void
on_radiobutton_f_m_a_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	i=1;
}


void
on_button_supprimer_agent_clicked      (GtkWidget       *supp_a,
                                        gpointer         user_data)
{

	GtkWidget* input ;
	GtkWidget* output ;
	
	char tmp[150];
	
	int i;	
	input = lookup_widget(supp_a, "entry_c_a_sp");
	output = lookup_widget(supp_a, "label_a_ag_sp");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(str_is_int(tmp)&&strlen(tmp)!=0) 	
	i=supprimer_agent(AgentBDD, str_to_int(tmp));
	else {
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(supp_a)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			"ID invalide!");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		gtk_entry_set_text(GTK_ENTRY(output),"ID invalide!");
		return;
	}
	if(i!=0) {
		sprintf(tmp,"Agent N°%d supprimé!",str_to_int(tmp));
		gtk_label_set_text(GTK_LABEL(output),tmp);
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(supp_a)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			tmp);	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
	} else {
		sprintf(tmp,"Agent N°%d introuvable!",str_to_int(tmp));
		gtk_label_set_text(GTK_LABEL(output),tmp);
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(supp_a)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			tmp);	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		gtk_entry_set_text(GTK_ENTRY(output),"ID invalide!");
		return;

	}
	

}


void
on_button_recher_a_clicked             (GtkWidget       *r_a,
                                        gpointer         user_data)
{

	agent a;
	char tmp[10];
    	int id ;
	GtkWidget *treeview;
	treeview = lookup_widget(r_a, "treeview_r_a");
	
	//vider_agent(treeview);

        GtkWidget *input;
        input = lookup_widget(r_a, "entry_r_n_a");
        strcpy(tmp, gtk_entry_get_text(GTK_ENTRY(input)));
	

        if (strlen(tmp) > 0) {
	    id=atoi(tmp);
            agent s1 =rechercher_agent(AgentBDD, id);
	if(s1.cin_a==-1){
		vider_agent(treeview);
            	afficheragent("base_recherche_agent.txt", treeview);
		 return ;}
	    else{ajouter_agent("base_recherche_agent.txt", s1);
	    vider_agent(treeview);
            afficheragent("base_recherche_agent.txt", treeview);
	    remove("base_recherche_agent.txt");}

	}
}




void
on_button_r_r_aff_clicked              (GtkWidget       *r_r,
                                        gpointer         user_data)
{
/*
	reservation r1;
	char tmp[10];
    	int id ;
	GtkWidget *treeview;
	treeview = lookup_widget(r_r, "treeview_afct_res");
        GtkWidget *input;
	GtkWidget *output;
        input = lookup_widget(r_r, "entry_id_res_afectter");
        strcpy(tmp, gtk_entry_get_text(GTK_ENTRY(input)));
	
        if (strlen(tmp) > 0) {
	    id=atoi(tmp);
	    r1=rechercher_reservation("r.txt", id);
	    if(r1.id_res==-1){
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(r_r)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			"ID invalide!");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		gtk_entry_set_text(GTK_ENTRY(output),"ID invalide!");
		
		 return;		
		}
	    r1.id_res= id ;
	    //ajouter_sc_reservation("base_r_.txt", r1);
	    ajouter_reservation2("base_r_.txt", r1);
            afficher_reservation("base_r_.txt", treeview);
	    remove("base_r_.txt");	
	} */

}


void
on_button_r_s_aff_clicked              (GtkWidget       *r_sa,
                                        gpointer         user_data)
{

	char tmp[10];
    	int id ;
	GtkWidget *treeview;
	treeview = lookup_widget(r_sa, "treeview_afct_sv");
        GtkWidget *input;
	GtkWidget *output;
	output=lookup_widget(r_sa,"label_res_sv");
        input = lookup_widget(r_sa, "entry_id_sc_afecter");
        strcpy(tmp, gtk_entry_get_text(GTK_ENTRY(input)));
	
        if (strlen(tmp) > 0) {
	    id=atoi(tmp);
            service s1 =rechercher_service(base_service,id);
	    if(s1.id_sc==-1){
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(r_sa)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			"ID invalide!");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		gtk_entry_set_text(GTK_ENTRY(output),"ID invalide!");
		 return;		
		}
	    s1.id_sc = id ;
	    ajouter_service("base_r_sv.txt", s1);
	    vider_service(treeview);
            afficher_servicee("base_r_sv.txt", treeview);
	    remove("base_r_sv.txt");	
	} 
	
}



void
on_button_affect_service_clicked       (GtkWidget       *a,
                                        gpointer         user_data)
{/*
	//ajouter_sc_reservation("base_r_.txt", r1);
	char tmp[10];
	char tmp1[10];
    	int id , idr;
	reservation r1;
	GtkWidget *treeview;
	treeview = lookup_widget(a, "treeview_afct_res");
        GtkWidget *input;
	GtkWidget *output;
        input = lookup_widget(a, "entry_id_sc_afecter");
        strcpy(tmp, gtk_entry_get_text(GTK_ENTRY(input)));

	if (strlen(tmp) > 0) {
	    idr=atoi(tmp);
            service s1 =rechercher_service(base_service,idr);
	    if(s1.id_sc==-1){
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(a)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			"ID invalide service!");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		gtk_entry_set_text(GTK_ENTRY(output),"ID invalide!");
		 return;		
		}	
	} 

	output = lookup_widget(a, "entry_id_res_afectter");
        strcpy(tmp1, gtk_entry_get_text(GTK_ENTRY(output)));
        if (strlen(tmp) > 0) {
	    id=atoi(tmp);
	    r1=rechercher_reservation("r.txt", id);
	    if(r1.id_res==-1){
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(a)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			"ID reservation invalide!");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		gtk_entry_set_text(GTK_ENTRY(output),"ID invalide!");
		
		 return;		
		}
	    r1.ser= idr ;
	    modifier_reservation("r.txt", id, r1);
	    ajouter_reservation2("base_r_.txt", r1);
            afficher_reservation("base_r_.txt", treeview);
	    remove("base_r_.txt");	
	} */
}


void
on_button_afficher_historique_clicked  (GtkWidget      *r_af,
                                        gpointer         user_data)
{


	agent a;
	char tmp[10];
    	int id ;
	GtkWidget *treeview;
	treeview = lookup_widget(r_af, "treeview_h_r");
	
	//vider_agent(treeview);

        GtkWidget *input;
        input = lookup_widget(r_af, "entry_c_h_a");
        strcpy(tmp, gtk_entry_get_text(GTK_ENTRY(input)));
	printf("%s\n",tmp);
	input=lookup_widget(r_af,"spinbutton_m_h_a");
	int m=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(r_af,"spinbutton_a_h_a");
	int an=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
	input=lookup_widget(r_af,"spinbutton_j_h_a");
	int j=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));


	if (strlen(tmp) > 0) {
	    id=atoi(tmp);
	    printf("%d %d %d %d\n", id, j, m, an);
	    afficherhistorique("parking.txt","r.txt", id, j, m, an);
	    afficher_reservation("Historiquedereservation.txt", treeview);
	    remove("Historiquedereservation.txt");

	}

}






char sexe0='f';
char paiment='c';
char  tmp[150];












void
on_radioresmdpc_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
	{
		paiment ='c';
	}


}


void
on_radioresmdpe_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
	{
		paiment ='e';
	}

}


void
on_radiogenm_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
	{
		sexe0='m';
	}

}


void
on_radiogenf_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
	{
		sexe0='f';
	}

}
void
on_buttonajouter_clicked                (GtkWidget *button, gpointer user_data)
{
	reservation r;

	GtkWidget* cl ;
	cl = lookup_widget(button,"entryrescl");	
	const char* cl_text=gtk_entry_get_text(GTK_ENTRY(cl));
	r.id_cl=atoi(cl_text);
	if(strlen(cl_text)==0||r.id_cl==0)
	{
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_ERROR,
		GTK_BUTTONS_OK,
		"Id client invalide");	
	gtk_dialog_run(GTK_DIALOG(dialog));	
	gtk_widget_destroy(dialog);
		return;
	}
	printf("testa2");
	
	GtkWidget* nometprenom ;//demarche de string
	nometprenom=lookup_widget(button,"entryidnep");
	strcpy(r.nep,gtk_entry_get_text(GTK_ENTRY(nometprenom)));
	printf("testa3");
	if (strlen(r.nep) == 0) {
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                               "Le champ 'Nom' est obligatoire !");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		return;
	}
	if (!is_only_alpha(r.nep))
	{
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Le champ 'Nom' doit contenir uniquement des lettres !");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		return;
	}
	
	GtkWidget* mt ;//demarche deint
	mt=lookup_widget(button,"entryresidmt");
	const char* mt_text=gtk_entry_get_text(GTK_ENTRY(mt));
	r.id_mt=atoi(mt_text);
	printf("testa4");
	if(strlen(mt_text)==0||r.id_mt==0)
	{
		
            		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Le champ 'Matricule' est obligatoire!");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
			return;
        }
	if(strlen(mt_text)!=0||r.id_mt==0)
	{
		if (!is_only_digits(mt_text)) {
            		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Le champ 'Matricule' doit contenir uniquement des chiffres !");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
			return;
        }
	}


	

	GtkWidget* dr ;//damarche de spinbutton
	dr=lookup_widget(button,"spinresjdr");
	r.jdr=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dr));
	printf("testa7");

	dr=lookup_widget(button,"spinresmdr");
	r.mdr=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dr));
	printf("testa8");

	dr=lookup_widget(button,"spinresadr");
	r.adr=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dr));
	printf("testa9");

	dr=lookup_widget(button,"spinresdrr");
	r.drr=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dr));
	printf("testa10");
	r.h_f=sexe0;
	r.mdp=paiment;


	

	printf("testa6");

	ajouter_reservation("r.txt", r);
	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
		                                               GTK_DIALOG_MODAL,
		                                               GTK_MESSAGE_ERROR,
		                                               GTK_BUTTONS_OK,
		                                               "Reservation ajoutee avec succes");
				gtk_dialog_run(GTK_DIALOG(dialog));
				gtk_widget_destroy(dialog);

	
}













void
on_buttonafficher_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

	GtkWidget *treeview_afficher_res;
	treeview_afficher_res= lookup_widget(button, "treeafficher");


	if (!treeview_afficher_res) {
        	g_warning("Treeview not found!");
        	return;
	}


	vider_reservation(treeview_afficher_res);
	afficher_reservation("r.txt",treeview_afficher_res);



}


void
on_buttonrid_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	reservation r;
	tmp[150];

	GtkWidget* res ;
	res = lookup_widget(button,"entrymires");	
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(res)));
	r.id_res=atoi(tmp);

	//if id==0
	printf("testid1\n");
	//id
	if (r.id_res != 0) { 
    r = rechercher_reservation("r.txt", r.id_res);
    printf("testid2\n");
	} else { 
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
        GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "ID invalide!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    printf("testid3\n");
    return;
	}
	if(r.id_res==0){
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			"ID inexistant!");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
	printf("testid4\n");
		return;
	}//
	
	affichier_reservation( r);
	
	printf("testid5\n");
	//entrymcl
	res = lookup_widget(button,"entrymcl");
	sprintf(tmp,"%d",r.id_cl);
	gtk_entry_set_text(GTK_ENTRY(res),tmp);
	printf("testid6\n");	

	//entrymnep
	res = lookup_widget(button,"entrymnep");
	gtk_entry_set_text(GTK_ENTRY(res),r.nep);
	printf("testid7\n");

	//radiomsm

	if (r.h_f=='m') {
		
		res = lookup_widget(button, "radiomsm") ;
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(res),TRUE);
	printf("testid8\n");
	}
	else {

		res = lookup_widget(button, "radiomsf") ;
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(res),TRUE);
	printf("testid9\n");
	}
	//entrymimt
	res = lookup_widget(button,"entrymimt");
	sprintf(tmp,"%d",r.id_mt);
	gtk_entry_set_text(GTK_ENTRY(res),tmp);
	printf("testid10\n");

	//entrympk
	res = lookup_widget(button,"entrympk");
	sprintf(tmp,"%d",r.id_pk);
	gtk_entry_set_text(GTK_ENTRY(res),tmp);
	printf("testid11\n");

	//spin  spinmjr
	res=lookup_widget(button,"spinmjr");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(res),r.jdr);

	res=lookup_widget(button,"spinmmr");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(res),r.mdr);

	res=lookup_widget(button,"spinmar");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(res),r.adr);

	res=lookup_widget(button,"spinmdr");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(res),r.drr);

	//combo
	res = lookup_widget(button, "combobox_s_m");
	gtk_combo_box_set_active(GTK_COMBO_BOX(res),r.ser);
	printf("erreurcombo");
	/*int i=0;//gtk_combo_box_get_active_text(GTK_COMBO_BOX(input))
	while (i<6&&(strcmp(r.ser,gtk_combo_box_get_active_text(GTK_COMBO_BOX(res)))!=0)){
		gtk_combo_box_set_active(GTK_COMBO_BOX(res),i);
		i++;
	}*/

//radiomdp

	/*if (r.h_f=='m') {
		
		res = lookup_widget(button, "radiompre") ;
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(res),TRUE);
	}
	else {

		res = lookup_widget(button, "radiomprc") ;
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(res),TRUE);
	}
*/

	if (r.h_f == 'm') {
    	res = lookup_widget(button, "radiompre");
    	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(res), TRUE);
	} else {
    	res = lookup_widget(button, "radiomprc");
    	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(res), TRUE);
	}
	printf("erreurspinfh");

	if (r.mdp == 'e') {
    	res = lookup_widget(button, "radiompre");
    	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(res), TRUE);
	} else {
    	res = lookup_widget(button, "radiomprc");
    	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(res), TRUE);
	}
	printf("erreurspincm");

}





void
on_radiomsf_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

if(gtk_toggle_button_get_active(togglebutton))
	{
		sexe0 ='f';
	}

}


void
on_radiomsm_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton))
	{
		sexe0='m';
	}

}


void
on_radiompre_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton))
	{
		paiment ='e';
	}

}


void
on_radiomprc_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton))
	{
		paiment ='c';
	}

}


void
on_buttonmres_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	reservation r;

	GtkWidget* cl ;
	cl = lookup_widget(button,"entrymcl");	
	const char* cl_text=gtk_entry_get_text(GTK_ENTRY(cl));
	r.id_cl=atoi(cl_text);

	if(strlen(cl_text)==0||r.id_cl==0)
	{
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_ERROR,
		GTK_BUTTONS_OK,
		"Id client invalide");	
	gtk_dialog_run(GTK_DIALOG(dialog));	
	gtk_widget_destroy(dialog);
		return;
	}
	if(strlen(cl_text)!=0)
	{
		if (!is_only_digits(cl_text)) {
            		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Le champ 'cin' doit contenir uniquement des chiffres !");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
			return;
        }
	}

	printf("testm2");

	GtkWidget* nometprenom ;//demarche de string
	nometprenom=lookup_widget(button,"entrymnep");
	strcpy(r.nep,gtk_entry_get_text(GTK_ENTRY(nometprenom)));
	printf("testm3");

	if (strlen(r.nep) == 0) {
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                               "Le champ 'Nom' est obligatoire !");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		return;
	}
	if (!is_only_alpha(r.nep))
	{
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Le champ 'Nom' doit contenir uniquement des lettres !");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		return;
	}
	
	GtkWidget* pk ;//demarche deint
	pk=lookup_widget(button,"entrympk");
	const char* pk_text=gtk_entry_get_text(GTK_ENTRY(pk));
	r.id_pk=atoi(pk_text);
	if(strlen(pk_text)==0)
	{
		
            		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Le champ 'ID Parking' est obligatoire!");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
			return;
        }
	if(strlen(pk_text)!=0)
	{
		if (!is_only_digits(pk_text)) {
            		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Le champ 'ID Parking' doit contenir uniquement des chiffres !");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
			return;
        }
	}
	printf("testm4");

	GtkWidget* res ;//idres
	res = lookup_widget(button,"entrymires");	
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(res)));
	if(strlen(tmp)==0)
	{
		
            		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Le champ 'ID' est obligatoire!");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
			return;
        }
	if(strlen(tmp)!=0)
	{
		if (!is_only_digits(tmp)) {
            		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Le champ 'ID' doit contenir uniquement des chiffres !");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
			return;
        }
	}

	r.id_res=atoi(tmp);
	int id_r=r.id_res;

	//entrymimt
	GtkWidget* mt ;//demarche deint
	mt=lookup_widget(button,"entrymimt");
	char mt_text[20];
	strcpy(mt_text,gtk_entry_get_text(GTK_ENTRY(mt)));
	r.id_mt=atoi(mt_text);
	if(strlen(mt_text)==0||r.id_mt==0)
	{
		
            		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Le champ 'Matricule' est obligatoire!");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
			return;
        }
	if(strlen(mt_text)!=0||r.id_mt==0)
	{
		if (!is_only_digits(mt_text)) {
            		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Le champ 'Matricule' doit contenir uniquement des chiffres !");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
			return;
        }
	}
	

	GtkWidget* dr ;//damarche de spinbutton
	dr=lookup_widget(button,"spinmjr");
	r.jdr=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dr));
	printf("testm7\n");

	dr=lookup_widget(button,"spinmmr");
	r.mdr=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dr));
	printf("testm8\n");

	dr=lookup_widget(button,"spinmar");
	r.adr=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dr));
	printf("testm9\n");

	dr=lookup_widget(button,"spinmdr");
	r.drr=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dr));
	printf("testm10\n");
	
	//r.h_f=sexe;
	dr=lookup_widget(button,"radiomsm");
	if (gtk_toggle_button_get_active(dr)) r.h_f='m';
	dr=lookup_widget(button,"radiomsf");
	if (gtk_toggle_button_get_active(dr)) r.h_f='f';
	dr=lookup_widget(button,"radiompre");
	if (gtk_toggle_button_get_active(dr)) r.mdp='e';
	dr=lookup_widget(button,"radiomprc");
	if (gtk_toggle_button_get_active(dr)) r.mdp='c';
	//r.mdp=paiment;
	r.ser=-1;
	res = lookup_widget(button, "combobox_s_m");
	//gtk_combo_box_set_active(GTK_COMBO_BOX(res),r.ser);
	printf("erreurcombo");
	char tompon[50];
	if(gtk_combo_box_get_active_text(GTK_COMBO_BOX(res))!=NULL){ strcpy(tompon,gtk_combo_box_get_active_text(GTK_COMBO_BOX(res)));
	int i=0;//gtk_combo_box_get_active_text(GTK_COMBO_BOX(input))
	do{
		gtk_combo_box_set_active(GTK_COMBO_BOX(res),i);
		i++;
		printf("i %d\n",i);
	}while (i<6&&(strcmp(tompon,gtk_combo_box_get_active_text(GTK_COMBO_BOX(res)))!=0));
	r.ser=i-1;
	}
	//*/
	printf("testm6\n");
	affichier_reservation(r) ;
	modifier_reservation("r.txt",id_r, r);
	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Reservation modifiee avec succes");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
}


void
on_buttonsupres_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	
	GtkWidget* input ;
	GtkWidget* output ;
	char tmp[150];
	
	reservation r;	
	
	//id
	input = lookup_widget(button, "entryres_a_supprimer");
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(input)));
	if(atoi(tmp)!=0) r=rechercher_reservation("r.txt",atoi(tmp));
	else {
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			"ID invalide!");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		return;
	}
	if(r.id_res!=0) {
		sprintf(tmp,"Voulez-vous vraiment supprimer la reservation N°%d ?",r.id_res);
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
        	                            GTK_DIALOG_MODAL,
            	                        GTK_MESSAGE_QUESTION,
                	                    GTK_BUTTONS_YES_NO,
                    	                tmp);

    	int result = gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		
		if (result == GTK_RESPONSE_YES){
			supprimer_reservation("r.txt",r.id_res);

			sprintf(tmp,"Reservation N°%d supprimé!",r.id_res);
			gtk_label_set_text(GTK_LABEL(output),tmp);
			dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
				GTK_DIALOG_MODAL,
				GTK_MESSAGE_INFO,
				GTK_BUTTONS_OK,
				tmp);	
			gtk_dialog_run(GTK_DIALOG(dialog));	
			gtk_widget_destroy(dialog);
			}
	} else {
		sprintf(tmp,"Reservation N°%d introuvable!",atoi(tmp));
		gtk_label_set_text(GTK_LABEL(output),tmp);
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			tmp);	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
		gtk_entry_set_text(GTK_ENTRY(output),tmp);
		return;
	}



	/*reservation r;
	tmp[150];

	GtkWidget* res ;
	res = lookup_widget(button,"entryres_a_supprimer");	
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(res)));
	r.id_res=atoi(tmp);

	//if id==0
	
	//id
	if (r.id_res != 0) { 
    r = rechercher_reservation("r.txt", r.id_res);
    printf("testid2\n");
	} else { 
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
        GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "ID invalide!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    printf("testid3\n");
    return;
	}
	if(r.id_res==0){
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			"ID inexistant!");	
		gtk_dialog_run(GTK_DIALOG(dialog));	
		gtk_widget_destroy(dialog);
	printf("testid4\n");
		return;
	}//*/
}


void
on_button_recherche_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *rec;
	int x=0;
	char tmp[50];
	int id;
	reservation p;

	rec=lookup_widget(button,"res_rec_id");
	if (gtk_toggle_button_get_active(rec)){ x=1;rec = lookup_widget(button, "citoyen_modifier_male") ;
		gtk_toggle_button_set_active(GTK_RADIO_BUTTON(rec),FALSE);}
	else {
		rec=lookup_widget(button,"res_rec_nom");
		if (gtk_toggle_button_get_active(rec)) x=2;
		else x=0;
	}
	
	switch(x){
		case 0:
			return;
		case 1:
			rec=lookup_widget(button,"entry_recherche_res");
			strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(rec)));
			id=atoi(tmp);
			if (id==0)return;
			p=rechercher_reservation("r.txt",id);
			if (p.id_res==0) return;
			remove("temp.txt");
			ajouter_reservation2("temp.txt",p);
			rec=lookup_widget(button,"entry_recherche_res");
			printf("test1\n");
			rec=lookup_widget(button,"res_rec_treeview");
			afficher_reservation("temp.txt",rec);
			break;
		case 2:
			rec=lookup_widget(button,"entry_recherche_res");
			strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(rec)));
			FILE *f=fopen("r.txt","r");
			if (f==NULL)return;
			remove("temp.txt");
			while(fscanf(f, "%d %d %s %c %d %d %d %d %d %d %c %d\n",
                  &p.id_res, &p.id_cl, p.nep, &p.h_f, &p.id_mt, &p.id_pk,
                  &p.jdr, &p.mdr, &p.adr, &p.drr, &p.mdp, &p.ser) == 12){
				if(strstr(p.nep,tmp)!=NULL) ajouter_reservation2("temp.txt",p);
			}
			//if(strstr(c.prenom,prenom)==NULL) res=0;
			fclose(f);			
			rec=lookup_widget(button,"res_rec_treeview");
			afficher_reservation("temp.txt",rec);
			break;
	}
}





void
on_buttonaffectres_clicked             (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	//buttonaffectres
	int n;
	FILE *file = fopen("counter.txt", "r");
    	if (file != NULL)
    	{
        	fscanf(file, "%d", &n);
        	fclose(file);
    	}
	Parking *T=malloc(n*sizeof(Parking));
	file=fopen("parking.txt","r");
	if(file==NULL){free(T); return;}
	int i=0;
	while (fscanf(file, "%d,%d,%99[^,],%99[^,],%99[^,],%d,%d,%d,%c,%c,%d,%d\n", &T[i].id, &T[i].id_agent, T[i].nom, T[i].region, 
                   T[i].adresse, &T[i].nbetages, &T[i].numero_de_telephone, &T[i].tarif, &T[i].est_couvert, &T[i].supporte_pour_handicappe, 
                   &T[i].capacite, &T[i].place_disponible) ==12){i++;printf("wtf %d\n",T[i-1].place_disponible);}
	fclose(file);
	trier_parkings(T,i);
	remove("parkingtriee.txt");
	for (int j=0;j<i;j++){
		ajouterParkingReservation("parkingtriee.txt",T[j]);
	}
	free(T);
	GtkWidget *treeview_afficher_park;//treeviewaffres
	treeview_afficher_park= lookup_widget(objet_graphique, "treeviewaffres");
	

	if (!treeview_afficher_park) {
        	g_warning("Treeview not found!");
        	return;
	}


	//vider_reservation(treeview_afficher_res);
	vider(treeview_afficher_park);
	afficher_parking("parkingtriee.txt",treeview_afficher_park);
	

}














void
on_buttonaffectationpark_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	Parking p;
	reservation r;
	char tmp[150];
	//entryresaffecte   ires
	//entryparkaffecter ipk
	//buttonaffectationpark
	GtkWidget* ires = lookup_widget(button,"entryresaffecte");	
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(ires)));
	if(atoi(tmp)==0) return;
	r=rechercher_reservation("r.txt",atoi(tmp));
	if(r.id_res==0||r.id_pk!=0) return;
	GtkWidget* ipk = lookup_widget(button,"entryparkaffecter");	
	strcpy(tmp,gtk_entry_get_text(GTK_ENTRY(ipk)));
	if(atoi(tmp)==0) return;
	p=rechercherParking("parking.txt",atoi(tmp));
	if(p.id==-1||p.place_disponible<=0) return;
	p.place_disponible--;
	r.id_pk=p.id;
	affichier_reservation(r);
	modifier_reservation("r.txt", r.id_res,r);
	modifierParking("parking.txt", p.id, p);
	
	on_buttonaffectres_clicked(button,user_data);
	on_buttonafficher_clicked(button,user_data);
		
	//affecter_reservation( "parking.txt","r.txt", p.id ,r.id_res);
}





void
on_treeviewaffres_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	 GtkTreeIter iter;
    gchar *id_str;
    int id;

    GtkTreeModel *model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path)) {

        gtk_tree_model_get(GTK_LIST_STORE(model), &iter,
                           0, &id_str,  
                           -1);

        
        GtkWidget* ptr = lookup_widget(treeview,"entryparkaffecter");
	gtk_entry_set_text(GTK_ENTRY(ptr),id_str);
 g_free(id_str);}

/*GtkTreeIter iter;

    gchar* id_res;
    gchar* id_cl;
    gchar* nom;
    gchar* sex;
    gchar* mat;
    gchar* id_par;
    gchar* date;
    gchar* duree;
    gchar* mode_pay;
    gchar* service;
	
	GtkWidget* output;
	output = lookup_widget(treeview, "entryparkaffecter");

	GtkTreeModel *model = gtk_tree_view_get_model(treeview);

	if(gtk_tree_model_get_iter(model,&iter,path))
	{
		gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id_res,1,&id_cl,2,&nom,3,&sex,4,&mat,5,&id_par,6,&date,7,&duree,8,&mode_pay,9,&service,-1);
		gtk_entry_set_text(GTK_ENTRY(output),id);
		on_button26_clicked(treeview,user_data);
	}//*/
}



