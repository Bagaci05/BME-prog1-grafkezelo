#include <stdio.h>
#include <stdlib.h>
#include "graf.h"
#include "debugmalloc.h"

Graf *createGraf(void){
    Graf *graf = malloc (sizeof(Graf));

    if (graf == NULL){
        return NULL; 
    }

    graf->csucsok = NULL;
    graf->csucsCnt = 0;
    graf->elCnt = 0;

    return graf;
} 

Csucs *csucsFind(Graf const *graf, int keresettid){
    Csucs *aktualis = graf->csucsok;
    while(aktualis != NULL){
        if (aktualis->id == keresettid){
            return aktualis;
        }
        aktualis = aktualis->kov;
    }
    return NULL;
}

El *elFind(Graf const *graf, int src, int dest){
    Csucs *aktualis = graf->csucsok;
    while(aktualis != NULL){
        El *vizsEl = aktualis->szomszedok;
        while(vizsEl != NULL){
            if(aktualis->id == src && vizsEl->cel == dest){
                return vizsEl;
            }
            vizsEl = vizsEl->kov;
        }
        aktualis = aktualis->kov;
    }
    return NULL;

}

int csucsHozzad(Graf *graf, int newId){
    if (graf == NULL)
        return 2;
    if(csucsFind(graf, newId) != NULL){
        return 2;
    }
    Csucs* newCsucs = malloc(sizeof(Csucs));
    if (newCsucs == NULL){
        return 0;
    }
    newCsucs -> id = newId;
    newCsucs -> szomszedok = NULL;
    newCsucs -> kov = NULL;
    Csucs* last = graf -> csucsok;
    
    if (last == NULL){
        graf->csucsok = newCsucs;
        graf->csucsCnt+=1;
        return 1;
    }
    while (last->kov != NULL ){
        last = last->kov;
    }
    last->kov = newCsucs;
    graf->csucsCnt+=1;
    return 1;
}

int elHozzaad(Graf *graf, int forras, int cel, double suly){
    if (graf == NULL || suly < 0){
        return 2;
    }
    if (csucsFind(graf, forras) == NULL || csucsFind(graf, cel)== NULL){
        return 2;
    }
    
    El *newEl = malloc(sizeof(El));

    if(newEl == NULL){return 0;}

    newEl->cel = cel;
    newEl->suly = suly;
    newEl->kov= NULL;
        
    Csucs* parent = csucsFind(graf, forras);
    if (parent->szomszedok == NULL){
        parent->szomszedok = newEl;
        graf->elCnt +=1;
        return 1;
    }

    El *lastel = parent->szomszedok;
    while (lastel->kov !=NULL){
        lastel = lastel->kov;
    }
    lastel->kov = newEl;
    graf->elCnt +=1;
    return 1;
}

void freeGraf(Graf *graf){
    if (graf == NULL){return;}

    Csucs *vizsgaltCs = graf-> csucsok;
    while(vizsgaltCs !=NULL){
        El* vizsgaltEl = vizsgaltCs->szomszedok;
        while(vizsgaltEl != NULL){
            El* tmpEl = vizsgaltEl->kov;
            free(vizsgaltEl);
            vizsgaltEl = tmpEl;
        }
        Csucs *tmpCs = vizsgaltCs->kov;
        free(vizsgaltCs);
        vizsgaltCs = tmpCs;
    }
    free(graf);
}

void printGraf(const Graf *graf){
    if (graf ==NULL){
        printf("Hibás Gráf lett printeltetve");
        return;
    }
    printf("\033[2J\033[H"); //Clear terminal
    printf("======== GRAF ADATAI ========\n");

    printf("\nÉlek száma: %d", graf->elCnt);
    printf("\nCsúcsok száma: %d\n\n", graf->csucsCnt);

    const Csucs* vizsCs= graf-> csucsok;
    while(vizsCs != NULL){
        const El* vizsEl = vizsCs->szomszedok;
        printf("\n%d: ", vizsCs->id);

        if(vizsEl == NULL){
            printf(" Nincs kimenő éle");
        }

        while(vizsEl!=NULL){
           printf("-> %d (%.2f) ", vizsEl->cel, vizsEl->suly);
           vizsEl = vizsEl->kov;
        }
        vizsCs = vizsCs->kov;
    }
    
    printf("\n===============================\n ");
}



