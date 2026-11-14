#include <stdio.h>
#include <stdlib.h>
#include "graf.h"


Graf *bfs(const Graf *srcGraf, int startId){
    if (srcGraf == NULL){
        return NULL;
    }
    Graf* bfsGraf = createGraf();
    if(bfsGraf == NULL){
        return NULL;
    }
    if( csucsFind(srcGraf, startId)== NULL){
        freeGraf(bfsGraf);
        return NULL;
    }

    int* sor = malloc(srcGraf->csucsCnt * sizeof*sor );
    if (sor == NULL){
        freeGraf(bfsGraf);
        return NULL;
    }

    int* latogatott = malloc(srcGraf->csucsCnt * sizeof*latogatott );
    if (latogatott == NULL ){
        freeGraf(bfsGraf);
        free(sor);
        return NULL;
    }

    int eleje = 0;
    int vege = 0;
    int lenLatog = 1;

    if (csucsHozzad(bfsGraf,startId)!= 1) {
        free(sor);
        free(latogatott);
        freeGraf(bfsGraf);
        return NULL;
    }
    latogatott[0] = startId;
    sor[0] = startId;
    vege=1;
    while (eleje < vege){
        int aktualis = sor[eleje++];

        Csucs *aCsucs = csucsFind(srcGraf, aktualis);

        if (aCsucs == NULL){
            free (sor);
            free(latogatott);
            freeGraf(bfsGraf);
            return NULL;
        }
        
        El* vizsEl = aCsucs->szomszedok;
        
        while(vizsEl != NULL){
           int celId= vizsEl->cel;
            int count = 0;
            for (int i = 0; i<lenLatog; i++){
                if (celId == latogatott[i]){
                    count ++;
                } 
            }
            if (count== 0){
                latogatott[lenLatog++]=celId;
                if(csucsHozzad(bfsGraf, celId)!=1){
                    free(sor);
                    free(latogatott);
                    freeGraf(bfsGraf);
                    return NULL;
                }

                if( elHozzaad(bfsGraf,aCsucs->id ,celId, vizsEl->suly) !=1){
                    free(sor);
                    free(latogatott);
                    freeGraf(bfsGraf);
                    return NULL;
                }

                sor[vege++] = celId;
            };
            vizsEl= vizsEl->kov;
        }
    }
    free(sor);
    free(latogatott);
    return bfsGraf; 
}


int dfsRekurzio(const Graf* srcGraf, Graf* dfsGraf, int aktualisId, int *Latogatott, int *lenLatog){ // TODO HIBAKEZELÉS (nem void visszatérés)
    Csucs * aCsucs = csucsFind(srcGraf, aktualisId);
    if (aCsucs == NULL){
        return 0;
    }
    El * aEl = aCsucs->szomszedok;
    while (aEl != NULL){
        int kovNode = aEl->cel; 
        int cnt = 0; 
        for (int i=0; i<*lenLatog;i++){
            if (Latogatott[i] == kovNode){
                cnt++;
            }
        }
        if(cnt == 0){
            Latogatott[*lenLatog] = kovNode;
            *lenLatog +=1;
            if(csucsHozzad(dfsGraf, kovNode) != 1){
                return 0;
            };
            if(elHozzaad(dfsGraf, aktualisId, kovNode, aEl->suly) != 1){
                return 0;
            };
            if(dfsRekurzio(srcGraf, dfsGraf, kovNode, Latogatott, lenLatog) != 1){
                return 0;
            };
        }
        aEl = aEl->kov;
    }
    return 1;
}

Graf *dfs(const Graf *srcGraf, int startId){
    if (srcGraf == NULL)
        return NULL;
    Graf* dfsGraf = createGraf();
    if (dfsGraf == NULL){
        return NULL;
    }
    if (csucsFind(srcGraf, startId) == NULL){
        freeGraf(dfsGraf);
        return NULL;
    }
    
    int* latogatott = malloc(srcGraf->csucsCnt* sizeof (int));
    if (latogatott == NULL){
        freeGraf(dfsGraf);
        return NULL;
    }
    int lenLatog=1;
    
    if(csucsHozzad(dfsGraf,startId) !=1){
        free(latogatott);
        freeGraf(dfsGraf);
        return NULL;
    }
    latogatott[0] = startId;
    
    if(dfsRekurzio(srcGraf, dfsGraf, startId, latogatott, &lenLatog) != 1){
        freeGraf(dfsGraf);
        free(latogatott);
        return NULL;
    };
    free(latogatott);
    return dfsGraf;   
}


Graf *dajkstra(const Graf *srcGraf);

