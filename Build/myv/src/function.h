#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

//Importation des librairies
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>
#include "interface.h"
#include "support.h"


/////////////////////////////////////////////////////////////

/*Entities*/

//////////////////////////////////////////////////////////////


//LISTE ELECTORAL

typedef struct{
	int day;//numero du jour
	int month;//numero du mois
	int year;//numero de l'année
}Date_;

typedef struct {
	int hour;// heure
	int min;// minutes
	int sec;// secondes
}Time;

typedef struct{
	Date_ date;//date 
	Time time;//temps
}DateTime;


typedef struct {
	int id_list;// identifiant de la liste electoral
	char name_list[50];// Nom de la liste
	int orientation;// Orientation de la tete de liste
	int head_list;// identifiant de la tete de liste
	int members[9];// les membres de la liste ,on utilise leurs identifiants
	int nb_members;// nombres de membres
	char affiche[100];// nom du fichier poster
	DateTime created_at;// date de creation
	int is_valid;// si la liste est valide
	int nb_vote; // le nombre de vote de la liste
	int id_election; // l'identifiant de l'election associé
}ElectoralList;

//Structure representant
typedef struct{
	_Bool id_list;//active la recherche par identifiant
	_Bool name_list;//active la recherche par nom
	_Bool orientation;//active la recherhche par orientation
	_Bool head_list;// activer la recherche par identifiant de tete de liste
}Criteria;
 
typedef struct{
	char id_list[50];// identifiant de la liste electoral
	char name_list[50];// Nom de la liste
	int orientation;// Orientation de la tete de liste
	char head_list[50];// identifiant de la tete de liste 
	int max_result;// max de recherche
	Criteria criteria;
}ListConfigSearch;



// Utilisateur


typedef struct
{
int jj,mm,aa;
}Date;

typedef struct
{
char nom[20];
char prenom[20];
int cin;
int id;
char sexe[10];
char nationalite[25];
char adresse[30];
char role[30];
int vote;
int mot_de_passe;
Date date_de_naissance;
}Utilisateur;



//Election

typedef struct 
{
Date dateElect;
int id;
int nbh;
int nbc;
char muni[20];
}Election;

//Bureau de Vote

typedef struct
{
    int  idBV;
    int capacite_e;
    int capacite_o;
    char salle [9];
    char adresse[10];
    int idABV;
}bureau_vote;

typedef struct
{
int idBV;
int id;
}linker;

//Observateurs

//Reclamation

///////////////////////////////////////////////////////////////////////////

/*Signatures des fonctions*/

///////////////////////////////////////////////////////////////////////////

//Liste Electoral


_Bool CreateElectoralList(ElectoralList L);
_Bool ModifyElectoralList(ElectoralList l);
_Bool DeleteElectoralList(int id_list);
_Bool RangeListElectoral(ElectoralList lists[],int *n);
_Bool findWinner(int Winner[],int *k,ElectoralList lists[],int nbHabitant,int numCandidat);
int ReturnNbConseiller(int nbHabitants);
_Bool stringIsIn(char ch1[],char ch2[]);
int ReturnNbListInFile();
_Bool ReturnAllList(ElectoralList lists[],int *n);
_Bool catchElectListFromListId(int listId,ElectoralList *l);
_Bool isInList(int id_member , int id_list);
_Bool UpdateVoteOnListElectoral();
_Bool catchElectListFromUserId(int UserId,ElectoralList *l);
_Bool searchListsFromIdList(int listId, ElectoralList lists[],int *n);
_Bool searchListsFromIdHeadOfList(int headId, ElectoralList lists[],int *n);
_Bool searchListsFromOrientation(int Orientation, ElectoralList lists[],int *n);
_Bool inTableList(ElectoralList el,ElectoralList l[],int n);
void concatTableList(ElectoralList l1[],int *n1,ElectoralList l2[],int n2);
void delInTableList(ElectoralList l[],int *n,int i);
_Bool RangeListElectoral(ElectoralList lists[],int *n);
_Bool findWinner(int Winner[],int *k,ElectoralList lists[],int nbHabitant,int numCandidat);
_Bool multiCriteriaSearch(ListConfigSearch config,ElectoralList l[],int *n);
_Bool stringIsNum(char str[]);
_Bool CheckEntryShowList(char entry[]);
_Bool CheckEntrySearchList(char entry[]);
_Bool CheckEntryListName(char entry[]);
_Bool CheckEntryPoster(char entry[]);
_Bool CheckEntryAddMember(char entry[]);
_Bool CheckEntryDeleteMember(char entry[]);
_Bool CheckEntryId(char entry[]);
//Utilistateur

int nbobserver();
void taux( float *tn, float *te);
int AjouterUser(Utilisateur U);
int modifierUser(int id,Utilisateur u);
int supprimerUser(int id);
Utilisateur chercherUser(int id);
void chercherpar(char * filename,char ch[]);


//Election



//Bureau de Vote


int ajouterBV( bureau_vote b );
int modifierBV(  int, bureau_vote b  );
int supprimerBV( int );
void afficherBV(bureau_vote b);
bureau_vote  chercherBV( int);
int affecterBV(int idE, int idB);

void nbr_elec_bv(int *s);
float TPE();


//Observateurs

//Reclamation

/*fonction interfacage*/


//Electoral List


void alert(char* msg);
void initWindowListMain(Utilisateur user,Election election,GtkWidget* window);
void showUserInList(GtkWidget *liste, Utilisateur users[],int n);
void showLists(GtkWidget *liste, ElectoralList lists[],int n);
void PreviewList(GtkWidget *object , ElectoralList l);
void initWindowManageList(GtkWidget *window ,Utilisateur user,ElectoralList l);
void initWindowShowList(GtkWidget *window,ElectoralList l);

//Utilisateur

void afficher_User(GtkWidget *liste);
void afficherNom_User(GtkWidget *liste);


/*Variables Programme */

//Electoral List
ElectoralList CurrentList;
ListConfigSearch listConfigSearch;
Utilisateur CurrentUser;
Election CurrentElection;
enum{
NAME_USER,
SURNAME_USER,
CIN_USER,
ID_USER,
SEX_USER,
NATIONALITIE_USER,
COLUMNS_USER
};

enum{
ID_LIST,
NAME_LIST,
ORIENTATION_LIST,
HEAD_LIST,
CREATED_AT,
NB_VOTE,
IS_VALID,
COLUMNS_LIST
};

//Utilisateur 

enum
{
	ENOM,
	EPRENOM,	
	ECIN,
	EID,
	ESEXE,
	ENATIONALITE,
	EDATE,
	EADRESSE,
	EROLE,
	EVOTE,
	EPASSE,
	COLUMNS
};


//

#endif // FUNCTION_H_INCLUDED
