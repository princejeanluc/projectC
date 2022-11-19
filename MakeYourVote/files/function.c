#include "function.h"
/* Ce fichier contient les fontions nécéssaire à la manipulation des listes elctorales */


/////////////////////////////////////////////////////////////

/*Fonctions CROUD*/

/////////////////////////////////////////////////////////////


FILE* catchListElectoralFile(char* mode){return fopen("listElectoralFile.txt",mode);}



const char* format_list_electoral(){return " %d %s %d %d %d %d %d %d %d %d %d %d %d %d %s %d %d %d %d %d %d %d %d \n";}

_Bool catchElectListFromUserId(int UserId,ElectoralList *l){
	FILE * f; ElectoralList L;
	int i;
	f = catchListElectoralFile("r");
	if (f==NULL){printf("le fichier est indisponible"); return false;}
	while(fscanf(f,format_list_electoral(),&(L.id_list),L.name_list,&(L.orientation),&(L.head_list),&(L.members[0]),&(L.members[1]),&(L.members[2]),&(L.members[3]),&(L.members[4]),&(L.members[5]),&(L.members[6]),&(L.members[7]),&(L.members[8]),&(L.nb_members),L.affiche.file_name,&(L.created_at.date.day),&(L.created_at.date.month),&(L.created_at.date.year),&(L.created_at.time.hour),&(L.created_at.time.min),&(L.created_at.time.sec),&(L.is_valid),&(L.nb_vote))!=EOF){	for(i=0;i<L.nb_members;i++){
		printf("In catchElectListFromUserId");
		for (i =0 ;i<L.nb_members;i++){
            if (UserId == L.members[i]){*l = L;printf("%d",L.members[i]);return true;}
		}
} return false;
}
fclose(f);
return false;
}

_Bool catchElectListFromListId(int listId,ElectoralList *l){
	FILE * f; ElectoralList L;
	f = catchListElectoralFile("r");
	if (f==NULL){printf("le fichier est indisponible"); return false;}
	while(fscanf(f,format_list_electoral(),&(L.id_list),L.name_list,&(L.orientation),&(L.head_list),&(L.members[0]),&(L.members[0]),&(L.members[1]),&(L.members[2]),&(L.members[3]),&(L.members[4]),&(L.members[5]),&(L.members[6]),&(L.members[7]),&(L.members[8]),L.affiche.file_name,&(L.created_at.date.day),&(L.created_at.date.month),&(L.created_at.date.year),&(L.created_at.time.hour),&(L.created_at.time.min),&(L.created_at.time.sec),&(L.is_valid),&(L.nb_vote))!=EOF
){
	printf("In catchEelectListFromListId");
	if (listId == L.id_list ){*l = L;return true;}
}
fclose(f);
return false;
}



_Bool isInList(int id_member , int id_list){
	bool test = false;
	int i ;
	FILE * f; ElectoralList L;
	f = catchListElectoralFile("r");
	if (f==NULL){printf("le fichier est indisponible"); return false;}
	while(fscanf(f,format_list_electoral(),&(L.id_list),L.name_list,&(L.orientation),&(L.head_list),&(L.members[0]),&(L.members[0]),&(L.members[1]),&(L.members[2]),&(L.members[3]),&(L.members[4]),&(L.members[5]),&(L.members[6]),&(L.members[7]),&(L.members[8]),L.affiche.file_name,&(L.created_at.date.day),&(L.created_at.date.month),&(L.created_at.date.year),&(L.created_at.time.hour),&(L.created_at.time.min),&(L.created_at.time.sec),&(L.is_valid),&(L.nb_vote))!=EOF
){
	printf("In isInList");
	if (L.id_list==id_list ){
		for (i = 0;i<L.nb_members;i++){ test = test || (L.members[i]==id_member);}
		return test;}
}
fclose(f);
return false;
}

_Bool ReturnAllIdList(int ids_list[],int *n){
	*n  = 0;
	FILE * f; ElectoralList L;
	f = catchListElectoralFile("r");
	if (f==NULL){printf("le fichier est indisponible"); return false;}
	while(fscanf(f,format_list_electoral(),&(L.id_list),L.name_list,&(L.orientation),&(L.head_list),&(L.members[0]),&(L.members[0]),&(L.members[1]),&(L.members[2]),&(L.members[3]),&(L.members[4]),&(L.members[5]),&(L.members[6]),&(L.members[7]),&(L.members[8]),L.affiche.file_name,&(L.created_at.date.day),&(L.created_at.date.month),&(L.created_at.date.year),&(L.created_at.time.hour),&(L.created_at.time.min),&(L.created_at.time.sec),&(L.is_valid),&(L.nb_vote))!=EOF)
{	printf("%d",*n);
	ids_list[*n] = L.id_list;
	(*n)++;
}
fclose(f);
return true;
}
/////////////////////////////////////////////////////////////

/*Fonctions principales*/

/////////////////////////////////////////////////////////////

//Fonction de creation de liste electoral

_Bool CreateElectoralList(ElectoralList L,User user){
	FILE * f;
	f = catchListElectoralFile("a+");
	fprintf(f,format_list_electoral(),(L.id_list),L.name_list,(L.orientation),L.head_list,L.members[0],L.members[1],L.members[2],L.members[3],L.members[4],L.members[5],L.members[6],L.members[7],L.members[8],(L.nb_members),L.affiche.file_name,(L.created_at.date.day),(L.created_at.date.month),(L.created_at.date.year),(L.created_at.time.hour),(L.created_at.time.min),(L.created_at.time.sec),(L.is_valid),(L.nb_vote));
	fclose(f);return true;
}

//Fonction de modification d'une liste electoral

_Bool ModifyElectoralList(ElectoralList l){
		ElectoralList L;
	FILE *f, *temp;
	f= catchListElectoralFile("r");
	temp = fopen("temp.txt","w");
	if (f==NULL){printf("le fichier est indisponible"); return false;}
	while(fscanf(f,format_list_electoral(),&L.id_list,L.name_list,&L.orientation,&L.head_list,&L.members[0],&L.members[1],&L.members[2],&L.members[3],&L.members[4],&L.members[5],&L.members[6],&L.members[7],&L.members[8],&L.nb_members,L.affiche.file_name,&L.created_at.date.day,&L.created_at.date.month,&L.created_at.date.year,&L.created_at.time.hour,&L.created_at.time.min,&L.created_at.time.sec,&L.is_valid,&L.nb_vote)!= EOF){
	if (L.id_list != l.id_list ){
    fprintf(temp,format_list_electoral(),(L.id_list),L.name_list,(L.orientation),L.head_list,L.members[0],L.members[1],L.members[2],L.members[3],L.members[4],L.members[5],L.members[6],L.members[7],L.members[8],(L.nb_members),L.affiche.file_name,(L.created_at.date.day),(L.created_at.date.month),(L.created_at.date.year),(L.created_at.time.hour),(L.created_at.time.min),(L.created_at.time.sec),(L.is_valid),(L.nb_vote));
    }else{
    fprintf(temp,format_list_electoral(),(l.id_list),l.name_list,(l.orientation),l.head_list,l.members[0],l.members[1],l.members[2],l.members[3],l.members[4],l.members[5],l.members[6],l.members[7],l.members[8],(l.nb_members),l.affiche.file_name,(l.created_at.date.day),(l.created_at.date.month),(l.created_at.date.year),(l.created_at.time.hour),(l.created_at.time.min),(l.created_at.time.sec),(l.is_valid),(l.nb_vote));
    }
}
fclose(f);
fclose(temp);
remove("listElectoralFile.txt");
rename("temp.txt","listElectoralFile.txt");
printf("\nlist modified...");
return true;
}

//Fonction de suppression d'une liste electoral

_Bool DeleteElectoralList(int id_list){
	ElectoralList L;
	FILE *f, *temp;
	f= catchListElectoralFile("r");
	temp = fopen("temp.txt","w");
	if (f==NULL){printf("le fichier est indisponible"); return false;}
	while(fscanf(f,format_list_electoral(),&L.id_list,L.name_list,&L.orientation,&L.head_list,&L.members[0],&L.members[1],&L.members[2],&L.members[3],&L.members[4],&L.members[5],&L.members[6],&L.members[7],&L.members[8],&L.nb_members,L.affiche.file_name,&L.created_at.date.day,&L.created_at.date.month,&L.created_at.date.year,&L.created_at.time.hour,&L.created_at.time.min,&L.created_at.time.sec,&L.is_valid,&L.nb_vote)!= EOF){
	if (L.id_list != id_list ){
    fprintf(temp,format_list_electoral(),(L.id_list),L.name_list,(L.orientation),L.head_list,L.members[0],L.members[1],L.members[2],L.members[3],L.members[4],L.members[5],L.members[6],L.members[7],L.members[8],(L.nb_members),L.affiche.file_name,(L.created_at.date.day),(L.created_at.date.month),(L.created_at.date.year),(L.created_at.time.hour),(L.created_at.time.min),(L.created_at.time.sec),(L.is_valid),(L.nb_vote));
    }
}
fclose(f);
fclose(temp);
remove("listElectoralFile.txt");
rename("temp.txt","listElectoralFile.txt");
printf("\nlist deleted...");
return true;
}

/*Fonction statistiques*/


/*
fonction qui range les listes par ordres de vote

*/

_Bool RangeListElectoral(ElectoralList lists[],int *n){
    *n=0;
    ElectoralList L ,temp ;
    FILE *f=catchListElectoralFile("r");
	if (f==NULL){printf("le fichier est indisponible"); return false;}
	while(fscanf(f,format_list_electoral(),&L.id_list,L.name_list,&L.orientation,&L.head_list,&L.members[0],&L.members[1],&L.members[2],&L.members[3],&L.members[4],&L.members[5],&L.members[6],&L.members[7],&L.members[8],&L.nb_members,L.affiche.file_name,&L.created_at.date.day,&L.created_at.date.month,&L.created_at.date.year,&L.created_at.time.hour,&L.created_at.time.min,&L.created_at.time.sec,&L.is_valid,&L.nb_vote)!= EOF){
	lists[*n] = L;
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
    //  affichage
    for(i= 0;i< (*n);i++){
        printf("\nliste :#%d , votes: %d ",lists[i].id_list,lists[i].nb_vote);
    }
}


_Bool findWinner(int Winner[],int *k,ElectoralList lists[],int numWinner){
    const int numConseiller = 9;//On fonction du nombre de conseillé par liste exigé
    int n , r ,i,j;
    *k = 0;//la taille tu tableau Winner
    n = numWinner / numConseiller;
    r = numWinner%numConseiller;
    for (i=0; i< n ; i++){
        for(j = 0;j< numConseiller;j++){
            Winner[*k] = lists[i].members[j];
            (*k)++;
        }
    }
    for(j = 0;j<r;j++){
        Winner[*k] = lists[i+1].members[j];
        (*k)++;
    }//Bravo au vainqquueeuurr !!!!
    for (j = 0 ;j< (*k);j++){
        printf("\n# %d : Vainqueur",Winner[j]);
    }
}
