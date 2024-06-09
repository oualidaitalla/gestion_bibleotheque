#include"lbrs.h"
#include"strs.h"

//######################## Les operation effectue par l'admin ##########################################################################################################################################################################################################################################

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
Livres *Ajouter_Livre(Livres *p){     //Enregistrer les information d'un livres sur un fichier
    char chaine[MAX];
    InfoLivre *nouveau=(InfoLivre*)malloc(sizeof(InfoLivre));
    Livres *L=(Livres*)malloc(sizeof(Livres));
    FILE* ouvrir=NULL;
    printf("!!!! Tout donnee de type chaine de caractere ne compte pas tout qui apres un espace (structure donnee)=(structure_donnee)!!!!\n \n"); // le systeme linux ne peut pas executer la fonction gets correctement !!
    ouvrir=fopen("Liste_Livres.txt", "a+");
    if(ouvrir!=NULL){                  // Saisir les information d'un livre
        printf("\t\tSaisir le nom du livre :");
        scanf(" %s", &nouveau->titre);
        printf("\t\tSaisir le nom de l'auteur :");
        scanf(" %s", &nouveau->Auteur.nom);
        printf("\t\tSaisir le prenom de l'auteur :");
        scanf(" %s", &nouveau->Auteur.prenom);
        printf("\t\tSaisir la nationalite de l'auteur :");
        scanf(" %s", &nouveau->Auteur.nationalite);
        printf("\t\tSaisir l'ISBN du livre :");
        scanf("%ld", &nouveau->ISBN);
        printf("\t\tSaisir l'edition du livre :");
        scanf("%d", &nouveau->Edition);
        printf("\t\tSaisir la date de publication :");
        scanf("%d", &nouveau->Date_pub);
        L->Livre=nouveau;
        L->suivant=p;
        // enregistrer les information dans le fichier Liste_livres.txt
        fprintf(ouvrir,"%s|%s %s|%s|%ld|%d|%d \n",nouveau->titre, nouveau->Auteur.nom,nouveau->Auteur.prenom,nouveau->Auteur.nationalite, nouveau->ISBN, nouveau->Edition,nouveau->Date_pub);
    }   fclose(ouvrir);
    return L;
}
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
 
 //
void Afficher_Livre(Livres *);
Livres *ajouter_de_liste();
 //

Livres *supprimer_Livre(Livres *L){
    L=ajouter_de_liste(L);
    int time=0 ,t=0;
    long int ISBN;
    int choix;
    Livres *pL=(Livres*)malloc(sizeof(Livres)), *cL=L, *trL=L;
    printf("\t\t La suppression d'un live seulement avec L ISBN \n");
    printf("\t\t Saisir L'ISBN :");
    scanf("%ld", &ISBN);
    while(trL!=NULL){
        if(trL->Livre->ISBN!=ISBN){
            time++;
        }
        t++;
        trL=trL->suivant;
    }
    if(t==time){
        printf("L'ISBN ne correspond pas a aucun livre dans la bibleotheque mondiale \n");
        return L;
    }
    FILE* ouvrir=fopen("Liste_Livres.txt", "w+");
    if(ouvrir!=NULL){
        while(cL!=NULL){
            if(cL->Livre->ISBN!=ISBN){    
                    fprintf(ouvrir,"%s|%s %s|%s|%ld|%d|%d \n",cL->Livre->titre, cL->Livre->Auteur.nom, cL->Livre->Auteur.prenom,cL->Livre->Auteur.nationalite,cL->Livre->ISBN,cL->Livre->Edition,cL->Livre->Date_pub);                
            }
        cL=cL->suivant;
        }
    }
    fclose(ouvrir);
    printf("\t\t\t :==========Les livres restants=========:\n");
    pL=ajouter_de_liste();
    Afficher_Livre(pL);
    return pL;
 }
 //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//

 Livres *ajouter_de_liste(){            //importer tous les livre dans liste Livre 
    FILE *ouvrir=fopen("Liste_Livres.txt", "r");
        Livres *listeLivres=NULL;
        Livres *courant=NULL;
        char line[MAX];
        while(fgets(line, sizeof(line), ouvrir)){
            InfoLivre *nouveau=(InfoLivre*)malloc(sizeof(InfoLivre));
            sscanf(line, "%[^|]|%[^ ] %[^|]|%[^|]|%ld|%d|%d", nouveau->titre, nouveau->Auteur.nom, nouveau->Auteur.prenom, nouveau->Auteur.nationalite, &nouveau->ISBN, &nouveau->Edition, &nouveau->Date_pub);
            Livres *nouveauLivre=(Livres*)malloc(sizeof(Livres));
            nouveauLivre->Livre=nouveau;
            nouveauLivre->suivant=NULL;
            if(listeLivres==NULL) {
                listeLivres=nouveauLivre;
                courant=nouveauLivre;
            }else{
                courant->suivant=nouveauLivre;
                courant=courant->suivant;
            }
        }
         fclose(ouvrir);
        return listeLivres;
}
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
//=================================================================================================================================================================================================================
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
Livres *Modifier_Info_Livre(Livres *L){ //modification d'une information d'un livre
    int choix,op ,t=0,time=0;
    int choixISBN;          
    int operation;
    long int ISBN;
    Livres *pL=L;
    Livres *ppL=L;
    choix=0;
    printf("Saisir L'ISBN d'un livre a changer ses information :");
    scanf("%ld",&ISBN);
    while(ppL!=NULL){
        if(ppL->Livre->ISBN!=ISBN)
            t++;
        time++;
        ppL=ppL->suivant;
    }
    if(time==t){ // cas d'un ISBN no correct  
        printf("Nous n'avons pas un livre de ce ISBN  %ld!!", ISBN);
        return L;
    }
    printf("thsi is it \n");
    while(pL!=NULL){
        printf("Qulle information voullez vous modifier ?:\n");
        printf("\t\t 1*le tittre \n\t\t ** information de l'auteur \n\t\t\t *2 Nom et prenom\n\t\t\t *3Nationalite \n\t\t 4*ISBN \n\t\t 5*Edition \n\t\t 6*Date de publication*\n");
        printf("\tVotre operation est :");
        scanf("%d", &operation);
        switch(operation){
            case 1:{
                    printf("Saisir le nouveau titre :");
                    scanf(" %s", &pL->Livre->titre);
                }break;
            case 2:{    
                    printf("Saisir le nouveau nom et le prenom  d 'auteur :");
                    scanf(" %s",&pL->Livre->Auteur.nom);    
                    scanf(" %s",&pL->Livre->Auteur.prenom);
                    }
                    break;
            case 3:{
                    printf("Saisir le nationalite d'auteur :");
                    scanf(" %s",&pL->Livre->Auteur.nationalite);
                    }
                   break;
            case 4:{
                    printf("Saisir le nouoveau ISBN :");
                    scanf("%ld", &pL->Livre->ISBN);
                }
                break;
            case 5:{
                    printf("Saisir le nouveau edition :");
                    scanf(" %d", &pL->Livre->Edition);
                }
                break;
            case 6:{
                printf("Date de publication :");
                scanf("%d" , &pL->Livre->Date_pub);
                }
            default:
                   printf("choix du menu 1 de (1 a 6) :");
        }
                  
    pL=pL->suivant;
    break;
    }
    return pL;
}
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
void Afficher_Livres_emprunter(emprunt_Livre *L){
    printf("\t\t\tles livres empruntee sont:\n");
    while(L!=NULL){
        printf("\t\t\t\t %s:de %d/%s/%d a %d/%s/%d \n",L->L.Livre->titre, L->emprunter.jour, L->emprunter.moix, L->emprunter.annee, L->retourner.jour, L->retourner.moix,L->retourner.annee);
        L=L->suivant;
    }
 }
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ bibleotheque mondiale pour l'Utilisateur @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//=======================================================================================================================
void Afficher_Livre(Livres *L){
    if(L==NULL){
        printf("\t\tAucun Livre n'a pas encore ajoutee !\n");
        printf("\t\t<merci> de contacter votre admin pour ajouter des livres");
    }
    else{
        printf("\t\tLes seggestions des livres sont :\n\n");
        while(L!=NULL){
            printf("\t\t|=======================\n");
            printf("\t\t|       %s              \n", L->Livre->titre);
            printf("\t\t|       %s %s           \n", L->Livre->Auteur.nom, L->Livre->Auteur.prenom);
            printf("\t\t|       ISBN:%d         \n", L->Livre->ISBN);
            printf("\t\t|=======================\n");
            L=L->suivant;
        }
    }
}
//=========================================================================================================================
void *afficher_Livre(InfoLivre *L){
            printf("\t\t|=======================\n");
            printf("\t\t|       %s              \n", L->titre);
            printf("\t\t|       %s %s           \n", L->Auteur.nom, L->Auteur.prenom);
            printf("\t\t|       ISBN:%d         \n", L->ISBN);
            printf("\t\t|=======================\n");
}
//==========================================================================================================================
 Livres *chercher_Livre(Livres *L){
    int choix;
    long int  ISBN;
    char *titre;
    int date;
    int edition;
    printf("؟؟؟؟؟؟methode de recherche ????? (l ISBN et le titre sont identifient un livre plus exacte) \n");
    printf("\t 1-----ISBN-----1\n");
    printf("\t 2-----titre----2\n");
    printf("\t 3-----Date_Publication---3\n");
    printf("\t 4-----l'edition-----4\n\t\t");
    do{
        scanf("%d", &choix);
    }while(choix>5);
    while(L!=NULL){
        switch(choix){
            case 1:{
                printf("Saisir L'ISBN :");
                scanf("%d",&ISBN);
                if(ISBN==L->Livre->ISBN)afficher_Livre(L->Livre);
                else printf("le livre d ISBN=%ld n'exst pas:",ISBN);
            }
            break;
            case 2:{
            printf("Saisir le titre :");
            scanf(" %s", titre);
            if(strcmp(titre,L->Livre->titre)==0)afficher_Livre(L->Livre);
            else
                printf("le livre de nom \"%s\"n'exist pas ", titre);
            }
            break;
            case 3:{
                printf("Saisir la date de publication :");
                scanf("%d", &date);
                if(date==L->Livre->Date_pub)Afficher_Livre(L);
                else printf("aucun livre n %d date publication !!\n", date);
            }
            break;
            case 4:{
                printf("Saisir l'edition :");
                scanf("%d", &edition);
                if(L->Livre->Edition==edition)Afficher_Livre(L);
                else printf("Aucun livre avec l'edition %d \n", edition);
            }
            break;
        }
    L=L->suivant;
    }

}
//==============================================================================================
Livres *Demander_Livre(Livres*L){
    Livres *ldemander=(Livres*)malloc(sizeof(Livres)), *pL=L;
    int time=0, t=0;
    printf("\n Saisir le nom de livre a demander :");
    scanf(" %s", ldemander->Livre->titre);
    while(pL!=NULL){
        if(strcmp(ldemander->Livre->titre,pL->Livre->titre)!=0){
            time++;
        }
        t++;
        pL=pL->suivant;
    }
    if(t==time){
        printf("ce nom du livre n'existe pas dans la bibleotheque mondiale \n");
        return L;
    }

    while(L!=NULL){
        if(strcmp(L->Livre->titre,ldemander->Livre->titre)==0)
            printf("votre livre \" %s \" sera dont notre point de relait bibleotheque la semaine prochaine , aurevoir \n",ldemander->Livre->titre);
        L=L->suivant;
    }if(L=NULL)
        printf("le livre saisir n'exist pas dans la bibleotheque mpndoale !!\n");
   return ldemander;
}
//=============================================================================================================
void Lire_Enligne(Livres *L) {
    FILE* ouvrir=NULL;
    char titre[MAX];
    printf("Saisir le titre de livre :");
    scanf(" %s", titre);
    int t=0;
    while(L!=NULL){
        if(strcmp(L->Livre->titre,titre)==0)
            t++;
        if(t!=0){
            ouvrir=fopen(L->Livre->titre,"r");
            if(ouvrir==NULL){
                printf("le livre existe et ses page n'est pas encore ajouter \n");
                return;
            }
            char c;
            do{
                c=fgetc(ouvrir);
                printf("%c",c);
            }while(c!=EOF);
            fclose(ouvrir);
            break;
        }
        L=L->suivant;
    }if(t==0)printf("le livre <%s> n'exist pas dans notre bibleotheque ! \n");
}
//===============================================================================================================================================================================
 emprunt_Livre *Emprunter(Livres *L, emprunt_Livre *suivante){
    emprunt_Livre *emp=(emprunt_Livre*)malloc(sizeof(emprunt_Livre)); //allocation de la memoire pour un livre emprunter
    char *titre;
    FILE *ouvrir=NULL;
    Livres *ppL=L;
    int time=0,t=0;
    printf("\t\tSaisir le titre du livre a emprunter :");
    scanf(" %s",titre);
    /*while(ppL!=NULL){
        if(strcmp(titre, L->Livre->titre)!=0)
            t++;
        time++;
        ppL=ppL->suivant;
    }
    if(time==t){
        printf("Aucun livre de nom :%s dans la bibleotheque mondiale \n",titre);
        return NULL;
    }*/
    while(L!=NULL){
        if(strcmp(L->Livre->titre, titre)==0){      //si le tlivre existe dans la bibleotheque alors on continue
            printf("Saisir la date de d'emprunter (date d'ajoudhui )[jour , mois, annee] :\n");     // entrer la date champ par champ
            scanf("%d",&emp->emprunter.jour);
            scanf(" %s",&emp->emprunter.moix);
            scanf("%d", &emp->emprunter.annee);
            printf("Saisir la date de retourner de meme maniere :\n");
            scanf("%d",&emp->retourner.jour);
            scanf(" %s", &emp->retourner.moix);
            scanf("%d", &emp->retourner.annee);
            emp->suivant=suivante;
            ouvrir=fopen("Livres_emprunter.txt","a+");    
            if(ouvrir!=NULL){ // enregistrer les livres emprunter dans le ficher Livres emprunter
                fprintf(ouvrir,"%s: de %d/%s/%d a %d/%s/%d \n", emp->L.Livre->titre,emp->emprunter.jour,emp->emprunter.moix,emp->emprunter.annee, emp->retourner.jour, emp->retourner.moix, emp->retourner.annee);
            }fclose(ouvrir);
            break;
        }
        L=L->suivant;
    }
    printf("\t\tReclamation : Vous devez respecter la date de retourner le livre <mreci >\n");
    return emp;
 }
 //========================================================================================================
 emprunt_Livre *Livres_emprunter_file(){
    FILE* ouvrir=fopen("Livres_emprunter.txt", "r");
    emprunt_Livre *EL=NULL, *AL=NULL ;
    char line[MAX];
        while(fgets(line, sizeof(line), ouvrir)){
            emprunt_Livre *ELR=(emprunt_Livre*)malloc(sizeof(emprunt_Livre));               
            sscanf(line, "%[^:]: de %d/%[^/]/%d a %d/%[^/]/%d", ELR->L.Livre->titre, &ELR->emprunter.jour, ELR->emprunter.moix, &ELR->emprunter.annee, &ELR->retourner.jour, ELR->retourner.moix, &ELR->retourner.annee);
            ELR->suivant=NULL;
            if(AL==NULL){
                AL=ELR;
                EL=ELR;
             }else{
                EL->suivant=ELR;
                EL=EL->suivant;
            }

        }
        fclose(ouvrir);
        return AL;
}
//=========================================================================================================

char principale(){
    char  choix;
    printf("\t\t >>>#@#@#@#@#@#@#@#@#@#@#@#@#@@##@#@#@#@#@#@#@##@#@#@#@#@#@#@#@#@##@#@#@#@#@<<<\n\n");
    printf("\t\t   >>>          |**|Bienvenu dans votre mondial Bibeleotheque            <<< \n");
    printf("\t\t    >>>>        @*******@: Votre espace Utilisatuer :@*******@        <<<< \n");
    printf("\t\t   >>>          #*******#:    Votre compte Admin    :#*******#           <<< \n\n");
    printf("\t\tL'espace  admin  en  apuuyant    sur # pour effectuer des operation d'ajouter ,suprimer,modifier des livres \n");
    printf("\t\tL'espace utilisateur en appuyant sur @ pour decouvrir o chercher ou demander ,emprunter les livres \n");
    printf("\t\t >>>#@@#@#@#@#@#@#@#@#@#@#@#@##@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@<<<\n");
    do{
        printf("\n\t\t\t\t\t\t\t\t");
        scanf("%c", &choix);
    }while(choix!='#' && choix!='@');
    switch (choix){
        case '@':choix='@';
            break;
        case '#': choix='#';
    }
    return choix;
}

