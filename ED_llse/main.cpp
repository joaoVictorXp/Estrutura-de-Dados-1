#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 100
#define AP 100

typedef struct{
	int id;
	char nome[N];
	float tam;
}Aplic;

typedef struct{
	Aplic app;
	int prox;
}No;

typedef struct{
	No L[N];
	int disp;
	int IL;
}LLSE;

void start(LLSE *list);
void ler(LLSE *MyApp, LLSE *Store);
void add(LLSE *list, int id, float tam, char nome[]);

int main(int argc, char** argv)
{
	system("color 3f"); system("title Trabalho de Estrutura de Dados");
	//Declaração dos Vetores de Estruturas
	
	LLSE MyApp, Store;
	
	start(&MyApp);
	start(&Store);
	printf("prox = %i\n", MyApp.disp);
	ler(&MyApp, &Store);
	
	for(int i = MyApp.IL, j = i; i != -1 ; i = MyApp.L[j].prox){
		printf("i == %i\n", i);
		printf("id = %i -- Tam = %.2f -- Nome = %s\n\n", MyApp.L[i].app.id, MyApp.L[i].app.tam, MyApp.L[i].app.nome);
		j = i;
	}
	
		printf("\n\nsegundo for\n");
	for(int i = 0; i < MyApp.disp; i++){
		printf("id = %i -- Tam = %.2f -- Nome = %s\n\n", MyApp.L[i].app.id, MyApp.L[i].app.tam, MyApp.L[i].app.nome);
	}
	//menu(storeED ,MobileED, RumED, &tamstoreED, &tamMobileED, &tamRumED);
	
	return 0;
}

void start(LLSE *list){
	list->disp = 0;
	list->L[0].prox = -5;
}

void ler(LLSE *MyApp, LLSE *Store){
	//variaveis auxiliares para receber os dados dos arquivos de textos
	int id;
	float tam;
	char nome[N];
	FILE *arq;
	FILE *arqMob;
	arq = fopen("StoreED.txt", "r");
	arqMob = fopen("MobileED.txt", "r");
	
	if(arq != NULL){
		while(fscanf(arq, "%i %s %f", &id, nome, &tam) != EOF){
			add(Store, id, tam, nome);
		}
	}
	else{
		printf("\t-- Aplicativos da StoreED nao foram carregados! -- \n\n\t");
		system("pause");
		
	}
	
	if(arqMob != NULL){
		while(fscanf(arqMob, "%i %s %f", &id, nome, &tam) != EOF){
			add(MyApp, id, tam, nome);
		}
	}
	else{
		printf("\t-- Meus Aplicativos nao Foram Carregados! -- \n\n\t");
		system("pause");
	}
	
	fclose(arq);
	fclose(arqMob);
	
}

void add(LLSE *list, int id, float tam, char nome[]){
	int i = list->disp;
	int k2;
	printf("disp = %i\n", list->disp);
	if(list->L[i].prox == -5){ //PRIMEIRO ELEMENTO
		printf("-- primeiro ok? -- \n\n");
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		list->L[i].prox = -1;
		list->disp++;
		list->IL = i;
		
	}
	else if(list->disp < N){
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		
		if(list->L[list->IL].app.tam > tam){
			list->L[i].prox = list->IL;
			list->IL = i;
		}
		else{
			k2 = list->IL;
			for(int k = list->L[list->IL].prox;  ; k = list->L[k2].prox){
				printf("k = %i\n\n", k);
				if(list->L[k].app.tam > tam){ //meio
					printf("if 1\n");
					list->L[i].prox = k;
					list->L[k2].prox = i;
					break;
				}
				else if(k == -1){ //final
					printf("if 2\n");
					list->L[i].prox = -1;
					list->L[k].prox = i;
					break;
				}
				else{ //armazena o valor prox do anterior
					printf("else\n");
					k2 = k;
				}	
			}
		}
		list->disp++;
	}
	else
		return;
}
