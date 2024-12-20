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

