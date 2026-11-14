#include <stdio.h>
#include <stdlib.h>
#include "graf.h"

#include "debugmalloc.h"

Graf *grafBeolvas(const char *fajlnev){
    if(fajlnev == NULL){
        return NULL;
    }

    FILE * fptr = fopen(fajlnev,"r");
    if(fptr == NULL){
        return NULL;
    }
    Graf* newGraf = createGraf();
    
    if(newGraf == NULL){
        fclose(fptr); 
        return NULL;
    }
    char line[100];
    while(fgets(line, 100, fptr)){
        int src, dest;
        double weight;
        if(sscanf(line,"%d;%d;%lf", &src, &dest, &weight) != 3){
            fclose(fptr);
            freeGraf(newGraf);
            return NULL;
        }
        if(csucsFind(newGraf, src) == NULL){
            if(csucsHozzad(newGraf, src) != 1){
                fclose(fptr); 
                freeGraf(newGraf);
                return NULL;
            }
        } 
        if(csucsFind(newGraf, dest) == NULL){
            if(csucsHozzad(newGraf, dest) != 1){
                fclose(fptr); 
                freeGraf(newGraf);
                return NULL;
            };
        }
        if(elHozzaad(newGraf, src, dest, weight) != 1){
            fclose(fptr); 
            freeGraf(newGraf);
            return NULL;
        }
    }         
    fclose(fptr); 
    return newGraf;
}
