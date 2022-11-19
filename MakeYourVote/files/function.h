#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_ID 10


//////////////////////////////////////////////////////////////

		/*LISTE ELECTORAL*/

//////////////////////////////////////////////////////////////


//Entities

typedef struct{
	int day;//numero du jour
	int month;//numero du mois
	int year;//numero de l'année
}Date;

typedef struct {
	int hour;// heure
	int min;// minutes
	int sec;// secondes
}Time;

typedef struct{
	Date date;
	Time time;

}DateTime;




typedef struct{
	char file_name[100] ;// nom du fichier
}Poster;


typedef struct {
	int id_list;// identifiant de la liste electoral
	char name_list[50];// Nom de la liste
	int orientation;// Orientation de la tete de liste
	int head_list;// identifiant de la tete de liste
	int members[9];// les membres de la liste ,on utilise leurs identifiants
	int nb_members;// nombres de membres
	Poster affiche;// affiche de la liste
	DateTime created_at;// date de creation
	int is_valid;
	int nb_vote;
}ElectoralList;




//////////////////////////////////////////////////////////////////////////

		/* User*/

//////////////////////////////////////////////////////////////////////////



typedef struct{
	int id_user;
	char nom_user[21];
	char prenom_user[21];
	int vote;
}User;

FILE* catchListElectoralFile(char* mode);
_Bool catchElectListFromUserId(int UserId,ElectoralList *l);
_Bool catchElectListFromListId(int listId,ElectoralList *l);
_Bool isInList(int id_member , int id_list);
_Bool ReturnAllIdList(int ids_list[],int *n);
_Bool CreateElectoralList(ElectoralList L,User user);
_Bool ModifyElectoralList(ElectoralList l);
_Bool DeleteElectoralList(int id_list);
_Bool RetractFromElectoralList(int id_list, int id_member);
_Bool RangeListElectoral(ElectoralList lists[],int *n);
_Bool findWinner(int Winner[],int *k,ElectoralList lists[],int numWinner)


#endif // FUNCTION_H_INCLUDED
