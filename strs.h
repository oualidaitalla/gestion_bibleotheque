#define MAX 100
//////////////////////////
typedef struct {
    char nom[MAX];
    char prenom[MAX];
    char nationalite[MAX];
}Auteur;
//////////////////////////
typedef struct{
    Auteur Auteur;
    char titre[MAX];
    long int ISBN;
    int Edition;
    int Date_pub;
}InfoLivre;
//////////////////////////
typedef struct Livres{
    InfoLivre *Livre;
    struct Livres *suivant;
}Livres;
//////////////////////////
typedef struct {
    int jour ;
    char moix[MAX];
    int annee;
}Date;
typedef struct emprunt_Livre{
    Livres L;
    Date emprunter;
    Date retourner;
    struct emprunt_Livre *suivant;
 }emprunt_Livre;

