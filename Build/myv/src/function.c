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
	ElectoralList lists[200];
	int n=0,i;
	_Bool find = false;
	if(!ReturnAllList(lists,&n)){return find;}
	for(i=0;i<n;i++){
		if(lists[i].id_list == listId){*l = lists[i];find = true; return find; }	
	}
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
			list[i].nb_vote = 0;
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
	//Retourne un tableau de liste contenant pour nom la chaine de caractere de caractère "nameList"
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



_Bool searchListsFromOrientation(int orientation, ElectoralList lists[],int *n){
	//Retourne Un tableau de liste possédant la meme orientation
	int i,j;
	(*n) = 0;
	if(!ReturnAllList(lists,n)){return false;};
	for(i=0;i< *n;i++){
		if(lists[i].orientation != orientation){
			for(j=i;j< (*n)-1;i++){lists[j]=lists[j+1];}
			(*n)--;		
		}
	}
	return true;
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
	if(i< *n){
		for(j=i;j< (*n)-1;j++){l[j]=l[j+1];}
		(*n)--;
	}
	
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

void chercherpar(char * filename,char ch[])
{
    Utilisateur U ;

    FILE * f=fopen(filename, "r");
    FILE * f1=fopen("nouv1.txt", "w");
    if(f!=NULL)
    {
while(fscanf(f,"%s %s %d %d %s %s %s %s %d %d %d %d %d\n",U.nom,U.prenom,&U.cin,&U.id,U.sexe,U.nationalite,U.adresse,U.role,&U.vote,&U.mot_de_passe,&U.date_de_naissance.jj,&U.date_de_naissance.mm,&U.date_de_naissance.aa)!=EOF)
        {
		if(strcmp(U.role,ch)==0){fprintf(f1,"%s %s %d %d %s %s %s %s %d %d %d %d %d\n",U.nom,U.prenom,U.cin,U.id,U.sexe,U.nationalite,U.adresse,U.role,U.vote,U.mot_de_passe,U.date_de_naissance.jj,U.date_de_naissance.mm,U.date_de_naissance.aa);}
	}
			
    }
    fclose(f);
    fclose(f1);

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
	} fclose(f);
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
	_Bool error=true,in_all;
	int id ,head_id,orientation,j,i;
	char name[50],p[20];
	*n = 0;
	id = atoi(config.id_list);
	head_id = atoi(config.head_list);
	strcpy(name,config.name_list);
	orientation = config.orientation;
	ReturnAllList(l,n);
	in_all = true;
	for(i=0;i< (*n);i++){//on verifie si l'élement vérifie tout les criteres activées
		if(config.criteria.id_list){if(l[i].id_list != id){in_all = false;}else{in_all = true;}}
		if(config.criteria.head_list){if(l[i].head_list != head_id){in_all = false;}else{in_all = true;}}
		if(config.criteria.name_list){if(!stringIsIn(l[i].name_list,name)){in_all = false;}else{in_all = true;}}
		if(config.criteria.orientation){if(l[i].orientation !=orientation){in_all = false;}else{in_all = true;}}
		//On supprime si l'element ne verifie  pas tout les critères activée
		if(!in_all){
			for(j=i;j<(*n)-1;j++){l[j]=l[j+1];}
			(*n)--;
		}
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
	if (strlen(entry)<=50 && strlen(entry)!=0 && stringIsNum(entry)){return true;}
	return false;
}

_Bool CheckEntryListName(char* entry){
	if (strcmp(entry,"")!=0 && strlen(entry)<=50){return true;}
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
	if(strlen(entry)<=10 && strlen(entry)!=0 && stringIsNum(entry)) return true;// si la chaine est numeric et non vide
	return false;
}


/*Fonction supplementaire d'interfacage*/



//----- Electoral List -----


void alert(char* msg){
	GtkWidget* WindowAlertList;
	GtkWidget* LabelMessageWindowAlert;
	WindowAlertList = create_WindowAlertList();
	LabelMessageWindowAlert = lookup_widget(WindowAlertList,"LabelMessageWindowAlert");
	gtk_label_set_text(GTK_LABEL(LabelMessageWindowAlert),msg);
	gtk_widget_show(WindowAlertList);
}





void showUserInList(GtkWidget *liste, Utilisateur users[],int n){
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store ;
	int i;
	char cin[10] ;char id[10];
	
	store = gtk_tree_view_get_model(liste);
	if(store == NULL){
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("  nom  ",renderer,"text",NAME_USER,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes(" prenom ",renderer,"text",SURNAME_USER,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("  cin  ",renderer,"text",CIN_USER,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("  id  ",renderer,"text",ID_USER,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("  sex  ",renderer,"text",SEX_USER,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("nationalité",renderer,"text",NATIONALITIE_USER,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	}
	store = gtk_list_store_new(COLUMNS_USER,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	for(i=0;i<n;i++){
		gtk_list_store_append(store,&iter);
		sprintf(cin,"%d",users[i].cin);
		sprintf(id,"%d",users[i].id);	gtk_list_store_set(store,&iter,NAME_USER,users[i].nom,SURNAME_USER,users[i].prenom,CIN_USER,cin,ID_USER,id,SEX_USER,users[i].sexe,NATIONALITIE_USER,users[i].nationalite,-1);
	}
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste),store);
	g_object_unref(store);
}





void showLists(GtkWidget *liste, ElectoralList lists[],int n){
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store ;
	int i;
	Utilisateur user;
	char id_list[10],orientation[10],head[21],created_at[35],nb_vote[10],is_valid[10];
	
	store = gtk_tree_view_get_model(liste);
	if(store == NULL){
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("  id  ",renderer,"text",ID_LIST,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("  nom  ",renderer,"text",NAME_LIST,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Orientation",renderer,"text",ORIENTATION_LIST,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Tete de liste",renderer,"text",HEAD_LIST,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Dernière modification",renderer,"text",CREATED_AT,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Vote",renderer,"text",NB_VOTE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Valide",renderer,"text",IS_VALID,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	}
	store = gtk_list_store_new(COLUMNS_LIST,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	for(i=0;i<n;i++){
		gtk_list_store_append(store,&iter);
		sprintf(id_list,"%d",lists[i].id_list);
		switch(lists[i].orientation){
			case 1:
				strcpy(orientation,"Droite");
			break;
			case 0:
				strcpy(orientation,"Centre");
			break;
			case -1:
				strcpy(orientation,"Gauche"); 
			break;
		}
		user = chercherUser(lists[i].head_list);
		strcpy(head,user.id != -1 ? user.nom:"xxxxx");
		sprintf(created_at,"\[ %d : %d : %d \] %d/ %d/ %d  ",lists[i].created_at.time.hour,lists[i].created_at.time.min,lists[i].created_at.time.sec,lists[i].created_at.date.day,lists[i].created_at.date.month,lists[i].created_at.date.year);
		sprintf(nb_vote,"%d",lists[i].nb_vote);
		strcpy(is_valid,lists[i].is_valid ? " Oui ":" Non ");	gtk_list_store_set(store,&iter,ID_LIST,id_list,NAME_LIST,lists[i].name_list,ORIENTATION_LIST,orientation,HEAD_LIST,head,CREATED_AT,created_at,NB_VOTE,nb_vote,IS_VALID,is_valid,-1);
	}
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste),store);
	g_object_unref(store);
}



void PreviewList(GtkWidget *object , ElectoralList l){
	//Warning !!! before use this function make shure that create_WindowManageList() has been called before
	char id[10];
	char orientation[10];
	char head[10];
	char nbVote[10];
	char isValid[5];
	char temp[10];
	Utilisateur users[10];
	Utilisateur buffer;
	int i,j=0;
	strcpy(id,"#");
	sprintf(temp,"%d",l.id_list);
	strcat(id,temp);
	switch(l.orientation){
		case -1:
			strcpy(orientation,"Gauche");
		break;
		case 0:
			strcpy(orientation,"Centre");
		break;
		case 1:
			strcpy(orientation,"Droite");
		break;
	}
	strcpy(head,"#");
	sprintf(temp,"%d",l.head_list);
	strcat(head,temp);
	sprintf(nbVote,"%d",l.nb_vote);
	strcpy(isValid,l.is_valid?"Oui":"Non");
	GtkWidget* LabelIdListPreviewWindowManageList = lookup_widget(object,"LabelIdListPreviewIdManageList");//xxx 
	GtkWidget* LabelNameListPreviewWindowManageList = lookup_widget(object,"LabelNameListPreviewWindowManageLIst");
	GtkWidget* LabelOrientationListPreviewWindowManageList = lookup_widget(object,"LabelOrientationListPreviewWindowManageList"); 
	GtkWidget* LabelHeadListPreviewWindowManageList = lookup_widget(object,"LabelHeadListPreviewWindowManageList"); 
	GtkWidget* LabelNbVoteListPreviewWindowManageList = lookup_widget(object,"LabelNbVoteListPreviewWIndowManageList");//xxx 
	GtkWidget* LabelIsValidListPreviewWindowManageList = lookup_widget(object,"LabelIsValidListPreviewWIndowManageList");//xxx 
	GtkWidget* TreeViewListMemberPreviewWindowManageList = lookup_widget(object,"TreeViewListMemberPreviewWindowManageList");
	//affichage labels
	gtk_label_set_text(GTK_LABEL(LabelIdListPreviewWindowManageList),id);
	gtk_label_set_text(GTK_LABEL(LabelNameListPreviewWindowManageList),l.name_list);
	gtk_label_set_text(GTK_LABEL(LabelOrientationListPreviewWindowManageList),orientation);
	gtk_label_set_text(GTK_LABEL(LabelHeadListPreviewWindowManageList),head);
	gtk_label_set_text(GTK_LABEL(LabelNbVoteListPreviewWindowManageList),nbVote);
	gtk_label_set_text(GTK_LABEL(LabelIsValidListPreviewWindowManageList),isValid);	
	//affichage TreeView
	for(i =0;i<l.nb_members;i++){
		buffer=chercherUser(l.members[i]);//si l'identifiant n'existe pas on n'affiche pas l'utilisateur
		if(buffer.id != -1){users[j]=buffer;j++;}//on utilise une 2eme variable d'incrementation pour eviter d'acceder a une memoire non alloué
	}
	showUserInList(TreeViewListMemberPreviewWindowManageList,users,j);
}



void initWindowListMain(Utilisateur user,Election election,GtkWidget* window){
	//Initialise les elements afficher dans la fenetre WindowListMain
	char id_election[50];
	char name_surname[100];
	char id_user[10];
	char tmp[5];
	ElectoralList l[200] ;
	int n;
	GtkWidget* LabelIdElectionWindowListMain;
	GtkWidget* LabelIdUserWindowListMain;
	GtkWidget* LabelNameUserWindowListMain;
	GtkWidget* RadioButtonCenterOrientationSearchWindowListMain;
	GtkWidget* CheckButtonIdListCriteriaWindowListMain;
	GtkWidget * TreeViewSearchListWindowListMain = lookup_widget(window,"TreeViewSearchListWindowListMain");

	LabelIdElectionWindowListMain = lookup_widget(window,"LabelIdElectionWindowListMain");
	LabelIdUserWindowListMain = lookup_widget(window,"LabelIdElectionWindowListMain");// remplacer label57 par LabelIdElectionWindowListMain !!!
	LabelNameUserWindowListMain = lookup_widget(window,"LabelNameUserWindowListMain");//remplacer LabelUserMain par LabelNameUserWindowListMain !!!
	RadioButtonCenterOrientationSearchWindowListMain = lookup_widget(window,"RadioButtonCenterOrientationSearchWindowListMain");
	CheckButtonIdListCriteriaWindowListMain = lookup_widget(window,"CheckButtonIdListCriteriaWindowListMain");
	strcpy(id_election,"Election :");
	sprintf(tmp,"%d",election.id);
	strcat(id_election,tmp);
	strcpy(name_surname,user.nom);
	strcat(name_surname," ");
	strcat(name_surname,user.prenom);
	strcpy(id_user,"#");
	sprintf(tmp,"%d",user.id);
	strcat(id_user,tmp);
	gtk_label_set_text(GTK_LABEL(LabelIdElectionWindowListMain),id_election);
	gtk_label_set_text(GTK_LABEL(LabelIdUserWindowListMain),id_user);
	gtk_label_set_text(GTK_LABEL(LabelNameUserWindowListMain),name_surname);
	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(RadioButtonCenterOrientationSearchWindowListMain),TRUE);
	gtk_toggle_button_set_active(GTK_CHECK_BUTTON(CheckButtonIdListCriteriaWindowListMain),TRUE);
	ReturnAllList(l,&n);
	showLists(TreeViewSearchListWindowListMain,l,n);
}




void initWindowManageList(GtkWidget *window ,Utilisateur user,ElectoralList l){
	//Warning !!! before use this function make shure that create_WindowManageList() has been called before
	char idUser[10];
	sprintf(idUser,"%d",user.id);
	GtkWidget * LabelIdUserWindowManageList = lookup_widget(window,"LabelIdUserWindowManageList");
	GtkWidget * LabelNameUserWindowManageList= lookup_widget(window,"LabelNameUserWindowManageList");
	GtkWidget * RadioButtonLeftOrientationWindowManageList= lookup_widget(window,"RadioButtonLeftOrientationWindowManageList");
	GtkWidget * RadioButtonCenterOrientationWindowManageList= lookup_widget(window,"RadioButtonCenterOrientationWindowManageList");
	GtkWidget * RadioButtonRightOrientationWindowManageList= lookup_widget(window,"RadioButtonRightOrientationWindowManageList");
	GtkWidget * EntryNameListWindowManageList= lookup_widget(window,"EntryNameListWindowManageList");
	GtkWidget * EntryPosterListWindowManageList= lookup_widget(window,"EntryPosterListWindowManageList");
	gtk_label_set_text(GTK_LABEL(LabelIdUserWindowManageList),idUser);
	gtk_label_set_text(GTK_LABEL(LabelNameUserWindowManageList),user.nom);
	switch(l.orientation){
		case -1:
			gtk_toggle_button_set_active(GTK_RADIO_BUTTON(RadioButtonLeftOrientationWindowManageList),TRUE);
			break;
		case 0:
			gtk_toggle_button_set_active(GTK_RADIO_BUTTON(RadioButtonCenterOrientationWindowManageList),TRUE);
			break;
		case 1:
			gtk_toggle_button_set_active(GTK_RADIO_BUTTON(RadioButtonRightOrientationWindowManageList),TRUE);
			break;
	}
	gtk_entry_set_text(GTK_ENTRY(EntryNameListWindowManageList),l.name_list);
	gtk_entry_set_text(GTK_ENTRY(EntryPosterListWindowManageList),l.affiche);
	l.members[0] = user.id;
	PreviewList(window,l);
}


void initWindowShowList(GtkWidget *window,ElectoralList l){
	//Warning !!! before use this function make shure that create_WindowShowList() has been called before
	char id[10];
	char orientation[10];
	char head[10];
	char nbVote[10];
	char isValid[5];
	char temp[10];
	Utilisateur users[10];
	Utilisateur buffer;
	int i,j=0;
	strcpy(id,"#");
	sprintf(temp,"%d",l.id_list);
	strcat(id,temp);
	switch(l.orientation){
		case -1:
			strcpy(orientation,"Gauche");
		break;
		case 0:
			strcpy(orientation,"Centre");
		break;
		case 1:
			strcpy(orientation,"Droite");
		break;
	}
	strcpy(head,"#");
	sprintf(temp,"%d",l.head_list);
	strcat(head,temp);
	sprintf(nbVote,"%d",l.nb_vote);
	strcpy(isValid,l.is_valid?"Oui":"Non");
	GtkWidget* LabelListIdWindowShowList = lookup_widget(window,"LabelListIdWindowShowList");
	GtkWidget* LabelListNameWindowShowList = lookup_widget(window,"LabelListNameWindowShowList");
	GtkWidget* LabelOrientationWindowShowList = lookup_widget(window,"LabelOrientationWindowShowList"); 
	GtkWidget* LabelHeadListWindowShowList = lookup_widget(window,"LabelHeadListWindowShowList"); 
	GtkWidget* LabelNbVoteWindowShowList = lookup_widget(window,"LabelNbVoteWindowShowList");//xxx 
	GtkWidget* LabelIsValidWindowShowList = lookup_widget(window,"LabelIsValidWindowShowList");//xxx 
	GtkWidget* TreeViewListMemberWindowShowList = lookup_widget(window,"TreeViewListMemberWindowShowList");
	//affichage labels
	gtk_label_set_text(GTK_LABEL(LabelListIdWindowShowList),id);
	gtk_label_set_text(GTK_LABEL(LabelListNameWindowShowList),l.name_list);
	gtk_label_set_text(GTK_LABEL(LabelOrientationWindowShowList),orientation);
	gtk_label_set_text(GTK_LABEL(LabelHeadListWindowShowList ),head);
	gtk_label_set_text(GTK_LABEL(LabelNbVoteWindowShowList),nbVote);
	gtk_label_set_text(GTK_LABEL(LabelIsValidWindowShowList),isValid);	
	//affichage TreeView
	for(i =0;i<l.nb_members;i++){
		buffer=chercherUser(l.members[i]);//si l'identifiant n'existe pas on n'affiche pas l'utilisateur
		if(buffer.id != -1){users[j]=buffer;j++;}//on utilise une 2eme variable d'incrementation pour eviter d'acceder a une memoire non alloué
	}
	showUserInList(TreeViewListMemberWindowShowList,users,j);
}


//Utilisateur

void afficher_User(GtkWidget *liste)
{
Utilisateur u,U;

char DATE[30];
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
store = NULL;
FILE *fp;


store = gtk_tree_view_get_model(liste);
if (store == NULL)
{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Id",renderer,"text",EID,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Nom",renderer,"text",ENOM,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Prenom",renderer,"text",EPRENOM,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" C.I.N ",renderer,"text",ECIN,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Sexe",renderer,"text",ESEXE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Nationalite",renderer,"text",ENATIONALITE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date",renderer,"text",EDATE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Adresse ",renderer,"text",EADRESSE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();

	column = gtk_tree_view_column_new_with_attributes("Role",renderer,"text",EROLE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Vote ",renderer,"text",EVOTE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Mot de passe ",renderer,"text",EPASSE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

}
	store = gtk_list_store_new(COLUMNS, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	fp = fopen("Utilisateur.txt", "r");

	if(fp==NULL)
	{
	return;
	}

	else
	{
	fp = fopen("Utilisateur.txt", "a");
	while(fscanf(fp,"%s %s %d %d %s %s %s %s %d %d %d %d %d\n",U.nom,U.prenom,&U.cin,&U.id,U.sexe,U.nationalite,U.adresse,U.role,&U.vote,&U.mot_de_passe,&U.date_de_naissance.jj,&U.date_de_naissance.mm,&U.date_de_naissance.aa)!=EOF)
		{
		sprintf(DATE, "%d/%d/%d", U.date_de_naissance.jj,U.date_de_naissance.mm,U.date_de_naissance.aa);

		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter, EID, U.id, ENOM, U.nom,EPRENOM, U.prenom,EDATE,DATE , ECIN,u.cin,ESEXE, U.sexe,  ENATIONALITE, U.nationalite,  EADRESSE, U.adresse,  EROLE, U.role,  EVOTE, U.vote,  EPASSE, U.mot_de_passe,-1);
		}
	fclose(fp);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
	g_object_unref(store);
	}

}

void afficherNom_User(GtkWidget *liste)
{
	Utilisateur u,U;


	char DATE[30];
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	store = NULL;
	FILE *fp;


	store = gtk_tree_view_get_model(liste);
	if (store == NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Id",renderer,"text",EID,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes(" Nom",renderer,"text",ENOM,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes(" Prenom",renderer,"text",EPRENOM,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes(" C.I.N ",renderer,"text",ECIN,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Sexe",renderer,"text",ESEXE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes(" Nationalite",renderer,"text",ENATIONALITE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Date",renderer,"text",EDATE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Adresse ",renderer,"text",EADRESSE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();

		column = gtk_tree_view_column_new_with_attributes("Role",renderer,"text",EROLE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Vote ",renderer,"text",EVOTE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Mot de passe ",renderer,"text",EPASSE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	}

	store = gtk_list_store_new(COLUMNS, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	fp = fopen("Utilisateur.txt", "r");

		if(fp==NULL)
		{
			return;
		}

		else
		{
			fp = fopen("nouv1.txt", "a");
			while(fscanf(fp,"%s %s %d %d %s %s %s %s %d %d %d %d %d\n",U.nom,U.prenom,&U.cin,&U.id,U.sexe,U.nationalite,U.adresse,U.role,&U.vote,&U.mot_de_passe,&U.date_de_naissance.jj,&U.date_de_naissance.mm,&U.date_de_naissance.aa)!=EOF)
			{
			sprintf(DATE, "%d/%d/%d", U.date_de_naissance.jj,U.date_de_naissance.mm,U.date_de_naissance.aa);

			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store, &iter, EID, U.id, ENOM, U.nom,EPRENOM, U.prenom,EDATE,DATE , ECIN,u.cin,ESEXE, U.sexe,  ENATIONALITE, U.nationalite,  EADRESSE, U.adresse,  EROLE, U.role,  EVOTE, U.vote,  EPASSE, U.mot_de_passe,-1);
			}
			fclose(fp);
			gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
			g_object_unref(store);
		}

}




//------- 

