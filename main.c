#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

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

void partie1(void) {
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
}

/* ---------------------------------------------------------------------------------------- */

#define TAILLE_MAX_FILE 1000

// Structure - Client
// classe : Classe du client (0 = Ordinaire / 1 = Prioritaire Relatif / 2 = Prioritaire Absolu)
// dureeService : Durée de service du client
// minuteArrivee : Minute d'arrivée du client dans la file
typedef struct {
    int classe;
    int dureeService;
    int minuteArrivee;
} Client;

// Structure - File
// donneesClients : Données des clients dans la file
// iPremier : Indice du premier client dans la file
// iDernier : Indice du dernier client dans la file
typedef struct {
    Client donneesClients[TAILLE_MAX_FILE];
    int iPremier;
    int iDernier;
} File;

// Méthode - Initialiser()
// Initialise une file vide
void initialiser(File* file) {
    file->iPremier = 0;
    file->iDernier = -1;
}

// Méthode - estVide()
// Vérifie si une file est vide
int estVide(File* file) {
    return file->iDernier < file->iPremier;
}

// Méthode - ajouterClient()
// Ajoute un client à la fin d'une file
void ajouterClient(File* file, Client client) {
    if (file->iDernier < TAILLE_MAX_FILE - 1) {
        file->iDernier++;
        file->donneesClients[file->iDernier] = client;
    } else {
        printf("[ERREUR] : LA FILE EST PLEINE\n\n");
    }
}

// Méthode retirerClient()
// Retire le client en tête d'une file
Client retirerClient(File* file) {
    if (!estVide(file)) {
        Client client = file->donneesClients[file->iPremier];
        file->iPremier++;

        return client;
    } else {
        printf("[ERREUR] : LA FILE EST VIDE\n\n");

        Client client;
        client.classe = -1;

        return client;
    }
}

// Méthode - poisson()
// Génère un entier selon la loi de Poisson
int poisson(double lambda) {
    double L = exp(-lambda);
    double p = 1.0;
    int k = 0;

    do {
        k++;
        p *= (double)rand() / RAND_MAX;
    } while (p > L);

    return k - 1;
}

// Méthode - binomial()
// Génère un entier selon une loi binomiale
int binomial(int n, double p) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        double u = (double)rand() / RAND_MAX;

        if (u < p) {
            count++;
        }
    }

    return count;
}

// Méthode - initStations()
// Initialise des stations
void initStations(int* stations, int nbStations) {
    for (int i = 0; i < nbStations; i++) {
        stations[i] = 0;
    }
}

// Méthode - nbArriveesGenerees()
// Génère un nombre de clients arrivant
void nbArriveesGenerees(int* nbArriveesO, int* nbArriveesP) {
    *nbArriveesO = poisson(1.5);
    *nbArriveesP = poisson(0.7);
}

// Méthode - dureeClient()
// Génère une durée de service d'un client selon une distribution prédéfinie
int dureeClient() {
    int alea = rand() % 60 + 1;

    if (alea <= 24) {
        return 1;
    } else if (alea <= 24 + 18) {
        return 2;
    } else if (alea <= 24 + 18 + 10) {
        return 3;
    } else if (alea <= 24 + 18 + 10 + 3) {
        return 4;
    } else if (alea <= 24 + 18 + 10 + 3 + 3) {
        return 5;
    } else {
        return 6;
    }
}

// Méthode - classStation()
// Donne une description textuelle de la classe d'un client à une station
void classStation(int i, char classeClient[50], int classeStations[]) {
    if (classeStations[i] == 0) {
        strcpy(classeClient, "Ordinaire");
    } else if (classeStations[i] == 1) {
        strcpy(classeClient, "Prioritaire Relatif");
    } else if (classeStations[i] == 2) {
        strcpy(classeClient, "Prioritaire Absolu");
    } else {
        strcpy(classeClient, "Libre");
    }
}

// Méthode - rechercheCoutMin()
// Recherche l'indice du coût minimal dans un tableau de coûts
int rechercheCoutMin(int couts[1000], int nbStationsTestees) {
    int minIndex = 0;
    int minCout = couts[0];

    for (int i = 1; i < nbStationsTestees; i++) {
        if (couts[i] < minCout) {
            minCout = couts[i];
            minIndex = i;
        }
    }

    return minIndex;
}

int nbStationsOptimal(int nbStationsMin, int nbStationsMax, int tempsSimul) {
    int couts[1000];
    int nbStationsTestees = nbStationsMax - nbStationsMin + 1;

    for (int nbStations = nbStationsMin; nbStations <= nbStationsMax; nbStations++) {
        int tempsPresenceO = 0; // Temps de présence d'un client ordinaire
        int tempsPresencePR  = 0; // Temps de présence d'un client prioritaire relatif
        int tempsPresencePA  = 0; // Temps de présence d'un client prioritaire absolu
        int tempsOccupationO = 0; // Temps d'occupation d'une station par un client ordinaire
        int tempsOccupationP = 0; // Temps d'occupation d'une station par un client prioritaire
        int tempsInoccupation = 0; // Temps d'inoccupation d'une station
        int pertesO = 0; // Pertes de clients ordinaires
        int pertesP = 0; // Pertes de clients prioritaires

        int stations[nbStations];
        initStations(stations, nbStations);

        int classeStations[nbStations]; // 0 = O // 1 = PR // 2 = PA // -1 = Libre
        for (int i = 0; i < nbStations; i++) {
            classeStations[i] = -1;
        }

        File fileO, filePR, filePA;
        initialiser(&fileO);
        initialiser(&filePR);
        initialiser(&filePA);

        for (int temps = 0; temps < tempsSimul; temps++) {
            int nbArriveesO; // Nombre d'arrivées de clients ordinaires
            int nbArriveesP; // Nombre d'arrivées de clients prioritaires

            if (temps < 20) {
                printf("\n[DEBUT MINUTE %d]\n\n", temps);

                printf("[STATIONS]\n");
                printf("----------\n");

                for (int i = 0; i < nbStations; i++) {
                    char classeClient[50];

                    classStation(i, classeClient, classeStations);

                    printf("Station %d - %s (Duree restante: %d)\n", i, classeClient, stations[i]);
                }

                printf("\n[FILES]\n");
                printf("----------\n");

                printf("File O:\n");

                for (int i = fileO.iPremier; i <= fileO.iDernier; i++) {
                    Client c = fileO.donneesClients[i];
                    printf("Client %d: classe=%d, duree=%d, arrivee=%d\n", i, c.classe, c.dureeService, c.minuteArrivee);
                }

                printf("File PR:\n");

                for (int i = filePR.iPremier; i <= filePR.iDernier; i++) {
                    Client c = filePR.donneesClients[i];
                    printf("Client %d: classe=%d, duree=%d, arrivee=%d\n", i, c.classe, c.dureeService, c.minuteArrivee);
                }

                printf("File PA:\n");

                for (int i = filePA.iPremier; i <= filePA.iDernier; i++) {
                    Client c = filePA.donneesClients[i];
                    printf("Client %d: classe=%d, duree=%d, arrivee=%d\n", i, c.classe, c.dureeService, c.minuteArrivee);
                }
            }

            nbArriveesGenerees(&nbArriveesO, &nbArriveesP);

            int nbArriveesPA = binomial(nbArriveesP, 0.3);
            int nbArriveesPR = nbArriveesP - nbArriveesPA;

            for (int i = 0; i < nbArriveesPA; i++) {
                Client client;
                client.classe = 2;
                client.dureeService = dureeClient();
                client.minuteArrivee = temps;
                ajouterClient(&filePA, client);
            }

            for (int i = 0; i < nbArriveesPR; i++) {
                Client client;
                client.classe = 1;
                client.dureeService = dureeClient();
                client.minuteArrivee = temps;
                ajouterClient(&filePR, client);
            }

            for (int i = 0; i < nbArriveesO; i++) {
                Client client;
                client.classe = 0;
                client.dureeService = dureeClient();
                client.minuteArrivee = temps;
                ajouterClient(&fileO, client);
            }

            if (temps < 20) {
                printf("\n[ARRIVEES DES CLIENTS]\n", temps);
                printf("----------\n");

                for (int i = 0; i < nbArriveesO; i++) {
                    Client c = fileO.donneesClients[fileO.iDernier - nbArriveesO + 1 + i];
                    printf("Ordinaire: duree = %d\n", c.dureeService);
                }

                for (int i = 0; i < nbArriveesPR; i++) {
                    Client c = filePR.donneesClients[filePR.iDernier - nbArriveesPR + 1 + i];
                    printf("Prioritaire relatif: duree = %d\n", c.dureeService);
                }

                for (int i = 0; i < nbArriveesPA; i++) {
                    Client c = filePA.donneesClients[filePA.iDernier - nbArriveesPA + 1 + i];
                    printf("Prioritaire absolu: duree = %d\n", c.dureeService);
                }
            }

            if (temps < 20) {
                printf("\n[FILES]\n");
                printf("----------\n");

                printf("File O:\n");

                for (int i = fileO.iPremier; i <= fileO.iDernier; i++) {
                    Client c = fileO.donneesClients[i];
                    printf("Client %d: classe = %d, duree = %d, arrivee = %d\n", i, c.classe, c.dureeService, c.minuteArrivee);
                }

                printf("\n");

                printf("File PR:\n");

                for (int i = filePR.iPremier; i <= filePR.iDernier; i++) {
                    Client c = filePR.donneesClients[i];
                    printf("Client %d: classe = %d, duree = %d, arrivee = %d\n", i, c.classe, c.dureeService, c.minuteArrivee);
                }

                printf("\n");

                printf("File PA:\n");

                for (int i = filePA.iPremier; i <= filePA.iDernier; i++) {
                    Client c = filePA.donneesClients[i];
                    printf("Client %d: classe = %d, duree = %d, arrivee = %d\n", i, c.classe, c.dureeService, c.minuteArrivee);
                }
            }

            for (int i = 0; i < nbStations; i++) {
                if (stations[i] == 0) {
                    Client client;
                    if (!estVide(&filePA)) {
                        client = retirerClient(&filePA);
                    } else if (!estVide(&filePR)) {
                        client = retirerClient(&filePR);
                    } else if (!estVide(&fileO)) {
                        client = retirerClient(&fileO);
                    } else {
                        continue;
                    }

                    stations[i] = client.dureeService;
                    classeStations[i] = client.classe;
                }
            }

            int nbPAEnAttente = filePA.iDernier - filePA.iPremier + 1;
            int nbStationsPA = 0;

            for (int i = 0; i < nbStations; i++) {
                if (classeStations[i] == 2) nbStationsPA++;
            }

            int pertesPA = (nbPAEnAttente > 0 && nbStationsPA == nbStations) ? nbPAEnAttente : 0;

            pertesP += pertesPA;

            for (int i = 0; i < nbStations; i++) {
                if (stations[i] > 0) {
                    stations[i]--;
                } else {
                    classeStations[i] = -1;
                }
            }

            for (int i = 0; i < nbStations; i++) {
                if (stations[i] > 0) {
                    if (classeStations[i] == 0) {
                        tempsPresenceO++;
                        tempsOccupationO++;
                    } else if (classeStations[i] == 1) {
                        tempsPresencePR++;
                        tempsOccupationP++;
                    } else if (classeStations[i] == 2) {
                        tempsPresencePA++;
                        tempsOccupationP++;
                    }
                } else {
                    tempsInoccupation++;
                }
            }

            if (temps < 20) {
                printf("\n[STATIONS]\n");
                printf("----------\n");

                for (int i = 0; i < nbStations; i++) {
                    char classeClient[50];

                    classStation(i, classeClient, classeStations);

                    printf("Station %d: %s, duree restante: %d\n", i, classeClient, stations[i]);
                }
            }
        }

        couts[nbStations - nbStationsMin] =
            15 * ((double)tempsPresenceO / 60) +
            35 * ((double)tempsPresencePR / 60) +
            45 * ((double)tempsPresencePA / 60) +
            28 * ((double)tempsOccupationO / 60) +
            33 * ((double)tempsOccupationP / 60) +
            18 * ((double)tempsInoccupation / 60) +
            15 * pertesO +
            20 * pertesP;
    }

    int indexOpt = rechercheCoutMin(couts, nbStationsTestees);

    return nbStationsMin + indexOpt;
}

void partie2(void) {
    srand(time(NULL));

    /* Declaration et initialisation des valeurs des paramètres */

    printf("-- DECLARATION ET INITIALISATION DES VALEURS DES PARAMETRES --\n\n");

    int nbStationsMin, nbStationsMax, tempsSimul;

    printf("Valeur du parametre nbStationsMin : ");
    scanf_s("%d", &nbStationsMin);

    while (nbStationsMin <= 0) {
        printf("[ERREUR] : la valeur du parametre nbStationsMin doit etre > 0\n\n");

        printf("Valeur du parametre nbStationsMin : ");
        scanf_s("%d", &nbStationsMin);
    }

    printf("Valeur du parametre nbStationsMax : ");
    scanf_s("%d", &nbStationsMax);

    while (nbStationsMax <= nbStationsMin) {
        printf("[ERREUR] : la valeur du parametre nbStationsMax doit etre > nbStationsMin\n\n");

        printf("Valeur du parametre nbStationsMax : ");
        scanf_s("%d", &nbStationsMax);
    }

    printf("Valeur du parametre tempsSimul : ");
    scanf_s("%d", &tempsSimul);

    while (tempsSimul <= 60) {
        printf("[ERREUR] : la valeur du parametre tempsSimul doit etre > 60\n\n");

        printf("Valeur du parametre tempsSimul : ");
        scanf_s("%d", &tempsSimul);
    }

    /* Simulation */

    printf("-- SIMULATION --\n");

    int resultat = nbStationsOptimal(nbStationsMin, nbStationsMax, tempsSimul);

    /* Resultat */

    printf("\n-- RESULTAT --\n\n");

    printf("Nombre de stations optimal : %d", resultat);
}

int main(void) {
    partie1();

    partie2();

    return 0;
}
