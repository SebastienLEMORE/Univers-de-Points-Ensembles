#include <stdio.h>
#include <stdlib.h>
#include "geo.h"

/**
 * AFFICHAGE D'UN POINT 
**/
void affichePoint(point *p){
    int i;
    printf("X : %d  Y : %d Z : %d\n",p[0],p[1],p[2]);
}
/**
 * LECTURE D'UN POINT 
**/
point *lirePoint(){
    point *p=(point *) malloc(sizeof(int)*3);
    printf("X : ");
    scanf("%d",&p[0]);
    printf("Y : ");
    scanf("%d",&p[1]);
    printf("Z : ");
    scanf("%d",&p[2]);
    printf("\n");
    return p;
}