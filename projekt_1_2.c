/*
 * autor - Vladimír Veèerek
 * názov -projekt_1_2.c
 * verzia -
 * dátum -2017
 */

#include <stdio.h>
#include <string.h>

struct blok {
	void* pointer_o_b;
	void* pointer_v_za;
	struct blok *pointer_b_za;
	struct blok *pointer_b_pred;

};

typedef struct blok blok;

struct vlastnosti_pola {
	void *najb_volny_pointer;
	void *najb_obsadeny_za_pointer;
	struct blok *naj_k_volnemu_pred_blok;
	struct blok *prvy_blok;
	unsigned int celkova_kapacita;
//	unsigned int volne_miesto;
	unsigned int zaplnene_miesto;

};
typedef struct vlastnosti_pola pole;

void *Zaciatok;
int nanic;

void* najblizsi_volny(unsigned int velkost) {

	struct vlastnosti_pola* tmp = (struct vlastnosti_pola*) Zaciatok;

	if (tmp->zaplnene_miesto == 0) {
		if ((tmp->celkova_kapacita - sizeof(struct vlastnosti_pola)) > velkost) {
			return tmp->najb_volny_pointer;
		} else {
			return NULL;
		}
	} else {
		while (((int) tmp->najb_obsadeny_za_pointer - (int) tmp->najb_volny_pointer - sizeof(blok)) < velkost) {

			if (tmp->naj_k_volnemu_pred_blok == NULL) {
				tmp->najb_volny_pointer = tmp->prvy_blok->pointer_v_za;
			} else {
				if (tmp->naj_k_volnemu_pred_blok->pointer_b_za == NULL) {
					tmp->najb_obsadeny_za_pointer = (void*) (tmp->celkova_kapacita + (int) Zaciatok);

					if(((int) tmp->najb_obsadeny_za_pointer - (int) tmp->najb_volny_pointer - sizeof(blok)) < velkost){
						return tmp->najb_volny_pointer;
					}
					return NULL;
				}

				tmp->najb_volny_pointer = tmp->naj_k_volnemu_pred_blok->pointer_b_za->pointer_v_za;
			}
			while ((int) tmp->najb_obsadeny_za_pointer < (int) tmp->najb_volny_pointer) {

				tmp->naj_k_volnemu_pred_blok = tmp->naj_k_volnemu_pred_blok->pointer_b_za;
				tmp->najb_obsadeny_za_pointer =tmp->naj_k_volnemu_pred_blok->pointer_b_za->pointer_o_b;
			}
		}



	}
	return tmp->najb_volny_pointer;

}

void najblizsi_zaplneny(struct blok pom) {

}

void *memory_alloc(unsigned int size) {

	struct vlastnosti_pola* tmp = (struct vlastnosti_pola*) Zaciatok;

	void* pom = najblizsi_volny(size);

	struct blok* novy = (struct blok*) pom;

	novy->pointer_b_pred = tmp->naj_k_volnemu_pred_blok;
	novy->pointer_b_za = tmp->naj_k_volnemu_pred_blok->pointer_b_za;
	novy->pointer_o_b = (void*)((int)pom + sizeof(blok));
	novy->pointer_v_za = novy->pointer_b_za->pointer_v_za;






}

int memory_free(void *valid_ptr) {
	return 0;
}

int memory_check(void *ptr) {
	return 0;
}

void memory_init(void *ptr, unsigned int size) {
	Zaciatok = ptr;
	struct vlastnosti_pola* tmp = (struct vlastnosti_pola*) Zaciatok;

	tmp->celkova_kapacita = size;
	tmp->najb_volny_pointer = (void*) ((int) Zaciatok + sizeof(struct vlastnosti_pola));
	tmp->najb_obsadeny_za_pointer = (void*) (size + (int) Zaciatok);
//	tmp->volne_miesto = size;
	tmp->zaplnene_miesto = 0;
	tmp->naj_k_volnemu_pred_blok = NULL;

}

int main() {
	char region[50];
	memory_init(region, 50);

	struct vlastnosti_pola* tmp = (struct vlastnosti_pola*) Zaciatok;
		printf("pointer prve miesto %d \n",Zaciatok);
		printf("pointer prve miesto %d \n",sizeof(pole));
		printf("pointer na prve miesto %d \n",(int)tmp->najb_volny_pointer);
		printf("pointer na posledne miesto %d\n",(int)tmp->najb_obsadeny_za_pointer);

}
