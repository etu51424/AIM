#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

#define LONGUEUR_SUITE 5000

/* Probabilités théoriques */
#define POKER (10.0 / 100000.0) // Probabilité théorique d'obtention d'un POKER
#define CARRE (450.0 / 100000.0) // Probabilité théorique d'obtention d'un CARRE
#define FULL (900.0 / 100000.0) // Probabilité théorique d'obtention d'un FULL
#define BRELAN (7200.0 / 100000.0) // Probabilité théorique d'obtention d'un BRELAN
#define DOUBLE_PAIRE (10800.0 / 100000.0) // Probabilité théorique d'obtention d'une DOUBLE PAIRE
#define PAIRE (50400.0 / 100000.0) // Probabilité théorique d'obtention d'une PAIRE
#define DIFFERENCE (30240.0 / 100000.0) // Probabilité théorique d'obtention d'une DIFFERENCE

/* Méthode - calculerPGCD() */
uint64_t calculerPGCD(uint64_t nombre1, uint64_t nombre2) {
	uint64_t t;

	while (nombre2 != 0) {
		t = nombre1 % nombre2;
		nombre1 = nombre2;
		nombre2 = t;
	}

	return nombre1;
}

/* Méthode - determinerEstPremier() */
bool determinerEstPremier(uint64_t nombre) {
	if (nombre < 2) {
		return false;
	}

	for (uint64_t i = 2; i * i <= nombre; i++) {
		if (nombre % i == 0) {
			return false;
		}
	}

	return true;
}

/* Méthode - calculerPeriode() */
uint64_t calculerPeriode(uint64_t x0, uint64_t a, uint64_t c, uint64_t m) {
	uint64_t i = 0;
	uint64_t x = (a * x0 + c) % m;

	while (x != x0 && i < m) {
		x = (a * x + c) % m;

		i++;
	}

	return i + 1;
}

/* Méthode - genererSuite() */
void genererSuite(double* suiteXn, uint64_t x0, uint64_t a, uint64_t c, uint64_t m) {
	uint64_t x = x0;

	suiteXn[0] = x;

	printf("%llu ", x);

	for (uint64_t i = 1; i < LONGUEUR_SUITE; i++) {
		x = (a * x + c) % m;
		suiteXn[i] = x;

		printf("%llu ", x);
	}

	printf("\n");
}

/* Méthode - calculerUn() */
void calculerUn(double suiteXn[], double suiteUn[], uint64_t m) {
	for (uint64_t i = 0; i < LONGUEUR_SUITE; i++) {
		suiteUn[i] = suiteXn[i] / m;
	}
}

/* Méthode - calculerYn() */
void calculerYn(double suiteUn[], double suiteYn[]) {
	for (uint64_t i = 0; i < LONGUEUR_SUITE; i++) {
		suiteYn[i] = (double)(int)(suiteUn[i] * 10);
	}
}

/* Méthode - trouverRepetition() */
uint64_t trouverRepetition(double suiteYn[], uint64_t x) {
	uint64_t repetition = 0;

	for (uint64_t i = 0; i < LONGUEUR_SUITE; i++) {
		if (suiteYn[i] == x) {
			repetition++;
		}
	}

	return repetition;
}

/* Méthode - testFrequences34() */
double testFrequences34(double suiteYn[]) {
	uint64_t totalRi = 0;
	double totalPi = 0;
	double totalNpi = 0;
	double totalKhi = 0;

	printf("Xi - ri - pi - n.pi - (ri-n.pi)2/(n.pi)\n");

	printf("******************************\n");

	for (int i = 0; i < 10; i++) {
		uint64_t ri = trouverRepetition(suiteYn, i);
		double pi = 0.1;
		double npi = LONGUEUR_SUITE * pi;
		double khi = pow(ri - npi, 2) / npi;

		totalRi += ri;
		totalPi += pi;
		totalNpi += npi;
		totalKhi += khi;

		if (LONGUEUR_SUITE >= 50) {
			printf("%d - %llu - 1/10 - %.lf - %.2lf\n", i, ri, npi, khi);
		}
	}

	if (LONGUEUR_SUITE < 50) {
		printf("0 a 9 - %llu - %lf - 1/10 - %.lf - %.2lf\n", totalRi, totalPi, totalNpi, totalKhi);
	}

	printf("******************************\n");

	printf("Total - %llu - %.lf - %.lf - %.2lf\n\n", totalRi, totalPi, totalNpi, totalKhi);

	return totalKhi;
}

/* Méthode - triBulles() */
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

/* Méthode - testPoker34() */
double testPoker34(double suiteYn[]) {
	assert(LONGUEUR_SUITE % 5 == 0);

	uint64_t poker = 0;
	uint64_t carre = 0;
	uint64_t full = 0;
	uint64_t brelan = 0;
	uint64_t doublePaire = 0;
	uint64_t paire = 0;
	uint64_t difference = 0;

	for (uint64_t i = 0; i < LONGUEUR_SUITE; i += 5) {
		int tranche[10] = { 0 };

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
		else if (a == 4 && b == 1) { // CARRE
			carre++;
		}
		else if (a == 3 && b == 2) { // FULL
			full++;
		}
		else if (a == 3 && b == 1 && c == 1) { // BRELAN
			brelan++;
		}
		else if (a == 2 && b == 2 && c == 1) { // DOUBLE PAIRE
			doublePaire++;
		}
		else if (a == 2 && b == 1 && c == 1 && d == 1) { // PAIRE
			paire++;
		}
		else {
			difference++; // DIFFERENCE
		}
	}

	double khiPoker = (pow((poker - LONGUEUR_SUITE / 5 * POKER), 2)) / (LONGUEUR_SUITE / 5 * POKER);
	double khiCarre = (pow((carre - LONGUEUR_SUITE / 5 * CARRE), 2)) / (LONGUEUR_SUITE / 5 * CARRE);
	double khiFull = (pow((full - LONGUEUR_SUITE / 5 * FULL), 2)) / (LONGUEUR_SUITE / 5 * FULL);
	double khiBrelan = (pow((brelan - LONGUEUR_SUITE / 5 * BRELAN), 2)) / (LONGUEUR_SUITE / 5 * BRELAN);
	double khiDoublePaire = (pow((doublePaire - LONGUEUR_SUITE / 5 * DOUBLE_PAIRE), 2)) / (LONGUEUR_SUITE / 5 * DOUBLE_PAIRE);
	double khiPaire = (pow((paire - LONGUEUR_SUITE / 5 * PAIRE), 2)) / (LONGUEUR_SUITE / 5 * PAIRE);
	double khiDiff = (pow((difference - LONGUEUR_SUITE / 5 * DIFFERENCE), 2)) / (LONGUEUR_SUITE / 5 * DIFFERENCE);

	char modalites[7][20] = {
		"Poker",
		"Carre",
		"Full",
		"Brelan",
		"Double Paire",
		"Paire",
		"Difference"
	};

	double donnees[7][4] = {
		{ poker, POKER, LONGUEUR_SUITE / 5 * POKER, khiPoker },
		{ carre, CARRE, LONGUEUR_SUITE / 5 * CARRE, khiCarre },
		{ full, FULL, LONGUEUR_SUITE / 5 * FULL, khiFull },
		{ brelan, BRELAN, LONGUEUR_SUITE / 5 * BRELAN, khiBrelan },
		{ doublePaire, DOUBLE_PAIRE, LONGUEUR_SUITE / 5 * DOUBLE_PAIRE, khiDoublePaire },
		{ paire, PAIRE, LONGUEUR_SUITE / 5 * PAIRE, khiPaire },
		{ difference, DIFFERENCE, LONGUEUR_SUITE / 5 * DIFFERENCE, khiDiff }
	};

	// Avant regroupement

	double totalRi = 0;
	double totalPi = 0;
	double totalNpi = 0;
	double totalKhi = 0;

	printf("Xi - ri - pi - n.pi - (ri-n.pi)2/(n.pi)\n");

	printf("******************************\n");

	for (int i = 0; i < 7; i++) {
		printf("%s - %.0lf - %lf - %lf - %lf\n", modalites[i], donnees[i][0], donnees[i][1], donnees[i][2], donnees[i][3]);

		totalRi += donnees[i][0];
		totalPi += donnees[i][1];
		totalNpi += donnees[i][2];
		totalKhi += donnees[i][3];
	}

	printf("******************************\n");

	printf("Total - %.0lf - %lf - %lf - %lf\n\n", totalRi, totalPi, totalNpi, totalKhi);

	// Apres regroupement

	totalRi = 0;
	totalPi = 0;
	totalNpi = 0;
	totalKhi = 0;

	printf("Xi - ri - pi - n.pi - (ri-n.pi)2/(n.pi)\n");

	printf("******************************\n");

	int i = 0;

	do {
		printf("%s ", modalites[i]);

		totalRi += donnees[i][0];
		totalPi += donnees[i][1];
		totalNpi += donnees[i][2];
		totalKhi += donnees[i][3];

		i++;
	} while (i < 7 && totalNpi <= 5);

	printf("- %lf - %lf - %lf - %lf\n", totalRi, totalPi, totalNpi, totalKhi);

	for (int j = i; j < 7; j++) {
		totalRi += donnees[j][0];
		totalPi += donnees[j][1];
		totalNpi += donnees[j][2];
		totalKhi += donnees[j][3];

		printf("%s - %lf - %lf - %lf - %lf\n", modalites[j], totalRi, totalPi, totalNpi, totalKhi);
	}

	printf("******************************\n");

	printf("Total - %lf - %lf - %lf - %.2lf\n\n", totalRi, totalPi, totalNpi, totalKhi);

	return totalKhi;
}

/* Méthode - tableKhiCarre() */
double tableKhiCarre(double alpha, int dl) {
	FILE* table;
	fopen_s(&table, "tables.csv", "r");

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

	int profondeur = avant + 1;

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

void partie1(void) {
	/* Declaration et initialisation des valeurs des coefficients */

	printf("-- DECLARATION ET INITIALISATION DES VALEURS DES COEFFICIENTS --\n\n");

	uint64_t x0, a, c, m;

	printf("Valeur du coefficient m : ");
	scanf_s("%llu", &m);

	while (m <= 0) {
		printf("[ERREUR] : la valeur du coefficient m doit etre > 0\n\n");

		printf("Valeur du coefficient m : ");
		scanf_s("%llu", &m);
	}

	printf("Valeur du coefficient a : ");
	scanf_s("%llu", &a);

	while (a < 0 || a >= m) {
		printf("[ERREUR] : la valeur du coefficient a doit etre >= 0 et < m\n\n");

		printf("Valeur du coefficient a : ");
		scanf_s("%llu", &a);
	}

	printf("Valeur du coefficient c : ");
	scanf_s("%llu", &c);

	while (c < 0 || c >= m) {
		printf("[ERREUR] : la valeur du coefficient c doit etre >= 0 et < m\n\n");

		printf("Valeur du coefficient c : ");
		scanf_s("%llu", &c);
	}

	printf("Valeur du coefficient x0 : ");
	scanf_s("%llu", &x0);

	while (x0 < 0 || x0 >= m) {
		printf("[ERREUR] : la valeur du coefficient x0 doit etre >= 0 et < m\n\n");

		printf("Valeur du coefficient x0 : ");
		scanf_s("%llu", &x0);
	}

	/* Verification des hypotheses du theoreme de Hull-Dobell */

	printf("-- VERIFICATION DES HYPOTHESES DU THEOREME DE HULL-DOBELL --\n\n");

	bool estOK = true;

	// Hypothese 1

	if (calculerPGCD(c, m) != 1) {
		printf("[HYPOTHESE 1] : c et m ne sont pas premiers entre eux\n\n");

		estOK = false;
	}
	else {
		printf("[HYPOTHESE 1] : c et m sont premiers entre eux\n\n");
	}

	// Hypothese 2

	for (uint64_t p = 2; p <= m; p++) {
		if (determinerEstPremier(p) && (m % p) == 0) {
			if ((a - 1) % p != 0) {
				printf("[HYPOTHESE 2] : (a - 1) n'est pas multiple de %llu\n\n", p);

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
		}
		else {
			printf("[HYPOTHESE 3] : m et (a - 1) sont multiples de 4\n\n");
		}
	}
	else {
		printf("[HYPOTHESE 3] : m n'est pas multiple de 4\n\n");
	}

	// Conclusion

	if (estOK) {
		printf("[CONCLUSION] : les hypotheses du theoreme de Hull-Dobell sont verifiees\n\n");
	}
	else {
		printf("[CONCLUSION] : les hypotheses du theoreme du Hull-Dobell ne sont pas toutes verifiees\n\n");
	}

	/* Calcul de la periode de la suite */

	printf("-- CALCUL DE LA PERIODE DE LA SUITE --\n\n");

	uint64_t periode;

	if (estOK) {
		periode = m;
	}
	else {
		periode = calculerPeriode(x0, a, c, m);
	}

	printf("[RESULTAT] : la periode de la suite est de %llu\n\n", periode);

	/* Generation de la suite de nombres pseudo-aleatoires */

	printf("-- GENERATION DE LA SUITE DE NOMBRES PSEUDO-ALEATOIRES --\n\n");

	double suiteXn[LONGUEUR_SUITE];

	genererSuite(suiteXn, x0, a, c, m);

	/* Tests statistiques de validite */

	printf("-- TESTS STATISTIQUES DE VALIDITE --\n\n");

	double suiteUn[LONGUEUR_SUITE], suiteYn[LONGUEUR_SUITE];

	calculerUn(suiteXn, suiteUn, m);
	calculerYn(suiteUn, suiteYn);

	double alpha = 0.05;

	bool decisionH0 = false;

	/* Test des frequences */

	printf("-- TEST DES FREQUENCES --\n\n");

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
	}
	else {
		printf("[DECISION] : La suite de nombres pseudo aleatoire n'est pas acceptable pour ce test\n\n");
	}

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
	}
	else {
		printf("[DECISION] : La suite de nombres pseudo aleatoire n'est pas acceptable pour ce test\n\n");
	}
}

/* ---------------------------------------------------------------------------------------- */

#define TAILLE_MAX_FILE 1000
#define TAILLE_MAX_CLASSE 50

// Enum - Classe
typedef enum {
	ORDINAIRE = 0,
	PRIORITAIRE_RELATIVE = 1,
	PRIORITAIRE_ABSOLUE = 2,
	LIBRE = -1
} Classe;

// Structure - Client
// classe : Classe du client (0 = Ordinaire / 1 = Prioritaire Relatif / 2 = Prioritaire Absolu)
// dureeService : Durée de service du client
// minuteArrivee : Minute d'arrivée du client dans la file
typedef struct {
	Classe classe;
	uint64_t dureeService;
	uint64_t minuteArrivee;
} Client;

// Structure - File
// donneesClients : Données des clients dans la file
// iPremier : Indice du premier client dans la file
// iDernier : Indice du dernier client dans la file
typedef struct {
	Client donneesClients[TAILLE_MAX_FILE];
	uint64_t iPremier;
	uint64_t iDernier;
} File;

// Méthode - Initialiser()
// Initialise une file vide
void initialiser(File* file) {
	file->iPremier = 0;
	file->iDernier = 0; // -1 de base
}

// Méthode - estVide()
// Vérifie si une file est vide
int estVide(File* file) {
	return file->iDernier == file->iPremier;
}

// Méthode - ajouterClient()
// Ajoute un client à la fin d'une file
void ajouterClient(File* file, Client client) {
	if (file->iDernier < TAILLE_MAX_FILE) {
		file->donneesClients[file->iDernier] = client;
		file->iDernier++;
	}
	else {
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
	}
	else {
		printf("[ATTENTION] : LA FILE EST VIDE\n\n");

		Client client;
		client.classe = LIBRE;

		return client;
	}
}

// Méthode - poisson()
// Génère un entier selon la loi de Poisson
uint64_t poisson(double lambda) {
	double L = exp(-lambda);
	double p = 1.0;
	uint64_t k = 0;

	do {
		k++;
		p *= (double)rand() / RAND_MAX;
	} while (p > L);

	return k - 1;
}

// Méthode - binomial()
// Génère un entier selon une loi binomiale
uint64_t binomial(uint64_t n, double p) {
	uint64_t count = 0;

	for (uint64_t i = 0; i < n; i++) {
		double u = (double)rand() / RAND_MAX;

		if (u < p) {
			count++;
		}
	}

	return count;
}

// Méthode - initStations()
// Initialise des stations
void initStations(uint64_t* stations, uint64_t nbStations) {
	for (uint64_t index = 0; index < nbStations; index++) {
		stations[index] = 0;
	}
}

// Méthode - nbArriveesGenerees()
// Génère un nombre de clients arrivant
void nbArriveesGenerees(uint64_t* nbArriveesO, uint64_t* nbArriveesP) {
	*nbArriveesO = poisson(1.5);
	*nbArriveesP = poisson(0.7);
}

// Méthode - dureeClient()
// Génère une durée de service d'un client selon une distribution prédéfinie
uint64_t dureeClient() {
	int alea = rand() % 60 + 1;

	if (alea <= 24) {
		return 1;
	}
	else if (alea <= 24 + 18) {
		return 2;
	}
	else if (alea <= 24 + 18 + 10) {
		return 3;
	}
	else if (alea <= 24 + 18 + 10 + 3) {
		return 4;
	}
	else if (alea <= 24 + 18 + 10 + 3 + 3) {
		return 5;
	}
	else {
		return 6;
	}
}

// Méthode - classToString()
// Donne une description textuelle de la classe d'un client à une station
void classToString(Classe classe, char destination[]) {
	switch (classe) {
		case ORDINAIRE:
			strcpy_s(destination, TAILLE_MAX_CLASSE, "Ordinaire");
			break;
		case PRIORITAIRE_RELATIVE:
			strcpy_s(destination, TAILLE_MAX_CLASSE, "Prioritaire Relatif");
			break;
		case PRIORITAIRE_ABSOLUE:
			strcpy_s(destination, TAILLE_MAX_CLASSE, "Prioritaire Absolu");
			break;
		case LIBRE:
			strcpy_s(destination, TAILLE_MAX_CLASSE, "Libre");
			break;
		default:
			printf("[ERREUR] : La classe n'existe pas !", classe);
	}
}

// Méthode - rechercheCoutMin()
// Recherche l'indice du coût minimal dans un tableau de coûts
uint64_t rechercheCoutMin(double couts[], uint64_t taille) {
	uint64_t minIndex = 0;
	double minCout = couts[0];

	for (uint64_t i = 1; i < taille; i++) {
		if (couts[i] < minCout) {
			minCout = couts[i];
			minIndex = i;
		}
	}

	return minIndex;
}

uint64_t nbStationsOptimal(uint64_t nbStationsMin, uint64_t nbStationsMax, uint64_t tempsSimul) {
	double couts[1000];

	for (uint64_t nbStations = nbStationsMin; nbStations <= nbStationsMax; nbStations++) {
		double tempsPresenceO = 0; // Temps de présence d'un client ordinaire
		double tempsPresencePR = 0; // Temps de présence d'un client prioritaire relatif
		double tempsPresencePA = 0; // Temps de présence d'un client prioritaire absolu
		double tempsOccupationO = 0; // Temps d'occupation d'une station par un client ordinaire
		double tempsOccupationP = 0; // Temps d'occupation d'une station par un client prioritaire
		double tempsInoccupation = 0; // Temps d'inoccupation d'une station
		uint64_t pertesO = 0; // Pertes de clients ordinaires
		uint64_t pertesP = 0; // Pertes de clients prioritaires

		uint64_t stations[nbStations];
		initStations(stations, nbStations);

		Classe classeStations[nbStations];
		for (uint64_t i = 0; i < nbStations; i++) {
			classeStations[i] = LIBRE;
		}

		File fileO, filePR, filePA;
		initialiser(&fileO); // File des clients ordinaires
		initialiser(&filePR); // File des clients prioritaires relatifs
		initialiser(&filePA); // File des clients prioritaires absolus

		for (uint64_t temps = 0; temps < tempsSimul; temps++) {
			uint64_t nbArriveesO; // Nombre d'arrivées de clients ordinaires
			uint64_t nbArriveesP; // Nombre d'arrivées de clients prioritaires

			if (temps < 20) {
				printf("\n[DEBUT MINUTE %llu]\n\n", temps + 1);

				printf("[STATIONS]\n");
				printf("----------\n");

				for (uint64_t i = 0; i < nbStations; i++) {
					char classeClient[TAILLE_MAX_CLASSE];

					classToString(classeStations[i], classeClient);

					printf("Station %llu - %s (Duree restante: %llu)\n", i + 1, classeClient, stations[i]);
				}

				printf("\n[FILES]\n");
				printf("----------\n");

				printf("File O:\n");

				for (uint64_t i = fileO.iPremier; i < fileO.iDernier; i++) {
					Client client = fileO.donneesClients[i];

					printf("Client %llu: classe=%d, duree=%llu, arrivee=%llu\n", i, client.classe, client.dureeService, client.minuteArrivee);
				}

				printf("File PR:\n");

				for (uint64_t i = filePR.iPremier; i < filePR.iDernier; i++) {
					Client client = filePR.donneesClients[i];

					printf("Client %llu: classe=%d, duree=%llu, arrivee=%llu\n", i, client.classe, client.dureeService, client.minuteArrivee);
				}

				printf("File PA:\n");

				for (uint64_t i = filePA.iPremier; i < filePA.iDernier; i++) {
					Client client = filePA.donneesClients[i];

					printf("Client %llu: classe=%d, duree=%llu, arrivee=%llu\n", i, client.classe, client.dureeService, client.minuteArrivee);
				}
			}

			nbArriveesGenerees(&nbArriveesO, &nbArriveesP);

			uint64_t nbArriveesPA = binomial(nbArriveesP, 0.3);
			uint64_t nbArriveesPR = nbArriveesP - nbArriveesPA;

			for (uint64_t i = 0; i < nbArriveesPA; i++) {
				Client client;

				client.classe = PRIORITAIRE_ABSOLUE;
				client.dureeService = dureeClient();
				client.minuteArrivee = temps;

				ajouterClient(&filePA, client);
			}

			for (uint64_t i = 0; i < nbArriveesPR; i++) {
				Client client;

				client.classe = PRIORITAIRE_RELATIVE;
				client.dureeService = dureeClient();
				client.minuteArrivee = temps;

				ajouterClient(&filePR, client);
			}

			for (uint64_t i = 0; i < nbArriveesO; i++) {
				Client client;

				client.classe = ORDINAIRE;
				client.dureeService = dureeClient();
				client.minuteArrivee = temps;

				ajouterClient(&fileO, client);
			}

			if (temps < 20) {
				printf("\n[ARRIVEES DES CLIENTS]\n");
				printf("----------\n");

				for (uint64_t i = 0; i < nbArriveesO; i++) {
					Client client = fileO.donneesClients[fileO.iDernier - nbArriveesO + i];

					printf("Ordinaire: duree = %llu\n", client.dureeService);
				}

				for (uint64_t i = 0; i < nbArriveesPR; i++) {
					Client client = filePR.donneesClients[filePR.iDernier - nbArriveesPR + 1 + i];

					printf("Prioritaire relatif: duree = %llu\n", client.dureeService);
				}

				for (uint64_t i = 0; i < nbArriveesPA; i++) {
					Client client = filePA.donneesClients[filePA.iDernier - nbArriveesPA + 1 + i];

					printf("Prioritaire absolu: duree = %llu\n", client.dureeService);
				}

				printf("\n[FILES]\n");
				printf("----------\n");

				printf("File O:\n");

				for (uint64_t i = fileO.iPremier; i < fileO.iDernier; i++) {
					Client client = fileO.donneesClients[i];

					printf("Client %llu: classe = %d, duree = %llu, arrivee = %llu\n", i, client.classe, client.dureeService, client.minuteArrivee);
				}

				printf("\n");

				printf("File PR:\n");

				for (uint64_t i = filePR.iPremier; i < filePR.iDernier; i++) {
					Client client = filePR.donneesClients[i];

					printf("Client %llu: classe = %d, duree = %llu, arrivee = %llu\n", i, client.classe, client.dureeService, client.minuteArrivee);
				}

				printf("\n");

				printf("File PA:\n");

				for (uint64_t i = filePA.iPremier; i < filePA.iDernier; i++) {
					Client client = filePA.donneesClients[i];

					printf("Client %llu: classe = %d, duree = %llu, arrivee = %llu\n", i, client.classe, client.dureeService, client.minuteArrivee);
				}
			}

			for (uint64_t index = 0; index < nbStations; index++) {
				if (stations[index] == 0) {
					Client client;

					if (!estVide(&filePA)) {
						client = retirerClient(&filePA);
					}
					else if (!estVide(&filePR)) {
						client = retirerClient(&filePR);
					}
					else if (!estVide(&fileO)) {
						client = retirerClient(&fileO);
					}
					else {
						continue;
					}

					stations[index] = client.dureeService;
					classeStations[index] = client.classe;
				}
			}

			uint64_t nbStationsPA = 0;

			for (uint64_t i = 0; i < nbStations; i++) {
				if (classeStations[i] == PRIORITAIRE_ABSOLUE) {
					nbStationsPA++;
				}
			}

			uint64_t nbPAEnAttente = filePA.iDernier - filePA.iPremier + 1;
			uint64_t pertesPA = nbPAEnAttente > 0 && nbStationsPA == nbStations ? nbPAEnAttente : 0;

			pertesP += pertesPA;

			for (uint64_t index = 0; index < nbStations; index++) {
				if (stations[index] > 0) {
					stations[index]--;
				}
				else {
					classeStations[index] = LIBRE;
				}
			}

			for (uint64_t i = 0; i < nbStations; i++) {
				if (stations[i] > 0) {
					switch (classeStations[i]) {
						case ORDINAIRE:
							tempsPresenceO++;
							tempsOccupationO++;

							break;
						case PRIORITAIRE_RELATIVE:
							tempsPresencePR++;
							tempsOccupationP++;

							break;
						case PRIORITAIRE_ABSOLUE:
							tempsPresencePA++;
							tempsOccupationP++;

							break;
					}
				}
				else {
					tempsInoccupation++;
				}
			}

			if (temps < 20) {
				printf("\n[STATIONS]\n");
				printf("----------\n");

				for (uint64_t i = 0; i < nbStations; i++) {
					char classeClient[TAILLE_MAX_CLASSE];

					classToString(classeStations[i], classeClient);

					printf("Station %llu: %s, duree restante: %llu\n", i, classeClient, stations[i]);
				}
			}
		}

		couts[nbStations - nbStationsMin] =
			15 * (tempsPresenceO / 60) +
			35 * (tempsPresencePR / 60) +
			45 * (tempsPresencePA / 60) +
			28 * (tempsOccupationO / 60) +
			33 * (tempsOccupationP / 60) +
			18 * (tempsInoccupation / 60) +
			15 * pertesO +
			20 * pertesP;
	}

	uint64_t indexOpt = rechercheCoutMin(couts, nbStationsMax - nbStationsMin + 1);

	return nbStationsMin + indexOpt;
}

void partie2(void) {
	srand(time(NULL));

	/* Declaration et initialisation des valeurs des paramètres */

	printf("-- DECLARATION ET INITIALISATION DES VALEURS DES PARAMETRES --\n\n");

	uint64_t nbStationsMin, nbStationsMax, tempsSimul;

	printf("Valeur du parametre nbStationsMin : ");
	scanf_s("%llu", &nbStationsMin);

	while (nbStationsMin <= 0) {
		printf("[ERREUR] : la valeur du parametre nbStationsMin doit etre > 0\n\n");

		printf("Valeur du parametre nbStationsMin : ");
		scanf_s("%llu", &nbStationsMin);
	}

	printf("Valeur du parametre nbStationsMax : ");
	scanf_s("%llu", &nbStationsMax);

	while (nbStationsMax <= nbStationsMin) {
		printf("[ERREUR] : la valeur du parametre nbStationsMax doit etre > nbStationsMin\n\n");

		printf("Valeur du parametre nbStationsMax : ");
		scanf_s("%llu", &nbStationsMax);
	}

	printf("Valeur du parametre tempsSimul : ");
	scanf_s("%llu", &tempsSimul);

	while (tempsSimul < 60) {
		printf("[ERREUR] : la valeur du parametre tempsSimul doit etre >= 60\n\n");

		printf("Valeur du parametre tempsSimul : ");
		scanf_s("%llu", &tempsSimul);
	}

	/* Simulation */

	printf("-- SIMULATION --\n");

	uint64_t resultat = nbStationsOptimal(nbStationsMin, nbStationsMax, tempsSimul);

	/* Resultat */

	printf("\n-- RESULTAT --\n\n");

	printf("Nombre de stations optimal : %llu", resultat);
}

int main(void) {
	// partie1();

	partie2();

	return 0;
}