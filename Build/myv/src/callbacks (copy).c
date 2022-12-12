#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "function.h"

// ----- Program Variable -----







// ----- Callbacks -----

void
on_SpinButtonMaxResultSearchWindowListMain_change_value
                                        (GtkSpinButton   *spinbutton,
                                        GtkScrollType    scroll,
                                        gpointer         user_data)
{

}


void
on_ButtonCreateListWindowListMain_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	
	GtkWidget *WindowManageList = create_WindowManageList();
	//initialisation de CurrentList
	CurrentList.id_list = ReturnNbListInFile()+1;
	strcpy(CurrentList.name_list,"");
	CurrentList.orientation= 0;
	CurrentList.head_list = CurrentUser.id;
	CurrentList.members[0] = CurrentList.head_list;
	CurrentList.nb_members = 1;
	strcpy(CurrentList.affiche,"");
	CurrentList.created_at.date.year = 0;
	CurrentList.created_at.date.month = 0;
	CurrentList.created_at.date.day = 0;
	CurrentList.created_at.time.hour = 0;
	CurrentList.created_at.time.min = 0;
	CurrentList.created_at.time.sec = 0;
	CurrentList.is_valid = 0;
	CurrentList.nb_vote = 0;
	CurrentList.id_election = CurrentElection.id;
	//Initialisation de la fenetre WindowManageList
	initWindowManageList(WindowManageList ,CurrentUser,CurrentList);
	gtk_widget_show(WindowManageList);
}


void
on_ButtonModifyListWindowListMain_clicked
                                        (GtkWidget      *button,
                                        gpointer         user_data)
{
	GtkWidget *WindowActionOnList = create_WindowActionOnList();
	GtkWidget *ComboBoxSelectActionWindowActionOnList = lookup_widget(WindowActionOnList,"ComboBoxSelectActionWindowActionOnList");
	gtk_combo_box_set_active(GTK_COMBO_BOX(ComboBoxSelectActionWindowActionOnList),0);
	gtk_widget_show(WindowActionOnList);
}


void
on_ButtonDeleteListWindowListMain_clicked
                                        (GtkWidget      *button,
                                        gpointer         user_data)
{
	GtkWidget *WindowActionOnList = create_WindowActionOnList();
	GtkWidget *ComboBoxSelectActionWindowActionOnList = lookup_widget(WindowActionOnList,"ComboBoxSelectActionWindowActionOnList");
	gtk_combo_box_set_active(GTK_COMBO_BOX(ComboBoxSelectActionWindowActionOnList),1);
	gtk_widget_show(WindowActionOnList);
}


void
on_ButtonProposeList_clicked           (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *WindowManageList = create_WindowManageList();
	//initialisation de CurrentList
	CurrentList.id_list = ReturnNbListInFile()+1;
	strcpy(CurrentList.name_list,"");
	CurrentList.orientation= 0;
	CurrentList.head_list = CurrentUser.id;
	CurrentList.members[0] = CurrentList.head_list;
	CurrentList.nb_members = 1;
	strcpy(CurrentList.affiche,"");
	CurrentList.created_at.date.year = 0;
	CurrentList.created_at.date.month = 0;
	CurrentList.created_at.date.day = 0;
	CurrentList.created_at.time.hour = 0;
	CurrentList.created_at.time.min = 0;
	CurrentList.created_at.time.sec = 0;
	CurrentList.is_valid = 0;
	CurrentList.nb_vote = 0;
	CurrentList.id_election = CurrentElection.id;
	//Initialisation de la fenetre WindowManageList
	initWindowManageList(WindowManageList ,CurrentUser,CurrentList);
	gtk_widget_show(WindowManageList);
}


void
on_ButtonShowListWindowListMain_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *EntryShowListWindowListMain = lookup_widget(button,"EntryShowListWindowListMain");
	char id_list_ch[40];//une telle longueur [20] pour eviter l'erreur overflow car la valeur par defaut de la zone de saisie est longue
	int id_list;
	ElectoralList l;
	strcpy(id_list_ch,gtk_entry_get_text(GTK_ENTRY(EntryShowListWindowListMain)));
	id_list = atoi(id_list_ch);
	if(!CheckEntryId(id_list_ch)){alert("Erreur à la saisie ,Veuillez verifier \n vos entrées");return;}
	if(!catchElectListFromListId(id_list,&l)){alert("la liste ciblée n'existe pas \n Veuillez saisir un idendifiant valide");return;}
	GtkWidget *WindowShowList = create_WindowShowList();
	initWindowShowList(WindowShowList,l);
	gtk_widget_show(WindowShowList);
}


void
on_RadioButtonLeftOrientationSearchWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	listConfigSearch.orientation = -1; 
}

void
on_RadioButtonCenterOrientationSearchWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	listConfigSearch.orientation = 0; 
}


void
on_RadioButtonRightOrientationSearchWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{	
	listConfigSearch.orientation = 1; 
}


void
on_ButtonSearchWindowListMain_clicked  (GtkWidget      *button,
                                        gpointer         user_data)
{
	GtkWidget *SpinButtonMaxResultSearchWindowListMain = lookup_widget(button,"SpinButtonMaxResultSearchWindowListMain");
	GtkWidget *EntryIdListSearchWindowListMain = lookup_widget(button,"EntryIdListSearchWindowListMain");
	GtkWidget *EntryNameListSearchWindowListMain = lookup_widget(button,"EntryNameListSearchWindowListMain");
	GtkWidget *EntryHeadListSearchWindowListMain = lookup_widget(button,"EntryIdHeadListSearchWindowListMain");
	GtkWidget *treeview = lookup_widget(button,"TreeViewSearchListWindowListMain");
	ElectoralList l[200];
	int n=0,n_max;
	char name_list[30],id_list_ch[30],head_list_ch[30];

	if(listConfigSearch.criteria.id_list || listConfigSearch.criteria.head_list || listConfigSearch.criteria.name_list || listConfigSearch.criteria.orientation){
		strcpy(name_list,gtk_entry_get_text(GTK_ENTRY(EntryNameListSearchWindowListMain)));
		strcpy(head_list_ch,gtk_entry_get_text(GTK_ENTRY(EntryHeadListSearchWindowListMain)));
		strcpy(id_list_ch,gtk_entry_get_text(GTK_ENTRY(EntryIdListSearchWindowListMain )));
		if(listConfigSearch.criteria.id_list){if(!CheckEntryId(id_list_ch)){alert("verifier l'identifiant de la liste  ");return ;}}
		if(listConfigSearch.criteria.head_list){if(!CheckEntryId(head_list_ch)){alert("verifier l'identifiant de la tete de liste");return ;}}
		if(listConfigSearch.criteria.name_list){if(!CheckEntryListName(name_list)){alert("verifier le nom de la liste à chercher");return ;}}
		strcpy(listConfigSearch.id_list,id_list_ch);
		strcpy(listConfigSearch.name_list,name_list);
		strcpy(listConfigSearch.head_list,head_list_ch);
		if(!multiCriteriaSearch(listConfigSearch,l,&n)){alert("Une erreur est survenue dans la recherche");return;}
		n_max = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(SpinButtonMaxResultSearchWindowListMain));
		if(n_max< n){n=n_max;}//nombre maximal de recherche
		showLists(treeview,l,n);
		alert("Recherche effectué avec succes !!!");
		
	}else{alert("Choisissez un option");}
	
}


void
on_ButtonPreviousWindowListMain_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget * WindowListMain = lookup_widget(button,"WindowListMain");
	GtkWidget * WindowMainMenu = create_WindowMainMenu();
	gtk_widget_destroy(WindowListMain);
	gtk_widget_show(WindowMainMenu);
}


void
on_ButtonVoteWindowListMain_clicked    (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget * WindowVote = create_WindowVote();
	gtk_widget_show(WindowVote);
}


void
on_CheckButtonIdListCriteriaWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{	
	if(gtk_toggle_button_get_active(togglebutton)){listConfigSearch.criteria.id_list = true;}
	else{listConfigSearch.criteria.id_list= false;}
}


void
on_CheckButtonHeadListCriteriaWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{	
	if(gtk_toggle_button_get_active(togglebutton)){listConfigSearch.criteria.head_list = true;}
	else{listConfigSearch.criteria.head_list= false;}
}


void
on_CheckButtonNameListCriteriaWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{	
	if(gtk_toggle_button_get_active(togglebutton)){listConfigSearch.criteria.name_list = true;}
	else{listConfigSearch.criteria.name_list= false;}
}


void
on_CheckButtonOrientationCriteriaWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{	
	if(gtk_toggle_button_get_active(togglebutton)){listConfigSearch.criteria.orientation = true;}
	else{listConfigSearch.criteria.orientation= false;}
}


void
on_RadioButtonLeftOrientationWindowManageList_toggled
                                        (GtkWidget *togglebutton,
                                        gpointer         user_data)
{
	CurrentList.orientation = -1;
	GtkWidget *EntryNameListWindowManageList = lookup_widget(togglebutton,"EntryNameListWindowManageList");
	GtkWidget *EntryPosterListWindowManageList = lookup_widget(togglebutton,"EntryPosterListWindowManageList");
	strcpy(CurrentList.name_list,gtk_entry_get_text(GTK_ENTRY(EntryNameListWindowManageList)));
	strcpy(CurrentList.affiche,gtk_entry_get_text(GTK_ENTRY(EntryPosterListWindowManageList)));
	PreviewList(togglebutton,CurrentList);
}

void
on_RadioButtonCenterOrientationWindowManageList_toggled
                                        (GtkWidget *togglebutton,
                                        gpointer         user_data)
{
	CurrentList.orientation = 0;
	GtkWidget *EntryNameListWindowManageList = lookup_widget(togglebutton,"EntryNameListWindowManageList");
	GtkWidget *EntryPosterListWindowManageList = lookup_widget(togglebutton,"EntryPosterListWindowManageList");
	strcpy(CurrentList.name_list,gtk_entry_get_text(GTK_ENTRY(EntryNameListWindowManageList)));
	strcpy(CurrentList.affiche,gtk_entry_get_text(GTK_ENTRY(EntryPosterListWindowManageList)));
	PreviewList(togglebutton,CurrentList);
}

void
on_RadioButtonRightOrientationWindowManageList_toggled
                                        (GtkWidget *togglebutton,
                                        gpointer         user_data)
{
	CurrentList.orientation = 1;
	GtkWidget *EntryNameListWindowManageList = lookup_widget(togglebutton,"EntryNameListWindowManageList");
	GtkWidget *EntryPosterListWindowManageList = lookup_widget(togglebutton,"EntryPosterListWindowManageList");
	strcpy(CurrentList.name_list,gtk_entry_get_text(GTK_ENTRY(EntryNameListWindowManageList)));
	strcpy(CurrentList.affiche,gtk_entry_get_text(GTK_ENTRY(EntryPosterListWindowManageList)));
	PreviewList(togglebutton,CurrentList);
}


void
on_ButtonAddMemberWindowManageList_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data)
{	
	GtkWidget *EntryNameListWindowManageList = lookup_widget(button,"EntryNameListWindowManageList");
	GtkWidget *EntryPosterListWindowManageList = lookup_widget(button,"EntryPosterListWindowManageList");
	GtkWidget *EntryAddMemberWindowManageList = lookup_widget(button,"EntryAddMemberWindowManageList");
	char id_member_ch[10];
	int i ;
	Utilisateur temp;
	strcpy(CurrentList.name_list,gtk_entry_get_text(GTK_ENTRY(EntryNameListWindowManageList)));
	strcpy(CurrentList.affiche,gtk_entry_get_text(GTK_ENTRY(EntryPosterListWindowManageList)));
	strcpy(id_member_ch,gtk_entry_get_text(GTK_ENTRY(EntryAddMemberWindowManageList)));
	//On verifie d'abord si les entrées précedentes sont correctes
	if(!CheckEntryListName(CurrentList.name_list)){alert("verifier le nom de la liste");return ;}
	if(!CheckEntryPoster(CurrentList.affiche)){alert("verifier le chemin du fichier poster ");return ;}
	if(!CheckEntryAddMember(id_member_ch) || !stringIsNum(id_member_ch)){alert("l'identifiant à ajouter n'est pas correcte");return;}
	int id_member = atoi(id_member_ch);
	temp = chercherUser(id_member);
	if(temp.id == -1){alert("cette utilisateur n'existe pas");return ;}//chercherUser retourne -1 si l'utilisateur n'existe pas
	ElectoralList l;
	if(catchElectListFromUserId(id_member,&l)){alert("Ce candidat est déja dans une autre liste !");return ;}
	if(CurrentList.nb_members >= 9){alert("Nombre maximal de membre deja atteint \n Pour un nouvel ajout , supprimer d'autre \n Candidats dans la liste");return ;}
	for(i=0;i<CurrentList.nb_members;i++){
		if(id_member == CurrentList.members[i]){alert("Ce candidat est déja dans Votre liste !");return ;}
	}
	CurrentList.members[CurrentList.nb_members] = id_member;
	CurrentList.nb_members+=1;
	PreviewList(button,CurrentList);
}


void
on_ButtonDeleteMemberWindowManageList_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *EntryNameListWindowManageList = lookup_widget(button,"EntryNameListWindowManageList");
	GtkWidget *EntryPosterListWindowManageList = lookup_widget(button,"EntryPosterListWindowManageList");
	GtkWidget *EntryDeleteMemberWindowManageList = lookup_widget(button,"EntryDeleteMemberWindowManageList");
	char id_member_ch[10];
	int i,j ;
	_Bool v = false;
	Utilisateur temp;
	strcpy(CurrentList.name_list,gtk_entry_get_text(GTK_ENTRY(EntryNameListWindowManageList)));
	strcpy(CurrentList.affiche,gtk_entry_get_text(GTK_ENTRY(EntryPosterListWindowManageList)));
	strcpy(id_member_ch,gtk_entry_get_text(GTK_ENTRY(EntryDeleteMemberWindowManageList)));
	//On verifie d'abord si les entrées précedentes sont correctes
	if(!CheckEntryListName(CurrentList.name_list)){alert("verifier le nom de la liste");return ;}
	if(!CheckEntryPoster(CurrentList.affiche)){alert("verifier le chemin du fichier poster ");return ;}
	if(!CheckEntryListName(id_member_ch) || !stringIsNum(id_member_ch)){alert("l'identifiant à ajouter n'est pas correcte");return;}
	int id_member = atoi(id_member_ch);
	temp = chercherUser(id_member);
	if(temp.id == -1){alert("cette utilisateur n'existe pas");return ;}//chercherUser retourne -1 si l'utilisateur n'existe pas
	ElectoralList l;
	if(catchElectListFromUserId(id_member,&l)){alert("Ce candidat est déja dans une autre liste !");return ;}
	if(CurrentList.nb_members <=1){alert("Suppression Impossible \n >> Nombre minimal de membre atteint");return ;}
	for(i=0;i<CurrentList.nb_members;i++){//On supprime si l'utilisateur est dans la liste 
		if(id_member == CurrentList.members[0]){alert("Suppression de la tete de liste impossible\n Vous pouvez annuler la creation ou \n supprimer la liste ");return;}
		if(id_member == CurrentList.members[i]){
			for(j = i;j<CurrentList.nb_members-1;j++){CurrentList.members[j]=CurrentList.members[j+1];}
			CurrentList.nb_members -=1;
			v = true;
		}
	}
	if(!v){alert("l'utilisateur ne se trouve pas dans votre liste");return;}
	PreviewList(button,CurrentList);
}


void
on_ButtonCancelWindowManageList_clicked
                                        (GtkWidget        *button,
                                        gpointer         user_data)
{
	GtkWidget * WindowManageList = lookup_widget(button,"WindowManageList");
	gtk_widget_destroy(WindowManageList);
}


void
on_ButtonValidateWindowManageList_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data)
{	int i;ElectoralList buffer;
	GtkWidget *WindowManageList = lookup_widget(button,"WindowManageList");
	GtkWidget *EntryNameListWindowManageList = lookup_widget(button,"EntryNameListWindowManageList");
	GtkWidget *EntryPosterListWindowManageList = lookup_widget(button,"EntryPosterListWindowManageList");
	GtkWidget *EntryDeleteMemberWindowManageList = lookup_widget(button,"EntryDeleteMemberWindowManageList");
	strcpy(CurrentList.name_list,gtk_entry_get_text(GTK_ENTRY(EntryNameListWindowManageList)));
	strcpy(CurrentList.affiche,gtk_entry_get_text(GTK_ENTRY(EntryPosterListWindowManageList)));
	//On verifie d'abord si les entrées précedentes sont correctes
	
	if(!CheckEntryListName(CurrentList.name_list)){alert("verifier le nom de la liste");return ;}
	if(!CheckEntryPoster(CurrentList.affiche)){alert("verifier le chemin du fichier poster ");return ;}
	
	if(CurrentList.nb_members <= 3){alert("Attention les listes Contenant moins de 3 membres\n seront supprimé le jour de l'election");}
	time_t now;
	now = time(NULL);//On recupere le temp qu'il fait 
	struct tm * now_tm = localtime(&now);
	CurrentList.created_at.date.year = now_tm->tm_year+1900;//tm_year represente le nombre d'année écoulé depuis l'année 1900
	CurrentList.created_at.date.month = now_tm->tm_mon+1;// tm_day va de 0 à 11 
	CurrentList.created_at.date.day = now_tm->tm_mday;
	CurrentList.created_at.time.hour = now_tm->tm_hour;
	CurrentList.created_at.time.min = now_tm->tm_min;
	CurrentList.created_at.time.sec = now_tm->tm_sec;
	for(i=CurrentList.nb_members;i<9;i++){
		CurrentList.members[i] = 0;//Pour eviter des erreurs a l'écriture des données pour manque d'information
	}
	if(catchElectListFromListId(CurrentList.id_list,&buffer)){//La liste existe déja dans le fichier
		if(ModifyElectoralList(CurrentList)){alert("LISTE MODIFIÉ AVEC SUCCESS !!!");gtk_widget_destroy(WindowManageList);}
		else{alert("Echec de la modification !!!");}
	}
	else{//On creer si la liste n'existe pas
		if(CreateElectoralList(CurrentList)){alert("LISTE CRÉE AVEC SUCCESS !!!");gtk_widget_destroy(WindowManageList);}
		else{alert("Echec de la creation !!!");}
	}
	

}


void
on_ButtonResetWindowManageList_clicked (GtkWidget       *button,
                                        gpointer         user_data)
{
	//initialisation de CurrentList
	CurrentList.id_list = ReturnNbListInFile()+1;
	strcpy(CurrentList.name_list,"");
	CurrentList.orientation= 0;
	CurrentList.head_list = CurrentUser.id;
	CurrentList.nb_members = 1;
	CurrentList.members[0] = CurrentList.head_list;
	strcpy(CurrentList.affiche,"");
	CurrentList.created_at.date.year = 0;
	CurrentList.created_at.date.month = 0;
	CurrentList.created_at.date.day = 0;
	CurrentList.created_at.time.hour = 0;
	CurrentList.created_at.time.min = 0;
	CurrentList.created_at.time.sec = 0;
	CurrentList.is_valid = 0;
	CurrentList.nb_vote = 0;
	CurrentList.id_election = CurrentElection.id;
	initWindowManageList(button ,CurrentUser,CurrentList);

}


void
on_RadioButtonCenterOrientationWindowOrientation_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)//xxxxx
{

}


void
on_ButtonOkWindowAlert_clicked         (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget * WindowAlertList;
	WindowAlertList = lookup_widget(button,"WindowAlertList");
	gtk_widget_destroy(WindowAlertList);
}


void
on_ButtonCloseWindowShowList_clicked   (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget* WindowShowList = lookup_widget(button,"WindowShowList");
	gtk_widget_destroy(WindowShowList);
}


void
on_ButtonCancelWindowActionOnList_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget* WindowActionOnList = lookup_widget(button,"WindowActionOnList");
	gtk_widget_destroy(WindowActionOnList);
}


void
on_ButtonConfirmWindowActionOnList_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget* EntryIdListWindowActionOnList = lookup_widget(button,"EntryIdListWindowActionOnList");
	GtkWidget* ComboBoxSelectActionWindowActionOnList = lookup_widget(button,"ComboBoxSelectActionWindowActionOnList"); 
	char id_list_ch[40];//une telle longueur [20] pour eviter l'erreur overflow car la valeur par defaut de la zone de saisie est longue
	int id_list;
	ElectoralList l;
	strcpy(id_list_ch,gtk_entry_get_text(GTK_ENTRY(EntryIdListWindowActionOnList)));
	id_list = atoi(id_list_ch);
	if(!CheckEntryId(id_list_ch)){alert("Erreur à la saisie ,Veuillez verifier \n vos entrées");return;}
	if(!catchElectListFromListId(id_list,&l)){alert("la liste ciblée n'existe pas \n Veuillez saisir un idendifiant valide");return;}
	if(l.head_list!=CurrentUser.id){alert("******Accès Refusé****** \n Vous n'avez pas les droits requis pour cette action");return;}
	if(strcmp("Modifier",gtk_combo_box_get_active_text(GTK_COMBO_BOX(ComboBoxSelectActionWindowActionOnList)))==0){
		CurrentList = l;
		GtkWidget* WindowManageList = create_WindowManageList();
		GtkWidget* WindowActionOnList = lookup_widget(button,"WindowActionOnList");
		initWindowManageList(WindowManageList ,CurrentUser,CurrentList);
		gtk_widget_destroy(WindowActionOnList);
		gtk_widget_show(WindowManageList);
		return;}
	if(strcmp("Supprimer",gtk_combo_box_get_active_text(GTK_COMBO_BOX(ComboBoxSelectActionWindowActionOnList)))==0){
		if(DeleteElectoralList(id_list)){alert("Liste Supprimée avec Succes");return;}
		alert("Action non effectuée \n Un probleme est survenu lors de la \n suppression");
	}
}


void
on_ComboBoxSelectActionWindowActionOnList_changed
                                        (GtkComboBox     *combobox,
                                        gpointer         user_data)
{

}


void
on_ButtonNextWindowStart_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_ButtonPreviousWindowConnection_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_ButtonResetWindowConnection_clicked (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_ButtonConnectionWindowConnection_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_BouttonOpenUser_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_OpenBDV_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_OpenObservation_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_ButtonOpenElectoralList_clicked     (GtkWidget      *button,
                                        gpointer         user_data)
{	
	
	//Init Config
	UpdateVoteOnListElectoral(); 
	strcpy(listConfigSearch.id_list,"");
	strcpy(listConfigSearch.name_list,"");
	listConfigSearch.orientation = 0 ;
	strcpy(listConfigSearch.head_list,"");
	listConfigSearch.max_result = 10;
	listConfigSearch.criteria.id_list = true;
	listConfigSearch.criteria.name_list = false ;
	listConfigSearch.criteria.orientation = false ;
	listConfigSearch.criteria.head_list = false ;
	//Init Current User
	CurrentUser = chercherUser(10);
	//InitElection
	CurrentElection.id = 1;
	CurrentElection.nbh = 6000;
	CurrentElection.nbc = 12;
	strcpy(CurrentElection.muni,"Ariana");

	GtkWidget* treeview;
	GtkWidget* WindowListMain = create_WindowListMain();
	GtkWidget* WindowMainMenu = lookup_widget(button,"WindowMainMenu");
	treeview = lookup_widget(WindowListMain,"TreeViewSearchListWindowListMain");
	initWindowListMain(CurrentUser,CurrentElection,WindowListMain);
	gtk_widget_destroy(WindowMainMenu);
	gtk_widget_show(WindowListMain);


}


void
on_OpenElection_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_OpenReclamation_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_PrecedentMainMenu_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_ButtonOpenStat_clicked              (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *WindowMainMenu;
	GtkWidget *WindowStatistics;
	GtkWidget *TreeViewListOrderDescending;
	GtkWidget *TreeViewAdvisersWinners;
	ElectoralList l[200];
	Utilisateur Winner_user[200];
	int n,i,k=0;
	int Winner[50];
	//InitElection
	CurrentElection.id = 1;
	CurrentElection.nbh = 6000;
	CurrentElection.nbc = 12;
	strcpy(CurrentElection.muni,"Ariana");

	WindowStatistics=create_WindowStatistics ();
	WindowMainMenu=lookup_widget(button, "WindowMainMenu");
	TreeViewListOrderDescending=lookup_widget(WindowStatistics, "TreeViewListOrderDescending");
	TreeViewAdvisersWinners=lookup_widget(WindowStatistics, "TreeViewAdvisersWinners");
	RangeListElectoral(l,&n);
	showLists(TreeViewListOrderDescending,l,n);
	findWinner(Winner,&k,l,CurrentElection.nbh,9);
	for(i=0;i<k;i++){
		Winner_user[i] = chercherUser(Winner[i]);
	}
	showUserInList(TreeViewAdvisersWinners,Winner_user,k);
	gtk_widget_destroy (WindowMainMenu);
	gtk_widget_show (WindowStatistics);
}

void
on_ButtonPreviousWindowStatistic_clicked
                                        (GtkWidget      *button,
                                        gpointer         user_data)
{
	GtkWidget *WindowStatistics = lookup_widget(button,"WindowStatistics");
	GtkWidget *WindowMainMenu =create_WindowMainMenu();
	gtk_widget_destroy (WindowStatistics);
	gtk_widget_show (WindowMainMenu);
}


void
on_ButtonNothingWindowVote_clicked     (GtkWidget        *button,
                                        gpointer         user_data)
{
	CurrentUser.vote = 0 ;
	if(modifierUser(CurrentUser.id,CurrentUser)!=1){alert("Vote non émis .Une erreur est survenue");return;}
	alert("Abstention Enregistrée");
	UpdateVoteOnListElectoral();
	GtkWidget *WindowVote = lookup_widget(button,"WindowVote");
	gtk_widget_destroy(WindowVote);
}


void
on_ButtonVoteWindowVote_clicked        (GtkWidget       *button,
                                        gpointer         user_data)
{	char temp_ch[20];
	int temp;
	ElectoralList l;
	GtkWidget * EntryIdListWindowVote = lookup_widget(button,"EntryIdListWindowVote");
	strcpy(temp_ch,gtk_entry_get_text(GTK_ENTRY(EntryIdListWindowVote)));
	if(!CheckEntryId(temp_ch)){alert("Erreur à la saisie ,Veuillez verifier \n vos entrées");return;}
	temp = atoi(temp_ch);
	if(!catchElectListFromListId(temp,&l)){alert("la liste ciblée n'existe pas \n Veuillez saisir un idendifiant valide");return;}
	CurrentUser.vote = temp ;
	if(modifierUser(CurrentUser.id,CurrentUser)!=1){alert("Vote non émis .Une erreur est survenue");return;}
	alert("Vote Enregistrée");
	UpdateVoteOnListElectoral();
	GtkWidget *WindowVote = lookup_widget(button,"WindowVote");
	gtk_widget_destroy(WindowVote);	
}




