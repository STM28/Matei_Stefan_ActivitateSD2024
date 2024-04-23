#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include<malloc.h>
#include<string.h>

typedef struct Nod Nod;
typedef struct Rezervare Rezervare;

struct Rezervare
{
	int id;
	char* numeClient;
	int nrPersoane;
};

struct Nod {
	Nod* stanga;
	Nod* dreapta;
	Rezervare info;
};

Rezervare citireRezervare(FILE* f)
{
	Rezervare r;
	char aux[30];
	fscanf(f, "%d", &r.id);
	fscanf(f, "%s", &aux);
	r.numeClient = malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(r.numeClient, aux);
	fscanf(f, "%d", &r.nrPersoane);
	return r;
}

Nod* inserareInArbore(Nod* arbore, Rezervare rez)
{
	if (arbore != NULL)
	{
		if (arbore->info.id < rez.id)
		{
			arbore->dreapta = inserareInArbore(arbore->dreapta, rez);
		}
		else
		{
			arbore->stanga = inserareInArbore(arbore->stanga, rez);
		}
	}
	else
	{
		Nod* temp = (Nod*)malloc(sizeof(Nod));
		temp->info = rez;
		temp->dreapta = NULL;
		temp->stanga = NULL;
		arbore = temp;
	}
	return arbore;
}

void citireFisier(char* numeFisier,Nod** radacina)
{
	int nrRez;
	FILE* f = fopen(numeFisier, "r");
	fscanf(f, "%d", &nrRez);
	for (int i = 0; i < nrRez; i++)
	{
		Rezervare r;
		r=citireRezervare(f);
		*radacina = inserareInArbore(*radacina, r);
	}

}
void afisareRezervare(Rezervare r)
{
	printf("Rezervarea cu ID-ul %d a fost facuta de %s pentru %d persoane\n",
		r.id, r.numeClient, r.nrPersoane);
}
void afisareArborePreordine(Nod* arbore)
{
	if (arbore != NULL)
	{
		afisareRezervare(arbore->info);
		afisareArborePreordine(arbore->stanga);
		afisareArborePreordine(arbore->dreapta);
	}
}
void afisareArboreInordine(Nod* arbore)
{
	if (arbore != NULL)
	{
		
		afisareArboreInordine(arbore->stanga);
		afisareRezervare(arbore->info);
		afisareArboreInordine(arbore->dreapta);
	}
}

void afisareArborePostordine(Nod* arbore)
{
	if (arbore != NULL)
	{

		afisareArboreInordine(arbore->stanga);
		afisareArboreInordine(arbore->dreapta);
		afisareRezervare(arbore->info);
	}
}

Rezervare cautarerezervareDupaId(Nod* rad, int id)
{
	if (rad)
	{
		if (rad->info.id < id) {
			return cautarerezervareDupaId(rad->dreapta, id);
		}
		else
			if (rad->info.id > id)
				return cautarerezervareDupaId(rad->stanga, id);
			else
				return rad->info;
	}
	else
	{
		Rezervare r;
		r.id = -1;
		r.numeClient = NULL;
		r.nrPersoane = -1;
		return r;
	}
}
int calculnrTotalPersoane(Nod* rad)
{
	if (rad)
	{
		int rPersoane = rad->info.nrPersoane;
		int sPersoane = calculnrTotalPersoane(rad->stanga);
		int dPersoane = calculnrTotalPersoane(rad->dreapta);
		int suma = rPersoane + sPersoane + dPersoane;
		
		return suma;
	}
	return 0;
}


void main()
{
	Nod* radacina = NULL;
	citireFisier("Rezervari.txt", &radacina);
	afisareArborePreordine(radacina);
	printf("\nIIIIIIIIIIIIIIIIIIIIIII\n");
	afisareArboreInordine(radacina);
	printf("\nIIIIIIIIIIIIIIIIIIIIIII\n");
	afisareArborePostordine(radacina);
	printf("\nIIIIIIIIIIIIIIIIIIIIIII\n");
	afisareRezervare(cautarerezervareDupaId(radacina, 8));
	printf("\nIIIIIIIIIIIIIIIIIIIIIII\n");
	printf("\nNumar total de persoane:");
	printf("\nNumar total de persoane:%d",calculnrTotalPersoane(radacina));

}