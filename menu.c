#include <stdio.h>
#include <stdlib.h>
#include "graf.h"
#include "algoritmus.h"
#include "fileIo.h"

void initMenu(Graf *graf){
    int input;
    printf("\033[2J\033[H"); 
    printf("========== GRAFKEZELO ==========\n\n1. BFS bejárás\n2. DFS bejárás\n3. Dijkstra\n4. Gráf adatainak megjelenítése\n5. Kilépés\n\nVálasztás:");
    if(scanf("%d", &input) != 1 || input <1  || input >5){
        printf("hibás input");
        return;
    }


    int startNode;
    switch(input){
        case 1:
            printf("\nAdjon meg egy kezdp nodeot: ");
            scanf("%d", &startNode);
            Graf *bfsG = bfs(graf, startNode);
            printGraf(bfsG);
            freeGraf(bfsG);
            break;
        case 2: 
            printf("\nAdjon meg egy kezdő nodeot: ");
            scanf("%d", &startNode);
            Graf *dfsG = dfs(graf, startNode);
            printGraf(dfsG);
            freeGraf(dfsG);
            break;
        case 4:
            printGraf(graf);
            break;
        case 5:
            break;
    }
}  
