#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define LONGUEUR_SUITE 1000

/*
struct Suite {
    int valeur;
    struct Suite* suivant;
};
*/

int calculerPGCD(int nombre1, int nombre2);
bool determinerEstPremier(int nombre);
int calculerPeriode(int x0, int a, int c, int m);
void genererSuite(double* suiteXn, int x0, int a, int c, int m);
void calculerUn(double suiteXn[], double suiteUn[], int m);
void calculerYn(double suiteUn[], double suiteYn[]);
void frequence(double suiteYn[]);
void test(void);

/*
void ajouterDansListe(struct Suite** suite, int x);
*/


int main(void) {
    /* Test du programme */

    test();

    /* Declaration des coefficients */

    int x0, a, c, m;

    /* Initialisation des valeurs des coefficients */

    printf("-- INITIALISATION DES VALEURS DES COEFFICIENTS --\n\n");

    printf("Valeur du coefficient m : ");
    scanf_s("%d", &m);

    while (m <= 0) {
        printf("[ERREUR] : la valeur du coefficient m doit etre > 0\n\n");

        printf("Valeur du coefficient m : ");
        scanf_s("%d", &m);
    }

    printf("Valeur du coefficient a : ");
    scanf_s("%d", &a);

    while (a < 0 || a >= m) {
        printf("[ERREUR] : la valeur du coefficient a doit etre >= 0 et < m\n\n");

        printf("Valeur du coefficient a : ");
        scanf_s("%d", &a);
    }

    printf("Valeur du coefficient c : ");
    scanf_s("%d", &c);

    while (c < 0 || c >= m) {
        printf("[ERREUR] : la valeur du coefficient c doit etre >= 0 et < m\n\n");

        printf("Valeur du coefficient c : ");
        scanf_s("%d", &c);
    }

    printf("Valeur du coefficient x0 : ");
    scanf_s("%d", &x0);

    while (x0 < 0 || x0 >= m) {
        printf("[ERREUR] : la valeur du coefficient x0 doit etre >= 0 et < m\n\n");

        printf("Valeur du coefficient x0 : ");
        scanf_s("%d", &x0);
    }

    /* Verification des hypotheses du theoreme de Hull-Dobell */

    printf("-- VERIFICATION DES HYPOTHESES DU THEOREME DE HULL-DOBELL --\n\n");

    bool estOK = true;

    // Hypothese 1

    if (calculerPGCD(c, m) != 1) {
        printf("[HYPOTHESE 1] : c et m ne sont pas premiers entre eux\n\n");
        estOK = false;
    } else {
        printf("[HYPOTHESE 1] : c et m sont premiers entre eux\n\n");
    }

    // Hypothese 2

    for (int p = 2; p <= m; p++) {
        if (determinerEstPremier(p) && (m % p) == 0) {
            if ((a - 1) % p != 0) {
                printf("[HYPOTHESE 2] : (a - 1) n'est pas multiple de %d\n\n", p);
                estOK = false;
            }
        }
    }

    if (estOK) {
        printf("[HYPOTHESE 2] : (a - 1) est multiple de tous les facteurs premiers de m\n\n");
    }

    // Hypothese 3

    if (m % 4 == 0) {
        if ((a - 1) % 4 != 0) {
            printf("[HYPOTHESE 3] : m est multiple de 4 mais (a-1) ne l'est pas\n\n");
            estOK = false;
        } else {
            printf("[HYPOTHESE 3] : m et (a-1) sont multiples de 4\n\n");
        }
    } else {
        printf("[HYPOTHESE 3] : m n'est pas multiple de 4\n\n");
    }

    // Conclusion

    if (estOK) {
        printf("Les coefficients remplissent les conditions du theoreme de Hull-Dobell\n\n");
    } else {
        printf("Les coefficients ne remplissent pas toutes les conditions du theoreme du Hull-Dobell\n\n");
    }

    /* Calcul de la periode de la suite */

    printf("-- CALCUL DE LA PERIODE DE LA SUITE --\n\n");

    int periode;

    if (estOK) {
        periode = m;
    } else {
        periode = calculerPeriode(x0, a, c, m);
    }

    printf("La periode de la suite est de %d\n\n", periode);

    /* Generation de la suite de nombres pseudo-aleatoires */

    printf("-- GENERATION DE LA SUITE PSEUDO-ALEATOIRE --\n\n");

    double suiteXn[LONGUEUR_SUITE];

    genererSuite(suiteXn, x0, a, c, m);

    /* Test des frequences */

    printf("-- TEST DES FREQUENCES --\n\n");

    double suiteUn[LONGUEUR_SUITE], suiteYn[LONGUEUR_SUITE];

    calculerUn(suiteXn, suiteUn, m);
    calculerYn(suiteUn, suiteYn);

    frequence(suiteYn);

    return 0;
}

int calculerPGCD(int nombre1, int nombre2) {
    int t;

    while (nombre2 != 0) {
        t = nombre1 % nombre2;
        nombre1 = nombre2;
        nombre2 = t;
    }

    return nombre1;
}

bool determinerEstPremier(int nombre) {
    if (nombre < 2) {
        return false;
    }

    for (int i = 2; i * i <= nombre; i++) {
        if (nombre % i == 0) {
            return false;
        }
    }

    return true;
}

int calculerPeriode(int x0, int a, int c, int m) {
    int i = 0;
    int x = (a * x0 + c) % m;

    while (x != x0) {
        int next = (a * x + c) % m;
        x = next;

        i++;
    }

    return i + 1;
}

void genererSuite(double* suiteXn, int x0, int a, int c, int m) {
    int x = x0;

    suiteXn[0] = x;
    printf("%d", x);

    for (int i = 1; i < LONGUEUR_SUITE; i++) {
        x = (a * x + c) % m;
        printf(" %d", x);
        suiteXn[i] = x;
    }

    printf("\n\n");
}

void calculerUn(double suiteXn[], double suiteUn[], int m) {
    for (int i = 0; i < LONGUEUR_SUITE; i++) {
        suiteUn[i] = suiteXn[i] / m;
    }
}

void calculerYn(double suiteUn[], double suiteYn[]) {
    for (int i = 0; i < LONGUEUR_SUITE; i++) {
        suiteYn[i] = ceil(suiteUn[i] * 10);
    }
}

int trouverRepetition(double suiteYn[], int x) {
    int repetition = 0;

    for (int i = 0; i < LONGUEUR_SUITE; i++) {
        if (suiteYn[i] == x) {
            repetition++;
        }
    }

    return repetition;
}

void frequence(double suiteYn[]) {
    int totalRi = 0;
    double totalPi = 0;
    double totalNpi = 0;
    double totalKhi = 0;

    printf("Xi1 - ri - pi - n.pi - (ri-n.pi)2/(n.pi)\n");

    printf("******************************\n");

    for (int i = 0; i < 10; i++) {
        int ri = trouverRepetition(suiteYn, i);
        double pi = 0.1;
        double npi = LONGUEUR_SUITE * pi;
        double khi = pow(ri - npi, 2) / npi;

        totalRi += ri;
        totalPi += pi;
        totalNpi += npi;
        totalKhi += khi;

        printf("%d - %d - 1/10 - %.lf - %.2lf\n", i, ri, npi, khi);
    }

    printf("******************************\n");

    printf("Total - %d - %.lf - %.lf - %.2lf\n", totalRi, totalPi, totalNpi, totalKhi);
}

/*
void ajouterDansListe(struct Suite** suite, int x) {
    struct Suite* nouveau = malloc(sizeof(struct Suite));

    if (!nouveau) {
        return;
    }

    nouveau->valeur = x;
    nouveau->suivant = NULL;

    if (*suite == NULL) {
        *suite = nouveau;
    } else {
        struct Suite* courant = *suite;

        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }

        courant->suivant = nouveau;
    }
}
*/

void test(void) {
    /* Verification des hypotheses du theoreme de Hull-Dobell */

    // Hypothese 1

    assert(calculerPGCD(3, 5) == 1);
    assert(calculerPGCD(15, 28) == 1);
    assert(calculerPGCD(25, 36) == 1);
    assert(calculerPGCD(33, 56) == 1);
    assert(calculerPGCD(39, 80) == 1);

    // Hypothese 2

    assert(determinerEstPremier(2));
    assert(determinerEstPremier(13));
    assert(determinerEstPremier(101));
    assert(determinerEstPremier(137));
    assert(determinerEstPremier(199));

    /* Calcul de la periode de la suite */

    assert(calculerPeriode(35, 13, 65, 100) == 4);
    assert(calculerPeriode(3, 5, 5, 8) == 8);
    assert(calculerPeriode(7, 7, 7, 8) == 2);
    assert(calculerPeriode(7, 5, 3, 16) == 16);

    /* Calcul de la periode de la suite */

    /* Generation de la suite de nombres pseudo-aleatoires */

    printf("Tous les tests se sont bien passes.\n");
}