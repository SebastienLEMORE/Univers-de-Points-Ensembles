#include <stdio.h>
#include <stdlib.h>
#include "ensembleDePoints.h"

/**
 * FONCTION D'AFFICHAGE
**/

void afficheEnsembleDePoint(ensemble_t *e,univers *u){
    ensemble_t *tmp = e;
    int i;
    while(tmp != NULL){
        printf("\nPoint %d =>\n", tmp->indice);
        affichePoint(u->point[tmp->indice]);
        printf("\n");
        tmp=tmp->suiv;
    }
}

void afficheTousEnsembleDePoints(univers* u, ensemble_t **ens){
    int i;
    for(i=0;i<3;i++){
        printf("\n<------ ENSEMBLE %d ------>\n",i);
        afficheEnsembleDePoint(ens[i],u);
    }
}

void afficheUnivers(univers *u){
    int i,j;
    printf("\n\nUnivers =>\nNombre de point : %d\n\n",u->taille);
    for(i=0;i<u->taille;i++){
        affichePoint(u->point[i]);
        printf("\n");
    }
}
/**
 * FONCTION DE CRÉATION DE L'UNIVERS ET DES 3 ENSEMBLES
**/
univers* initUnivers(){
    printf("\nNombre de point de l'Univers : ");
    int n=-1,i;
    point *p=NULL;
    do{
        scanf("%d",&n);
    }while(n<1);
    univers *u=(univers *)malloc(sizeof(univers));
    u->point=NULL;
    u->taille=0;
    for(i=0;i<n;i++){
        printf("\nPoint %d de l'univers : \n",i);
        p=lirePoint();
        u=ajouterPoint(u,p);
    }
    return u;
}

ensemble_t** initEnsemble(univers *u, int n){
    ensemble_t **ens=(ensemble_t **)malloc(sizeof(ensemble_t *)*3);
    int i,j, indice=0;
    for(i=0;i<3;i++){
        ens[i]=NULL;
        for(j=0;j<n;j++){
            do{
                printf("\nSaisir l'indice %d du sous-ensemble %d (entre 0 et %d) : ",j,i,u->taille-1);
                scanf("%d",&indice);
            }while(indice<0 || indice>u->taille-1);
            ens[i]=ajouterElement(indice,ens[i]);
        }
    }
    return ens;
}
/**
 * FONCTION D'AJOUT D'ELEMENT DANS UN ENSEMBLE
**/
ensemble_t *ajouterElement(int o,ensemble_t *e){
    ensemble_t* c=(ensemble_t*) malloc(sizeof(ensemble_t));
    c->indice=o;
    if(e==NULL){
        c->suiv=NULL;
        e=c;
        return e;
    }
    if(c->indice<e->indice){
        c->suiv=e;
        e=c;
        return e;
    }
    ensemble_t *p=e;
    while(p->suiv!=NULL && p->suiv->indice<=o){
        p=p->suiv;
    }
    if(p->indice!=o){
        c->suiv=p->suiv;
        p->suiv=c;
    }
    else
        printf("\n\nLe point est déjà dans l'ensemble.\n");
    return e;
}

/**
 * FONCTION D'AJOUT DE POINT DANS UN UNIVERS 
**/

univers *ajouterPoint(univers *u, point *p){
    u->taille=u->taille+1;
    u->point=realloc(u->point,sizeof(point *)*u->taille);
    u->point[u->taille-1]=p;
    return u;
}
/**
 * FONCTION PERMETTANT DE VOIR SI LE POINT
 * EXISTE DANS L'UNIVERS
 * SI OUI, RETOURNE L'INDICE DE CE DERNIER
**/
int existUnivers(univers *u, point *p){
    int i,j;
    for(i=0;i<u->taille;i++){
        for(j=0;j<3;j++){
            if(u->point[i][j]==p[j]){
                if(j==2){
                    printf("\nLe point est déjà dans l'univers.\n");
                    return i;
                }
            }     
            else
                break;
        }
    }
    return -1;
}

/**
 * AJOUT DU CENTRE À UN ENSEMBLE 
 * SI LE POINT N'EXISTE PAS
 * AJOUTE CE DERNIER À L'UNIVERS 
 **/
ensemble_t* ajouterCentre(ensemble_t *ens, univers *u){
    point *p=(point *)malloc(sizeof(int)*3);
    ensemble_t *tmp=ens;
    int i=0,j=0;
    for(i=0;i<3;i++){
        p[i]=0;
    }
    while(tmp != NULL){
        for(i=0;i<3;i++){
            p[i]=p[i]+(int) u->point[tmp->indice][i];
        }
        j++;
        tmp=tmp->suiv;
    }
    for(i=0;i<3;i++){
        p[i]=p[i]/j;
    }
    // Vérifie si le point existe
    int indice=existUnivers(u,p);
    if(indice!=-1){
        ens=ajouterElement(indice,ens);
        return ens;
    }
    // ajoute le point
    u=ajouterPoint(u,p);
    ens=ajouterElement(u->taille-1,ens);
    return ens;
}
/**
 * OPÉRATION SUR 2 ENSEMBLES UNION/INTERSECTION
**/
ensemble_t* unionE(ensemble_t *e1, ensemble_t *e2){
    ensemble_t *e;
    e=NULL;
    ensemble_t *p1=e1;
    ensemble_t *p2=e2;
    while(p1!=NULL && p2!=NULL){
        if(p1->indice == p2->indice){
            e=ajouterElement(p1->indice,e);
            p1=p1->suiv;
            p2=p2->suiv;
        }
        else if(p1->indice<p2->indice){
            e=ajouterElement(p1->indice,e);
            p1=p1->suiv;
        } 
        else{
            e=ajouterElement(p2->indice,e);
            p2=p2->suiv;
        }
    }
    if(p1!=NULL){
        while(p1!=NULL){
            e=ajouterElement(p1->indice,e);
            p1=p1->suiv;
        }
    }
    else{
        while(p2!=NULL){
            e=ajouterElement(p2->indice,e);
            p2=p2->suiv;
        }
    }
    return e;
    
}

ensemble_t* interE(ensemble_t *e1, ensemble_t *e2){
    ensemble_t *e;
    e=NULL;
    ensemble_t *p1=e1;
    ensemble_t *p2=e2;
    while(p1!=NULL && p2!=NULL){
        if(p1->indice == p2->indice){
            e=ajouterElement(p1->indice,e);
            p1=p1->suiv;
            p2=p2->suiv;
        }
        else if(p1->indice<p2->indice){
            p1=p1->suiv;
        } 
        else{
            p2=p2->suiv;
        }
    }
    return e;
    
}

/**
 * LECTURE DE L'EXPRESSION ET
 * APPLICATION
**/
void expression(univers *u, ensemble_t **ens){
    char c[100];
    // Saisie de l'expression
    printf("\nSaisir une expression :\n");
    scanf("%s",c);
    char operande[50];
    char operante[50];
    int i=0,y=0,j=0;
    int centre=0;
    // Séparation de l'opérade et opérante
    for(i=0;c[i]!='\0';i++){
        if(c[i]=='i' || c[i]=='u'){
            operande[j]=c[i];
            j++;
        }
        else if(c[i]>= '0' && c[i]<='2'){
            operante[y]=c[i]-'0';
            y++;
        }
        else if(c[i]=='a')
            centre++;
    }
    ensemble_t *e;
    e=NULL;
    // Initialisation
    if(operande[0]=='i')
        e=interE(ens[operante[0]],ens[operante[1]]);
    else if(operande[1]=='u')
        e=unionE(ens[operante[0]],ens[operante[1]]);
    // Calcul de l'expression
    for(i=1;i<j;i++){
        if(operande[i]=='i')
            e=interE(e,ens[operante[i+1]]);
        else if(operande[i]=='u')
            e=unionE(e,ens[operante[i+1]]);
    }
    //Ajout du centre si a dans l'expression
    for(i=0;i<centre;i++){
        printf("\n<------ Centre %d ------->\n",i);
        e=ajouterCentre(e,u);
    }
    printf("\n\n<------ RÉSULTAT ------>\n");
    afficheEnsembleDePoint(e,u);
    freeEnsemble(e);
}

/**
 * FONCTION PERMETTANT DE LIBÉRÉE LA MÉMOIRE 
**/
void freeUnivers(univers* u){
    int i,j;
    for(i=0;i<u->taille;i++){
        for(j=0;j<3;j++){
            u->point[i][j]=0;
        }
        free(u->point[i]);
    }
    free(u->point);
    u->taille=0;
    free(u);
}

int freeEnsemble(ensemble_t *ens){
    if(ens->suiv==NULL){
        ens->indice=0;
        free(ens);
        return 1;
    }
    if(freeEnsemble(ens->suiv)){
        ens->indice=0;
        ens->suiv=NULL;
        free(ens);
        return 1;
    }
    return 0;
}

void freeAllEnsemble(ensemble_t **ens){
    int i;
    for(i=0;i<3;i++){
        freeEnsemble(ens[i]);
    }
    free(ens);
}