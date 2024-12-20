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

void
on_checkbutton_pcouvert_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void on_button_p_ajouter_clicked(GtkWidget *objet_graphique, gpointer user_data);

void
on_non_supp_radio_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_psupportepourhandicappe_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void on_modifier_selectbutton_clicked(GtkWidget *objet_graphique, gpointer user_data);

void
on_radiobutton_modifier_psup_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_modifier_pnonsup_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_check_modifier_pcouvert_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_modifier_p_button_clicked (GtkWidget *objet_graphique, gpointer user_data);

void
on_checkbutton_pnoncouvert_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_check_modifier_pnoncouvert_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void on_suppreimer_p_button_clicked (GtkWidget *objet_graphique, gpointer user_data);

void on_rechercher_p_button_clicked         (GtkWidget    *objet_graphique,gpointer         user_data);

void
on_check_rechercher_p_id_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_check_rechercher_p_region_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_check_rechercher_p_nom_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_treeview_p_rechercher_row_activated (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeview_afficher_parking_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_aficher_parking_clicked (GtkWidget *objet_graphique, gpointer user_data);

void
on_affecter_agent_button_clicked       (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_affecter_treeview_parking_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_affecte_treeview_agent_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_affecteragent_afficherbutton_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_modfier_p_annuler_clicked           (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_annul_ajout_button_clicked          (GtkWidget       *objet_graphique,
                                        gpointer         user_data);




void
on_radiobutton_a_oui_sv_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_a_d_sv_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_a_sv_clicked                 (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_sup_aj_sv_clicked            (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_modif_sv_clicked             (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_a_modif_sv_clicked           (GtkWidget       *button,
                                        gpointer         user_data);

void
on_checkbutton_o_m_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton_n_m_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_r_id_sv_m_clicked            (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_aff_sv_clicked               (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_supprimmer_sv_clicked        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_rch_sv_clicked               (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_rech_affect_clicked          (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_affect_clicked               (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_a_agent_clicked              (GtkWidget       *button,
                                        gpointer         user_data);

void
on_radiobutton_a_h_agen_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_a_f_age_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton_a_e_n_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton_a_e_o_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_aff_ag_clicked               (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_modifier_agent_clicked       (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_r_id_ag_clicked              (GtkWidget       *button,
                                        gpointer         user_data);

void
on_checkbutton_o_m_a_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton_n_m_a_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_h_m_a_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_f_m_a_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_supprimer_agent_clicked      (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_recher_a_clicked             (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_r_r_aff_clicked              (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_r_s_aff_clicked              (GtkWidget       *button,
                                        gpointer         user_data);


void
on_button_affect_service_clicked       (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_afficher_historique_clicked  (GtkWidget       *button,
                                        gpointer         user_data);


void
on_buttonajouter_clicked                (GtkWidget *objet_graphique, 
					 gpointer       user_data);



void
on_radioresmdpc_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radioresmdpe_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiogenm_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiogenf_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_buttonafficher_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonrid_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiomsm_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiompre_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiomprc_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_buttonmres_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonaffectres_clicked             (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_radiomsf_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_buttonsupres_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_recherche_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonaffectationpark_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeviewaffres_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);
