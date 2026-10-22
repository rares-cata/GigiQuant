#include "functii.h"
#include <stdio.h>
#include <stdlib.h>

long long semn(long long x) {
    if(x<0)
        return -x;
    return x;
}

long long cmmdc(long long a, long long b) {
    a=semn(a);
    b=semn(b);
    while(b) {
        long long temp=b;
        b=a%b;
        a=temp;
    }
    return a;
}

void simplificare(long long n, long long d, Fractie *f) {
    if(d<0) {
        n=-n;
        d=-d;
    }
    long long g=cmmdc(n,d);
    if(g==0) {
        f->num=0;
        f->den=1;
        return;
    }
    f->num=n/g;
    f->den=d/g;
}

void adunare(const Fractie *a, const Fractie *b, Fractie *rez) {
    if(a->num==0) {
        rez->num=b->num;
        rez->den=b->den;
        return;
    }
    if(b->num==0) {
        rez->num=a->num;
        rez->den=a->den;
        return;
    }
    long long g1=cmmdc(a->den, b->den);
    long long lcm=(a->den/g1)*b->den;
    long long n=a->num*(lcm/a->den)+b->num*(lcm/b->den);
    simplificare(n, lcm, rez);
}

void inmultire(const Fractie *a, const Fractie *b, Fractie *rez) {
    if(a->num==0 || b->num==0) {
        simplificare(0, 1, rez);
        return;
    }
    long long g1=cmmdc(semn(a->num), b->den);
    long long g2=cmmdc(semn(b->num), a->den);

    long long n=(a->num/g1)*(b->num/g2);
    long long d=(a->den/g2)*(b->den/g1);

    simplificare(n, d, rez);
}

int index(int *state_id, int *num_state, int id) {
    for(int i=0;i<*num_state;i++)
        if(state_id[i]==id)
            return i;
    state_id[*num_state]=id;
    (*num_state)++;
    return (*num_state)-1;
}

void Markov(int N, double d, int k, double p_start, double p_target, const double *preturi, FILE *fout) {
    int max_stari=N+2;
    int *state_id=(int*)malloc(max_stari*sizeof(int));
    int num_state=0;

    int **T=(int**)malloc(max_stari*sizeof(int*));
    for(int i=0;i<max_stari;i++) {
        T[i]=(int*)malloc(max_stari*sizeof(int));
        for(int j=0;j<max_stari;j++)
            T[i][j]=0;
    }
    int *grad_iesire=(int*)malloc(max_stari*sizeof(int));
    for(int i=0;i<max_stari;i++)
        grad_iesire[i]=0;

        for(int i=0;i<N-1;i++) {
            int u_id=(int)(preturi[i]/d);
            int v_id=(int)(preturi[i+1]/d);

            int u=index(state_id, &num_state, u_id);
            int v=index(state_id, &num_state, v_id);

            T[u][v]++;
            grad_iesire[u]++;
        }
    int start=(int)(p_start/d);
    int target=(int)(p_target/d);
    int start_ind=index(state_id, &num_state, start);
    int target_ind=index(state_id, &num_state, target);

    Fractie **prob=(Fractie**)malloc(max_stari*sizeof(Fractie*));
    Fractie **prob_urm=(Fractie**)malloc(max_stari*sizeof(Fractie*));
    for(int i=0;i<max_stari;i++) {
        prob[i]=(Fractie*)malloc(sizeof(Fractie));
        prob_urm[i]=(Fractie*)malloc(sizeof(Fractie));
    }
    Fractie *t_prob=(Fractie*)malloc(sizeof(Fractie));
    Fractie *p_trans=(Fractie*)malloc(sizeof(Fractie));
    Fractie *temp_urm=(Fractie*)malloc(sizeof(Fractie));

    for(int i=0;i<num_state;i++)
        simplificare(0, 1, prob[i]);
    simplificare(1, 1, prob[start_ind]);

    for(int i=1;i<=k;i++) {
        const Fractie *rez=prob[target_ind];
        if(rez->num==0) 
            fprintf(fout, "0");
        else if(rez->den==1)
            fprintf(fout, "%lld", rez->num);
        else fprintf(fout, "%lld/%lld", rez->num, rez->den);

        if(i==k)
            break;
        fprintf(fout, "\n");
        for(int j=0;j<num_state;j++)
            simplificare(0, 1, prob_urm[j]);
        for(int x=0;x<num_state;x++) {
            if(grad_iesire[x]>0) {
                for(int y=0;y<num_state;y++) {
                    if(T[x][y]>0) {
                        simplificare(T[x][y], grad_iesire[x], t_prob);
                        inmultire(prob[x], t_prob, p_trans);
                        adunare(prob_urm[y], p_trans, temp_urm);
                        
                        prob_urm[y]->num=temp_urm->num;
                        prob_urm[y]->den=temp_urm->den;
                    }
                } 
            } else {
                adunare(prob_urm[x], prob[x], temp_urm);
                prob_urm[x]->num=temp_urm->num;
                prob_urm[x]->den=temp_urm->den;
            }
        }
        for(int i1=0;i1<num_state;i1++) {
            prob[i1]->num=prob_urm[i1]->num;
            prob[i1]->den=prob_urm[i1]->den;
        }
    }
    free(t_prob);
    free(p_trans);
    free(temp_urm);
    for(int i=0;i<max_stari;i++) {
        free(prob[i]);
        free(prob_urm[i]);
        free(T[i]);
    }
    free(prob);
    free(prob_urm);
    free(grad_iesire);
    free(T);
    free(state_id);
}

void task4(FILE *fin, FILE *fout) {
    int N,k;
    double d,p_start,p_target;
    if(fscanf(fin, "%d", &N)==1) {
        fscanf(fin, "%lf", &d);
        fscanf(fin, "%d", &k);
        fscanf(fin, "%lf", &p_start);
        fscanf(fin, "%lf", &p_target);

        double *preturi=(double*)malloc(N*sizeof(double));
        for(int i=0;i<N;i++)
            fscanf(fin, "%lf", &preturi[i]);
        Markov(N, d, k, p_start, p_target, preturi, fout);
        free(preturi);
    }
}