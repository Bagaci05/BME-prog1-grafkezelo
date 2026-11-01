#ifndef GRAF_H
#define GRAF_H

typedef struct El {
    int cel;
    double suly;
    struct El *kov;
} El;

typedef struct Csucs {
    int id;
    El *szomszedok;
    struct Csucs *kov;
} Csucs;

typedef struct Graf {
   Csucs *csucsok;
    int csucsCnt;
    int elCnt;
} Graf;

Graf *createGraf(void);
void freeGraf(Graf *graf);
Csucs *csucsFind(Graf const *graf, int keresettid); 
int csucsHozzad(Graf *graf, int id);
int elHozzaad(Graf *graf, int forras, int cel, double suly);
void printGraf(const Graf *graf);
#endif
