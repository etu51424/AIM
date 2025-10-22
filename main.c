#include <stdio.h>
#include <math.h>

int main(void) {
    /* Déclaration des coefficients */

    int x0 = 0;
    int a = 0;
    int c = 0;
    int m = 0;

    /* Initialisation des valeurs des coefficients */

    printf("Valeur du coefficient 'm' : ");
    scanf_s("%d", &m);

    do {
        printf("\nERREUR : la valeur du coefficient 'm' doit être > 0\n\n");

        printf("Valeur du coefficient 'm' : ");
        scanf_s("%d", &m);
    } while (m <= 0);

    printf("Valeur du coefficient 'a' : ");
    scanf_s("%d", &a);

    do {
        printf("\nERREUR : la valeur du coefficient 'a' doit être >= 0 et < m\n\n");

        printf("Valeur du coefficient 'a' : ");
        scanf_s("%d", &a);
    } while (a < 0 || a >= m);

    printf("Valeur du coefficient 'c' : ");
    scanf_s("%d", &c);

    do {
        printf("\nERREUR : la valeur du coefficient 'c' doit être >= 0 et < m\n\n");

        printf("Valeur du coefficient 'c' : ");
        scanf_s("%d", &c);
    } while (c < 0 || c >= m);

    printf("Valeur du coefficient 'x0' : ");
    scanf_s("%d", &x0);

    do {
        printf("\nERREUR : la valeur du coefficient 'x0' doit être >= 0 et < m\n\n");

        printf("Valeur du coefficient 'x0' : ");
        scanf_s("%d", &x0);
    } while (x0 < 0 || x0 >= m);

    return 0;
}