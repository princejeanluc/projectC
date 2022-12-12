#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "function.h"


int a,jj,mm,aa,id;
char chjj[2],chmm[2],chaa[4],chid[20];
int SexeAdd[2],SexeModify[2];
Utilisateur u,U;


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
on_RadioButtonRightOrientationSearchWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{	
	listConfigSearch.orientation = 1; 
}


void
on_RadioButtonCenterOrientationSearchWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	listConfigSearch.orientation = 0; 
}

void
on_RadioButtonLeftOrientationSearchWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	listConfigSearch.orientation = -1; 
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
on_CheckButtonNameListCriteriaWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{	
	if(gtk_toggle_button_get_active(togglebutton)){listConfigSearch.criteria.name_list = true;}
	else{listConfigSearch.criteria.name_list= false;}
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
on_CheckButtonIdListCriteriaWindowListMain_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{	
	if(gtk_toggle_button_get_active(togglebutton)){listConfigSearch.criteria.id_list = true;}
	else{listConfigSearch.criteria.id_list= false;}
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
on_ButtonNextWindowStart_clicked       (GtkWidget *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *WindowConnection;
  GtkWidget *WindowStart;
  WindowStart=lookup_widget(objet_graphique, "WindowStart");
  gtk_widget_hide (WindowStart);

  WindowConnection=create_WindowConnection ();
  gtk_widget_show (WindowConnection);
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
                                        (GtkWidget *objet_graphique,
                                        gpointer         user_data)
{
	char entry_id_ch[10],entry_password_ch[10];
	int entry_id,entry_password;
	GtkWidget *WindowConnection;
	GtkWidget *WindowMainMenu;
	GtkWidget * EntryIdWindowConnection =lookup_widget(objet_graphique, "EntryIdWindowConnection");
	GtkWidget * EntryPasswordWindowConnection =lookup_widget(objet_graphique, "EntryPasswordWindowConnection");
	strcpy(entry_id_ch,gtk_entry_get_text(GTK_ENTRY(EntryIdWindowConnection)));
	strcpy(entry_password_ch,gtk_entry_get_text(GTK_ENTRY(EntryPasswordWindowConnection)));
	entry_id = atoi(entry_id_ch);
	entry_password = atoi(entry_password_ch);
	CurrentUser = chercherUser(entry_id);
	if(CurrentUser.id == -1){alert("Cette identifiant n'existe pas ");return ;}
	if(CurrentUser.mot_de_passe!= entry_password){alert("Mot de passe incorrecte");return ;}	
	WindowConnection=lookup_widget(objet_graphique, "WindowConnection");
	gtk_widget_hide (WindowConnection);
	WindowMainMenu=create_WindowMainMenu ();
	gtk_widget_show (WindowMainMenu);	



  


}


void
on_BouttonOpenUser_clicked             (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
  GtkWidget *WindowMainUser;
  GtkWidget *WindowStatistics;

  WindowStatistics=lookup_widget(objet_graphique, "WindowMainMenu");
  gtk_widget_destroy (WindowStatistics);

  WindowMainUser=create_WindowMainUser ();
  gtk_widget_show (WindowMainUser);


}


void
on_OpenBDV_clicked                     (GtkWidget *objet_graphique,
                                        gpointer         user_data)
{
  GtkWidget *WindowMainPollingOffice;
  GtkWidget *WindowMainMenu;
  WindowMainMenu=lookup_widget(objet_graphique, "WindowMainMenu");
  gtk_widget_hide (WindowMainMenu);

  WindowMainPollingOffice=create_WindowMainPollingOffice ();
  gtk_widget_show (WindowMainPollingOffice);
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
	
//------Utilisateur
	char chnb[20],chtt[20];
	int nb;
	float ttt,tte;
	 
	taux( &ttt, &tte);
	nb=nbobserver();

	GtkWidget *pa,*ma;
	sprintf(chnb, "nb = %d \n" , nb);
	sprintf(chtt, "Tt= %f %% et Te= %f %% \n" , ttt,tte);

	pa=lookup_widget(button,"LabelTotalObservateurs");
	strcpy(chnb,gtk_entry_get_text(GTK_ENTRY(pa)));

	ma=lookup_widget(button,"LabelRateObservateursNationality");
	strcpy(chtt,gtk_entry_get_text(GTK_ENTRY(ma)));



//-----------
	gtk_widget_destroy (WindowMainMenu);
	gtk_widget_show (WindowStatistics);



}


on_BouttonShowUser_clicked             (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
  char chid[20];
  GtkWidget *WriteIdUser;
  WriteIdUser=lookup_widget(objet_graphique,"WriteIdUser");
  strcpy(chid,gtk_entry_get_text(GTK_ENTRY(WriteIdUser)));
  id=atoi(chid);

//---------
  int tr=0;
    FILE * f=fopen("Utilisateur.txt", "r");
    if(f!=NULL)
    {
        while(tr==0 && fscanf(f,"%s %s %d %d %s %s %s %s %d %d %d %d %d\n",U.nom,U.prenom,&U.cin,&U.id,U.sexe,U.nationalite,U.adresse,U.role,&U.vote,&U.mot_de_passe,&U.date_de_naissance.jj,&U.date_de_naissance.mm,&U.date_de_naissance.aa)!=EOF)
        {
            if(U.id== id)
                tr=1;
        }
    }
    fclose(f);
    if(tr==0)
        U.id=-1;

//---------------------------------------


  //u=chercher("Utilisateur.txt",id);
if(U.id==(-1))
{
  GtkWidget *WindowErreur;
  WindowErreur=create_WindowErreur ();
  gtk_widget_show (WindowErreur);

}
else
{

//----------
  
  GtkWidget *NomShowUser, *PrenomShowUser, *CINShowUser, *AdresseShowUser, *IdShowUser, *NationaliteShowUser, *RoleShowUser, *PasseShowUser, *DateShowUser, *VoteShowUser, *SexeShowUser;
  char chcin[20],chpasse[20],chjj[4],chmm[4],chaa[6],chdate[20],chvote[20];

NomShowUser=lookup_widget(objet_graphique,"LabelNom");
PrenomShowUser=lookup_widget(objet_graphique,"LabelPrenom");
CINShowUser=lookup_widget(objet_graphique,"LabelCIN");
AdresseShowUser=lookup_widget(objet_graphique,"LabelAdresse");
IdShowUser=lookup_widget(objet_graphique,"LabelId");
NationaliteShowUser=lookup_widget(objet_graphique,"LabelNationalite");
RoleShowUser=lookup_widget(objet_graphique,"LabelRole");
PasseShowUser=lookup_widget(objet_graphique,"LabelPasse");
DateShowUser=lookup_widget(objet_graphique,"LabelDate");
VoteShowUser=lookup_widget(objet_graphique,"LabelVote");
SexeShowUser=lookup_widget(objet_graphique,"LabelSexe");
  

gtk_label_set_text(GTK_LABEL(NomShowUser),u.nom);
gtk_label_set_text(GTK_LABEL(PrenomShowUser),u.prenom);
sprintf(chcin, "%d" , u.cin);
gtk_label_set_text(GTK_LABEL(CINShowUser),chcin);
gtk_label_set_text(GTK_LABEL(AdresseShowUser),u.adresse);
sprintf(chid, "%d" , u.id);
gtk_label_set_text(GTK_LABEL(IdShowUser),chid);
gtk_label_set_text(GTK_LABEL(NationaliteShowUser),u.nationalite);
gtk_label_set_text(GTK_LABEL(RoleShowUser),u.role);
sprintf(chpasse, "%d" , u.mot_de_passe);
gtk_label_set_text(GTK_LABEL(PasseShowUser),chpasse);
sprintf(chjj, "%d" , u.date_de_naissance.jj);
sprintf(chmm, "%d" , u.date_de_naissance.mm);
sprintf(chaa, "%d" , u.date_de_naissance.aa);
sprintf(chdate,"%s / %s / %s \n",chjj,chmm,chaa);

gtk_label_set_text(GTK_LABEL(DateShowUser),chdate);
if(u.vote==1){strcpy(chvote,"Votee");}
else if(u.vote==0){strcpy(chvote,"Vote blanc");}
else {strcpy(chvote,"n\'est pas votee");}
gtk_label_set_text(GTK_LABEL(VoteShowUser),chvote);
gtk_label_set_text(GTK_LABEL(SexeShowUser),u.sexe);


//-------

  GtkWidget *WindowMainUser;
  GtkWidget *WindowShowUser;
  WindowMainUser=lookup_widget(objet_graphique, "WindowMainUser");
  gtk_widget_hide (WindowMainUser);

  WindowShowUser=create_WindowShowUser ();
  gtk_widget_show (WindowShowUser);
}


}



void
on_BouttonModifyUser_clicked           (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{  

  GtkWidget *WriteIdUser;
  WriteIdUser=lookup_widget(objet_graphique,"WriteIdUser");
  strcpy(chid,gtk_entry_get_text(GTK_ENTRY(WriteIdUser)));
  id=atoi(chid);

//---------
  int tr=0;
    FILE * f=fopen("Utilisateur.txt", "r");
    if(f!=NULL)
    {
        while(tr==0 && fscanf(f,"%s %s %d %d %s %s %s %s %d %d %d %d %d\n",U.nom,U.prenom,&U.cin,&U.id,U.sexe,U.nationalite,U.adresse,U.role,&U.vote,&U.mot_de_passe,&U.date_de_naissance.jj,&U.date_de_naissance.mm,&U.date_de_naissance.aa)!=EOF)
        {
            if(U.id== id)
                tr=1;
        }
    }
    fclose(f);
    if(tr==0)
        U.id=-1;

//---------------------------------------


  //u=chercher("Utilisateur.txt",id);
if(U.id==(-1))
{
  GtkWidget *WindowErreur;
  WindowErreur=create_WindowErreur ();
  gtk_widget_show (WindowErreur);

}
else
{
  GtkWidget *WindowMainUser;
  GtkWidget *WindowModifyUser;
  WindowMainUser=lookup_widget(objet_graphique, "WindowMainUser");
  gtk_widget_destroy (WindowMainUser);

  WindowModifyUser=create_WindowModifyUser ();
  gtk_widget_show (WindowModifyUser);
}

}



void
on_BouttonDeleteUser_clicked           (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{  
  GtkWidget *WriteIdUser;
  WriteIdUser=lookup_widget(objet_graphique,"WriteIdUser");
  strcpy(chid,gtk_entry_get_text(GTK_ENTRY(WriteIdUser)));
  id=atoi(chid);
  
//--------------------

    a=0;
    FILE * f=fopen("Utilisateur.txt", "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%s %s %d %d %s %s %s %s %d %d %d %d %d\n",U.nom,U.prenom,&U.cin,&U.id,U.sexe,U.nationalite,U.adresse,U.role,&U.vote,&U.mot_de_passe,&U.date_de_naissance.jj,&U.date_de_naissance.mm,&U.date_de_naissance.aa)!=EOF)
        {
            if(U.id== id)
                a=1;
            else
                fprintf(f2,"%s %s %d %d %s %s %s %s %d %d %d %d %d\n",U.nom,U.prenom,U.cin,U.id,U.sexe,U.nationalite,U.adresse,U.role,U.vote,U.mot_de_passe,U.date_de_naissance.jj,U.date_de_naissance.mm,U.date_de_naissance.aa);
        }
    }
    fclose(f);
    fclose(f2);
    remove("Utilisateur.txt");
    rename("nouv.txt", "Utilisateur.txt");





 // a=supprimer("Utilisateur.txt",id);
//-----------
  if (a==1)
{
  GtkWidget *WindowSucceed;
  WindowSucceed=create_WindowSucceed ();
  gtk_widget_show (WindowSucceed);
}
else
{
  GtkWidget *WindowErreur;
  WindowErreur=create_WindowErreur ();
  gtk_widget_show (WindowErreur);
}

GtkWidget *snumero,*cap;
cap=lookup_widget(objet_graphique,"WindowMainUser");
snumero=lookup_widget(objet_graphique,"TreeviewUser");
//afficher_User(snumero);

}
void
on_SearchUser_clicked                  (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
  char chrole[20];
  GtkWidget *WriteRoleUser;
  WriteRoleUser=lookup_widget(objet_graphique,"WriteSearchUser");
  strcpy(chrole,gtk_entry_get_text(GTK_ENTRY(WriteRoleUser)));

GtkWidget *snumero,*cap;
cap=lookup_widget(objet_graphique,"WindowMainUser");
snumero=lookup_widget(objet_graphique,"TreeviewUser");
//afficherNom_User(snumero);

  
}
void
on_PrecedentUser_clicked               (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
  GtkWidget *WindowMainUser;
  GtkWidget *WindowMainMenu;

  WindowMainUser=lookup_widget(objet_graphique, "WindowMainUser");
  gtk_widget_destroy (WindowMainUser);

  WindowMainMenu=create_WindowMainMenu ();
  gtk_widget_show (WindowMainMenu);

GtkWidget *snumero,*cap;
cap=lookup_widget(objet_graphique,"WindowMainUser");
snumero=lookup_widget(objet_graphique,"TreeviewUser");
//afficher_User(snumero);
}


void
on_SearchNameUser_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_AddUser_clicked                     (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
  GtkWidget *WindowMainUser;
  GtkWidget *WindowAddUser;
  WindowMainUser=lookup_widget(objet_graphique, "WindowMainUser");
  gtk_widget_destroy (WindowMainUser);

  WindowAddUser=create_WindowAddUser ();
  gtk_widget_show (WindowAddUser);
}


void
on_WriteJourAddUser_changed            (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
  GtkWidget *WriteJourAddUser;
  WriteJourAddUser=lookup_widget(objet_graphique,"WriteJourAddUser");
  u.date_de_naissance.jj=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(WriteJourAddUser));
  
  
}


void
on_WriteAnneeAddUser_changed           (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
  GtkWidget *WriteAnneeAddUser;
  WriteAnneeAddUser=lookup_widget(objet_graphique,"WriteAnneeAddUser");
  u.date_de_naissance.aa=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(WriteAnneeAddUser));
}


void
on_WriteMoiAddUser_changed             (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
  GtkWidget *WriteMoiAddUser;
  WriteMoiAddUser=lookup_widget(objet_graphique,"WriteMoiAddUser");
  u.date_de_naissance.mm=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(WriteMoiAddUser));
}

void
on_FemmeAddUser_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if (gtk_toggle_button_get_active(togglebutton))
{SexeAdd[0]=1;}
}


void
on_HommeAddUser_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if (gtk_toggle_button_get_active(togglebutton))
{SexeAdd[1]=1;}
}


void
on_BouttonAjouterAddUser_clicked       (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *NomAddUser, *PrenomAddUser, *CINAddUser, *AdresseAddUser, *IdAddUser, *NationaliteAddUser, *RoleAddUser, *PasseAddUser;
char chcin[20],chid[20],chpasse[20];

NomAddUser=lookup_widget(objet_graphique,"WriteNomAddUser");
PrenomAddUser=lookup_widget(objet_graphique,"WritePrenomAddUser");
CINAddUser=lookup_widget(objet_graphique,"WriteCINAddUser");
AdresseAddUser=lookup_widget(objet_graphique,"WriteAdresseAddUser");
IdAddUser=lookup_widget(objet_graphique,"WriteIdAddUser");
NationaliteAddUser=lookup_widget(objet_graphique,"WriteNationaliteAddUser");
RoleAddUser=lookup_widget(objet_graphique,"WriteRoleAddUser");
PasseAddUser=lookup_widget(objet_graphique,"WritePasseAddUser");

strcpy(u.nom,gtk_entry_get_text(GTK_ENTRY(NomAddUser)));
strcpy(u.prenom,gtk_entry_get_text(GTK_ENTRY(PrenomAddUser)));
strcpy(chcin,gtk_entry_get_text(GTK_ENTRY(CINAddUser)));
u.cin=atoi(chcin);
strcpy(u.adresse,gtk_entry_get_text(GTK_ENTRY(AdresseAddUser)));
strcpy(chid,gtk_entry_get_text(GTK_ENTRY(IdAddUser)));
u.id=atoi(chid);
strcpy(u.nationalite,gtk_entry_get_text(GTK_ENTRY(NationaliteAddUser)));
strcpy(u.role,gtk_entry_get_text(GTK_ENTRY(RoleAddUser)));
strcpy(chpasse,gtk_entry_get_text(GTK_ENTRY(PasseAddUser)));
u.mot_de_passe=atoi(chpasse);

//---------
  int tr=0;
    FILE * f=fopen("Utilisateur.txt", "r");
    if(f!=NULL)
    {
        while(tr==0 && fscanf(f,"%s %s %d %d %s %s %s %s %d %d %d %d %d\n",U.nom,U.prenom,&U.cin,&U.id,U.sexe,U.nationalite,U.adresse,U.role,&U.vote,&U.mot_de_passe,&U.date_de_naissance.jj,&U.date_de_naissance.mm,&U.date_de_naissance.aa)!=EOF)
        {
            if(U.id == id)
                tr=1;
        }
    }
    fclose(f);
    if(tr==0)
        U.id=-1;

//---------------------------------------

u.vote=-1;
if ((SexeAdd[0]=1)&&(SexeAdd[1]=0)){strcpy(u.sexe,"Femme");}
if ((SexeAdd[0]=0)&&(SexeAdd[1]=1)){strcpy(u.sexe,"Homme");}
if (((SexeAdd[0]=0)&&(SexeAdd[1]=1))||((SexeAdd[0]=1)&&(SexeAdd[1]=0)))
{if (tr==1){a=AjouterUser(u);}}
else {a=0;}

  GtkWidget *WindowMainUser;
  GtkWidget *WindowAddUser;
  WindowAddUser=lookup_widget(objet_graphique, "WindowAddUser");
  gtk_widget_destroy (WindowAddUser);

  WindowMainUser=create_WindowMainUser ();
  gtk_widget_show (WindowMainUser);
if (a==1)
{
  GtkWidget *WindowSucceed;
  WindowSucceed=create_WindowSucceed ();
  gtk_widget_show (WindowSucceed);
}
else
{
  GtkWidget *WindowErreur;
  WindowErreur=create_WindowErreur ();
  gtk_widget_show (WindowErreur);
}

GtkWidget *snumero,*cap;
cap=lookup_widget(objet_graphique,"WindowMainUser");
snumero=lookup_widget(objet_graphique,"TreeviewUser");
//afficher_User(snumero);

}


void
on_BouttonPrecedentAddUser_clicked     (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
  GtkWidget *WindowMainUser;
  GtkWidget *WindowAddUser;
  WindowAddUser=lookup_widget(objet_graphique, "WindowAddUser");
  gtk_widget_destroy (WindowAddUser);

  WindowMainUser=create_WindowMainUser ();
  gtk_widget_show (WindowMainUser);


GtkWidget *snumero,*cap;
cap=lookup_widget(objet_graphique,"WindowMainUser");
snumero=lookup_widget(objet_graphique,"TreeviewUser");
//afficher_User(snumero);

}


void
on_WriteJourModifyUser_changed         (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
  GtkWidget *WriteJourModifyUser;
  WriteJourModifyUser=lookup_widget(objet_graphique,"WriteJourModifyUser");
  u.date_de_naissance.jj=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(WriteJourModifyUser));
  
}


void
on_WriteAnneeModifyUser_changed        (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
  GtkWidget *WriteAnneeModifyUser;
  WriteAnneeModifyUser=lookup_widget(objet_graphique,"WriteAnneeModifyUser");
  u.date_de_naissance.aa=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(WriteAnneeModifyUser));
}


void
on_WriteMoisModifyUser_changed         (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
  GtkWidget *WriteMoiModifyUser;
  WriteMoiModifyUser=lookup_widget(objet_graphique,"WriteMoiModifyUser");
  u.date_de_naissance.mm=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(WriteMoiModifyUser));
}

void
on_HommeModifyUser_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if(gtk_toggle_button_get_active(togglebutton)){SexeModify[1]=1;}
}


void
on_FemmeModifyUser_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if(gtk_toggle_button_get_active(togglebutton)){SexeModify[0]=1;}
}



void
on_BouttonModifierUser_clicked         (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
  GtkWidget *NomAddUser, *PrenomAddUser, *CINAddUser, *AdresseAddUser, *IdAddUser, *NationaliteAddUser, *RoleAddUser, *PasseAddUser;
char cin[20],chid[20],passe[20];

NomAddUser=lookup_widget(objet_graphique,"WriteNomModifyUser");
PrenomAddUser=lookup_widget(objet_graphique,"WritePrenomModifyUser");
CINAddUser=lookup_widget(objet_graphique,"WriteCINModifyUser");
AdresseAddUser=lookup_widget(objet_graphique,"WriteAdresseModifyUser");
//IdAddUser=lookup_widget(objet_graphique,"WriteIdModifyUser");
NationaliteAddUser=lookup_widget(objet_graphique,"WriteNationaliteModifyUser");
RoleAddUser=lookup_widget(objet_graphique,"WriteRoleModifyUser");
PasseAddUser=lookup_widget(objet_graphique,"WritePasseModifyUser");

strcpy(u.nom,gtk_entry_get_text(GTK_ENTRY(NomAddUser)));
strcpy(u.prenom,gtk_entry_get_text(GTK_ENTRY(PrenomAddUser)));
strcpy(cin,gtk_entry_get_text(GTK_ENTRY(CINAddUser)));
u.cin=atoi(cin);
strcpy(u.adresse,gtk_entry_get_text(GTK_ENTRY(AdresseAddUser)));
//strcpy(id,gtk_entry_get_text(GTK_ENTRY(IdAddUser)));
u.id=id;
strcpy(u.nationalite,gtk_entry_get_text(GTK_ENTRY(NationaliteAddUser)));
strcpy(u.role,gtk_entry_get_text(GTK_ENTRY(RoleAddUser)));
strcpy(passe,gtk_entry_get_text(GTK_ENTRY(PasseAddUser)));
u.mot_de_passe=atoi(passe);
u.vote=-1;
if ((SexeModify[0]=1)&&(SexeModify[1]=0)){strcpy(u.sexe,"Femme");}
if ((SexeModify[0]=0)&&(SexeModify[1]=1)){strcpy(u.sexe,"Homme");}
if (((SexeModify[0]=0)&&(SexeModify[1]=1))||((SexeModify[0]=1)&&(SexeModify[1]=0)))
{a=AjouterUser(u);}
else {a=0;}

  GtkWidget *WindowMainUser;
  GtkWidget *WindowModifyUser;
  WindowModifyUser=lookup_widget(objet_graphique, "WindowModifyUser");
  gtk_widget_destroy (WindowModifyUser);

  WindowMainUser=create_WindowMainUser ();
  gtk_widget_show (WindowMainUser);

if (a==1)
{
  GtkWidget *WindowSucceed;
  WindowSucceed=create_WindowSucceed ();
  gtk_widget_show (WindowSucceed);
}
else
{
  GtkWidget *WindowErreur;
  WindowErreur=create_WindowErreur ();
  gtk_widget_show (WindowErreur);
}


}


void
on_BouttonPrecedentModifyUser_clicked  (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
  GtkWidget *WindowMainUser;
  GtkWidget *WindowModifyUser;

  WindowModifyUser=lookup_widget(objet_graphique, "WindowModifyUser");
  gtk_widget_destroy (WindowModifyUser);

  WindowMainUser=create_WindowMainUser ();
  gtk_widget_show (WindowMainUser);
}



void
on_BouttonSucces_clicked               (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
  GtkWidget *WindowSucceed;
  GtkWidget *WindowMainUser;

  WindowSucceed=lookup_widget(objet_graphique, "WindowSucceed");
  gtk_widget_destroy (WindowSucceed);

GtkWidget *snumero,*cap;
cap=lookup_widget(objet_graphique,"WindowMainUser");
snumero=lookup_widget(objet_graphique,"TreeviewUser");
//afficher_User(snumero);

}


void
on_BouttonErreur_clicked               (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
  GtkWidget *WindowErreur;
  WindowErreur=lookup_widget(objet_graphique, "WindowErreur");
  gtk_widget_destroy (WindowErreur);

GtkWidget *snumero,*cap;
cap=lookup_widget(objet_graphique,"WindowMainUser");
snumero=lookup_widget(objet_graphique,"TreeviewUser");
//afficher_User(snumero);
}


void
on_BouttonPrecedentShowUser_clicked    (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
  GtkWidget *WindowMainUser;
  GtkWidget *WindowShowUser;

  WindowShowUser=lookup_widget(objet_graphique, "WindowShowUser");
  gtk_widget_destroy (WindowShowUser);

  WindowMainUser=create_WindowMainUser ();
  gtk_widget_show (WindowMainUser);

GtkWidget *snumero,*cap;
cap=lookup_widget(objet_graphique,"WindowMainUser");
snumero=lookup_widget(objet_graphique,"TreeviewUser");
//afficher_User(snumero);
}


void
on_WriteCapaciteDeElecteurBVAdd_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_WriteCapaciteDeObservateurBVAdd_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_PrecedentBVAdd_clicked              (GtkWidget *objet_graphique,
                                        gpointer         user_data)
{
  GtkWidget *WindowAddPollingOffice;
  GtkWidget *WindowMainPollingOffice;
  WindowAddPollingOffice=lookup_widget(objet_graphique, "WindowAddPollingOffice");
  gtk_widget_hide (WindowAddPollingOffice);

  WindowMainPollingOffice=create_WindowMainPollingOffice ();
  gtk_widget_show (WindowMainPollingOffice);
}



void
on_AjouterBVAdd_clicked                (GtkWidget *objet_graphique,
                                        gpointer         user_data)
{
bureau_vote b;
   
   GtkWidget *inputIdBV ;
   GtkWidget *inputNumS ;
   GtkWidget *ob;
   GtkWidget *elec;

   GtkWidget *inputAddr ;
   GtkWidget *inputIdABV;
inputIdBV = lookup_widget(objet_graphique, "WriteIdBVAdd") ;
inputNumS=lookup_widget(objet_graphique, "WriteNumDeSalleAdd") ;
inputAddr=lookup_widget(objet_graphique, "WriteAdresseBVAdd") ;
inputIdABV =lookup_widget(objet_graphique, "WriteIdABVAdd") ;

int y=atoi(gtk_entry_get_text(GTK_ENTRY(inputIdBV)));
int x=atoi(gtk_entry_get_text(GTK_ENTRY(inputIdABV)));
strcpy(b.adresse,gtk_entry_get_text(GTK_ENTRY(inputAddr)));
strcpy(b.salle,gtk_entry_get_text(GTK_ENTRY(inputNumS)));
b.idBV=y ;
b.idABV=x ;
b.capacite_e=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (elec));
b.capacite_o=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (ob));
int a = ajouterBV(b);
   if (a==1)
{
  GtkWidget *windowSucced;

  windowSucced=create_WindowSucceed ();
  gtk_widget_show (windowSucced);
}
   else 
{
GtkWidget *windowErreur;

  windowErreur=create_WindowErreur ();
  gtk_widget_show (windowErreur);
}

}


void
on_writeCapaciteDeElecteurBVSupp_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_WriteCapaciteDeObservateurBVSupp_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_PrecedentBVSupp_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_ModifierBVSupp_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_WriteCapaciteDeElecteurBVAff_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_WriteCapaciteDeObservateurBVAff_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_PrecedentBVAff_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_nbh_ajou_election_changed           (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_nbc_ajou_electon_changed            (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_jour_ajou_election_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_mois_ajou_election_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_annee_ajou_election_changed         (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_Precedent1_election_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_Ajouter_election_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_nbh_modi_election_changed           (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_nbc_modi_election_changed           (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_jour_modi_election_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_mois_modi_election_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_annee_modi_election_changed         (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_Modifier_election_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_precedent2_election_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_nbh_affi_election_changed           (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_nbc_affi_election_changed           (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_jour_affi_election_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_mois_affi_election_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_annee_affi_election_changed         (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_precedent3_election_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_buttonBVAdd_clicked                 (GtkWidget *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *WindowAddPollingOffice;
  GtkWidget *WindowMainPollingOffice;
  WindowMainPollingOffice=lookup_widget(objet_graphique, "WindowMainPollingOffice");
  gtk_widget_hide (WindowMainPollingOffice);

  WindowAddPollingOffice=create_WindowAddPollingOffice ();
  gtk_widget_show (WindowAddPollingOffice);
}


void
on_buttonBVMod_clicked                 (GtkWidget *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *WindowModifyPollingOffice;
  GtkWidget *WindowMainPollingOffice;
  WindowMainPollingOffice=lookup_widget(objet_graphique, "WindowMainPollingOffice");
  gtk_widget_hide (WindowMainPollingOffice);

  WindowModifyPollingOffice=create_WindowModifyPollingOffice ();
  gtk_widget_show (WindowModifyPollingOffice);
}


void
on_buttonBVSupp_clicked                (GtkWidget *objet_graphique,
                                        gpointer         user_data)
{

}

void
on_button48_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button49_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button50_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button51_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

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


