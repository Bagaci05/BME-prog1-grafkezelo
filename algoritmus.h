#ifndef ALGORITMUS_H
#define ALGORITMUS_H

#include "graf.h"

Graf *bfs(const Graf *srcGraf, int startId);
Graf *dfs(const Graf *srcGraf, int startId);

Graf *dajkstra(const Graf *srcGraf);


#endif
