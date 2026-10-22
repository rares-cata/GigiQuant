#include <stdio.h>
struct Node {
    double valoare;
    double randament;
    struct Node* next;
};

struct Node* creare_nod(double valoare);
void adaugare_final(struct Node** head, double valoare);
void eliberare_lista(struct Node* head);
void calcul_randament(struct Node* head);
double calcul_randMediu(struct Node* head, int N);
double calcul_volatilitate(struct Node* head, double medie, int N);

void oportunitati(
    const double *pretP1, int n1, const char *numeP1,
    const double *pretP2, int n2, const char *numeP2, 
    const double *pretP3, int n3, const char *numeP3,
    FILE *fout);

void portofoliu(const char nume[][50], const double pret[][100], int N, int zile, FILE *fout);

typedef struct {
    long long num;
    long long den;
}Fractie;

void Markov(int N, double d, int k, double p_start, double p_target, const double *preturi, FILE *fout);

int cifra(char a);
int extragereNumar(const char *nume);
double conversie(const char *s);

void task1(FILE *fin, FILE *fout);
void task2(FILE *fin, FILE *fout);
void task3(FILE *fin, FILE *fout);
void task4(FILE *fin, FILE *fout);