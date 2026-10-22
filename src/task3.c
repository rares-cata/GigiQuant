#include "functii.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StockList {
    char symbol[20];
    struct StockList *next;
}StockList;

typedef struct TreeNode {
    StockList *stocks;
    struct TreeNode *left;
    struct TreeNode *right;
    int depth;
}TreeNode;

typedef struct {
    int indx1, indx2;
    char sym1[20], sym2[20];
}Pair;

StockList* nodStock(const char* symbol) {
    StockList* nod=(StockList*)malloc(sizeof(StockList));
    strcpy(nod->symbol, symbol);
    nod->next=NULL;
    return nod;
}

void adaugaStock(StockList **top, const char* symbol) {
    StockList* nod=nodStock(symbol);
    nod->next=*top;
    *top=nod;
}

TreeNode* arbore(int depth) {
    TreeNode* nod=(TreeNode*)malloc(sizeof(TreeNode));
    nod->stocks=NULL;
    nod->left=NULL;
    nod->right=NULL;
    nod->depth=depth;
    return nod;
}

void eliberareArbore(TreeNode* root) {
    if(root==NULL)
        return;

    eliberareArbore(root->left);
    eliberareArbore(root->right);

    StockList* curent=root->stocks;
    while(curent!=NULL) {
        StockList* temp=curent;
        curent=curent->next;
        free(temp);
    }
    free(root);
}

void creareArbore(TreeNode* root, const char nume[][50], const double pret[][100], int N, int zile) {
    for(int i=0;i<N;i++) {
        TreeNode* curent=root;
        adaugaStock(&curent->stocks, nume[i]);

        for(int j=1;j<zile;j++) {
            if(pret[i][j]>=pret[i][j-1]) {
                if(curent->right==NULL)
                    curent->right=arbore(j);
                curent=curent->right;
            } else {
                if(curent->left==NULL)
                    curent->left=arbore(j);
                curent=curent->left;
            }
            adaugaStock(&curent->stocks, nume[i]);
        }
    }
}

int pozitie(const char nume[][50], int N, const char* symbol) {
    for(int i=0;i<N;i++)
        if(strcmp(nume[i], symbol)==0)
            return i;
    return -1;
}

void gasirePereche(TreeNode* n1, TreeNode* n2, int adancime, Pair* perechi, int* contor, const char nume[][50], int N) {
    if(n1==NULL || n2==NULL)
        return;
    if(n1->depth==adancime && n2->depth==adancime) {
        StockList* s1=n1->stocks;
        while(s1!=NULL) {
            StockList* s2=n2->stocks;
            while(s2!=NULL) {
                int indx_left=pozitie(nume, N, s1->symbol);
                int indx_right=pozitie(nume, N, s2->symbol);
                int i1, i2;
                if(indx_left<indx_right)
                    i1=indx_left;
                else i1=indx_right;
                if(indx_left<indx_right)
                    i2=indx_right;
                else i2=indx_left;
                if(i1!=i2) {
                    int exista=0;
                    for(int i=0;i<*contor;i++)
                        if(perechi[i].indx1==i1 && perechi[i].indx2==i2) {
                            exista=1;
                            break;
                        }
                    if(!exista) {
                        Pair* pereche=&perechi[*contor];
                        pereche->indx1=i1;
                        pereche->indx2=i2;
                        strcpy(pereche->sym1, nume[i1]);
                        strcpy(pereche->sym2, nume[i2]);
                        (*contor)++;
                    }
                }
                s2=s2->next;
            }
            s1=s1->next;
        }
        return;
    }

    if(n1->left && n2->right)
        gasirePereche(n1->left, n2->right, adancime, perechi, contor, nume, N);
    if(n1->right && n2->left)
        gasirePereche(n1->right, n2->left, adancime, perechi, contor, nume, N);
}

void sortare(Pair perechi[], int n) {
    for(int i=0;i<n-1;i++) {
        for(int j=0;j<n-i-1;j++) {
            if(perechi[j].indx1>perechi[j+1].indx1 || (perechi[j].indx1==perechi[j+1].indx1 && perechi[j].indx2>perechi[j+1].indx2)) {
                Pair temp=perechi[j];
                perechi[j]=perechi[j+1];
                perechi[j+1]=temp;
            }
        }
    }
}

void portofoliu(const char nume[][50], const double pret[][100], int N, int zile, FILE *fout) {
    if(zile<=1 || N==0)
        return;

    TreeNode* root=arbore(0);
    creareArbore(root, nume, pret, N, zile);
    Pair perechi[1000];
    int nr_perechi=0;

    gasirePereche(root, root, zile-1, perechi, &nr_perechi, nume, N);
    sortare(perechi, nr_perechi);

    for(int i=0;i<nr_perechi;i++) {
        if(i==nr_perechi-1)
            fprintf(fout, "%s-%s", perechi[i].sym1, perechi[i].sym2);
        else fprintf(fout, "%s-%s\n", perechi[i].sym1, perechi[i].sym2);
    }
    eliberareArbore(root);
}

int cifra(char a) {
    if(a>='0' && a<='9')
        return 1;
    return 0;
}

double conversie(const char *s) {
    double rez=0.0;
    double factor=1.0;
    int i=0;
    int gasit=0;

    while(s[i]!='\0') {
        if(s[i]=='.')
            gasit=1;
        else if(cifra(s[i])) {
            if(!gasit)
                rez=rez*10.0+(s[i]-'0');
            else {
                factor/=10.0;
                rez=rez+(s[i]-'0')*factor;
            }
        }
        i++;
    }
    return rez; 
}

void task3(FILE *fin, FILE *fout) {
    char nume[100][50];
    double pret[100][100];
    int N=0, zile=0;
    char buffer[5000];

    if(fscanf(fin, " %4999[^\n]", buffer)==1) {
        const char *p=strtok(buffer, ", \r\n");
        while(p!=NULL) {
            strcpy(nume[N], p);
            N++;
            p=strtok(NULL, ", \r\n");
        }
        zile=0;
    }
    while(fscanf(fin, " %4999[^\n]", buffer)==1) {
        if(strlen(buffer)<2)
            continue;
        int idx=0;
        const char *p=strtok(buffer, ", \r\n");
        while(p!=NULL && idx<N) {
            pret[idx][zile]=conversie(p);
            idx++;
            p=strtok(NULL, ", \r\n");
        }
        zile++;
    }
    portofoliu(nume, pret, N, zile, fout);
}