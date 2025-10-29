#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int calculerPGCD(int nombre1, int nombre2);
bool determinerEstPremier(int nombre);
int calculerPeriode(int x0, int a, int c, int m);
void genererSuite(int x0, int a, int c, int m);

int main(void) {
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

    if (periode == -1) {
        printf("[ERREUR] : l'allocation de la memoire a echouee\n\n");
    } else {
        printf("La periode de la suite est de %d\n\n", periode);
    }

    /* Generation de la suite de nombres pseudo-aleatoires */

    printf("\n-- GENERATION DE LA SUITE PSEUDO-ALEATOIRE --\n\n");

    genererSuite(x0, a, c, m);

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
    int periode;
    int x = x0;
    int etape = 0;

    int* suite = malloc(m * sizeof(int));

    if (suite == NULL) {
        return -1;
    }

    for (int i = 0; i < m; i++) {
        suite[i] = -1;
    }

    while (suite[x] == -1) {
        suite[x] = etape;
        x = (a * x + c) % m;
        etape++;
    }

    periode = etape - suite[x];

    free(suite);

    return periode;
}

void genererSuite(int x0, int a, int c, int m) {
    int x = x0;

    printf("%d", x);

    for (int i = 1; i < m; i++) {
        x = (a * x + c) % m;

        printf(" ");
        printf("%d", x);
    }

    printf("\n\n");
}