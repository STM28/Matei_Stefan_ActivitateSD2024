#include<stdio.h>
typedef struct Santier Santier;
typedef struct Nod Nod;

struct Santier {
	char* numeProiect;
	int nrMuncitori;
	float suprafata;
};

struct Nod {
	Santier santier;
	Nod* next;
};

Santier initializareSantier(const char* numeProiect,int nrMuncitori,float suprafata)
{
	Santier santier;
	santier.numeProiect = (char*)malloc(strlen(numeProiect) + 1);
	strcpy(santier.numeProiect, numeProiect);
	santier.nrMuncitori = nrMuncitori;
	santier.suprafata = suprafata;
	return santier;
}

Nod* inserareInceput(Santier s, Nod* lista)
{
	Nod* nod=(Nod*)malloc(sizeof(Nod));
	nod->santier = s;
	nod->next = lista;
	return nod;
}

void afisareSantier(Santier s)
{
	printf("Santierul %s are %d muncitori si o suprafata de %.f metri patrati\n",s.numeProiect,s.nrMuncitori,s.suprafata);

}

void afisareLista(Nod* lista)
{
	while (lista != NULL)
	{
		//procesare
		afisareSantier(lista->santier);
		lista=lista->next;
		
	}
}

int sumaMuncitori(Nod* lista)
{
	int suma = 0;
	while (lista != NULL) {
		suma = suma + lista->santier.nrMuncitori;
		lista = lista->next;
	}
	return suma;

}

float densitate(Santier s)
{
	if (s.suprafata > 0)
	{
		return s.nrMuncitori / s.suprafata;
	}
	else return 0;
}

char* numeSantierDensMax(Nod* lista)
{
	float max = 0;
	char* aux=NULL;
	while (lista != NULL)
	{
		if (max < densitate(lista->santier))
		{
			max = densitate(lista->santier);
			aux = lista->santier.numeProiect;
		}
		lista = lista->next;
	}
	if (aux != NULL) {
		char* nume = (char*)malloc(strlen(aux) + 1);
		nume = strcpy(nume, aux);


		return nume;
	}
	else return NULL;
}

void stergereLista(Nod** lista)
{
	while ((*lista) != NULL)
	{
		free((*lista)->santier.numeProiect);
		Nod* aux;
		aux = (*lista)->next;
		free((*lista));
		(*lista) = aux;

	}
	(*lista) = NULL;

}

typedef struct NodLdi NodLdi;
struct NodLdi {
	Santier info;
	NodLdi* prev;
	NodLdi* next;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla {
	NodLdi* prim;
	NodLdi* ultim;
};

void inserareInceputLdi(ListaDubla* lista, Santier s) {
	NodLdi* aux = malloc(sizeof(NodLdi));
	aux->info = s;
	aux->next = lista->prim;
	aux->prev = NULL;
	if (lista->prim != NULL) {
		lista->prim->prev = aux;
		//lista->prim = aux;
	}
	else {
		//lista->prim = aux;
		lista->ultim = aux;
	}
	lista->prim = aux;
	
}

void afisareLdiDeLaInceput(ListaDubla lista)
{
	for (NodLdi* nod = lista.prim; nod != NULL; nod = nod->next)
		afisareSantier(nod->info);
}

void stergereSantier(ListaDubla* lista, const char* numeSantier)
{
	NodLdi* nod = lista->prim;
	while (nod != NULL)
	{
		if (strcmp(nod->info.numeProiect, numeSantier) == 0)
		{
			if (nod->prev == NULL)
			{
				if (nod->next == NULL)
				{
					lista->prim = NULL;
					lista->ultim = NULL;

				}
				else
				{
					nod->next->prev = NULL;
					lista->prim = nod->next;
				}
			}
			else {

				if (nod->next == NULL)
				{
					nod->prev->next = NULL;
					lista->ultim = nod->prev;
				}
				else
				{
					nod->prev->next = nod->next;
					nod->next->prev = nod->prev;
				}
			}
			free(nod->info.numeProiect);
			free(nod);
		}
		nod = nod->next;
	}

	
}


int calcNrTotalMuncitori(ListaDubla lista)
{
	int s = 0;
	for (NodLdi* i = lista.prim; i != NULL; i = i->next)
	{
		s += i->info.nrMuncitori;
	}
	return s;
}

int caclNrMuncitoriSuprafata(ListaDubla lista, int suprafata)
{
	int s = 0;
	for (NodLdi* i = lista.prim; i != NULL; i = i->next)
	{
		if(i->info.suprafata<suprafata)
		s += i->info.nrMuncitori;
	}
	return s;
}


void stergereCompleta(ListaDubla* lista)
{
	if (lista != NULL)
	{
		NodLdi* aux = lista->prim;
		while (aux != NULL)
		{
			free(aux->info.numeProiect);
			NodLdi* temp = aux->next;
			free(aux);
			aux = temp;
		}
		lista->prim = NULL;
		lista->ultim = NULL;
	}
}

int main()
{
	Nod* lista = NULL;
	Santier s1 = initializareSantier("Santier1", 10, 300);
	Santier s2 = initializareSantier("Santier2", 20, 200.7);
	Santier s3 = initializareSantier("Santier3", 121, 1500);
	lista=inserareInceput(s1, lista);
	lista=inserareInceput(s2, lista);
	lista=inserareInceput(s3, lista);
	//afisareLista(lista);
	//int suma = sumaMuncitori(lista);
	//printf("%d", suma);
	//printf("\n%s\n", numeSantierDensMax(lista));


	//stergereLista(&lista);
	//afisareLista(lista);
	//tema Stergere un nod(grija la refeacere legatura)
	ListaDubla listad;
	listad.prim = NULL;
	listad.ultim = NULL;
	inserareInceputLdi(&listad, s1);
	inserareInceputLdi(&listad, s2);
	inserareInceputLdi(&listad, s3);
	afisareLdiDeLaInceput(listad);
	stergereSantier(&listad,"Santier3");
	afisareLdiDeLaInceput(listad);

}
