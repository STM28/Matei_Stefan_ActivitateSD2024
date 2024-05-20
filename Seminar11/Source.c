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

Nod* rotireLaDreapta(Nod* rad)
{
	Nod* aux = rad->stanga;
	if (rad)
	{
		rad->stanga = aux->dreapta;
		aux->dreapta = rad;
	}
	return aux;
}

Nod** rotireLaStanga(Nod* rad)
{
	if (rad)
	{
		Nod* aux = rad->dreapta;
		rad->dreapta = aux->stanga;
		aux->stanga = rad;
		return aux;
	}
	else
		return NULL;
}

int inaltimeArbore(Nod* rad)
{
	if (rad)
	{
		int inaltimeStanga = inaltimeArbore(rad->stanga);
		int inlatimeDreapta = inaltimeArbore(rad->dreapta);
		/*if (inaltimeStanga > inlatimeDreapta)
			maxim = inaltimeStanga;
		else {
			maxim = inlatimeDreapta;
		}
		maxim = maxim + 1;
		return maxim;*/
		return 1 + (inaltimeStanga > inlatimeDreapta ? inaltimeStanga : inlatimeDreapta);

	}
	else {
		return 0;
	}
}


int calculGradEchilibru(Nod* rad)
{
	if (rad)
	{
		int inaltimeStanga = inaltimeArbore(rad->stanga);
		int inlatimeDreapta = inaltimeArbore(rad->dreapta);
		return inaltimeStanga - inlatimeDreapta;

	}
	else
	{
		return 0;
	}
}

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
		int grad = calculGradEchilibru(arbore);
		if (grad == 2)
		{
			if (calculGradEchilibru(arbore->stanga) == 1)
			{
				arbore = rotireLaDreapta(arbore);
			}
			else
			{
				arbore->stanga = rotireLaStanga(arbore->stanga);
				arbore = rotireLaDreapta(arbore);
			}
		}
		if (grad == -2)
		{
			if (calculGradEchilibru(arbore->dreapta) == 1)
			{
				arbore = rotireLaDreapta(arbore->dreapta);
			}
			arbore = rotireLaStanga(arbore);
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

void citireFisier(char* numeFisier, Nod** radacina)
{
	int nrRez;
	FILE* f = fopen(numeFisier, "r");
	fscanf(f, "%d", &nrRez);
	for (int i = 0; i < nrRez; i++)
	{
		Rezervare r;
		r = citireRezervare(f);
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


void stergereArbore(Nod** rad)
{
	if (rad)
	{
		stergereArbore(&(*rad)->stanga);
		stergereArbore(&(*rad)->dreapta);
		free((*rad)->info.numeClient);
		free((*rad));
		(*rad) = NULL;
	}
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
	
	printf("\nNumar total de persoane:%d", calculnrTotalPersoane(radacina));
	stergereArbore(&radacina);

}