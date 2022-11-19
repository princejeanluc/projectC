/*Fichier contenant toutes les structures necessaires au bon fonctionnement du logiciel*/

#include <bool.h>


//////////////////////////////////////////////////////////////

		LISTE ELECTORAL

//////////////////////////////////////////////////////////////
typedef struct{
	int day;//numero du jour 
	int month;//numero du mois 
	int year;//numero de l'année 
}Date;

typedef struct{
	bool left;// pour la gauche 
	bool center;// pour le centre
	bool right;// pour la droite 
}Orientation;

typedef struct{
	char file_name;// nom du fichier
	char path[2000];// chemin relatif du fichier
}Image;


typedef struct {
	char id[10];// identifiant de la liste electoral
	char name[50];// Nom de la liste
	Orientation orientation;// Orientation de la liste 
	char head_list[10];// identifiant de la tete de liste
	Elector members[9];// les membres de la liste 
	int nb_members;// nombres de membres
	Image affiche;
	Date created_at;
	char commentary[2000];// Ici la tete de liste pourra inserer des commentaires pour presenter ses objectifs de campagne

}ElectoralList;

typedef struct{
	char id_sender[10];// id de la personne qui invite
	char id_receiver[10];// id de la personne invité
	char id_list[10];//id de la liste proposé
	bool accepted ; // proposition accepté ou pas 
	Date acceptedAt;// date de la derniere acceptation
}Proposition;











