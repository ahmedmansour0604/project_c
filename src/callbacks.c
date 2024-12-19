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

