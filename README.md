# GigiQuant

Acest proiect este structurat sub forma unei serii de interviuri tehnice de manager de portofoliu la compania fictiva "GigiQuant". Scopul principal este aplicarea diverselor structuri de date pentru rezolvarea unor probleme specifice domeniului financiar.

Proiectul contine 4 task-uri principale care analizeaza si optimizeaza date financiare:
* **Task 1:** Modeleaza evolutia unui portofoliu folosind liste simplu inlantuite pentru a calcula randamentul, volatilitatea si indicatorul Sharpe Ratio.
* **Task 2:** Identifica oportunitati de arbitraj intre trei piete diferite, folosind stive pentru stocarea preturilor cronologice si o coada pentru salvarea oportunitatilor.
* **Task 3:** Optimizeaza un portofoliu prin diversificare, gasind actiuni cu evolutii opuse cu ajutorul arborilor binari.
* **Task 4:** Modeleaza comportamentul preturilor pe termen mediu folosind un graf/matrice de tranzitie pentru a determina algoritmic probabilitatea ca o actiune sa atinga un pret tinta.

## Structura fisierelor
Fisierele principale se afla in folderul `src/`:
* `main.c`: Punctul de intrare in program. Se ocupa exclusiv de deschiderea fisierelor, citirea si extragerea datelor si delegarea executiei catre task-ul corespunzator.
* `functii.h`: Header-ul global care contine definitiile tuturor structurilor de date si semnaturile functiilor.
* `functii.c`: Contine rezolvarea primului task.
* `arbitraj.c`: Implementarea structurilor de tip stiva si coada, precum si logica de identificare a ineficientelor de pe piata.
* `task3.c`: Implementarea si parcurgerea arborilor binari pentru gruparea actiunilor complementare.
* `task4.c`: Implementarea alogoritmului pe Lanturi Markov si operatii matematice pe fractii ireductibile.

## Compilare si rulare
Proiectul foloseste un `Makefile` automatizat.

**Compilare:** Deschideti terminalul in directorul radacina al proiectului si rulati comanda:
```
make
```
Aceasta comanda va compila toate fisierele din folderul `src/` si va genera executabilul `test` in folderul `bin/`.

**Rulare:** Programul primeste doua argumente in linia de comanda: fisierul de intrare si fisierul de iesire. Rulati executabilul astfel:
```
./bin/test drum/catre/input.txt drum/catre/output.txt
```