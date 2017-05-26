#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 100
#define AP 20

typedef struct{
	int id;
	char nome[N];
	float tam;
}Aplic;

typedef struct{
	Aplic app;
	int prox;
	int back;
}No;

typedef struct{
	int IA, FA;
	int IL, FL;
	Aplic app[AP];
}LLV;

typedef struct{
	No L[AP];
	int disp;
	int IL;
	int FL;
	int total;
}LLSE;

typedef struct{
	No L[AP];
	int disp;
	int IL;
	int FL;
	int total;
}LLDE;

void Start_LLV(LLV *list){
	list->IA = 0;
	list->FA = AP;
	list->IL = -1;
	list->FL = -1;
}

void Start_LLSE(LLSE *list){
	list->disp = 0;
	for(int i = 0; i < AP; i++){
		list->L[i].prox = i + 1;
	}
	list->IL = -5;
	list->FL = -5;
	list->L[AP].prox = -1;
	list->total = 0;
}

void Start_LLDE(LLDE *list){
	list->disp = 0;
	for(int i = 0; i < AP; i++){
		list->L[i].prox = i + 1;
		list->L[i].back = i - 1;
	}
	list->IL = -5;
	list->FL = -5;
	list->L[AP].prox = -1;
	list->total = 0;
}

void Add_LLV(LLV *list, int id, float tam, char nome[]){
	//verifica se ja possui algum app igual instalado
	for(int s = list->IL; s <= list->FL; s++){
		if(list->app[s].id == id){
			return;
		}
	}
	int j = list->IL;
	int k = list->FL;
	//ADICIONA NO INICIO
	if(list->IL == -1 || tam < list->app[j].tam){
		if((list->IA == list->IL) && (list->FA == list->FL)){
			return;	
		}
		else if(list->IL == -1){
		
			list->IL = list->IA;
			list->FL = list->IA;
		
		}
		else if(list->IL > list->IA){
			
			list->IL = list->IL - 1;
		
		}
		else
		{
			for(int i = list->FL; i >= list->IL; i--){
				
				list->app[i+1].id = list->app[i].id;
				list->app[i+1].tam = list->app[i].tam;
				strcpy(list->app[i+1].nome, list->app[i].nome);
				
			}
			list->FL+=1;
		}
		
		list->app[list->IL].id = id;
		list->app[list->IL].tam = tam;
		strcpy(list->app[list->IL].nome, nome);
	}
	//ADICIONA NO FINAL
	else if(tam > list->app[k].tam){
		if((list->IA == list->IL) && (list->FA == list->FL)){
			return;	
		}
		
		else if(list->FL == -1){
			list->IL = list->IA;
			list->FL = list->IA;
		}
		
		else if(list->FL < list->FA){
			list->FL = list->FL + 1;
		}
		
		else{
			for(int i = list->IL; i < list->FL; i++)
			{
				list->app[i-1].id = list->app[i].id;
				list->app[i-1].tam = list->app[i].tam;
				strcpy(list->app[i-1].nome, list->app[i].nome);
			}
			list->IL-=1;
		}
		
		list->app[list->FL].id = id;
		list->app[list->FL].tam = tam;
		strcpy(list->app[list->FL].nome, nome);
	}
	//ADICIONA NO MEIO E VERIFICA QUAL A MELHOR POSIÇÃO PARA ADICINAR
	else
	{
		int k;
		for(int i = list->IL; i <= list->FL; i++){
			if(tam < list->app[i].tam){
				k = i;
				break;
			}
		}
		
		if((list->IL == list->IA && list->FA == list->FL)){
			return;
		}
		else if(list->IL == -1){
			list->IL = list->IA;
			list->FL = list->IA;
		}
		else if(list->FL-k < k-list->IL)
		{
			if(list->FL < list->FA){
				for(int i = list->FL; i >= k; i--){
					list->app[i+1].id = list->app[i].id;
					list->app[i+1].tam = list->app[i].tam;
					strcpy(list->app[i+1].nome, list->app[i].nome);
				}
				list->FL+=1;
			}
			else{
				if(list->IL > list->IA){
					for(int i = list->IL; i <= k; i++){
						list->app[i-1].id = list->app[i].id;
						list->app[i-1].tam = list->app[i].tam;
						strcpy(list->app[i-1].nome, list->app[i].nome);
					}
					list->IL-=1;
				}
				else{
					return;
				}
			}
		}
		else if(list->FL-k > k-list->IL)
		{
			if(list->IL > list->IA){
				for(int i = list->IL; i <= k; i++){
					list->app[i-1].id = list->app[i].id;
					list->app[i-1].tam = list->app[i].tam;
					strcpy(list->app[i-1].nome, list->app[i].nome);
				}
				list->IL-=1;
			}
			else{
				if(list->FL < list->FA){
					for(int i = list->FL; i >= k; i--){
						list->app[i+1].id = list->app[i].id;
						list->app[i+1].tam = list->app[i].tam;
						strcpy(list->app[i+1].nome, list->app[i].nome);
					}
					list->FL+=1;			
				}
				else{
					return;
				}
			}
		}
		else{
			if(list->FL < list->FA){
				for(int i = list->FL; i >= k; i--){
					list->app[i+1].id = list->app[i].id;
					list->app[i+1].tam = list->app[i].tam;
					strcpy(list->app[i+1].nome, list->app[i].nome);
				}
				list->FL+=1;
			}
			else{
				if(list->IL > list->IA){
					for(int i = list->IL; i <= k; i++){
						list->app[i-1].id = list->app[i].id;
						list->app[i-1].tam = list->app[i].tam;
						strcpy(list->app[i-1].nome, list->app[i].nome);
					}
					list->IL-=1;
				}
				else{
					return;
				}
			}
		}
		
		list->app[k].id = id;
		list->app[k].tam = tam;
		strcpy(list->app[k].nome, nome);
		
	}
}

int NoLLSE(LLSE *list){
    int n;
    if(list->disp == -1) {
        return -2;
    }
    n = list->disp;
    list->disp = list->L[list->disp].prox;
    return n;
}

int NoLLDE(LLDE *list){
    int n;
    if(list->disp == -1) {
        return -2;
    }
    n = list->disp;
    list->disp = list->L[list->disp].prox;
    return n;
}

void Add_LLSE(LLSE *list, int id, float tam, char nome[]){
	int i = NoLLSE(list);
	
	if(i != -2){
		list->total++;
		if(list->IL == -5){ //PRIMEIRO ELEMENTO
		
			list->L[i].app.id = id;
			list->L[i].app.tam = tam;
			strcpy(list->L[i].app.nome, nome);
			list->L[i].prox = -1;
			list->IL = i;
			list->FL = i;

			return;
		}
		//EVITAR REPETIÇOES DE ELEMENTOS
		for(int k = list->IL; k != -1; k = list->L[k].prox)
		{
			if(id == list->L[k].app.id){
				return;
			}
		}
		//PASSA OS DADOS PARA O DISPONIVEL
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		
		//ADICIONA NO INICIO
		if(list->L[list->IL].app.tam <= tam)
		{
			list->L[i].prox = list->IL;
			list->IL = i;
		}
		//ADICIONA NO FINAL
		else if(list->L[list->FL].app.tam >= tam)
		{
			list->L[i].prox = -1;
			list->L[list->FL].prox = i;
			list->FL = i;
		}
		//ADICIONA NO MEIO
		else{
			int k2 = list->IL;
			for(int k = list->IL;  ; k = list->L[k].prox)
			{				
				if(list->L[k].app.tam <= tam){ //meio					
					list->L[i].prox = k;
					list->L[k2].prox = i;
					break;
				}
				else{ //armazena o valor prox do anterior
					k2 = k;
				}	
			}
		}
	}
}


void Add_LLDE(LLDE *list, int id, float tam, char nome[]){
	int i = NoLLDE(list);
	
	if(i != -2){
		list->total++;
		if(list->IL == -5){ //PRIMEIRO ELEMENTO
		
			list->L[i].app.id = id;
			list->L[i].app.tam = tam;
			strcpy(list->L[i].app.nome, nome);
			list->L[i].prox = -1;
			list->IL = i;
			list->FL = i;

			return;
		}
		
		//EVITA REPETICÕES DE ELEMENTOS
		for(int k = list->IL, n = list->FL; k != -1 || n != -1; k = list->L[k].prox, n = list->L[n].back)
		{
			if(id == list->L[k].app.id || id == list->L[n].app.id){
				return;		//se existir algum app semelhante ja instalado ele para
			}
		}
		//PASSA OS DADOS PARA O DISPONIVEL
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		//ADCIONA NO INICIO
		if(list->L[list->IL].app.tam <= tam)
		{
			list->L[list->IL].back = i;
			list->L[i].prox = list->IL;
			list->L[i].back = -1;
			
			list->IL = i;
		}
		//ADICIONA NO FINAL
		else if(list->L[list->FL].app.tam >= tam)
		{
			list->L[i].back = list->FL;
			list->L[i].prox = -1;
			list->L[list->FL].prox = i;
			list->FL = i;
			
		}
		//ADICIONA NO MEIO
		else{
			for(int k = list->IL, n = list->FL; k != -1 || n != -1; k = list->L[k].prox, n = list->L[n].back)
			{				
				if(list->L[k].app.tam >= tam)
				{					
					list->L[i].prox = k;
					list->L[i].back = list->L[k].back;
					list->L[list->L[k].back].prox = i;
					list->L[k].back = i;
					break;
				}
				else if(list->L[n].app.id >= tam)
				{
					list->L[i].prox = n;
					list->L[i].back = list->L[n].back;
					list->L[list->L[n].back].prox = i;
					list->L[n].back = i;
					break;
				}
			}
		}
	}
}	


/**
 * ADD_LLDE_FILA tem como objetivo adiciona o elemento someente no inicio
 */
void Add_LLDE_FILA(LLDE *list, int id, float tam, char nome[]){
	if(list->IL == -5)//ADICIONA O PRIMEIRO ELEMENTO
	{
		int i = NoLLDE(list);
		
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		
		list->L[i].prox = -1;
		list->IL = i;
		list->FL = i;
		list->total++;
		return;
	}
	//EVITA REPETIÇÕES DE ELEMENTOS 
	for(int k = list->IL; k != -1 ; k = list->L[k].prox)
	{
		if(id == list->L[k].app.id){
			printf("\n\t -- Ja existe! -- \n");
			return;		//se existir algum app semelhante ja instalado ele para
		}
	}
	printf("\n\t -- Adicionado a fila com sucesso! -- \n");
	int i = NoLLDE(list);
	//PASSA OS DADOS
	list->L[i].app.id = id;
	list->L[i].app.tam = tam;
	strcpy(list->L[i].app.nome, nome);
	//ADICIONA NO INICIO
	list->L[list->L[i].back].prox = i;
	list->FL = i;
	list->L[i].prox = -1;
		
	list->total++;
}

/**
 * Add_LLSE_PILHA tem como objetivo adiciona elementos somente no final
 */

void Add_LLSE_PILHA(LLSE *list, int id, float tam, char nome[]){
	int i = list->disp;
	if(list->IL == -5)
	{ //PRIMEIRO ELEMENTO		
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		
		list->total++;
		list->disp++; //disponivel atualiza 
		list->L[i].prox = -1; //prox é o ultimo
		list->IL = i;
		list->total++;
	}
	//VERIFICA SE A PILHA ESTA CHEIA
	else if(list->disp < AP){
		//ADICIONA OS DADOS
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		//ADICIONA NO FINAL
		list->L[i].prox = list->IL;
		list->IL = i;
		list->total++;
	}
	else
		return;
}


/**
 * Remove_LLDE_FILA tem como objetivo remover elementos somente no incio 
 * e ajuda no loop para um reaproveiamento da estrutura
 */
void Remove_LLDE_FILA(LLDE *list){
	int IL = list->IL;
	list->IL = list->L[IL].prox;
	list->disp = IL;
	list->L[IL].back = list->FL;
	list->total--;
}

void Remove_LLV(LLV *list, int k){
	//REMOVER NO INICIO
	if(k == list->IL){
		list->IL = list->IL + 1;
	}
	//REMOVER NO FINAL
	else if(k == list->FL){
		list->FL = list->FL - 1;
	}
	//REMOVER NO MEIO E VERIFICAR QUAL O LADO ENVOLVE MENOS TRABALHO
	else if(list->FL-k < k-list->IL){
		for(int i = k; i < list->FL; i++){
			list->app[i].id = list->app[i+1].id;
			list->app[i].tam = list->app[i+1].tam;
			strcpy(list->app[i].nome, list->app[i+1].nome);
		}
		list->FL-=1;
	}
	else if(list->FL-k > k-list->IL){
		for(int i = k; i > list->IL; i--){
			list->app[i].id = list->app[i-1].id;
			list->app[i].tam = list->app[i-1].tam;
			strcpy(list->app[i].nome, list->app[i-1].nome);
		}
		list->IL+=1;
	}
	else{
		for(int i = k; i < list->FL; i++){
			list->app[i].id = list->app[i+1].id;
			list->app[i].tam = list->app[i+1].tam;
			strcpy(list->app[i].nome, list->app[i+1].nome);
		}
		list->FL-=1;
	}	
}

void Remove_LLSE(LLSE *list, int pos){
	list->total--;
	//REMOVER NO INICIO
	if(pos == list->IL){
		if(list->L[pos].prox == -1){
			Start_LLSE(list);
			return;
		}
		list->IL = list->L[list->IL].prox;
		if(list->disp != -1){
			list->L[pos].prox = list->disp;
		}
		else{
			list->disp = pos;
			list->L[pos].prox = -1;
		}
	}
	//REMOVER NO FINAL
	else if(pos == list->FL){
		int i;
		for(i = list->IL; i != -1; i = list->L[i].prox){
			if(list->L[i].prox == list->FL){
				list->disp = list->FL;
				list->FL = i;
				list->L[list->FL].prox = -1;
				break;
			}
		}
	}
	//REMOVER NO MEIO
	else
	for(int i = list->IL; i != pos; i = list->L[i].prox){
		if(list->L[i].prox == pos){
			list->L[i].prox = list->L[pos].prox;
			
			list->L[pos].prox = list->disp;
			break;
		}
	}
}

void Remove_LLDE(LLDE *list, int pos){
	list->total--;
	//REMOVER NO INICIO
	if(pos == list->IL){
		if(list->L[pos].prox == -1){
			Start_LLDE(list);
			return;
		}
		list->IL = list->L[pos].prox;
		list->L[pos].prox = list->disp;
		list->L[list->disp].back = pos;
		list->L[pos].back = -1;
		list->L[list->IL].back = -1;
		list->disp = pos;
	}
	//REMOVER NO FINAL
	else if(pos == list->FL){
		list->FL = list->L[list->FL].back;
		list->L[list->FL].prox = -1;
		list->L[pos].prox = list->disp;
		list->L[list->disp].back = pos;
		list->L[pos].back = -1;
		list->disp = pos;
	}
	//REMOVER NO MEIO
	else
	{
		list->L[list->L[pos].back].prox = list->L[pos].prox;
		list->L[list->L[pos].prox].back = list->L[pos].back;
		list->L[pos].prox = list->disp;
		list->L[list->disp].back = pos;
		list->L[pos].back = -1;
		list->disp = pos;
		return;
	}
}

void Ler_LLV(LLV *list, char string[]){
	int id;
	float tam;
	char nome[N];
	
	FILE *arq;
	
	arq = fopen(string, "r");
	
	if(arq != NULL){
				
		while(fscanf(arq, "%i %s %f", &id, nome, &tam) != EOF){
			Add_LLV(list, id, tam, nome);
		}
	}
	else{
		printf("\t-- LLV: Erro ao ler o arquivo! -- \n\n\t");
		system("pause");
		
	}
	
	fclose(arq);
}
       
void Ler_LLSE(LLSE *list, char string[]){
	int id;
	float tam;
	char nome[N];
	FILE *arqMob;
	arqMob = fopen(string, "r");
	printf("%s ", string);
	if(arqMob != NULL){
		while(fscanf(arqMob, "%i %s %f", &id, nome, &tam) != EOF){
			Add_LLSE(list, id, tam, nome);
		}
	}
	else{
		printf("\t-- LLSE: Erro ao ler o arquivo! -- \n\n\t");
		system("pause");
	}
	
	fclose(arqMob);
	
}
