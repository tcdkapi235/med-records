#include <stdio.h>
#include <string.h>
typedef struct{
    int numagr;
    char name[20], prenom[30];
    char specialite[40];
    char adresse[30], mail[30];
    char tel[20]; 
}medecin;
typedef struct{
    int id, age;
    char name[20], prenom[30], adresse[30], typedemaladie[30], RDV[20], tel[20];
}patient;
// Triage des patient
void tripatient(){
    FILE *f;
    int n;
    patient t[100], x;
    int i, j;
 
    f = fopen("patient.dat", "rb");
    if(f == NULL){
        return;
    }
    n = 0;
    while(fread(&t[n],sizeof(patient), 1, f)){
        n++;
    }
    fclose(f);
    for(i = 0; i < n - 1; i++){
        for(j = i + 1; j < n; j++){
            if(t[i].id > t[j].id){
                x = t[i];
                t[i] = t[j];
                t[j] = x;
            }       
        }
    }
    f = fopen("patient.dat", "wb");
    if(f == NULL){
        printf("error\n"); return;
    }
    for(i = 0; i < n; i++){
        fwrite(&t[i], sizeof(patient), 1, f);
    }
    fclose(f);
}
// Triage des medecins
void tripmedecin(){
    FILE *f;
    int n;
    medecin t[100], x;
    int i, j;
 
    f = fopen("medecin.dat", "rb");
    if(f == NULL){
        return;
    }
    n = 0;
    while(fread(&t[n],sizeof(medecin), 1, f)){
        n++;
    }
    fclose(f);
    for(i = 0; i < n - 1; i++){
        for(j = i + 1; j < n; j++){
            if(t[i].numagr > t[j].numagr){
                x = t[i];
                t[i] = t[j];
                t[j] = x;
            }       
        }
    }
    f = fopen("medecin.dat", "wb");
    if(f == NULL){
        printf("error\n"); return;
    }
    for(i = 0; i < n; i++){
        fwrite(&t[i], sizeof(medecin), 1, f);
    }
    fclose(f);
}
// Verification d'un numero
int numverification(char tel[]){
    int i = 0;
    while(tel[i] != '\0'){
        if(tel[i] < '0' || tel[i] > '9'){
            return 0; 
        }
        i++;
    }
    return 1;
}
// Verification des mails
int mailverification(char mail[30]){
    return strstr(mail, "@gmail.com") != NULL; // or strch(mail, "@")
}
// Une fonction pour l'ajout de patient
void ajoutpatient(patient *P){
    printf("\nname : "); scanf("%s %s", P->name, P->prenom);
    printf("\nAge : "); scanf("%d", &P->age); 
    printf("\n Id  : "); scanf("%d", &P->id);
    printf("\nLe numero de telephone : "); 
    scanf(" %s", P->tel);
    while(!numverification(P->tel)){
         printf("\nMauvaise entree : ");
         scanf(" %s", P->tel);
    }
   
    printf("\nAdresse : "); scanf("%s", P->adresse);
    printf("\nType de maladie : "); scanf("%s", P->typedemaladie);
    printf("\nRDV : "); scanf("%s", P->RDV);
}
//Une fonction pour enregistrer un patient dans le fichier
void enrpatient(){
    FILE *f;
    patient p;
    f = fopen("patient.dat", "ab");
    if (f == NULL){
        printf("error\n"); return;
    } else printf("Ok\n");
    ajoutpatient(&p);
    fwrite(&p,sizeof(p), 1, f);
    fclose(f);
}
//une fonction pour affichier tout les patients
void affichpatient(){
    patient p;
    FILE *f;
    f = fopen("patient.dat", "rb");
    if (f == NULL){
        printf("error\n");
    } else printf("Ok\n");
    while(fread(&p, sizeof(p), 1, f) == 1){
        printf("%d %s %s %d %s %s %s %s\n", p.id, p.name, p.prenom, p.age, p.adresse, p.typedemaladie, p.tel, p.RDV);
    }
    fclose(f);
}
// une fontction pour l'ajout de medecin
void ajoutmedecin(medecin *M){
    printf("\nName :"); scanf("%s %s", M->name, M->prenom);
    printf("\nnumagr :"); scanf("%d", &M->numagr);
    printf("\nSpecialite : "); scanf("%s", M->specialite);
    printf("\nAdresse : "); scanf("%s", M->adresse);
    printf("\nMail : ");
    scanf(" %s", M->mail);
    while(!mailverification(M->mail)){
        printf("\nMauvaise entree : ");
        scanf(" %s", M->mail);
    }
    printf("\nTel : "); 
    scanf("%s", M->tel);
    while(!numverification(M->tel)){
        printf("\nMauvaise entree : ");
        scanf("%s", M->tel);
    }
    
}
//une fonction pour enregistrer un medecin dans le fichier 
void enrmedecin(){
    FILE *f;
    medecin m;
    f = fopen("medecin.dat", "ab");
    if(f == NULL){
        printf("error\n");
    } else printf("good\n");
    ajoutmedecin(&m);
    fwrite(&m, sizeof(m), 1, f);
    fclose(f);
}
//une fonction pour affichier tout les medecins
void affichmedecin(){
    medecin M;
    FILE *f;
    f = fopen("medecin.dat", "rb");
     if(f == NULL){
        printf("error\n");
    } else printf("good\n");
    while(fread(&M, sizeof(M), 1, f) == 1){
        printf("%d %s %s %s %s %s %s\n", M.numagr, M.name, M.prenom, M.specialite, M.adresse, M.mail, M.tel);
    }
    fclose(f);
}
// Une fonction pour afficher tout les corps
void affichertout(){
    medecin M;
    patient p;
    FILE *f1, *f2;
    f1 = fopen("medecin.dat", "rb");
    if(f1 == NULL){
        printf("error\n");
    } else printf("good\n");
    f2 = fopen("patient.dat", "rb");
    if(f2 == NULL){
        printf("error\n");
    } else printf("good\n");
    printf("==LES MEDECINS==\n");
     while(fread(&M, sizeof(M), 1, f1) == 1){
        printf("%d %s %s %s %s %s %s\n", M.numagr, M.name, M.prenom, M.specialite, M.adresse, M.mail, M.tel);
    }
    printf("==LES PATIENTS==\n");
      while(fread(&p, sizeof(p), 1, f2) == 1){
        printf("%d %s %s %d %s %s %s %s\n", p.id, p.name, p.prenom, p.age, p.adresse, p.typedemaladie, p.tel, p.RDV);
    }
    fclose(f1);
    fclose(f2);
}
// Une fonction qui recherche un patient par nom ou par son Id
void recherchepat(){
    FILE *f;
    patient p;
    int x = 0,id;
    char nom[20], recher[20];
    f = fopen("patient.dat", "rb");
    printf("\nVoulez le recherche par nom ou id : ");
    do {
    scanf("%s", recher);
   if(strcmp(recher, "nom") != 0 && strcmp(recher, "id") != 0)
   printf("Mauvaise entree! entrer nom' ou 'id'\n");
    } while (strcmp(recher, "nom") != 0 && strcmp(recher, "id") != 0);
   if(strcmp(recher, "nom") == 0){
        printf("\nDonner le nom : "); scanf("%s", nom);
    } else {
        printf("\nDonner l'id : "); scanf("%d", &id);
    }
    if(strcmp(recher, "nom") == 0){
        while(fread(&p, sizeof(p), 1, f)){
        if(strcmp(p.name, nom) == 0){
         printf("%d %s %s %d %s %s %s %s\n", p.id, p.name, p.prenom, p.age, p.adresse, p.typedemaladie, p.tel, p.RDV);
         x = 1;
        } 
    }
    if(!x)
        printf("patien non trouve\n");
        fclose(f);
} else
f = fopen("patient.dat", "rb");
while(fread(&p, sizeof(p), 1, f)){
        if(p.id == id){
         printf("%d %s %s %d %s %s %s %s\n", p.id, p.name, p.prenom, p.age, p.adresse, p.typedemaladie, p.tel, p.RDV);
         x = 1;
        } 
    }
    if(!x)
        printf("patien non trouve\n");

        fclose(f);

   
}
// Une fonction qui fait la recherche un medecin par son numero d'agrement ou son nom
void recherchemed(){
    FILE *f;
    medecin M;
    int x = 0, num;
    char nom[20], recher[20];
    f = fopen("medecin.dat", "rb");
    printf("\nVoulez-vous la recherche par numero d'agrement(num) ou nom : "); 
    do{
        scanf("%s", recher);
        if(strcmp(recher, "nom") != 0 && strcmp(recher, "num") != 0)
        printf("\nVeuillez entrer 'nom' ou 'num' : ");
    }while(strcmp(recher, "nom") != 0 && strcmp(recher, "num") != 0);
    if(strcmp(recher, "nom") == 0){
        printf("\nDonner le nom : "); scanf("%s", nom);
    }else {
        printf("\nDonner le  numero d'agrement : "); scanf("%d", &num);
    }
    if(strcmp(recher, "nom") == 0){
        while(fread(&M, sizeof(M), 1, f) == 1){
            if(strcmp(M.name, nom) == 0){
                printf("%d %s %s %s %s %s %s\n", M.numagr, M.name, M.prenom, M.specialite, M.adresse, M.tel, M.mail);
                x = 1;
            }
        }
        if(!x)
        printf("Medecin non trouve\n");
        fclose(f);
    } else 
    f = fopen("medecin.dat", "rb");
    while(fread(&M, sizeof(M), 1, f) == 1){
            if(M.numagr == num){
                printf("%d %s %s %s %s %s %s\n", M.numagr, M.name, M.prenom, M.specialite, M.adresse, M.tel, M.mail);
                x = 1;
            }
        }
        if(!x)
        printf("Medecin non trouve\n");
        fclose(f);
}
// Pour la recherche
void recherche(){
    int a;
    do {
    printf("\nVoulez-vous chercher un medecin(1) ou un patient(2) : ");
    scanf("%d", &a);
    if(a != 1 && a != 2)
        printf("Mauvaise entree! Veuillez entrer 1 ou 2.\n");
} while(a != 1 && a != 2);

switch (a) {
    case 1 : recherchemed();
        break;
    case 2 : recherchepat();
        break;
}
}

void RDV(){
    FILE *f;
    patient p;
    char date[20]; int x = 0;
    f = fopen("patient.dat", "rb");
    if(f == NULL){
        printf("fichier introuvable\n"); return;
    }
    printf("\nEntrer la date : "); scanf("%s", date);
    while(fread(&p, sizeof(p), 1, f) == 1){
        if (strcmp(p.RDV, date) == 0){
            printf("%d %s %s %d %s %s %s %s\n", p.id, p.name, p.prenom, p.age, p.adresse, p.typedemaladie, p.tel, p.RDV);
            x = 1;
        }
    }
    if(!x)
    printf("Aucun patient trouve\n");
    fclose(f);
}
int main(){
      int choix;
      printf("1.ENREGISTRER UN MEDECIN\n"); printf("2.AFFICHER TOUT LES MEDECINS\n"); printf("3.ENREGISTRER UN PATIENT\n"); 
        printf("4.AFFICHER TOUT LES PATIENTS\n"); printf("5.AFFICHER LES MEDECINS ET LES PATIENTS\n"); printf("6.RECHERCHE\n");
        printf("7.RDV\n");
      do
      {
        printf("\nentrez votre choix : ");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1 :
            enrmedecin(); tripmedecin();
            break;
          case 2 : affichmedecin();
          break;
          case 3 : enrpatient(); tripatient();
          break;
          case 4 : affichpatient();
          break;
          case 5 : affichertout();
          break;
          case 6 : recherche();
          break;
          case 7 : RDV();
          break;
        
        default:
            break;
        }
        if(choix == 0)
        printf("\n Merci a la prochaine \n");
      } while (choix != 0);
      
        return 0;
        
}