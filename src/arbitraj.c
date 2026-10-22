#include "functii.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double pretP1[10000];
double pretP2[10000];
double pretP3[10000];

struct Elem {
    double val;
    struct Elem *next;
};
typedef struct Elem Node;

void push(Node** top, double v) {
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->val=v;
    newNode->next=*top;
    *top=newNode;
}

double pop(Node** top) {
    if(*top==NULL)
        return -1.0;

    Node* temp=*top;
    double aux=temp->val;
    *top=(*top)->next;
    free(temp);

    return aux;
}

typedef struct elemCoada{
    int ziua;
    double dif;
    char piata[50];
    struct elemCoada *next;
}elemCoada;

typedef struct {
    elemCoada *front;
    elemCoada *rear;
}Coada;

Coada* creare() {
    Coada *q=(Coada*)malloc(sizeof(Coada));
    if(q!=NULL)
        q->front=q->rear=NULL;
    return q;
}

void enQueue(Coada* q, int ziua, double dif, const char* piata) {
    elemCoada* newNode=(elemCoada*)malloc(sizeof(elemCoada));
    newNode->ziua=ziua;
    newNode->dif=dif;
    strcpy(newNode->piata, piata);
    newNode->next=NULL;

    if(q->rear==NULL) {
        q->front=q->rear=newNode;
        return;
    }

    q->rear->next=newNode;
    q->rear=newNode;
}

void deQueue(Coada* q, int *ziua, double *dif, char *piata) {
    if(q->front==NULL)
        return;

    elemCoada* aux=q->front;
    *ziua=aux->ziua;
    *dif=aux->dif;
    strcpy(piata, aux->piata);
    q->front=q->front->next;

    if(q->front==NULL)
        q->rear=NULL;

    free(aux);
}

void oportunitati(
    const double *pretP1, int n1, const char *numeP1,
    const double *pretP2, int n2, const char *numeP2, 
    const double *pretP3, int n3, const char *numeP3,
    FILE *fout) {
        Node* stack1=NULL;
        Node* stack2=NULL;
        Node* stack3=NULL;

    for(int i=0;i<n1;i++)
        push(&stack1, pretP1[i]);
    for(int i=0;i<n2;i++)
        push(&stack2, pretP2[i]);
    for(int i=0;i<n3;i++)
        push(&stack3, pretP3[i]);

    Coada* posibilitati=creare();
    int ziua=1;

    while(stack1!=NULL && stack2!=NULL && stack3!=NULL) {
        double p1=pop(&stack1);
        double p2=pop(&stack2);
        double p3=pop(&stack3);

        double dif=0;
        char dif_piata[50]= "";
        int gasit=0;

        if(p1==p2 && p1!=p3) {
            dif=fabs(p1-p3);
            strcpy(dif_piata, numeP3);
            gasit=1;
        }else if(p1==p3 && p1!=p2) {
            dif=fabs(p1-p2);
            strcpy(dif_piata, numeP2);
            gasit=1;
        }else if(p2==p3 && p2!=p1) {
            dif=fabs(p2-p1);
            strcpy(dif_piata, numeP1);
            gasit=1;
        }

        if(gasit)
            enQueue(posibilitati, ziua, dif, dif_piata);

        ziua++;
    }

    while(posibilitati->front!=NULL) {
        int z;
        double d;
        char p[50];

        deQueue(posibilitati, &z, &d, p);
        fprintf(fout, "ziua %d - %.2lf - %s\n", z, d, p);
    }

    free(posibilitati);
    while(stack1!=NULL)
        pop(&stack1);
    while(stack2!=NULL)
        pop(&stack2);
    while(stack3!=NULL)
        pop(&stack3);
}

void task2(FILE *fin, FILE *fout) {
    char numeP1[50];

    if(fscanf(fin, " %49[^\n]", numeP1)==1) {
        int n1=0;
        while(fscanf(fin, "%lf", &pretP1[n1])==1)
            n1++;
        char numeP2[50];
        fscanf(fin, " %49[^\n]", numeP2);
        int n2=0;
        while(fscanf(fin, "%lf", &pretP2[n2])==1)
            n2++;
        char numeP3[50];
        fscanf(fin, " %49[^\n]", numeP3);
        int n3=0;
        while(fscanf(fin, "%lf", &pretP3[n3])==1)
            n3++;
        oportunitati(
            pretP1, n1, numeP1,
            pretP2, n2, numeP2,
            pretP3, n3, numeP3,
            fout);
    }
}