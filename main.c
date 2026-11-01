#include <stdio.h>
#include <stdlib.h>
#include "graf.h"
#include "fileIo.h"

int main(int argc, char *argv[]) {
    if(argc <2){
        printf("\nA program helytelenü lett használva. Helyes használat: ./grafbejaro [inputfile.csv] <outputfile.csv>");
        return 1;
    }

   Graf* graf = grafBeolvas(argv[1]);
   printGraf(graf);
   freeGraf(graf);
}
