#include "geo.h"

typedef struct Ensemble{
    int indice;
    struct Ensemble *suiv;
}ensemble_t;

typedef struct Univers{
    int taille;
    int **point;
}univers;

void afficheEnsembleDePoint(ensemble_t *e,univers *u);
void afficheTousEnsembleDePoints(univers* u, ensemble_t **ens);
void afficheUnivers(univers *u);

univers* initUnivers();
ensemble_t** initEnsemble(univers *u, int indice);

ensemble_t *ajouterElement(int o,ensemble_t *e);
univers *ajouterPoint(univers *u, point *p);

int existUnivers(univers *u, point *p);
ensemble_t* ajouterCentre(ensemble_t *ens, univers *u);

ensemble_t* unionE(ensemble_t *e1, ensemble_t *e2);
ensemble_t* interE(ensemble_t *e1, ensemble_t *e2);
void expression(univers *u, ensemble_t **ens);

void freeUnivers(univers* u);
int freeEnsemble(ensemble_t *ens);
void freeAllEnsemble(ensemble_t **ens);