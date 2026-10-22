#include "functii.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int extragereNumar(const char *nume) {
    int nr=0;
    for(int i=0;nume[i]!='\0';i++)
        if(cifra(nume[i]))
            nr=nr*10+(nume[i]-'0');

    return nr;
}

int main(int argc, const char *argv[]) {
    FILE *fin=fopen(argv[1], "r");
    FILE *fout=fopen(argv[2], "w");
    int nrFisier=extragereNumar(argv[1]);

    if(nrFisier>=1 && nrFisier<=5)
        task1(fin, fout);
    else if(nrFisier>=6 && nrFisier<=10)
        task2(fin, fout);
    else if(nrFisier>=11 && nrFisier<=15)
        task3(fin, fout);
    else if(nrFisier>=16 && nrFisier<=20)
        task4(fin, fout);

    fclose(fin);
    fclose(fout);
    return 0;
}