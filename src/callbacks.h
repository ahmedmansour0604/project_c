#include <gtk/gtk.h>


void
on_citoyen_ajouter_confirmer_clicked   (GtkWidget       *button,
                                        gpointer         user_data);

void
on_citoyen_ajouter_male_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_citoyen_ajouter_femelle_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_citoyen_afficher_bouton_clicked     (GtkWidget       *button,
                                        gpointer         user_data);

void
on_citoyen_modifier_bouton_clicked     (GtkWidget       *button,
                                        gpointer         user_data);

void
on_citoyen_modifier_femelle_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_citoyen_modifier_male_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_citoyen_supprimer_bouton_clicked    (GtkWidget       *button,
                                        gpointer         user_data);

void
on_citoyen_supprimer_afficher_clicked  (GtkWidget       *button,
                                        gpointer         user_data);

void
on_citoyen_supprimer_treeview_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_citoyen_rechercher_bouton_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button23_clicked                    (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button68_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button25_clicked                    (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button70_clicked                    (GtkWidget       *button,
                                        gpointer         user_data);

void
on_treeview23_row_activated            (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button26_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button64_clicked                    (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button74_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button75_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button76_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_citoyen_calculer_button_clicked     (GtkButton       *button,
                                        gpointer         user_data);
