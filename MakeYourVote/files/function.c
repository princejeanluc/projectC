#include "function.h"
/* Ce fichier contient les fontions nécéssaire à la manipulation des Crouds et d'autres fonctions intermediaire*/

/*Fonction de capture de fichier */
FILE* catchListElectoralFile(char* mode){return fopen("listElectoralFile.txt",mode);}

FILE* catchUserFile(char* mode){return fopen("UtilisateurFile.txt",mode);}

FILE* catchElectionFile(char* mode){return fopen("ElectionFile.txt",mode);}

FILE* catchPollingStationFile(char* mode){return fopen("BureauDeVoteFile.txt",mode);}

FILE* catchReclamationFile(char* mode){return fopen("ReclamationFile.txt",mode);}

FILE* catchObserverFile(char* mode){return fopen("ObserverFile.txt",mode);}

/*Fonction de formatage*/

const char* format_list_electoral(){return "%d , %s , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %s , %d , %d , %d , %d , %d ,%d , %d , %d , %d \n";}

const char* format_user(){return "%s , %s , %d , %d , %s , %s , %s , %s , %d , %d , %d , %d , %d \n";}

const char* format_election(){return "%d , %d , %d , %d , %d , %d , %s \n";}

const char* format_polling_station(){return "%d , %d , %d , %s , %s , %d \n";}

const char* format_reclamation(){return "%s , %s , %d , %d , %s , %s , %d , %d , %d , %s , %s , %d , %d \n";}//Don't use it ,before modify format !

const char* format_observer(){return "%s , %s , %d , %d , %s , %s , %d , %d , %d , %s , %s , %d , %d \n";}//Don't use it ,before modify format !


/*Fonction intermédiaires*/

// ----- Electoral List -----

int ReturnNbConseiller(int nbHabitants){
	//Fonctions permettant de retourner le nombre de Conseillers a élire en fonction du nombre d'Habitant
	int nbCons = 0;
	switch(nbHabitants){
		case 1 ... 5000:
			nbCons = 10;
			break;
		case 5001 ... 10000:
			nbCons = 12;
			break;
		case 10001 ... 25000:
			nbCons = 16;
			break;
		case 25001 ... 50000:
			nbCons = 22;
			break;
		case 50001 ... 100000:
			nbCons = 30;
			break;
		case 100001 ... 500000:
			nbCons = 40;
			break;
		default:
			nbCons = 60;		
	}
	return nbCons;
}

_Bool stringIsIn(char ch1[],char ch2[]){
	//fonction qui verifie si la chaine ch2 est inclue dans ch1
	int l1,l2,i,j;
	_Bool is_include = false;
	l1=strlen(ch1);
	l2=strlen(ch2);
	if(l2>l1){return false;}
	for(i=0;i<=l1-l2;i++){
		is_include = true;
		for(j=0;j<l2;j++){
			if(ch1[i+j] != ch2[j]){is_include=false;break;}
		}if(is_include){return is_include;}
	}return is_include;
	
}


int ReturnNbListInFile(){
    //Retourne le nombre de liste deja enregistré
    int compt = 0;
    ElectoralList L;
    FILE *f=catchListElectoralFile("r");
    if (f==NULL){printf("le fichier est indisponible"); return compt;}	while(fscanf(f,format_list_electoral(),&L.id_list,L.name_list,&L.orientation,&L.head_list,&L.members[0],&L.members[1],&L.members[2],&L.members[3],&L.members[4],&L.members[5],&L.members[6],&L.members[7],&L.members[8],&L.nb_members,L.affiche,&L.created_at.date.day,&L.created_at.date.month,&L.created_at.date.year,&L.created_at.time.hour,&L.created_at.time.min,&L.created_at.time.sec,&L.is_valid,&L.nb_vote,&(L.id_election))!= EOF){
	compt++;
      }   
    fclose(f);return compt;
}

_Bool ReturnAllList(ElectoralList lists[],int *n){
    //Retourne toutes les listes depuis le fichier
    *n=0;
    ElectoralList L ;
    FILE *f=catchListElectoralFile("r");
    if (f==NULL){printf("le fichier est indisponible"); return false;}	while(fscanf(f,format_list_electoral(),&L.id_list,L.name_list,&L.orientation,&L.head_list,&L.members[0],&L.members[1],&L.members[2],&L.members[3],&L.members[4],&L.members[5],&L.members[6],&L.members[7],&L.members[8],&L.nb_members,L.affiche,&L.created_at.date.day,&L.created_at.date.month,&L.created_at.date.year,&L.created_at.time.hour,&L.created_at.time.min,&L.created_at.time.sec,&L.is_valid,&L.nb_vote,&(L.id_election))!= EOF){
	lists[*n] = L;
	(*n)++;
      }   
    fclose(f);return true;
}

_Bool catchElectListFromListId(int listId,ElectoralList *l){
	//Retourne depuis le fichier la liste a partir de son identifiant
	FILE * f; ElectoralList L;
	f = catchListElectoralFile("r");
	_Bool find=false;
	if (f==NULL){printf("le fichier est indisponible"); return find;}
	while(fscanf(f,format_list_electoral(),&(L.id_list),L.name_list,&(L.orientation),&(L.head_list),&(L.members[0]),&(L.members[1]),&(L.members[2]),&(L.members[3]),&(L.members[4]),&(L.members[5]),&(L.members[6]),&(L.members[7]),&(L.members[8]),L.affiche,&(L.created_at.date.day),&(L.created_at.date.month),&(L.created_at.date.year),&(L.created_at.time.hour),&(L.created_at.time.min),&(L.created_at.time.sec),&(L.is_valid),&(L.nb_vote),&(L.id_election))!=EOF
){
	if (listId == L.id_list ){*l = L;find=true;break;}
}
fclose(f);
return find;
}


_Bool isInList(int id_member , int id_list){
	//Determine si l'identifiant du member est dans la liste
	_Bool isIn = false;
	ElectoralList L;
	int i;
	if(!catchElectListFromListId(id_list,&L)){printf("Cette liste n'existe pas");return isIn;}//[fonction intermédiaire] Retourne la liste depuis l'identifiant de la liste
	for(i = 0;i<L.nb_members;i++){
		isIn = isIn || (id_member == L.members[i]) ;
	}
	return isIn;
	
}



_Bool UpdateVoteOnListElectoral(){
	//Met à jour les votes des listes electorales
	ElectoralList list[2000];
	Utilisateur user;
	int n = 0 ,i;
	FILE* f ;
	if (!ReturnAllList(list,&n)){printf("mise a jour non effectuee\n");return false;}//[fonction intermédiaire] retourne toutes les listes
	else{
		for(i=0;i<n;i++){
			f = catchUserFile("r");
			if (f == NULL){printf("Utilisateur.txt indisponible ...");}
			else{while(fscanf(f,format_user(),(user.nom),(user.prenom),&(user.cin),&(user.id),(user.sexe),(user.nationalite),(user.adresse),(user.role),&(user.vote),&(user.mot_de_passe),&(user.date_de_naissance.jj),&(user.date_de_naissance.mm),&(user.date_de_naissance.aa))!=EOF){
				if(user.vote == list[i].id_list){list[i].nb_vote+=1;}
				if(list[i].nb_members>=9){list[i].is_valid = 1;}else{list[i].is_valid = 0;}
			}
		}
		fclose(f);
		}
		f = catchListElectoralFile("w");
		for(i=0;i<n;i++){ 
			fprintf(f,format_list_electoral(),(list[i].id_list),list[i].name_list,(list[i].orientation),list[i].head_list,list[i].members[0],list[i].members[1],list[i].members[2],list[i].members[3],list[i].members[4],list[i].members[5],list[i].members[6],list[i].members[7],list[i].members[8],(list[i].nb_members),list[i].affiche,(list[i].created_at.date.day),(list[i].created_at.date.month),(list[i].created_at.date.year),(list[i].created_at.time.hour),(list[i].created_at.time.min),(list[i].created_at.time.sec),(list[i].is_valid),(list[i].nb_vote),(list[i].id_election));
		}
		fclose(f);
	} return true;
}


_Bool catchElectListFromUserId(int UserId,ElectoralList *l){
	// Retourne depuis le fichier  la liste  contenant l'id de l'utilisateur
	FILE * f; ElectoralList L;
	int i;
	_Bool find = false;
	f = catchListElectoralFile("r");
	if (f==NULL){printf("le fichier est indisponible"); return find;}
	while(fscanf(f,format_list_electoral(),&(L.id_list),L.name_list,&(L.orientation),&(L.head_list),&(L.members[0]),&(L.members[1]),&(L.members[2]),&(L.members[3]),&(L.members[4]),&(L.members[5]),&(L.members[6]),&(L.members[7]),&(L.members[8]),&(L.nb_members),L.affiche,&(L.created_at.date.day),&(L.created_at.date.month),&(L.created_at.date.year),&(L.created_at.time.hour),&(L.created_at.time.min),&(L.created_at.time.sec),&(L.is_valid),&(L.nb_vote),&(L.id_election))!=EOF){	for(i=0;i<L.nb_members;i++){
		if (UserId == L.members[i]){*l = L;find=true;}
	}
	if(find){break;}
}
fclose(f);
return find;
}

_Bool searchListsFromIdList(int listId, ElectoralList lists[],int *n){
	//Retourne un tableau de liste contenant l'identifiant recherché 
	FILE * f; ElectoralList L;
	(*n) = 0;
	f = catchListElectoralFile("r");
	_Bool find=false;
	if (f==NULL){printf("le fichier est indisponible"); return find;}
	while(fscanf(f,format_list_electoral(),&(L.id_list),L.name_list,&(L.orientation),&(L.head_list),&(L.members[0]),&(L.members[1]),&(L.members[2]),&(L.members[3]),&(L.members[4]),&(L.members[5]),&(L.members[6]),&(L.members[7]),&(L.members[8]),L.affiche,&(L.created_at.date.day),&(L.created_at.date.month),&(L.created_at.date.year),&(L.created_at.time.hour),&(L.created_at.time.min),&(L.created_at.time.sec),&(L.is_valid),&(L.nb_vote),&(L.id_election))!=EOF){
	if (listId == L.id_list ){lists[(*n)] = L;(*n)++;find=true;}
     }
fclose(f);
return find;
}


_Bool searchListsFromIdHeadOfList(int headId, ElectoralList lists[],int *n){
	//Retourne un tableau de liste contenant l'identifiant de la tete de liste recherché
	FILE * f; ElectoralList L;
	(*n) = 0;
	f = catchListElectoralFile("r");
	_Bool find=false;
	if (f==NULL){printf("le fichier est indisponible"); return find;}
	while(fscanf(f,format_list_electoral(),&(L.id_list),L.name_list,&(L.orientation),&(L.head_list),&(L.members[0]),&(L.members[1]),&(L.members[2]),&(L.members[3]),&(L.members[4]),&(L.members[5]),&(L.members[6]),&(L.members[7]),&(L.members[8]),L.affiche,&(L.created_at.date.day),&(L.created_at.date.month),&(L.created_at.date.year),&(L.created_at.time.hour),&(L.created_at.time.min),&(L.created_at.time.sec),&(L.is_valid),&(L.nb_vote),&(L.id_election))!=EOF
){
	if (headId == L.head_list ){lists[(*n)] = L;(*n)++;find=true;}
}
fclose(f);
return find;
}


_Bool searchListsFromNameList(char nameList[], ElectoralList lists[],int *n){
	//Retourne un tableau de liste contenant pour nom la chaine de caracter de caractère "nameList"
	FILE * f; ElectoralList L;
	(*n) = 0;
	f = catchListElectoralFile("r");
	_Bool find=false;
	if (f==NULL){printf("le fichier est indisponible"); return find;}
	while(fscanf(f,format_list_electoral(),&(L.id_list),L.name_list,&(L.orientation),&(L.head_list),&(L.members[0]),&(L.members[1]),&(L.members[2]),&(L.members[3]),&(L.members[4]),&(L.members[5]),&(L.members[6]),&(L.members[7]),&(L.members[8]),L.affiche,&(L.created_at.date.day),&(L.created_at.date.month),&(L.created_at.date.year),&(L.created_at.time.hour),&(L.created_at.time.min),&(L.created_at.time.sec),&(L.is_valid),&(L.nb_vote),&(L.id_election))!=EOF
){
	if (stringIsIn(L.name_list,nameList)){lists[(*n)] = L;(*n)++;find=true;}
}
fclose(f);
return find;
}



_Bool searchListsFromOrientation(int Orientation, ElectoralList lists[],int *n){
	//Retourne Un tableau de liste possédant la meme orientation
	FILE * f; ElectoralList L;
	(*n) = 0;
	f = catchListElectoralFile("r");
	_Bool find=false;
	if (f==NULL){printf("le fichier est indisponible"); return find;}
	while(fscanf(f,format_list_electoral(),&(L.id_list),L.name_list,&(L.orientation),&(L.head_list),&(L.members[0]),&(L.members[1]),&(L.members[2]),&(L.members[3]),&(L.members[4]),&(L.members[5]),&(L.members[6]),&(L.members[7]),&(L.members[8]),L.affiche,&(L.created_at.date.day),&(L.created_at.date.month),&(L.created_at.date.year),&(L.created_at.time.hour),&(L.created_at.time.min),&(L.created_at.time.sec),&(L.is_valid),&(L.nb_vote),&(L.id_election))!=EOF
){
	if (L.orientation == Orientation){lists[(*n)] = L;(*n)++;find=true;}
}
fclose(f);
return find;
}


_Bool inTableList(ElectoralList el,ElectoralList l[],int n){
	//Verifie si une liste est contenue dans une table de liste
	int i;	
	for(i=0;i< n;i++){
		if(el.id_list == l[i].id_list ) return true ;
	}return false;
}

void concatTableList(ElectoralList l1[],int *n1,ElectoralList l2[],int n2){
	//Concatenation de deux table contenant des listes
	int i;
	for(i=0;i<n2;i++){
		l1[(*n1)+i]=l2[i];
		(*n1)++;
	}
	
}

void delInTableList(ElectoralList l[],int *n,int i){
	//Suppression à partir d'un indice une liste de la table
	int j ;
	for(j=i;j< (*n)-1;j++){l[j]=l[j+1];}
	(*n)--;
}


// ----- Utilisateur ------




Utilisateur chercherUser( int id)
{
    Utilisateur U ;
    int tr=0;
    FILE * f=catchUserFile("r");
    if(f!=NULL)
    {
        while(tr==0 && fscanf(f,format_user(),U.nom,U.prenom,&U.cin,&U.id,U.sexe,U.nationalite,U.adresse,U.role,&U.vote,&U.mot_de_passe,&U.date_de_naissance.jj,&U.date_de_naissance.mm,&U.date_de_naissance.aa)!=EOF)
        {
            if(U.id== id)
                tr=1;
        }
    }
    fclose(f);
    if(tr==0)
        U.id=-1;
    return U;

}

// ----- Bureau de vote -----



int affecterBV(int idE, int idB)
{
    int a=0;
    FILE * f=fopen("link.txt", "a");
    if(f!=NULL)
    {
	fprintf(f,"%d , %d \n",idE,idB);
	a=a+1;
    }
    return a;
}


bureau_vote chercherBV( int id)
{
    
   bureau_vote b;
    int tr=0;
    FILE * f=catchPollingStationFile("r");
    if(f!=NULL)
    {
        while(tr==0&& fscanf(f,format_polling_station(),&b.idBV,&b.capacite_e,&b.capacite_o,b.salle,b.adresse,&b.idABV)!=EOF)
        {
            if(b.idBV== id)
                tr=1;
        }
    }
    fclose(f);
    if(tr==0)
        b.idBV=-1;
    return b;
}

/*Fonction de manipulation de CROUD*/

// ----- Electoral List -----

_Bool CreateElectoralList(ElectoralList L){
	//permet d'ajouter une liste electoral
	FILE * f;
	L.nb_vote = 0;//éviter les tentatives de triche
	f = catchListElectoralFile("a+");
	if (f == NULL){printf("fichier indisponible");return false;}
	fprintf(f,format_list_electoral(),(L.id_list),L.name_list,(L.orientation),L.head_list,L.members[0],L.members[1],L.members[2],L.members[3],L.members[4],L.members[5],L.members[6],L.members[7],L.members[8],(L.nb_members),L.affiche,(L.created_at.date.day),(L.created_at.date.month),(L.created_at.date.year),(L.created_at.time.hour),(L.created_at.time.min),(L.created_at.time.sec),(L.is_valid),(L.nb_vote),(L.id_election));
	fclose(f);return true;
} 

_Bool ModifyElectoralList(ElectoralList l){
	//Fonction Permettant de modifier une liste electoral
	ElectoralList L;
	FILE *f, *temp;
	f= catchListElectoralFile("r");
	temp = fopen("temp.txt","w");
	if (f==NULL){printf("le fichier est indisponible"); return false;}
	while(fscanf(f,format_list_electoral(),&(L.id_list),(L.name_list),&(L.orientation),&(L.head_list),&(L.members[0]),&(L.members[1]),&(L.members[2]),&(L.members[3]),&(L.members[4]),&(L.members[5]),&(L.members[6]),&(L.members[7]),&(L.members[8]),&(L.nb_members),(L.affiche),&(L.created_at.date.day),&(L.created_at.date.month),&(L.created_at.date.year),&(L.created_at.time.hour),&(L.created_at.time.min),&(L.created_at.time.sec),&(L.is_valid),&(L.nb_vote),&(L.id_election))!= EOF){
	if (L.id_list != l.id_list ){
    fprintf(temp,format_list_electoral(),(L.id_list),L.name_list,(L.orientation),L.head_list,L.members[0],L.members[1],L.members[2],L.members[3],L.members[4],L.members[5],L.members[6],L.members[7],L.members[8],(L.nb_members),(L.affiche),(L.created_at.date.day),(L.created_at.date.month),(L.created_at.date.year),(L.created_at.time.hour),(L.created_at.time.min),(L.created_at.time.sec),(L.is_valid),(L.nb_vote),(L.id_election));
    }else{
    fprintf(temp,format_list_electoral(),(l.id_list),l.name_list,(l.orientation),l.head_list,l.members[0],l.members[1],l.members[2],l.members[3],l.members[4],l.members[5],l.members[6],l.members[7],l.members[8],(l.nb_members),l.affiche,(l.created_at.date.day),(l.created_at.date.month),(l.created_at.date.year),(l.created_at.time.hour),(l.created_at.time.min),(l.created_at.time.sec),(l.is_valid),(l.nb_vote),(l.id_election));
    }
}
fclose(f);
fclose(temp);
remove("listElectoralFile.txt");
rename("temp.txt","listElectoralFile.txt");
printf("\nlist modified...");
return true;
}


_Bool DeleteElectoralList(int id_list){
	//permet de supprimer une liste electoral 
	ElectoralList L;
	FILE *f, *temp;
	f= catchListElectoralFile("r");
	temp = fopen("temp.txt","w");
	if (f==NULL){printf("le fichier est indisponible"); return false;}
	while(fscanf(f,format_list_electoral(),&(L.id_list),L.name_list,&(L.orientation),&(L.head_list),&(L.members[0]),&(L.members[1]),&(L.members[2]),(&L.members[3]),&(L.members[4]),&(L.members[5]),&(L.members[6]),&(L.members[7]),&(L.members[8]),&(L.nb_members),L.affiche,&(L.created_at.date.day),&(L.created_at.date.month),&(L.created_at.date.year),&(L.created_at.time.hour),&(L.created_at.time.min),&(L.created_at.time.sec),&(L.is_valid),&(L.nb_vote),&(L.id_election))!= EOF){
	if (L.id_list != id_list ){
    fprintf(temp,format_list_electoral(),(L.id_list),L.name_list,(L.orientation),L.head_list,L.members[0],L.members[1],L.members[2],L.members[3],L.members[4],L.members[5],L.members[6],L.members[7],L.members[8],(L.nb_members),L.affiche,(L.created_at.date.day),(L.created_at.date.month),(L.created_at.date.year),(L.created_at.time.hour),(L.created_at.time.min),(L.created_at.time.sec),(L.is_valid),(L.nb_vote),(L.id_election));
    }
}
fclose(f);
fclose(temp);
remove("listElectoralFile.txt");
rename("temp.txt","listElectoralFile.txt");
return true;
}

// ----- Utilisateur -----


int AjouterUser( Utilisateur U )
{
    FILE *f=catchUserFile("a");
    if(f!=NULL)
    {
        fprintf(f,format_user(),U.nom,U.prenom,U.cin,U.id,U.sexe,U.nationalite,U.adresse,U.role,U.vote,U.mot_de_passe,U.date_de_naissance.jj,U.date_de_naissance.mm,U.date_de_naissance.aa);
        fclose(f);
        return 1;
    }
    else return 0;
}



int modifierUser( int id, Utilisateur nouv )
{
    int tr=0;
    Utilisateur U;
    FILE * f=catchUserFile("r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,format_user(),U.nom,U.prenom,&U.cin,&U.id,U.sexe,U.nationalite,U.adresse,U.role,&U.vote,&U.mot_de_passe,&U.date_de_naissance.jj,&U.date_de_naissance.mm,&U.date_de_naissance.aa)!=EOF)
        {
            if(U.id== id)
            {
                fprintf(f2,format_user(),nouv.nom,nouv.prenom,nouv.cin,nouv.id,nouv.sexe,nouv.nationalite,nouv.adresse,nouv.role,nouv.vote,nouv.mot_de_passe,nouv.date_de_naissance.jj,nouv.date_de_naissance.mm,nouv.date_de_naissance.aa);
                tr=1;
            }
            else
                fprintf(f2,format_user(),U.nom,U.prenom,U.cin,U.id,U.sexe,U.nationalite,U.adresse,U.role,U.vote,U.mot_de_passe,U.date_de_naissance.jj,U.date_de_naissance.mm,U.date_de_naissance.aa);

        }
    }
    fclose(f);
    fclose(f2);
    remove("UtilisateurFile.txt");
    rename("nouv.txt", "UtilisateurFile.txt");
    return tr;

}




int supprimerUser(int id)
{
    int tr=0;
    Utilisateur U;
    FILE * f=catchUserFile("r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,format_user(),U.nom,U.prenom,&U.cin,&U.id,U.sexe,U.nationalite,U.adresse,U.role,&U.vote,&U.mot_de_passe,&U.date_de_naissance.jj,&U.date_de_naissance.mm,&U.date_de_naissance.aa)!=EOF)
        {
            if(U.id== id)
                tr=1;
            else
                fprintf(f2,format_user(),U.nom,U.prenom,U.cin,U.id,U.sexe,U.nationalite,U.adresse,U.role,U.vote,U.mot_de_passe,U.date_de_naissance.jj,U.date_de_naissance.mm,U.date_de_naissance.aa);
        }
    }
    fclose(f);
    fclose(f2);
    remove("UtilisateurFile.txt");
    rename("nouv.txt", "UtilisateurFile.txt");
    return tr;
}



// ----- Bureau de vote -----



int ajouterBV(bureau_vote b )
{
    FILE * f=catchPollingStationFile("a");
    if(f!=NULL)
    {
        fprintf(f,format_polling_station(),b.idBV,b.capacite_e,b.capacite_o,b.salle,b.adresse,b.idABV);
        fclose(f);
        return 1;
    }
    else return 0;
}
int modifierBV( int id, bureau_vote nouv )
{
    int tr=0;
    bureau_vote b;
    FILE * f=catchPollingStationFile("r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,format_polling_station(),&b.idBV,&b.capacite_e,&b.capacite_o,b.salle,b.adresse,&b.idABV)!=EOF)
        {
            if(b.idBV== id)
            {
                fprintf(f2,format_polling_station(),nouv.idBV,nouv.capacite_e,nouv.capacite_o,nouv.salle,nouv.adresse,nouv.idABV);
                tr=1;
            }
            else
                fprintf(f2,format_polling_station(),b.idBV,b.capacite_e,b.capacite_o,b.salle,b.adresse,b.idABV);

        }
    }
    fclose(f);
    fclose(f2);
    remove("BureauDeVoteFile.txt");
    rename("nouv.txt", "BureauDeVoteFile.txt");
    return tr;

}
int supprimerBV( int id)
{
    int tr=0;
    bureau_vote b;
    FILE * f=catchPollingStationFile("r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,format_polling_station(),&b.idBV,&b.capacite_e,&b.capacite_o,b.salle,b.adresse,&b.idABV)!=EOF)
        {
            if(b.idBV== id)
                tr=1;
            else
                fprintf(f2,format_polling_station(),b.idBV,b.capacite_e,b.capacite_o,b.salle,b.adresse,b.idABV);
        }
    }
    fclose(f);
    fclose(f2);
    remove("BureauDeVoteFile.txt");
    rename("nouv.txt", "BureauDeVoteFile.txt");
    return tr;
}



/*Fonction de Statistique */

//----- Electoral List -----


_Bool RangeListElectoral(ElectoralList lists[],int *n){
    //Range les listes par ordre decroissant les listes (Critere de tri = nombre de vote)
    *n=0;
    ElectoralList L ,temp ;
    FILE *f=catchListElectoralFile("r");
    UpdateVoteOnListElectoral();//[Fonction intermediaire] mise à jour des listes électorales
	if (f==NULL){printf("le fichier est indisponible"); return false;}
	while(fscanf(f,format_list_electoral(),&(L.id_list),L.name_list,&(L.orientation),&(L.head_list),&(L.members[0]),&(L.members[1]),&(L.members[2]),&(L.members[3]),&(L.members[4]),&(L.members[5]),&(L.members[6]),&(L.members[7]),&(L.members[8]),&(L.nb_members),(L.affiche),&(L.created_at.date.day),&(L.created_at.date.month),&(L.created_at.date.year),&(L.created_at.time.hour),&(L.created_at.time.min),&(L.created_at.time.sec),&(L.is_valid),&(L.nb_vote),&(L.id_election))!= EOF){
	lists[(*n)] = L;
	(*n)++;
}   fclose(f);
    // tri a bulle
    int i ;
    bool hasPermut = true;
    while (hasPermut){
        hasPermut = false;
        for(i=0;i< (*n)-1;i++){
            if (lists[i].nb_vote < lists[i+1].nb_vote){
                temp  = lists[i];
                lists[i] =  lists[i+1];
                lists[i+1] = temp;
                hasPermut = true;
            }
        }
    }
}


_Bool findWinner(int Winner[],int *k,ElectoralList lists[],int nbHabitant,int numCandidat){
    //trouve les gagnants des differentes listes
    int n , r ,i,j,numWinner;
    *k = 0;//la taille tu tableau Winner
    numWinner = ReturnNbConseiller(nbHabitant);//le nombre de conseiller a élire
    n = numWinner / numCandidat;//le nombre de liste totalement gagnante
    r = numWinner%numCandidat;// le nombre de place restante
    for (i=0; i< n ; i++){
        for(j = 0;j< numCandidat;j++){//Les membres des listes totalement gagnantes
            Winner[*k] = lists[i].members[j];
            (*k)++;
        }
    }
    for(j = 0;j<r;j++){//les places restantes sont attribuées a une parti des conseillers de la liste suivante
        Winner[*k] = lists[i].members[j];
        (*k)++;
    }
}


// ----- Utilisateur -----



int nbobserver()
{
    int a=0;
    Utilisateur U;
    FILE * f=catchUserFile("r");
    if(f!=NULL)
    {   while(fscanf(f,format_user(),U.nom,U.prenom,&U.cin,&U.id,U.sexe,U.nationalite,U.adresse,U.role,&U.vote,&U.mot_de_passe,&U.date_de_naissance.jj,&U.date_de_naissance.mm,&U.date_de_naissance.aa)!=EOF)
        {
            if(strcmp(U.role,"Observateur")==0){
a=a+1;}
        }
    }
    fclose(f);
    return a;
}

void taux(float *tn, float *te)
{
    FILE * f=catchUserFile("r");
    int a;
    Utilisateur U;
    a=nbobserver("Utilisateur.txt");
    if(f!=NULL)
    {   *tn=0;
*te=0;
        while(fscanf(f,format_user(),U.nom,U.prenom,&U.cin,&U.id,U.sexe,U.nationalite,U.adresse,U.role,&U.vote,&U.mot_de_passe,&U.date_de_naissance.jj,&U.date_de_naissance.mm,&U.date_de_naissance.aa)!=EOF)
        {
if(strcmp(U.role,"Observateur")==0){
            if ((strcmp(U.nationalite,"Tunisien")==0)||((strcmp(U.nationalite,"Tunisienne")==0))){
(*tn)=(*tn)+1;}
       else{
(*te)=(*te)+1;}
        }
}
    }
    fclose(f);
    (*tn)=(float)((*tn)/a);
    (*te)=(float)((*te)/a);
}



// ----- Bureau de vote -----



float TPE(){
	Utilisateur U;
	int nb=0,a=0;
	float x;
	FILE * f=catchPollingStationFile("r");

	if (f!=NULL)
	{
		while(fscanf(f,format_polling_station(),U.nom,U.prenom,&(U.cin),&(U.id),U.sexe,U.nationalite,U.adresse,U.role,&(U.vote),&(U.mot_de_passe),&(U.date_de_naissance.jj),&(U.date_de_naissance.mm),&(U.date_de_naissance.aa))!=EOF)
		{
			if (strcmp(U.role,"electeur")==0){a++;}
			if ((U.vote==1)||(U.vote==0)){nb++;}
		}x=((float) nb/a)*100;
	}else{x=0;printf("pas assez de memoire ...");}
	fclose(f);
	return x;
}

void nbr_elec_bv(int *s)
{
int bv;
Utilisateur U;
int nb=0;
FILE * f=catchPollingStationFile("r");
if (f!=NULL)
{
while(fscanf(f,format_polling_station(),U.nom,U.prenom,&U.cin,&U.id,U.sexe,U.nationalite,U.adresse,U.role,&U.vote,&U.mot_de_passe,&U.date_de_naissance.jj,&U.date_de_naissance.mm,&U.date_de_naissance.aa)!=EOF)
{
if (strcmp(U.role,"electeur")==0)
nb=nb+1;
}
*s= nb;
}
fclose(f);
}


/* Fonctions de recherche multicritère */

// ----- Electoral List -----

_Bool multiCriteriaSearch(ListConfigSearch config,ElectoralList l[],int *n){
	//Fonction de recherche multicritère 
	_Bool error=false,in_all;
	int id ,head_id,orientation,n1,n2,n3,n4,i;
	char name[50];
	*n = 0;
	ElectoralList l1[2000],l2[2000],l3[2000],l4[2000];
	id = atoi(config.id_list);
	head_id = atoi(config.head_list);
	strcpy(name,config.name_list);
	orientation = config.orientation;

	if(config.criteria.id_list){error = error || searchListsFromIdList(id,l1,&n1);concatTableList(l,n,l1,n1);}
	if(config.criteria.head_list){error = error || searchListsFromIdHeadOfList(head_id,l2,&n2);concatTableList(l,n,l2,n2);}
	if(config.criteria.name_list){error = error || searchListsFromNameList(name,l3,&n3);concatTableList(l,n,l3,n3);}
	if(config.criteria.orientation){error = error || searchListsFromOrientation(orientation,l4,&n4);concatTableList(l,n,l4,n4);}
	
	for(i=0;i< (*n);i++){//on verifie si l'element verifie tout les criteres activées
		in_all = true;
		if(config.criteria.id_list){in_all = in_all && inTableList(l[i],l1,n1);}
		if(config.criteria.head_list){in_all = in_all && inTableList(l[i],l2,n2);}
		if(config.criteria.name_list){in_all = in_all && inTableList(l[i],l3,n3);}
		if(config.criteria.orientation){in_all = in_all && inTableList(l[i],l4,n4);}
		//On supprime si l'element de verifie  pas tout les critères activée
		if(!in_all){delInTableList(l,n,i);}
	}
	return error;
}








/*Fonctiond de Control de Saisie */


// ----- Electoral List ------


_Bool stringIsNum(char str[]){
	//Determine si une chaine de caractère est numérique
	int l = strlen(str);
	int i;
	_Bool check = true;
	for(i=0;i<l;i++){
		if(str[i]<'0' || str[i]>'9'){check=false;return check;}
	}
	return check;
}

_Bool CheckEntryShowList(char entry[]){
	if(stringIsNum(entry) && strlen(entry)!=0) return true;// si la chaine est numeric et non vide
	return false;
}

_Bool CheckEntrySearchList(char entry[]){
	if (strlen(entry)<=50 && strlen(entry)!=0){return true;}
	return false;
}

_Bool CheckEntryListName(char entry[]){
	if (strlen(entry)<=50 && strlen(entry)!=0){return true;}
	return false;
}

_Bool CheckEntryPoster(char entry[]){
	if (strlen(entry)<=50 && strlen(entry)!=0){return true;}
	return false;
}

_Bool CheckEntryAddMember(char entry[]){
	if(stringIsNum(entry) && strlen(entry)!=0) return true;// si la chaine est numeric et non vide
	return false;
}

_Bool CheckEntryDeleteMember(char entry[]){
	if(stringIsNum(entry) && strlen(entry)!=0) return true;// si la chaine est numeric et non vide
	return false;
}

_Bool CheckEntryId(char entry[]){
	if(stringIsNum(entry) && strlen(entry)!=0) return true;// si la chaine est numeric et non vide
	return false;
}


/*Fonction supplementaire d'interfacage*/



//----
