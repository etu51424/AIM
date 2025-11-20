#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LONGUEUR_SUITE 1000

#define POKER (10 / pow(10, 5)) // Probabilité théorique d'obtention d'un POKER
#define CARRE (450 / pow(10, 5)) // Probabilité théorique d'obtention d'un CARRE
#define FULL (900 / pow(10, 5)) // Probabilité théorique d'obtention d'un FULL
#define BRELAN (7200 / pow(10, 5)) // Probabilité théorique d'obtention d'un BRELAN
#define DOUBLE_PAIRE (10800 / pow(10, 5)) // Probabilité théorique d'obtention d'une double paire
#define PAIRE (50400 / pow(10, 5)) // Probabilité théorique d'obtention d'une paire

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

double testFrequences34(double suiteYn[]) {
    int totalRi = 0;
    double totalPi = 0;
    double totalNpi = 0;
    double totalKhi = 0;

    printf("Xi - ri - pi - n.pi - (ri-n.pi)2/(n.pi)\n");

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

        if (LONGUEUR_SUITE >= 50) {
            printf("%d - %d - 1/10 - %.lf - %.2lf\n", i, ri, npi, khi);
        }
    }

    if (LONGUEUR_SUITE < 50) {
        printf("0 a 9 - %d - %lf - 1/10 - %.lf - %.2lf\n", totalRi, totalPi, totalNpi, totalKhi);
    }

    printf("******************************\n");

    printf("Total - %d - %.lf - %.lf - %.2lf\n\n", totalRi, totalPi, totalNpi, totalKhi);

    return totalKhi;
}

void triBulles(int tab[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tab[j] < tab[j + 1]) {
                int temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
}

double testPoker34(double suiteYn[]) {
    // TODO : taile % 5 != 0

    int poker = 0;
    int carre = 0;
    int full = 0;
    int brelan = 0;
    int doublePaire = 0;
    int paire = 0;

    for (int i = 0; i < LONGUEUR_SUITE / 5; i += 5) {
        int tranche[10] = {0};

        int a = suiteYn[i];
        int b = suiteYn[i + 1];
        int c = suiteYn[i + 2];
        int d = suiteYn[i + 3];
        int e = suiteYn[i + 4];

        tranche[a]++;
        tranche[b]++;
        tranche[c]++;
        tranche[d]++;
        tranche[e]++;

        triBulles(tranche, 10);

        a = tranche[0];
        b = tranche[1];
        c = tranche[2];
        d = tranche[3];
        e = tranche[4];

        if (a == 5) { // POKER
            poker++;
        }
        if (a == 4 && b == 1) { // CARRE
            carre++;
        }
        if (a == 3 && b == 2) { // FULL
            full++;
        }
        if (a == 3 && b == 1 && c == 1) { // BRELAN
            brelan++;
        }
        if (a == 2 && b == 2 && c == 1) { // DOUBLE PAIRE
            doublePaire++;
        }
        if (a == 2 && b == 1 && c == 1 && d == 1) { // PAIRE
            paire++;
        }
    }

    double khiPoker = (pow((poker - LONGUEUR_SUITE * POKER), 2)) / (LONGUEUR_SUITE * POKER);
    double khiCarre = (pow((carre - LONGUEUR_SUITE * CARRE), 2)) / (LONGUEUR_SUITE * CARRE);
    double khiFull = (pow((full - LONGUEUR_SUITE * FULL), 2)) / (LONGUEUR_SUITE * FULL);
    double khiBrelan = (pow((brelan - LONGUEUR_SUITE * BRELAN), 2)) / (LONGUEUR_SUITE * BRELAN);
    double khiDoublePaire = (pow((doublePaire - LONGUEUR_SUITE * DOUBLE_PAIRE), 2)) / (LONGUEUR_SUITE * DOUBLE_PAIRE);
    double khiPaire = (pow((paire - LONGUEUR_SUITE * PAIRE), 2)) / (LONGUEUR_SUITE * PAIRE);

    char modalites[6][13] = {
        "Poker",
        "Carre",
        "Full",
        "Brelan",
        "Double Paire",
        "Paire"
    };

    double donnees[6][4] = {
        { poker, POKER, LONGUEUR_SUITE * POKER, khiPoker },
        { carre, CARRE, LONGUEUR_SUITE * CARRE, khiCarre },
        { full, FULL, LONGUEUR_SUITE * FULL, khiFull },
        { brelan, BRELAN, LONGUEUR_SUITE * BRELAN, khiBrelan },
        { doublePaire, DOUBLE_PAIRE, LONGUEUR_SUITE * DOUBLE_PAIRE, khiDoublePaire },
        { paire, PAIRE, LONGUEUR_SUITE * PAIRE, khiPaire }
    };

    // Avant regroupement

    double totalRi = 0;
    double totalPi = 0;
    double totalNpi = 0;
    double totalKhi = 0;

    printf("Xi1 - ri - pi - n.pi - (ri-n.pi)2/(n.pi)\n");

    printf("******************************\n");

    for (int i = 0; i < 6; i++) {
        printf("%s - %lf - %lf - %lf - %lf\n", modalites[i], donnees[i][0], donnees[i][1], donnees[i][2], donnees[i][3]);

        totalRi += donnees[i][0]; totalPi += donnees[i][1]; totalNpi += donnees[i][2]; totalKhi += donnees[i][3];
    }

    printf("******************************\n");

    printf("Total - %lf - %lf - %lf - %lf\n\n", totalRi, totalPi, totalNpi, totalKhi);

    // Apres regroupement

    totalRi = 0;
    totalPi = 0;
    totalNpi = 0;
    totalKhi = 0;

    printf("Xi1 - ri - pi - n.pi - (ri-n.pi)2/(n.pi)\n");

    printf("******************************\n");

    int i = 0;

    do {
        printf("%s ", modalites[i]);

        totalRi += donnees[i][0]; totalPi += donnees[i][1]; totalNpi += donnees[i][2]; totalKhi += donnees[i][3];

        i++;
    } while (i < 6 && totalNpi <= 5);

    printf("- %lf - %lf - %lf - %lf\n", totalRi, totalPi, totalNpi, totalKhi);

    for (int j = i; j < 6; j++) {
        totalRi += donnees[j][0]; totalPi += donnees[j][1]; totalNpi += donnees[j][2]; totalKhi += donnees[j][3];
        printf("%s - %lf - %lf - %lf - %lf\n", modalites[j], totalRi, totalPi, totalNpi, totalKhi);

    }

    printf("******************************\n");

    printf("Total - %lf - %lf - %lf - %.2lf\n\n", totalRi, totalPi, totalNpi, totalKhi);

    return totalKhi;
}

double tableKhiCarre(double alpha, int dl) {
    FILE* table;
    fopen_s(&table, "table.csv", "r");

    char tampon[1024];
    fgets(tampon, sizeof(tampon), table);

    size_t avant = 0, mtn = 0; int sauts = 0;
    while (mtn < strlen(tampon)) {
        if (tampon[mtn] == ',') {
            tampon[mtn] = '.';
        }

        if (tampon[mtn] == ';' || tampon[mtn] == '\n') {
            char extrait[10];
            strncpy_s(extrait, sizeof(extrait), tampon + avant + 1, mtn - avant - 1);
            double alphaValeur = atof(extrait);

            if (alphaValeur == alpha) {
                break;
            }

            avant = mtn;
            sauts++;
        }

        mtn++;
    }

    int index = 0;
    fgets(tampon, sizeof(tampon), table);
    while (index < strlen(tampon))
    {
        int profondeur = 0;
        while (profondeur < strlen(tampon) && tampon[profondeur] != ';') {
            profondeur++;
        }

        char extrait[10];
        strncpy_s(extrait, sizeof(extrait), tampon, profondeur);
        double valeur = atof(extrait);

        if (dl == valeur) {
            break;
        }
        else {
            fgets(tampon, sizeof(tampon), table);
        }

        index++;
    }

    index = 0;
    int hop = 0;

    while (index < strlen(tampon) && hop < sauts) {
        if (tampon[index] == ',') {
            tampon[index] = '.';
        }

        if (tampon[index] == ';') {
            hop++;
            avant = index;
        }

        index++;
    }

    int profondeur = avant+1;

    while (profondeur < strlen(tampon) && tampon[profondeur] != ';') {
        if (tampon[profondeur] == ',') {
            tampon[profondeur] = '.';
        }

        profondeur++;
    }

    char extrait[10];

    strncpy_s(extrait, sizeof(extrait), tampon + avant + 1, profondeur - avant);

    return atof(extrait);
}

void tests(void) {
    assert(calculerPGCD(3, 5) == 1);
    assert(calculerPGCD(15, 28) == 1);
    assert(calculerPGCD(25, 36) == 1);
    assert(calculerPGCD(33, 56) == 1);
    assert(calculerPGCD(39, 80) == 1);

    assert(determinerEstPremier(2));
    assert(determinerEstPremier(13));
    assert(determinerEstPremier(101));
    assert(determinerEstPremier(137));
    assert(determinerEstPremier(199));

    assert(calculerPeriode(35, 13, 65, 100) == 4);
    assert(calculerPeriode(3, 5, 5, 8) == 8);
    assert(calculerPeriode(7, 7, 7, 8) == 2);
    assert(calculerPeriode(7, 5, 3, 16) == 16);

    assert(tableKhiCarre(0.01, 1) == 6.635);
    assert(tableKhiCarre(0.01, 2) == 9.21);
    assert(tableKhiCarre(0.01, 3) == 11.345);
    assert(tableKhiCarre(0.01, 4) == 13.277);
    assert(tableKhiCarre(0.01, 5) == 15.086);

    assert(tableKhiCarre(0.05, 1) == 3.841);
    assert(tableKhiCarre(0.05, 2) == 5.991);
    assert(tableKhiCarre(0.05, 3) == 7.815);
    assert(tableKhiCarre(0.05, 4) == 9.488);
    assert(tableKhiCarre(0.05, 5) == 11.070);

    assert(tableKhiCarre(0.025, 1) == 5.024);
    assert(tableKhiCarre(0.025, 2) == 7.378);
    assert(tableKhiCarre(0.025, 3) == 9.348);
    assert(tableKhiCarre(0.025, 4) == 11.143);
    assert(tableKhiCarre(0.025, 5) == 12.833);
}

int main(void) {
    /* Tests */

    printf("-- TESTS --\n\n");

    tests();

    printf("[SUCCES]\n\n");

    /* Declaration et initialisation des valeurs des coefficients */

    printf("-- DECLARATION ET INITIALISATION DES VALEURS DES COEFFICIENTS --\n\n");

    int x0, a, c, m;

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

    printf("[SUCCES]\n\n");

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
            printf("[HYPOTHESE 3] : m est multiple de 4 mais (a - 1) ne l'est pas\n\n");

            estOK = false;
        } else {
            printf("[HYPOTHESE 3] : m et (a - 1) sont multiples de 4\n\n");
        }
    } else {
        printf("[HYPOTHESE 3] : m n'est pas multiple de 4\n\n");
    }

    // Conclusion

    if (estOK) {
        printf("[CONCLUSION] : les hypotheses du theoreme de Hull-Dobell sont verifiees\n\n");
    } else {
        printf("[CONCLUSION] : les hypotheses du theoreme du Hull-Dobell ne sont pas toutes verifiees\n\n");
    }

    printf("[SUCCES]\n\n");

    /* Calcul de la periode de la suite */

    printf("-- CALCUL DE LA PERIODE DE LA SUITE --\n\n");

    int periode;

    if (estOK) {
        periode = m;
    } else {
        periode = calculerPeriode(x0, a, c, m);
    }

    printf("[RESULTAT] : la periode de la suite est de %d\n\n", periode);

    printf("[SUCCES]\n\n");

    /* Generation de la suite de nombres pseudo-aleatoires */

    printf("-- GENERATION DE LA SUITE PSEUDO-ALEATOIRE --\n\n");

    double suiteXn[LONGUEUR_SUITE];

    genererSuite(suiteXn, x0, a, c, m);

    printf("[SUCCES]\n\n");

    /* Tests statistiques de validite */

    printf("-- TESTS STATISTIQUES DE VALIDITE --\n\n");

    double suiteUn[LONGUEUR_SUITE], suiteYn[LONGUEUR_SUITE];

    calculerUn(suiteXn, suiteUn, m);
    calculerYn(suiteUn, suiteYn);

    double alpha = 0.05;

    bool decisionH0 = false;

    /* Test des frequences */

    printf("-- TEST DES FREQUENCES --\n\n");

    int dl = 9;

    // Etape 1

    printf("H0: La suite de nombres pseudo aleatoire est acceptable pour ce test\n");
    printf("H1: La suite de nombres pseudo aleatoire n'est pas acceptable pour ce test\n\n");

    // Etape 2

    printf("Alpha = %.2lf\n\n", alpha);

    // Etape 3 & 4

    double khiCarreFre = testFrequences34(suiteYn);

    // Etape 5

    if (khiCarreFre <= tableKhiCarre(alpha, 9)) {
        decisionH0 = true;
    }

    // Etape 6

    if (decisionH0) {
        printf("[DECISION] : La suite de nombres pseudo aleatoire est acceptable pour ce test\n\n");
    } else {
        printf("[DECISION] : La suite de nombres pseudo aleatoire n'est pas acceptable pour ce test\n\n");
    }

    printf("[SUCCES]\n\n");

    /* Test du poker */

    printf("-- TEST DU POKER --\n\n");

    decisionH0 = false;

    // Etape 1

    printf("H0: La suite de nombres pseudo aleatoire est acceptable pour ce test\n");
    printf("H1: La suite de nombres pseudo aleatoire n'est pas acceptable pour ce test\n\n");

    // Etape 2

    printf("Alpha = %.2lf\n\n", alpha);

    // Etape 3 && Etape 4

    double khiCarrePoker = testPoker34(suiteYn);

    // Etape 5

    if (khiCarrePoker <= tableKhiCarre(alpha, 9)) {
        decisionH0 = true;
    }

    // Etape 6

    if (decisionH0) {
        printf("[DECISION] : La suite de nombres pseudo aleatoire est acceptable pour ce test\n\n");
    } else {
        printf("[DECISION] : La suite de nombres pseudo aleatoire n'est pas acceptable pour ce test\n\n");
    }

    printf("[SUCCES]\n\n");

    return 0;
}