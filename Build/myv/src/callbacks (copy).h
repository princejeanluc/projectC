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
                                        (GtkWidget      *button,
                                        gpointer         user_data);

void
on_ButtonDeleteListWindowListMain_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonProposeList_clicked           (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonShowListWindowListMain_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_RadioButtonLeftOrientationSearchWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RadioButtonCenterOrientationSearchWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RadioButtonRightOrientationSearchWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_ButtonSearchWindowListMain_clicked  (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonPreviousWindowListMain_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonVoteWindowListMain_clicked    (GtkWidget       *button,
                                        gpointer         user_data);

void
on_CheckButtonIdListCriteriaWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_CheckButtonHeadListCriteriaWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_CheckButtonNameListCriteriaWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_CheckButtonOrientationCriteriaWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RadioButtonLeftOrientationWindowManageList_toggled
                                        (GtkWidget *togglebutton,
                                        gpointer         user_data);

void
on_RadioButtonRightOrientationWindowManageList_toggled
                                        (GtkWidget *togglebutton,
                                        gpointer         user_data);

void
on_ButtonAddMemberWindowManageList_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonDeleteMemberWindowManageList_clicked
                                        (GtkWidget        *button,
                                        gpointer         user_data);

void
on_ButtonCancelWindowManageList_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonValidateWindowManageList_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonResetWindowManageList_clicked (GtkWidget       *button,
                                        gpointer         user_data);

void
on_RadioButtonCenterOrientationWindowOrientation_toggled
                                        (GtkToggleButton *togglebutton,
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
on_ButtonNextWindowStart_clicked       (GtkButton       *button,
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
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_BouttonOpenUser_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_OpenBDV_clicked                     (GtkButton       *button,
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
on_ButtonPreviousWindowStatistic_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ButtonNothingWindowVote_clicked     (GtkWidget        *button,
                                        gpointer         user_data);

void
on_ButtonVoteWindowVote_clicked        (GtkWidget        *button,
                                        gpointer         user_data);

void
on_RadioButtonCenterOrientationWindowManageList_toggled
                                        (GtkWidget *togglebutton,
                                        gpointer         user_data);
