#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int determinerPGCD(int nombre1, int nombre2);
bool determinerEstPremier(int nombre);

int main(void) {
    /* Declaration des coefficients */

    int x0 = 0;
    int a = 0;
    int c = 0;
    int m = 0;

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

    if (determinerPGCD(c, m) != 1) {
        printf("[HYPOTHESE 1] : c et m ne sont pas premiers entre eux\n\n");
        estOK = false;
    } else {
        printf("[HYPOTHESE 1] : c et m sont premiers entre eux\n\n");
    }

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

    return 0;
}

int determinerPGCD(int nombre1, int nombre2) {
    int t;

    while (nombre2 != 0) {
        t = nombre1 % nombre2;
        nombre1 = nombre2;
        nombre2 = t;
    }

    return nombre1;
}

bool determinerEstPremier(int nombre) {
    if (nombre < 2) return false;

    for (int i = 2; i * i <= nombre; i++) {
        if (nombre % i == 0) return false;
    }

    return true;
}