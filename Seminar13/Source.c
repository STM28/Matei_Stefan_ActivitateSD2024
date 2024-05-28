#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct Autobuz Autobuz;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct Autobuz {
	int linie;
	char* capaLinie;
};

struct NodPrincipal {
	Autobuz info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

struct NodSecundar {
	NodPrincipal* nod;
	NodSecundar* next;
};

void inserarePrincipala(NodPrincipal** graf, Autobuz a) {
	NodPrincipal* nod = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nod->info = a;
	nod->next = NULL;
	nod->vecini = NULL;

	if ((*graf) != NULL)
	{
		NodPrincipal* temp = (*graf);
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = nod;
	}
	else
	{
		(*graf) = nod;
	}
}

NodPrincipal* cautaLinie(NodPrincipal* graf, int linie)
{
	while (graf && graf->info.linie != linie)
	{
		graf = graf->next;
	}

	return graf;
}

Autobuz initializareAutobuz(int linie, const char* capat) {
	Autobuz a;
	a.linie = linie;
	a.capaLinie = (char*)malloc(sizeof(char) * (strlen(capat) + 1));
	strcpy(a.capaLinie, capat);
	return a;
}

NodSecundar* inserareSecundara(NodSecundar* cap, NodPrincipal* info)
{
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->next = NULL;
	nou->nod = info;
	if (cap)
	{
		NodSecundar* p = cap;
		while (p->next)
		{
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else
	{
		return nou;
	}
}

void inserareMuchie(NodPrincipal* graf, int linieStart, int linieStop)
{
	NodPrincipal* nodStart = cautaLinie(graf, linieStart);
	NodPrincipal* nodStop = cautaLinie(graf, linieStop);
	nodStart->vecini = inserareSecundara(nodStart->vecini, nodStop);
	nodStop->vecini = inserareSecundara(nodStop->vecini, nodStart);
}

#pragma region Coada

typedef struct nodCoada NodCoada;
struct nodCoada {
	int id;
	NodCoada* next;
};

void inserareCoada(NodCoada** cap, int id) {
	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
	nou->id = id;
	nou->next = NULL;
	if (*cap)
	{
		NodCoada* p = *cap;
		while (p->next)
		{
			p = p->next;
		}
		p->next = nou;
	}
	else
	{
		*cap = nou;
	}
}

void inserareStiva(NodCoada** cap, int id)
{
	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
	nou->id = id;
	nou->next = *cap;
	*cap = nou;
}

int extrageDinCoada(NodCoada** cap)
{
	if (*cap)
	{
		int rezultat = (*cap)->id;
		NodCoada* temp = (*cap)->next;
		free(*cap);
		*cap = temp;
		return rezultat;
	}
	else
	{
		return -1;
	}
}

int extrageDinStiva(NodCoada** cap)
{
	return extrageDinCoada(cap);
}

#pragma endregion

int getNrNoduri(NodPrincipal* graf)
{
	int s = 0;
	while (graf)
	{
		s++;
		graf = graf->next;
	}
	return s;
}

void afisareAutobuz(Autobuz a)
{
	printf("%d. are capatul la %s \n", a.linie, a.capaLinie);
}

void afisareCuParcurgereInAdancime(NodPrincipal* graf, int nodPlecare)
{
	//initializari
	NodCoada* stiva = NULL;
	int nrNoduri = getNrNoduri(graf);
	char* vizitate = (char*)malloc(sizeof(char) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++)
	{
		vizitate[i] = 0;
	}
	inserareStiva(&stiva, nodPlecare);
	vizitate[nodPlecare] = 1;

	while (stiva)
	{
		//extragem nodul din coada
		int idNodCurent = extrageDinStiva(&stiva);
		NodPrincipal* nodCurent = cautaLinie(graf, idNodCurent);
		afisareAutobuz(nodCurent->info);

		NodSecundar* temp = nodCurent->vecini;
		//inserare in coada si marcare ca vizitat fiecare vecin
		while (temp)
		{
			if (vizitate[temp->nod->info.linie] == 0)
			{
				vizitate[temp->nod->info.linie] = 1;
				inserareStiva(&stiva, temp->nod->info.linie);
			}
			temp = temp->next;
		}
	}

	if (vizitate)
	{
		free(vizitate);
	}
}


void afisareCuParcurgereInLatime(NodPrincipal* graf, int nodPlecare)
{
	//initializari
	NodCoada* coada = NULL;
	int nrNoduri = getNrNoduri(graf);
	char* vizitate = (char*)malloc(sizeof(char) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++)
	{
		vizitate[i] = 0;
	}
	inserareCoada(&coada, nodPlecare);
	vizitate[nodPlecare] = 1;

	while (coada)
	{
		//extragem nodul din coada
		int idNodCurent = extrageDinCoada(&coada);
		NodPrincipal* nodCurent = cautaLinie(graf, idNodCurent);
		afisareAutobuz(nodCurent->info);

		NodSecundar* temp = nodCurent->vecini;
		//inserare in coada si marcare ca vizitat fiecare vecin
		while (temp)
		{
			if (vizitate[temp->nod->info.linie] == 0)
			{
				vizitate[temp->nod->info.linie] = 1;
				inserareCoada(&coada, temp->nod->info.linie);
			}
			temp = temp->next;
		}
	}
}

void stergereListaVecini(NodSecundar** cap) {
	NodSecundar* p = (*cap);
	while (p)
	{
		NodSecundar* aux = p;
		p = p->next;
		free(aux);
	}
	*cap = NULL;
}

void stergereGraf(NodPrincipal** graf) {
	while (*graf)
	{
		free((*graf)->info.capaLinie);
		NodSecundar* p = (*graf)->vecini;
		while (p)
		{
			NodSecundar* aux = p;
			p = p->next;
			free(aux);
		}
		NodPrincipal* temp = (*graf);
		*graf = temp->next;
		free(temp);
	}
}

void main()
{
	NodPrincipal* graf = NULL;

	inserarePrincipala(&graf, initializareAutobuz(0, "Roamana"));
	inserarePrincipala(&graf, initializareAutobuz(1, "Universitate"));
	inserarePrincipala(&graf, initializareAutobuz(2, "Unirii"));
	inserarePrincipala(&graf, initializareAutobuz(3, "Victoriei"));
	inserarePrincipala(&graf, initializareAutobuz(4, "Militari"));

	inserareMuchie(graf, 0, 4);
	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 3, 4);
	inserareMuchie(graf, 2, 4);

	afisareCuParcurgereInLatime(graf, 0);
	printf("\n\n");
	afisareCuParcurgereInAdancime(graf, 0);

	stergereGraf(graf);
	return 0;
}