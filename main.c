#include <stdio.h>
#include <stdlib.h>
#include "ensembleDePoints.h"

int main(){
    int i,n;
    univers *u=initUnivers();
    afficheUnivers(u);
    
    printf("\nNombre d'indice dans l'ensemble : ");
    do{
        scanf("%d",&n);
    }while(n<1);

    ensemble_t **ens=initEnsemble(u,n);
    
    printf("\n\n<------------------------------ INITIALISATION ------------------------------>");
    afficheUnivers(u);
    afficheTousEnsembleDePoints(u,ens);

    printf("\n\n<------------------------------ CALCUL DU CENTRE ------------------------------>");
    for(i=0;i<3;i++){
        ens[i]=ajouterCentre(ens[i],u);
    }
    afficheUnivers(u);
    afficheTousEnsembleDePoints(u,ens);
    
    expression(u,ens);
    
    freeUnivers(u);
    freeAllEnsemble(ens);

    return 0;
}