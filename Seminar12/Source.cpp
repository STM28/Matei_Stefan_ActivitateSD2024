#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>


typedef struct Autobuz Autobuz;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct Autobuz {
	int linie;
	char* capLinie;
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

//functie de inserare la sfarsit in lista principala
//functie de cautare dupa linie
//functie de inserare in lista secundara
//functie de inserare muchie

void inserarePrincipala(NodPrincipal** graf, Autobuz a){
	NodPrincipal* nod=(NodPrincipal*)malloc(sizeof(NodPrincipal));
	nod->info = a;
	nod->next = NULL;
	nod->vecini = NULL;
	if ((*graf) != NULL) {
		NodPrincipal* temp = *graf;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = nod;
	}
	else
	{
		*graf = nod;
	}
}


Autobuz initializareAutobuz(int linie, const char* capat) {
	Autobuz a;
	a.linie = linie;
	a.capLinie = (char*)malloc(sizeof(char) * (strlen(capat) + 1));
	strcpy(a.capLinie, capat);
	return a;
}

NodPrincipal* cautaLinie(NodPrincipal* graf, int linie)
{
	while (graf && graf->info.linie != linie)
	{
		graf = graf->next;
	}
	return graf;
}

NodSecundar* inserareSecundara(NodSecundar* cap, NodPrincipal* info)
{
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->next = NULL;
	nou->nod = info;
	if (cap) {
		NodSecundar* p = cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
		return cap;

	}
	else {
		return nou;
	}

}

void inserareMuchie(NodPrincipal* graf,int linieStart, int linieStop) {
	NodPrincipal* nodStart=cautaLinie(graf,linieStart);
	NodPrincipal* nodStop=cautaLinie(graf, linieStop);
	nodStart->vecini = inserareSecundara(nodStart->vecini, nodStop);
	nodStop->vecini = inserareSecundara(nodStop->vecini, nodStart);
}



void main(){
	NodPrincipal* graf=NULL;

	inserarePrincipala(&graf, initializareAutobuz(0, "Romana"));
	inserarePrincipala(&graf, initializareAutobuz(1, "Universitate"));
	inserarePrincipala(&graf, initializareAutobuz(2, "Unirii"));
	inserarePrincipala(&graf, initializareAutobuz(3, "Piata Victoriei"));
	inserarePrincipala(&graf, initializareAutobuz(4, "Militari"));

	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 0, 4);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 2, 4);
	inserareMuchie(graf, 3, 4);

}