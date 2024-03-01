#include <stdio.h>
#include <malloc.h>

struct Farmacie {
	int id;
	char* nume;
	float suprafata;
};

struct Farmacie initFarmacie(int id, const char* nume, float suprafata) {
	struct Farmacie f;
	f.id = id;
	f.nume = (char*)malloc( /*strlen(nume) + 1*/ sizeof(char*) * (strlen(nume) + 1));
	strcpy(f.nume, nume);
	f.suprafata = suprafata;

	return f;
}

void afisareFarmacie(struct Farmacie f) {
	printf("%d. %s are o suprafata de %5.2f mp.\n", f.id, f.nume, f.suprafata);
}

void afisareVector(struct Farmacie* v, int nr) {
	for (int i = 0; i < nr; i++) {
		afisareFarmacie(v[i]);
	}
	printf("\n");
}

struct Farmacie* copiereVector(struct Farmacie* v, int dim_v, int n) {
	if (n <= dim_v && n > 0) {
		struct Farmacie* v_new = (struct Farmacie*)malloc(sizeof(struct Farmacie) * n);
		for (int i = 0; i < n; i++) {
			v_new[i] = initFarmacie(v[i].id, v[i].nume, v[i].suprafata);
		}

		return v_new;
	}
	else {
		printf("Numarul de obiecte este invalid.\n");
		return NULL;
	}
}

struct Farmacie* copiereVectorSuprafata(struct Farmacie* v, int dim_v, float suprafata, int* dim_nou) {
	*dim_nou = 0;

	for (int i = 0; i < dim_v; i++) {
		if (v[i].suprafata < suprafata) (*dim_nou)++;
	}

	if (*dim_nou > 0) {
		struct Farmacie* v_nou = (struct Farmacie*)malloc(sizeof(struct Farmacie) * (*dim_nou));

		int k = 0;
		for (int i = 0; i < dim_v; i++) {
			if (v[i].suprafata < suprafata) {
				v_nou[k++] = initFarmacie(v[i].id, v[i].nume, v[i].suprafata);
			}
		}

		return v_nou;
	}
	else {
		printf("Nu exista farmacii in vector care sa verifice conditia.\n");
		return NULL;
	}
}

void stergeVector(struct Farmacie** v, int* n) {
	for (int i = 0; i < (*n); i++) {
		free((*v)[i].nume);
		(*v)[i].nume = NULL;
	}
	free(*v);
	(*n) = 0;
	*v = NULL;
}

struct Farmacie findByID(struct Farmacie* v, int dim_v, int ID) {
	for (int i = 0; i < dim_v; i++) {
		if (v[i].id == ID) {

			return initFarmacie(v[i].id, v[i].nume, v[i].suprafata);
		}
	}

	return initFarmacie(0, "N/A", 0);
}

int main() {
	int nrFarmacii = 4;
	struct Farmacie* v_farm = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrFarmacii);

	for (int i = 0; i < nrFarmacii; i++) {
		v_farm[i] = initFarmacie(i + 1, "Farmacie", 45 * (i + 1) + 10);
	}

	afisareVector(v_farm, nrFarmacii);

	int dimNou = 2;
	struct Farmacie* v_copie = copiereVector(v_farm, nrFarmacii, dimNou);
	afisareVector(v_copie, dimNou);

	int dimNou2;

	v_farm[3].suprafata = 99;
	struct Farmacie* v_copie2 = copiereVectorSuprafata(v_farm, nrFarmacii, 101.00, &dimNou2);
	afisareVector(v_copie2, dimNou2);

	struct Farmacie f = findByID(v_farm, nrFarmacii, 7);
	afisareFarmacie(f);
	free(f.nume);

	stergeVector(&v_copie2, &dimNou2);
	stergeVector(&v_copie, &dimNou);
	stergeVector(&v_farm, &nrFarmacii);
}