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

int main()
{
	Nod* lista = NULL;
	Santier s1 = initializareSantier("Santier1", 10, 300);
	Santier s2 = initializareSantier("Santier2", 20, 200.7);
	Santier s3 = initializareSantier("Santier3", 121, 1500);
	lista=inserareInceput(s1, lista);
	lista=inserareInceput(s2, lista);
	lista=inserareInceput(s3, lista);
	afisareLista(lista);
	int suma = sumaMuncitori(lista);
	printf("%d", suma);
	printf("\n%s\n", numeSantierDensMax(lista));


	stergereLista(&lista);
	afisareLista(lista);
	//tema Stergere un nod(grija la refeacere legatura)
}
