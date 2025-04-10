
#include"lbrs.h"
#include"fcts.c"

int main(){
    Livres *l=(Livres*)malloc(sizeof(Livres*)) , *L=(Livres*)malloc(sizeof(Livres));
    emprunt_Livre *LE=NULL;
    int quiter=0;
    l=ajouter_de_liste(l);              // importer tous les livres dans la liste l
    do{
        char compte=principale();
        switch (compte){
        case '@':{
            int choix;
            do{
                printf("\t\t|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@|@| \n");
                printf("\t\t||||||||||@|@|@|@|@|@                                         |@|@|@|@|@|@||||||||| \n");
                printf("\t\t**********************Bien venu dans la bibleotheque mondiale********************** \n");
                printf("\t\t||||||||||@|@|@|@|@|@                                          @|@|@|@|@|@||||||||| \n");
                printf("\t\t******************1 : Decouvrir nouveau livres en appuyant sur: 1****************** \n");
                printf("\t\t  ****************2 : Cherecher un livre par titre ou ISBN    : 2**************** \n");
                printf("\t\t    **************3 :            Demander un livre            : 3************** \n");
                printf("\t\t      ************4 :          Lire un livre enligne          : 4************ \n");
                printf("\t\t         *********5 :            Empunter un livre            : 5********** \n");
                printf("\t\t             ********************************************************** \n");
                printf("\t\t              >>>>>>>>>>>>>>>>>Saisir Votre choix<<<<<<<<<<<<<<<<<<<<<\n");
                printf("\t\t\t\t\t\t\t");scanf("%d",&choix);
            }while(choix>6);
            switch(choix){
                case 1:Afficher_Livre(l);                       break;
                case 2:l=ajouter_de_liste();chercher_Livre(l);  break;
                case 3:l=Demander_Livre(l);                     break;
                case 4:l=ajouter_de_liste();Lire_Enligne(l);                         break;
                case 5:l=ajouter_de_liste();Emprunter(l, LE);   break;
            }
            printf("\t\t\tVoullez vous ressayer (oui =1| non=autre clee :)");
            scanf("%d",&quiter);
        }break;
        case '#':{
                int choix;
                printf("\t\t\t\t\t\t#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#\n");
                printf("\t\t\t\t\t |#|#|#|#|#|******Bien venu dans votre compte admin*****#|#|#|#|#\n");
                printf("\t\t\t\t\t\t#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#\n\n");
                printf("\t\t\t\t\t\t    *Les operation sur votre bibleotheque mondial* \n");
                printf("\t\t\t\t\t       ****       1 :     Ajouter  un livre    :1          ****\n");
                printf("\t\t\t\t\t      ****        2 :    supprimer  un livre   :2           ****\n");
                printf("\t\t\t\t\t      ****        3 : Modifier infos d'un livre :3           ****\n");
                printf("\t\t\t\t\t       ****       4 : Voir les livres empruntée :4          ****\n");
                printf("\t\t\t\t\t<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
                printf("\t\t\t\t\t          votre operation est :");
                scanf("%d", &choix);
                switch(choix){
                    case 1:l=Ajouter_Livre(l);l=ajouter_de_liste();break;
                    case 2:l=ajouter_de_liste(l);l=supprimer_Livre(l);break;
                    case 3:Modifier_Info_Livre(l);break;
                    case 4:LE=Livres_emprunter_file();Afficher_Livres_emprunter(LE);break;
                    
                }
            }
            printf("\n\t\t\tVoullez vous ressayer (oui =1| non=autre clee :)");
            scanf("%d",&quiter);
        }   
    }while(quiter==1);
    return 0;
}
