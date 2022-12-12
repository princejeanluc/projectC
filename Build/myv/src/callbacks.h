#include <gtk/gtk.h>


void
on_SpinButtonMaxResultSearchWindowListMain_change_value
                                        (GtkSpinButton   *spinbutton,
                                        GtkScrollType    scroll,
                                        gpointer         user_data);

void
on_ButtonCreateListWindowListMain_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_ButtonModifyListWindowListMain_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonDeleteListWindowListMain_clicked
                                        (GtkWidget      *button,
                                        gpointer         user_data);

void
on_ButtonProposeList_clicked           (GtkWidget      *button,
                                        gpointer         user_data);

void
on_ButtonShowListWindowListMain_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonSearchWindowListMain_clicked  (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonPreviousWindowListMain_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonVoteWindowListMain_clicked    (GtkWidget      *button,
                                        gpointer         user_data);

void
on_RadioButtonRightOrientationSearchWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RadioButtonCenterOrientationSearchWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RadioButtonLeftOrientationSearchWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_CheckButtonOrientationCriteriaWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_CheckButtonNameListCriteriaWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_CheckButtonHeadListCriteriaWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_CheckButtonIdListCriteriaWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_ButtonAddMemberWindowManageList_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonDeleteMemberWindowManageList_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonCancelWindowManageList_clicked
                                        (GtkWidget      *button,
                                        gpointer         user_data);

void
on_ButtonValidateWindowManageList_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonResetWindowManageList_clicked (GtkWidget      *button,
                                        gpointer         user_data);

void
on_RadioButtonCenterOrientationWindowOrientation_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RadioButtonRightOrientationWindowManageList_toggled
                                        (GtkWidget *togglebutton,
                                        gpointer         user_data);

void
on_RadioButtonLeftOrientationWindowManageList_toggled
                                        (GtkWidget *togglebutton,
                                        gpointer         user_data);

void
on_ButtonOkWindowAlert_clicked         (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonCloseWindowShowList_clicked   (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonCancelWindowActionOnList_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonConfirmWindowActionOnList_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ComboBoxSelectActionWindowActionOnList_changed
                                        (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_ButtonNextWindowStart_clicked       (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_ButtonPreviousWindowConnection_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_ButtonResetWindowConnection_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_ButtonConnectionWindowConnection_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_BouttonOpenUser_clicked             (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_OpenBDV_clicked                     (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_OpenObservation_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_ButtonOpenElectoralList_clicked     (GtkWidget       *button,
                                        gpointer         user_data);

void
on_OpenElection_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_OpenReclamation_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_PrecedentMainMenu_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_ButtonOpenStat_clicked              (GtkWidget       *button,
                                        gpointer         user_data);

void
on_BouttonShowUser_clicked             (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_BouttonModifyUser_clicked           (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_BouttonDeleteUser_clicked           (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_SearchUser_clicked                  (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_PrecedentUser_clicked               (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_SearchNameUser_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_AddUser_clicked                     (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_WriteJourAddUser_changed            (GtkWidget     *objet_graphique,
                                        gpointer         user_data);

void
on_WriteAnneeAddUser_changed           (GtkWidget     *objet_graphique,
                                        gpointer         user_data);

void
on_WriteMoiAddUser_changed             (GtkWidget     *objet_graphique,
                                        gpointer         user_data);

void
on_FemmeAddUser_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_HommeAddUser_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_BouttonAjouterAddUser_clicked       (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_BouttonPrecedentAddUser_clicked     (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_WriteJourModifyUser_changed         (GtkWidget     *objet_graphique,
                                        gpointer         user_data);

void
on_WriteAnneeModifyUser_changed        (GtkWidget     *objet_graphique,
                                        gpointer         user_data);

void
on_WriteMoisModifyUser_changed         (GtkWidget     *objet_graphique,
                                        gpointer         user_data);

void
on_HommeModifyUser_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_FemmeModifyUser_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_BouttonModifierUser_clicked         (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_BouttonPrecedentModifyUser_clicked  (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_BouttonSucces_clicked               (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_BouttonErreur_clicked               (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_BouttonPrecedentShowUser_clicked    (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_WriteCapaciteDeElecteurBVAdd_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_WriteCapaciteDeObservateurBVAdd_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_PrecedentBVAdd_clicked              (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_AjouterBVAdd_clicked                (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_writeCapaciteDeElecteurBVSupp_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_WriteCapaciteDeObservateurBVSupp_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_PrecedentBVSupp_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_ModifierBVSupp_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_WriteCapaciteDeElecteurBVAff_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_WriteCapaciteDeObservateurBVAff_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_PrecedentBVAff_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_nbh_ajou_election_changed           (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_nbc_ajou_electon_changed            (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_jour_ajou_election_changed          (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_mois_ajou_election_changed          (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_annee_ajou_election_changed         (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_Precedent1_election_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_Ajouter_election_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_nbh_modi_election_changed           (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_nbc_modi_election_changed           (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_jour_modi_election_changed          (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_mois_modi_election_changed          (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_annee_modi_election_changed         (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_Modifier_election_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_precedent2_election_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_nbh_affi_election_changed           (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_nbc_affi_election_changed           (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_jour_affi_election_changed          (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_mois_affi_election_changed          (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_annee_affi_election_changed         (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_precedent3_election_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonBVAdd_clicked                 (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_buttonBVMod_clicked                 (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_buttonBVSupp_clicked                (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_button48_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button49_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button50_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button51_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_ButtonPreviousWindowStatistic_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonNothingWindowVote_clicked     (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonVoteWindowVote_clicked        (GtkWidget       *button,
                                        gpointer         user_data);
