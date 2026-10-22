#include "functii.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node* creare_nod(double valoare) {
    struct Node* nou=(struct Node*)malloc(sizeof(struct Node));
    if(nou!=NULL) {
        nou->valoare=valoare;
        nou->randament=0.0;
        nou->next=NULL;
    }
    return nou;
}

void adaugare_final(struct Node** head, double valoare) {
    struct Node* nou=creare_nod(valoare);
    
    if (*head == NULL) {
        *head=nou;
        return;
    }
    
    struct Node* curent=*head;
    while(curent->next!=NULL)
        curent=curent->next;

        curent->next=nou;
}

void calcul_randament(struct Node* head) {
    if(head==NULL || head->next==NULL)
    return;

    struct Node* curent=head;

    while(curent->next!=NULL) {
        if(curent->valoare!=0)
            curent->next->randament=(curent->next->valoare-curent->valoare)/curent->valoare;
        else curent->next->randament=0.0;

        curent=curent->next;
    }
}

double calcul_randMediu(struct Node* head, int N) {
    if(head==NULL || head->next==NULL)
    return 0.0;

    double suma=0.0;
    struct Node* curent=head->next;

    while(curent!=NULL) {
        suma+=curent->randament;
        curent=curent->next;
    }
    return suma/N;
}

double calcul_volatilitate(struct Node* head, double medie, int N) {
    if(head==NULL || head->next==NULL)
    return 0.0;

    double sumaPatrate=0.0;
    struct Node* curent=head->next;

    while(curent!=NULL) {
        sumaPatrate+=pow(curent->randament-medie,2);
        curent=curent->next;
    }
    return sqrt(sumaPatrate/N);
}

void eliberare_lista(struct Node* head) {
    while(head!=NULL) {
        struct Node* temp=head;
        head=head->next;
        free(temp);
    }
}

void task1(FILE *fin, FILE *fout) {
    int N=0;
    struct Node* lista=NULL;
    double val;
    if(fscanf(fin, "%d", &N)==1) {
        for(int i=0;i<N;i++)
            if(fscanf(fin, "%lf", &val)==1)
                adaugare_final(&lista, val);
        }
        if(N>=2) {
            calcul_randament(lista);
            double medie=calcul_randMediu(lista, N-1);
            double volatilitate=calcul_volatilitate(lista, medie, N-1);
            double sharpe_ratio=0.0;

            if(volatilitate!=0)
                sharpe_ratio=medie/volatilitate;

            fprintf(fout, "%.3lf\n", ((int)(medie*1000))/1000.0);
            fprintf(fout, "%.3lf\n", ((int)(volatilitate*1000))/1000.0);
            fprintf(fout, "%.3lf\n", ((int)(sharpe_ratio*1000))/1000.0);
    }
    eliberare_lista(lista);
}