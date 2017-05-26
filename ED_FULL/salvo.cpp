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
	int back;
}No;

typedef struct{
	int IA, FA;
	int IL, FL;
	Aplic app[AP];
}LLV;

typedef struct{
	No L[N];
	int disp;
	int IL;
	int FL;
	int total;
}LLSE;

typedef struct{
	No L[N];
	int disp;
	int IL;
	int FL;
	int total;
}LLDE;

void Start_LLV(LLV *list);
void Start_LLSE(LLSE *list);
void Start_LLDE(LLDE *list);
void Add_LLV(LLV *list, int id, float tam, char nome[]);
void Add_LLSE(LLSE *list, int id, float tam, char nome[]);
void Add_LLDE(LLDE *list, int id, float tam, char nome[]);
void AddPilha_LLDE(LLDE *list, int id, float tam, char nome[]);
void AddPilha_LLSE(LLSE *list, int id, float tam, char nome[]);
void AddFila_LLDE(LLDE *list, int id, float tam, char nome[]);
void AddFila_LLSE(LLSE *list, int id, float tam, char nome[]);
void Remover_LLV(LLV *list, int k);
void Remover_LLSE(LLSE *list, int pos);
void Remover_LLDE(LLDE *list, int pos);
void Ler_LLV(LLV *store, char string[]);
void Ler_LLSE(LLSE *MyApp, char string[]);

void Start_LLV(LLV *list){
	list->IA = 0;
	list->FA = AP;
	list->IL = -1;
	list->FL = -1;
}

void Start_LLSE(LLSE *list){
	list->disp = 0;
	list->L[0].prox = -1;
	list->IL = -5;
	list->FL = -5;
	list->total = 0;
}

void Start_LLDE(LLDE *list){
	list->disp = 0;
	list->L[0].prox = -1;
	list->L[0].back = -2;
	list->IL = -5;
	list->FL = -5;
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
	//ADICIONA NO MEIO
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

void Add_LLSE(LLSE *list, int id, float tam, char nome[]){
	int i = list->disp;
	int k2;
	if(list->IL == -5){ //PRIMEIRO ELEMENTO
		list->total++;
	
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		
		list->L[i].prox = -1; //prox é o ultimo
		list->disp++; //disponivel atualiza 
		list->IL = i;
		list->FL = i;
	}
	else if(list->disp < N){
		//verificar semelhantes 
		for(int k = list->IL; k != -1; k = list->L[k].prox)
		{
			if(id == list->L[k].app.id){
				return;
			}
		}
		
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		list->total++;
		
		if(list->L[list->IL].app.tam <= tam)
		{
			list->L[i].prox = list->IL;
			list->IL = i;
		}
		
		else if(list->L[list->FL].app.tam >= tam)
		{
			list->L[i].prox = -1;
			list->L[list->FL].prox = i;
			list->FL = i;
		}
		
		else{
			k2 = list->IL;
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
		list->disp++;
	}
	else
		return;
}

void Add_LLDE(LLDE *list, int id, float tam, char nome[]){
	int i = list->disp;
	if(list->IL == -5)
	{ //PRIMEIRO ELEMENTO		
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		
		list->disp++; //disponivel atualiza 
		list->L[i].prox = -1; //prox é o ultimo
		list->L[i].back = -2;
		list->IL = i;
		list->FL = i;
	}
	else if(list->disp < N){ 
		//verificar semelhantes 
		for(int k = list->IL, n = list->FL; k != -1 || n != -2; k = list->L[k].prox, n = list->L[n].back)
		{
			if(id == list->L[k].app.id || id == list->L[n].app.id){
				return;		//se existir algum app semelhante ja instalado ele para
			}
		}
		
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		//inicio
		if(list->L[list->IL].app.tam >= tam)
		{
			list->L[list->IL].back = i;
			list->L[i].prox = list->IL;
			list->L[i].back = -2;
			
			list->IL = i;
		}
		//fim
		else if(list->L[list->FL].app.tam <= tam)//se tamanho for maior que o ultimo elemento
		{
			list->L[i].back = list->FL;
			list->L[i].prox = -1;
			list->L[list->FL].prox = i;
			list->FL = i;
		}
		//meio
		else{
			for(int k = list->IL, n = list->FL; k != -1 || n != -2; k = list->L[k].prox, n = list->L[n].back)
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
		list->disp++;
	}
	else
		return;
}

void AddFila_LLDE(LLDE *list, int id, float tam, char nome[]){
	int i = list->disp;
	if(list->IL == -5)
	{ //PRIMEIRO ELEMENTO		
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		
		list->disp++; //disponivel atualiza 
		list->L[i].prox = -1; //prox é o ultimo
		list->L[i].back = -2;
		list->IL = i;
		list->FL = i;
		return;
	}
		//verificar semelhantes 
		for(int k = list->IL, n = list->FL; k != -1 || n != -2; k = list->L[k].prox, n = list->L[n].back)
		{
			if(id == list->L[k].app.id || id == list->L[n].app.id){
				return;		//se existir algum app semelhante ja instalado ele para
			}
		}
		
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		
		list->L[i].prox = -1;
		list->L[i].back = list->FL;
		list->L[list->FL].prox = i;
		list->FL = i;
			
		list->disp++;
		list->total++;
}

void AddFila_LLSE(LLSE *list, int id, float tam, char nome[]){
	int i = list->disp;
	if(list->IL == -5){ //PRIMEIRO ELEMENTO
		list->total++;
	
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		
		list->disp++; //disponivel atualiza 
		list->L[i].prox = -1; //prox é o ultimo
		list->IL = i;
		list->FL = i;
	}
		//verificar semelhantes 
		for(int k = list->IL; k != -1; k = list->L[k].prox)
		{
			if(id == list->L[k].app.id){
				return;
			}
		}
		
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		
		list->L[i].prox = -1;
		list->L[list->FL].prox = i;
		list->FL = i;
		
		list->disp++;
		list->total++;
}

void AddPilha_LLSE(LLSE *list, int id, float tam, char nome[]){
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
	}
	else if(list->disp < N){
		
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		//inicio
		list->L[i].prox = list->IL;
		list->IL = i;
		list->total++;
	}
	else
		return;
}

void AddPilha_LLDE(LLDE *list, int id, float tam, char nome[]){
	int i = list->disp;
	if(list->IL == -5)
	{ //PRIMEIRO ELEMENTO		
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		
		list->total++;
		list->disp++; //disponivel atualiza 
		list->L[i].prox = -1; //prox é o ultimo
		list->L[i].back = -2;
		list->IL = i;
		list->FL = i;
	}
	else if(list->disp < N){
		
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		//inicio
		list->L[i].back = list->FL;
		list->L[i].prox = -1;
		list->L[list->FL].prox = i;
		list->FL = i;
		list->total++;
	}
	else
		return;
}

void Remover_LLV(LLV *list, int k){
	if(k == list->IL){//remover no inicio
		list->IL = list->IL + 1;
	}
	else if(k == list->FL){ //remover no final
		list->FL = list->FL - 1;
	}
	else if(list->FL-k < k-list->IL){ //remover no meio
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

void Remover_LLSE(LLSE *list, int pos){
	list->total--;
	if(pos == list->IL){
		if(list->L[pos].prox == -1){
			Start_LLSE(list);
			return;
		}
		list->disp = list->IL;
		list->IL = list->L[pos].prox;
	}
	else
	for(int i = list->IL; i != pos; i = list->L[i].prox){
		if(list->L[i].prox == pos){
			list->L[i].prox = list->L[pos].prox;
			if(list->FL == pos){
				list->FL = i;
			}
			list->L[pos].prox = -5;
			list->disp = pos;
			break;
		}
	}
}

void Remover_LLDE(LLDE *list, int pos){
	list->total--;
	if(pos == list->IL){
		if(list->L[pos].prox == -1){
			Start_LLDE(list);
			return;
		}
		list->L[list->L[pos].prox].back = -2;
		list->IL = list->L[pos].prox;
		list->disp = pos;
		return;
	}
	else if(pos == list->FL){
		list->disp = pos;
		list->L[list->L[pos].back].prox = -1;
		list->FL = list->L[pos].back;
		return;
	}
	else
	{
		list->L[list->L[pos].back].prox = list->L[pos].prox;
		list->L[list->L[pos].prox].back = list->L[pos].back;
		list->L[pos].prox = -1;
		list->L[pos].back = -2;
		list->disp = pos;
		return;
	}
}

void Ler_LLV(LLV *store, char string[]){
	int id;
	//int armPos;//armazena a posicao para gravao do aplicativo, caso seja nescessario add no meio
	float tam;
	char nome[N];
	
	FILE *arq;
	
	arq = fopen(string, "r");
	
	if(arq != NULL){
				
		while(fscanf(arq, "%i %s %f", &id, nome, &tam) != EOF){
			Add_LLV(store, id, tam, nome);
		}
	}
	else{
		printf("\t-- Aplicativos da StoreED nao foram carregados! -- \n\n\t");
		system("pause");
		
	}
	
	/**@verificarLista
	for(int i = store->IL; i <= store->FL; i++){
		printf("%i -- %s -- %.2f\n", store->app[i].id, store->app[i].nome, store->app[i].tam);
	}		
	*/
	
	system("pause");
	fclose(arq);
}


void Ler_LLSE(LLSE *MyApp, char string[]){
	//variaveis auxiliares para receber os dados dos arquivos de textos
	int id;
	float tam;
	char nome[N];
	FILE *arqMob;
	arqMob = fopen(string, "r");
	if(arqMob != NULL){
		while(fscanf(arqMob, "%i %s %f", &id, nome, &tam) != EOF){
			Add_LLSE(MyApp, id, tam, nome);
		}
	}
	else{
		printf("\t-- Meus Aplicativos nao Foram Carregados! -- \n\n\t");
		system("pause");
	}
	
	fclose(arqMob);
	
}
