#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
// Structures
typedef struct {
    int id_tache;
    char titre_tache[30];
    char description_tache[300];
    char date_dajout_tache[11];
    char deadline_tache[11];
    char status[30];
} Tache;
// Global variables
Tache list_taches[100];
int count_taches = 0;
int tache_complete = 0;
int tache_incomplete = 0;
// Function to get the current date
void getCurrentDate(char *currentDate) {
    time_t currentTime;
    struct tm *localTime;
    currentTime = time(NULL);
    localTime = localtime(&currentTime);
    snprintf(currentDate, 11, "%02d-%02d-%04d", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
}
// fonction de calculation des taches celon statut
void calcul_selon_statut(){
    for(int i=0 ; i<count_taches ; i++){
        if(strcmp(list_taches[i].status,"deja fait")==0){
            tache_complete++;
        }else if(strcmp(list_taches[i].status,"fait")==0 || strcmp(list_taches[i].status,"a faire")==0){
            tache_incomplete++;
        }
    }
}
// fonction de calcule des deadline
int calc_deadline(int indice ,char dead_tache[11]){
    char date_loc[11];
    int day , month , year ,somme_days;
    int day1 , month1 , year1, somme_days1 ;
    int tot_jour;
    getCurrentDate(date_loc);
    sscanf( list_taches[indice].deadline_tache,"%d-%d-%d",&day , &month , &year );
                somme_days = day+month*30+year*365;
                sscanf( date_loc,"%d-%d-%d",&day1 , &month1 , &year1 );
                somme_days1 = day1+month1*30+year1*365;
                tot_jour = somme_days - somme_days1;
                return tot_jour;
}
//fonction pour l'ordre alphabetique
int order_alphabetique(){
    char titre_temp[30];
    char date_ajout_tmp[11];
    char description_tmp[300];
    char dead_tmp[11];
    char statut_tmp[30];
    int id_tmp;
    for(int i = 0 ; i < count_taches-1 ; i++){
        for(int j = i+1 ; j < count_taches ; j++){
           if(strcmp(list_taches[i].titre_tache,list_taches[j].titre_tache)==1){
                strcpy(titre_temp,list_taches[i].titre_tache);
                strcpy(list_taches[i].titre_tache,list_taches[j].titre_tache);
                strcpy(list_taches[j].titre_tache,titre_temp);

                strcpy(date_ajout_tmp,list_taches[i].date_dajout_tache);
                strcpy(list_taches[i].date_dajout_tache,list_taches[j].date_dajout_tache);
                strcpy(list_taches[j].date_dajout_tache,date_ajout_tmp);

                strcpy(description_tmp,list_taches[i].description_tache);
                strcpy(list_taches[i].description_tache,list_taches[j].description_tache);
                strcpy(list_taches[j].description_tache,description_tmp);

                strcpy(dead_tmp,list_taches[i].deadline_tache);
                strcpy(list_taches[i].deadline_tache,list_taches[j].deadline_tache);
                strcpy(list_taches[j].deadline_tache,dead_tmp);

                strcpy(statut_tmp,list_taches[i].status);
                strcpy(list_taches[i].status,list_taches[j].status);
                strcpy(list_taches[j].status,statut_tmp);

                id_tmp = list_taches[i].id_tache;
                list_taches[i].id_tache = list_taches[j].id_tache;
                list_taches[j].id_tache = id_tmp;
           }
        }
    }
}
// order by deadline
void order_by_deadline(){
        int day , month , year ,somme_days;
        int day1 , month1 , year1, somme_days1 ;
        char titre_temp[30];
        char date_ajout_tmp[11];
        char description_tmp[300];
        char dead_tmp[11];
        char statut_tmp[30];
        int id_tmp;
        for(int i = 0 ; i < count_taches-1 ; i++){
                sscanf( list_taches[i].deadline_tache,"%d-%d-%d",&day , &month , &year );
                somme_days = day+month*30+year*365;
        for(int j = i+1 ; j < count_taches ; j++){
                sscanf( list_taches[j].deadline_tache,"%d-%d-%d",&day1 , &month1 , &year1 );
                somme_days1 = day1+month1*30+year1*365;
           if(somme_days>somme_days1){
                strcpy(titre_temp,list_taches[i].titre_tache);
                strcpy(list_taches[i].titre_tache,list_taches[j].titre_tache);
                strcpy(list_taches[j].titre_tache,titre_temp);

                strcpy(date_ajout_tmp,list_taches[i].date_dajout_tache);
                strcpy(list_taches[i].date_dajout_tache,list_taches[j].date_dajout_tache);
                strcpy(list_taches[j].date_dajout_tache,date_ajout_tmp);

                strcpy(description_tmp,list_taches[i].description_tache);
                strcpy(list_taches[i].description_tache,list_taches[j].description_tache);
                strcpy(list_taches[j].description_tache,description_tmp);

                strcpy(dead_tmp,list_taches[i].deadline_tache);
                strcpy(list_taches[i].deadline_tache,list_taches[j].deadline_tache);
                strcpy(list_taches[j].deadline_tache,dead_tmp);

                strcpy(statut_tmp,list_taches[i].status);
                strcpy(list_taches[i].status,list_taches[j].status);
                strcpy(list_taches[j].status,statut_tmp);

                id_tmp = list_taches[i].id_tache;
                list_taches[i].id_tache = list_taches[j].id_tache;
                list_taches[j].id_tache = id_tmp;
           }}
    }
}
// order by deadline less then 3 jours
void order_by_deadline_less_3(){
        int day , month , year ,somme_days;
        int day1 , month1 , year1, somme_days1 ;
        char date_locale[11];
        int taille_temp_list=0;
        Tache temp_list_tache[100];
        getCurrentDate(date_locale);
        sscanf( date_locale,"%d-%d-%d",&day , &month , &year );
        somme_days = day+month*30+year*365;
          for(int i = 0 ; i < count_taches; i++){
                sscanf( list_taches[i].deadline_tache,"%d-%d-%d",&day1 , &month1 , &year1 );
                somme_days1 = day1+month1*30+year1*365;
                if(somme_days1-somme_days<=3){
                    strcpy(temp_list_tache[taille_temp_list].status,list_taches[i].status);
                    strcpy(temp_list_tache[taille_temp_list].date_dajout_tache,list_taches[i].date_dajout_tache);
                    strcpy(temp_list_tache[taille_temp_list].deadline_tache,list_taches[i].deadline_tache);
                    strcpy(temp_list_tache[taille_temp_list].titre_tache,list_taches[i].titre_tache);
                    temp_list_tache[taille_temp_list].id_tache=list_taches[i].id_tache;
                    taille_temp_list++;
                }
          }
           for(int i = 0 ; i < taille_temp_list ; i++){
                printf("id : %d\n",temp_list_tache[i].id_tache);
                printf("titre : %s\n",temp_list_tache[i].titre_tache);
                printf("statut : %s\n",temp_list_tache[i].status);
                printf("date d'ajout : %s\n",temp_list_tache[i].date_dajout_tache);
                printf("deadline : %s\n",temp_list_tache[i].deadline_tache);
          }
}
// Function to display the menu
void menu() {
    calcul_selon_statut();
    printf("\n\n");
    printf("\t============================================================================================\n");
    printf("\t \t \t \t \t \t Liste des taches (To-Do List)\n");
    printf("\t============================================================================================\n");
    printf("\t[1] Ajouter une tache\n");
    printf("\t[2] Ajouter plusieur taches\n");
    printf("\t[3] Afficher les taches\n");
    printf("\t[4] modifier les taches\n");
    printf("\t[5] rechercher les taches\n");
    printf("\t[6] supprimer une tache by id\n");
    printf("\t[7] Quitter\n");
    printf("\t=============================================================================================\n");
    printf("\t vous avez %d  taches %d complet %d incomplet \n",count_taches,tache_complete,tache_incomplete);
    printf("\t=============================================================================================\n");
    printf("\tEntrez votre choix selon le menu precedent, s'il vous plait : ");
    tache_complete = 0;
    tache_incomplete = 0;
}
// Function to add a task
void ajouter_tache( Tache nouvelle_tache) {
    int choix_statut;
    getCurrentDate(nouvelle_tache.date_dajout_tache);
    printf("Entrez le titre de la tache : ");
    fscanf(stdin, " ");
    gets(nouvelle_tache.titre_tache);
    printf("Entrez la description de la tache : ");
    gets(nouvelle_tache.description_tache);
    printf("Entrez le deadline du tache  comme suit <<jj-mm-yyyy>> s'il vous plait: ");
    scanf("%s", nouvelle_tache.deadline_tache);
    printf("choisisser le statut de la tache d'apres le menu suivant :\n ");
    printf("::::::::::::::::::::::::::: :\n ");
    printf("[1] a faire :\n ");
    printf("[2] fait :\n ");
    printf("[3] deja fait :\n ");
    printf("::::::::::::::::::::::::::: :\n ");
    scanf("%d",&choix_statut);
     switch(choix_statut){
        case 1 :strcpy(nouvelle_tache.status,"a faire");

            break;
        case 2 :strcpy(nouvelle_tache.status,"fait");
            break;
        case 3 :strcpy(nouvelle_tache.status,"deja fait");

            break;
        default : strcpy(nouvelle_tache.status,"a faire");
     }
    nouvelle_tache.id_tache = count_taches;
    list_taches[count_taches] = nouvelle_tache;
    printf("Tache ajoutee avec succes.");
    count_taches++;
}
// fonction pour ajouter plusieur tache
void ajouter_plusieurs_tache(){
    int nbr_taches;
    Tache nouvelle_tache;
    printf("entrer le nombre de taches que tu veux ajouter :\n");
    scanf("%d",&nbr_taches);
    int debut = count_taches;
    for(int i = debut ; i < debut + nbr_taches; i++ ){
        ajouter_tache( nouvelle_tache);
    }
}
// fonction d'affichage globale pour minimiser le code d'affichage et de recherche
void affichage(int indice){
    int totale_jour;
            printf("ID : %d\n", list_taches[indice].id_tache);
            printf("Titre : %s\n", list_taches[indice].titre_tache);
            printf("Description : %s\n", list_taches[indice].description_tache);
            printf("Date d'ajout : %s\n", list_taches[indice].date_dajout_tache);
            printf("deadline : %s\n", list_taches[indice].deadline_tache);
            printf("Statut : %s\n\n", list_taches[indice].status);
            totale_jour = calc_deadline(indice ,list_taches[indice].deadline_tache);
            if(totale_jour>0){
                printf("il reste %d jours :",totale_jour);
            }else{
                printf("tache deja fait :\n");
            }
}
// Function to display tasks
void afficher_taches() {
    int choix_affichage;
    if (count_taches > 0) {
        printf("::::::::::::::::::::::::::\n");
        printf("choisisser le type d'affichage :\n");
        printf("[1] alphabetiquement :\n");
        printf("[2] by deadline :\n");
        printf("[3] juste qui ont moins de 3 jour :\n");
        printf("::::::::::::::::::::::::::\n");
        scanf("%d",&choix_affichage);
            switch(choix_affichage){
                case 1 :    order_alphabetique();
                    break;
                case 2 :    order_by_deadline();
                    break;
                case 3 :    order_by_deadline_less_3();
                    break;
                default:    order_by_deadline();
            }
            if(choix_affichage!=3){
                printf("\nListe des taches :\n");
        for (int i = 0; i < count_taches; i++) {
          affichage(i);
        }
            }
    } else {
        printf("\nIl n'y a aucune tache a afficher.\n");
    }
}
// fonction de modification
void modifier_tache() {
    char titre_tache_mod[30];
    char new_mod[50];
    int choix_mod;
    int choix_statut;
    bool trouver = false;
    printf("entrer le titre du tache que tu veux modifier \n");
    fscanf(stdin, " ");
    gets(titre_tache_mod);
    for(int i = 0;i<count_taches;i++){
        if(strcmp(list_taches[i].titre_tache , titre_tache_mod)==0){
                printf(":::::::::::::::::::::::::::::::::::::\n");
                printf("[1] description:\n");
                printf("[2] deadline:\n");
                printf("[3] status:\n");
                printf("qu'est ce que tu veux modifier :\n");
                scanf("%d",&choix_mod);
                printf(":::::::::::::::::::::::::::::::::::::\n");
                if(choix_mod == 1 || choix_mod == 2){
                    printf("entrer votre modification :\n");
                    fscanf(stdin, " ");
                    gets(new_mod);
                    switch(choix_mod){
                        case 1 : strcpy(list_taches[i].description_tache , new_mod);
                            break;
                        case 2 : strcpy(list_taches[i].deadline_tache , new_mod);
                            break;
                        default : printf("votre choix invalid :\n");
                    }
                }else{
                        printf("choisisser le statut de la tache d'apres le menu suivant :\n ");
                        printf("::::::::::::::::::::::::::: :\n ");
                        printf("[1] a faire :\n ");
                        printf("[2] fait :\n ");
                        printf("[3] deja fait :\n ");
                        printf("::::::::::::::::::::::::::: :\n ");
                        scanf("%d",&choix_statut);
                     switch(choix_statut){
                            case 1 :strcpy(list_taches[i].status,"a faire");
                                break;
                            case 2 :strcpy(list_taches[i].status,"fait");
                                break;
                            case 3 :strcpy(list_taches[i].status,"deja fait");
                                break;
                            default : strcpy(list_taches[i].status,"a faire");
                        }
                }
                trouver = true;
    }
}
if(trouver == false){
    printf("tu n'a pas des taches avec ce titre :\n");
}
}
//fonction de recherche par titre
void recherche_by_titre(bool *trouver){
    char titre_tache_rech[30];
    printf("entrer le titre de la tache que vous voulez : \n");
    fscanf(stdin, " ");
    gets(titre_tache_rech);
    for(int i = 0 ;i<count_taches; i++){
        if(strcmp(list_taches[i].titre_tache , titre_tache_rech)==0){
            affichage(i);
            *trouver = true;
    }
}
}
//fonction de recherche par identifiant
void recherche_by_identifiant( bool *trouver){
    int id_tache_rech;
    printf("entrer l'identifiant de la tache que tu veux afficher : \n");
    scanf("%d",&id_tache_rech);
    for(int i = 0 ;i<count_taches; i++){
        if(list_taches[i].id_tache == id_tache_rech){
            affichage(i);
            *trouver = true;
    }
}
}
// fonction de recherche
void rechercher_tache() {
    int choix_rech;
    bool trouver = false;
      printf(":::::::::::::::::::::::::::::::::::::\n");
                printf("[1] titre:\n");
                printf("[2] id:\n");
                printf("entrer le choix de recherche : \n");
                scanf("%d",&choix_rech);
                printf(":::::::::::::::::::::::::::::::::::::\n");
                switch(choix_rech){
                    case 1 : recherche_by_titre(&trouver);
                                trouver = false;
                        break;
                    case 2 :recherche_by_identifiant(&trouver);
                        trouver = false;
                        break;
                    default : printf("choix de type de recherche invalid : \n");
                }
if(trouver == false && choix_rech == 1 ){
    printf("tu n'a pas des taches avec ce titre :\n");
}else if(trouver == false && choix_rech == 2 ){
    printf("tu n'a pas des taches avec ce identifiant :\n");
}
}
//fonction de suppresion identifiant
void supprimer_par_identifiant(){
    int id_tache_rech;
    int trouver_rech = -1;
    printf("entrer l'identifiant de la tache que vous voulez supprimer :");

    scanf("%d",&id_tache_rech);
    for(int i = 0 ; i < count_taches ; i++){
            trouver_rech = i;
        if(list_taches[i ].id_tache == id_tache_rech){
            for(int j = trouver_rech ; j < count_taches ; j++){
                list_taches[j].id_tache = list_taches[j+1].id_tache;
                strcpy(list_taches[j].titre_tache , list_taches[j+1].titre_tache);
                strcpy(list_taches[j].description_tache , list_taches[j+1].description_tache);
                strcpy(list_taches[j].date_dajout_tache , list_taches[j+1].date_dajout_tache);
                strcpy(list_taches[j].deadline_tache , list_taches[j+1].deadline_tache);
                strcpy(list_taches[j].status , list_taches[j+1].status);
                count_taches--;
            }
            }
}
if(trouver_rech == -1){
    printf("tu n'a aucune tache avec ce id !!");
}
}
// Main function
int main() {
    int choix_d_action;
    Tache nouvelle_tache;
    do {
        menu();
        scanf("%d", &choix_d_action);

        switch (choix_d_action) {
            case 1:
                ajouter_tache(nouvelle_tache);
                break;
             case 2:
                ajouter_plusieurs_tache();
                break;
            case 3:
                afficher_taches();
                break;
            case 4:
                modifier_tache();
                break;
            case 5:
                rechercher_tache();
                break;
            case 6:
                supprimer_par_identifiant();
                break;
            case 7:
                return 0;
                break;
            default:
                printf("Option invalide. Veuillez reessayer.\n");
        }
    } while (1);

    return 0;
}
