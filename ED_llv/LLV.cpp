/**
 * LLV
 */

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

typedef struct
{
	int IA, FA;
	int IL, FL;
	Aplic vet[AP];
	
}lista;

void inicializar(int *IA, int *FA, int *IL, int *FL);
void inserirInicio(Aplic vet[], int *IA, int *FA, int *IL, int *FL, int id, float tam, char nome[N]);
void inserirFim(Aplic vet[], int *IA, int *FA, int *IL, int *FL, int id, float tam, char nome[N]);
void inserirMeio(Aplic vet[], int *IA, int *FA, int *IL, int *FL, int id, float tam, char nome[N], int k);
void ler(Aplic vetStore[], int *IAs, int *FAs, int *ILs, int *FLs, Aplic vetMob[], int *IAm, int *FAm, int *ILm, int *FLm);
void menu(lista store, lista mobile, lista rum);
void consultar(Aplic vetMob[], int *IAm, int *FAm, int *ILm, int *FLm, Aplic vetrum[], int *IAr, int *FAr, int *ILr, int *FLr, int pos);
void AppStore(Aplic vetStore[], int *IAs, int *FAs, int *ILs, int *FLs, Aplic vetMob[], int *IAm, int *FAm, int *ILm, int *FLm);
void MeusAppED(Aplic vetMob[], int *IAm, int *FAm, int *ILm, int *FLm, Aplic vetrum[], int *IAr, int *FAr, int *ILr, int *FLr)
void AppRum(Aplic vetRum[], int *ILr, int *FLr);
void RumAppED(Aplic vetMob[], int *IAm, int *FAm, int *ILm, int *FLm, Aplic vetRum[], int *IAr, int *FAr, int *ILr, int *FLr, int id);
void stop(Aplic vetRum[], int *IAr, int *FAr, int *ILr, int *FLr, int id1);
void erase(Aplic vetMob[], int *IAm, int *FAm, int *ILm, int *FLm, Aplic vetrum[], int *IAr, int *FAr, int *ILr, int *FLr, int id);

int main(int argc, char** argv)
{
	system("color 3f"); system("title Trabalho de Estrutura de Dados");
	//Declaração dos Vetores de Estruturas
	lista store;
	lista mobile;
	lista rum;
	
	inicializar(&rum.IA, &rum.FA, &rum.IL, &rum.FL);
	ler(store.vet, &store.IA, &store.FA, &store.IL, &store.FL, mobile.vet, &mobile.IA, &mobile.FA, &mobile.IL, &mobile.FL);
	
	printf("%i - mobile.IL, %i - mobile.FL\n",mobile.IL, mobile.FL);
	
	for(int i = mobile.IL; i <= mobile.FL; i++){
		printf("%i -- %s -- %.2f\n", mobile.vet[i].id, mobile.vet[i].nome, mobile.vet[i].tam);
	}
	
	system("pause");
	
	menu(store, mobile, rum);
	
	return 0;
}

void inicializar(int *IA, int *FA, int *IL, int *FL){
	*IA = 0;
	*FA = AP;
	*IL = -1;
	*FL = -1;
}

void inserirInicio(Aplic vet[], int *IA, int *FA, int *IL, int *FL, int id, float tam, char nome[N]){
	
	if((*IA == *IL) && (*FA == *FL)){
		return;	
	}
	else if(*IL == -1){
	
		*IL = *IA;
		*FL = *IA;
	
	}
	else if(*IL > *IA){
		
		*IL = *IL - 1;
	
	}
	else
	{
		for(int i = *FL; i >= *IL; i--){
			
			vet[i+1].id = vet[i].id;
			vet[i+1].tam = vet[i].tam;
			strcpy(vet[i+1].nome, vet[i].nome);
			
		}
		*FL+=1;
	}
	
	vet[*IL].id = id;
	vet[*IL].tam = tam;
	strcpy(vet[*IL].nome, nome);
	
}

void inserirFim(Aplic vet[], int *IA, int *FA, int *IL, int *FL, int id, float tam, char nome[N]){
	if((*IA == *IL) && (*FA == *FL)){
		return;	
	}
	
	else if(*FL == -1){
		*IL = *IA;
		*FL = *IA;
	}
	
	else if(*FL < *FA){
		*FL = *FL + 1;
	}
	
	else{
		for(int i = *IL; i < *FL; i++){
			vet[i-1].id = vet[i].id;
			vet[i-1].tam = vet[i].tam;
			strcpy(vet[i-1].nome, vet[i].nome);
		}
		*IL-=1;
	}
	
	vet[*FL].id = id;
	vet[*FL].tam = tam;
	strcpy(vet[*FL].nome, nome);
	
}

void inserirMeio(Aplic vet[], int *IA, int *FA, int *IL, int *FL, int id, float tam, char nome[N], int k){
	if((*IL == *IA && *FA == *FL)){
		return;
	}
	else if(*IL == -1){
		*IL = *IA;
		*FL = *IA;
	}
	else if(*FL-k < k-*IL)//pode melhorar
	{
		if(*FL < *FA){
			for(int i = *FL; i >= k; i--){
				vet[i+1].id = vet[i].id;
				vet[i+1].tam = vet[i].tam;
				strcpy(vet[i+1].nome, vet[i].nome);
			}
			*FL+=1;
		}
		else{
			if(*IL > *IA){
				for(int i = *IL; i <= k; i++){
					vet[i-1].id = vet[i].id;
					vet[i-1].tam = vet[i].tam;
					strcpy(vet[i-1].nome, vet[i].nome);
				}
				*IL-=1;
			}
			else{
				return;
			}
		}
	}
	else if(*FL-k > k-*IL)
	{
		if(*IL > *IA){
			for(int i = *IL; i <= k; i++){
				vet[i-1].id = vet[i].id;
				vet[i-1].tam = vet[i].tam;
				strcpy(vet[i-1].nome, vet[i].nome);
			}
			*IL-=1;
		}
		else{
			if(*FL < *FA){
				for(int i = *FL; i >= k; i--){
					vet[i+1].id = vet[i].id;
					vet[i+1].tam = vet[i].tam;
					strcpy(vet[i+1].nome, vet[i].nome);
				}
				*FL+=1;			
			}
			else{
				return;
			}
		}
	}
	else{
		if(*FL < *FA){
			for(int i = *FL; i >= k; i--){
				vet[i+1].id = vet[i].id;
				vet[i+1].tam = vet[i].tam;
				strcpy(vet[i+1].nome, vet[i].nome);
			}
			*FL+=1;
		}
		else{
			if(*IL > *IA){
				for(int i = *IL; i <= k; i++){
					vet[i-1].id = vet[i].id;
					vet[i-1].tam = vet[i].tam;
					strcpy(vet[i-1].nome, vet[i].nome);
				}
				*IL-=1;
			}
			else{
				return;
			}
		}
	}
	
	vet[k].id = id;
	vet[k].tam = tam;
	strcpy(vet[k].nome, nome);
}


void remover(Aplic vet[], int *IA, int *FA, int *IL, int *FL, int k){
	if(k == *IL){//remover no inicio
		*IL = *IL + 1;
	}
	else if(k == *FL){ //remover no final
		*FL = *FL - 1;
	}
	else if(*FL-k < k-*IL){ //remover no meio
		for(int i = k; i < *FL; i++){
			vet[i].id = vet[i+1].id;
			vet[i].tam = vet[i+1].tam;
			strcpy(vet[i].nome, vet[i+1].nome);
		}
		*FL-=1;
	}
	else if(*FL-k > k-*IL){
		for(int i = k; i > *IL; i--){
			vet[i].id = vet[i-1].id;
			vet[i].tam = vet[i-1].tam;
			strcpy(vet[i].nome, vet[i-1].nome);
		}
		*IL+=1;
	}
	else{
		for(int i = k; i < *FL; i++){
			vet[i].id = vet[i+1].id;
			vet[i].tam = vet[i+1].tam;
			strcpy(vet[i].nome, vet[i+1].nome);
		}
		*FL-=1;
	}	
}


void ler(Aplic vetStore[], int *IAs, int *FAs, int *ILs, int *FLs, Aplic vetMob[], int *IAm, int *FAm, int *ILm, int *FLm){
	int id;
	int armPos;//armazena a posicao para gravao do aplicativo, caso seja nescessario add no meio
	float tam;
	char nome[N];
	
	FILE *arq;
	FILE *arqMob;
	
	arq = fopen("StoreED.txt", "r");
	arqMob = fopen("MobileED.txt", "r");
	
	if(arq != NULL){
		
		inicializar(IAs, FAs, ILs, FLs);
		
		while(fscanf(arq, "%i %s %f", &id, nome, &tam) != EOF){
			
			int valid = 1;
			
			for(int s = *ILs; s <= *FLs; s++){
				if(vetStore[s].id == id){
					valid = 0;
					break;
				}
			}
			
			if(valid){
				int posInsert;
				
				if(*ILs >= 0){
					int j = *ILs;
					int k = *FLs;
					
					if(tam < vetStore[j].tam){      //se o tam nao for maior que o primeiro elemento, entao add no inicio
						posInsert = 1;
					}
					else if(tam > vetStore[k].tam){ //adiciona no final
						posInsert = 2;
					}
					else 					      //senao, procurar a melhor posicao para add o aplicativo
					{
						posInsert = 3;			  //adiciona no meio
						for(int i = *ILs; i < *FLs; i++){
							if(tam < vetStore[i].tam){
								armPos = i;
								break;
							}
						}
					}
				}
				else
				{
					posInsert = 1;
				}
					
				switch(posInsert)
				{
				case 1:
					inserirInicio(vetStore, IAs, FAs, ILs, FLs, id, tam, nome);
					break;
				case 2:
					inserirFim(vetStore, IAs, FAs, ILs, FLs, id, tam, nome);
					break;
				case 3:
					inserirMeio(vetStore, IAs, FAs, ILs, FLs, id, tam, nome, armPos);
					break;
				default:
					break;
				}
			}
		}
	}
	else{
		printf("\t-- Aplicativos da StoreED nao foram carregados! -- \n\n\t");
		system("pause");
		
	}
	
	for(int i = *ILs; i < *FLs; i++){
		printf("%i -- %s -- %.2f\n", vetStore[i].id, vetStore[i].nome, vetStore[i].tam);
	}		

	
	if(arqMob != NULL){
		
		inicializar(IAm, FAm, ILm, FLm);

		while(fscanf(arqMob, "%i %s %f", &id, nome, &tam) != EOF){
			//printf("teste");
			int valid = 1;
			
			for(int s = *ILm; s <= *FLm; s++){
				if(vetMob[s].id == id){
					valid = 0;
					break;	
				}
			}
						
			if(valid){
				int posInsert;
				
				if(*ILm >= 0){
					int j = *ILm;
					int k = *FLm;
					
					if(tam < vetMob[j].tam){      //se o tam nao for maior que o primeiro elemento, entao add no inicio
						posInsert = 1;
					}
					else if(tam > vetMob[k].tam){ //adiciona no final
						posInsert = 2;
					}
					else 					      //senao, procurar a melhor posicao para add o aplicativo
					{
						posInsert = 3;			  //adiciona no meio
						for(int i = *ILm; i < *FLm; i++){
							if(tam <= vetMob[i].tam){
								armPos = i;
								break;
							}
						}
					}
				}
				else
				{
					posInsert = 1;
				}
					
				switch(posInsert)
				{
				case 1:
					inserirInicio(vetMob, IAm, FAm, ILm, FLm, id, tam, nome);
					break;
				case 2:
					inserirFim(vetMob, IAm, FAm, ILm, FLm, id, tam, nome);
					break;
				case 3:
					inserirMeio(vetMob, IAm, FAm, ILm, FLm, id, tam, nome, armPos);
					break;
				default:
					break;
				}
			}
		}
	}
	else{
		printf("\t-- Meus Aplicativos nao Foram Carregados! -- \n\n\t");
		system("pause");
	}
	
	system("pause");
	fclose(arq);
	fclose(arqMob);
}



void menu(lista store, lista mobile, lista rum){
	int resp;	
	do{
		int i = mobile.IL;
		int control = mobile.FL;
		system("cls");
	
		while(control >= 0 && i < 9 + mobile.IL){
			printf("\t%i - %s", i+1-mobile.IL , mobile.vet[i].nome);
			control-=1;
			i++;
			if((i-mobile.IL)%3 == 0) printf("\n\n");
		}
		while(i < 9 + mobile.IL)
		{
			printf("\t%i - \t", i+1);
			i++;
			if((i-mobile.IL)%3 == 0) printf("\n\n");
		}
		//Menus principais
		printf("\t10 - AppStore");
		printf("\t11 - Meus App");
		printf("\t12 - AppRum\n\n");
		
		printf("\n\t(Digite 0 para Desligar) --> ");
		
		scanf("%i", &resp);
		resp += mobile.IL;
		if(resp > 0 && resp <= 9){
			//caso digite um valos que nao corresponda a nenhum aplicativo na matriz 3x3
			if(resp > mobile.FL){
				printf("\n\t -- APLICATIVO NAO INSTALADO! -- \n\n");
				continue;
			}
			//senao sera chamado o menu interno do aplicativo
			consultar(mobile.vet, &mobile.IA, &mobile.FA, &mobile.IL, &mobile.FL, rum.vet, &rum.IA, &rum.FA, &rum.IL, &rum.FL, resp - 1);
		}
		//caso o valor nao esteja na matriz 3x3, sera chamado uma das tres funcoes principais
		else
		{
			switch(resp)
			{
			case 10:
				AppStore(store.vet, &store.IA, &store.FA, &store.IL, &store.FL, mobile.vet, &mobile.IA, &mobile.FA, &mobile.IL, &mobile.FL);
				break;
			case 11:
				MeusAppED(mobile.vet, &mobile.IA, &mobile.FA, &mobile.IL, &mobile.FL, rum.vet, &rum.IA, &rum.FA, &rum.IL, &rum.FL);
				break;
			case 12:
				AppRum(rum.vet , &rum.IL, &rum.FL);
				break;
			case 0:
				resp = 0;
				break;
			default:
				printf("Opcao invalida!\n");
				break;
			}
		}
		
	}while(resp != 0);
	system("cls");
	printf("\t\nBye!\n\n");
}

void consultar(Aplic vetMob[], int *IAm, int *FAm, int *ILm, int *FLm, Aplic vetrum[], int *IAr, int *FAr, int *ILr, int *FLr, int pos){
	system("cls");
	int resp, x;
	//Armazena o id da estrutura na posicao vetorial pos
	int id = vetMob[pos].id;
	do{
		system("cls");
		x = 0;
		printf("\t -- %i -- %s -- \n\n", vetMob[pos].id, vetMob[pos].nome);
		printf("\t1 - Executar o aplicativo\n");
		printf("\t2 - Parar o Aplicativo\n");
		printf("\t3 - Desistalar o Aplicativo\n");
		printf("\t0 - SAIR\n\n"); 
		printf("\t--> ");
		scanf("%i", &resp);
		
		switch(resp)
		{
		case 1:
			RumAppED(vetMob,IAm,FAm,ILm,FLm,vetrum,IAr,FAr,ILr,FLr,id);
			break;
		case 2:
			stop(vetrum,IAr,FAr,ILr,FLr,id);
			break;
		case 3:
			erase(vetMob,IAm,FAm,ILm,FLm,vetrum,IAr,FAr,ILr,FLr,id);
			break;
		case 0:
			break;
		default:
			x = 1;
			printf("\t -- Opcao invalida! Digite Novamente -- \n");
			printf("\n\t");
			system("pause");
			break;
		}
	}while(x);
}

void RumAppED(Aplic vetMob[], int *IAm, int *FAm, int *ILm, int *FLm, Aplic vetRum[], int *IAr, int *FAr, int *ILr, int *FLr, int id1){
	//int z = *FLr;
	int valid = 1;//variavel de validacao de aplicativos ja em execucao
	int id;
	float tam;
	char nome[N];
	for(int i = *ILm; i <= *FLm; i++){
		if(vetMob[i].id == id1){
			//verificar se o aplicativa ja esta em execucao
			for(int j = *ILr; j <= *FLr; j++){
				if(vetRum[j].id == id1){
					printf("\t -- O aplicativo %s ja esta em execucao! -- \n\n\t", vetRum[j].nome);
					valid = 0;
					break;
				}
			}
			
			id = vetMob[i].id;
			tam = vetMob[i].tam;
			strcpy(nome, vetMob[i].nome);
			
			if(valid){
				int posInsert;
				int armPos;
				if(*ILr >= 0){
					int j = *ILr;
					int k = *FLr;
					
					if(tam < vetRum[j].tam){      //se o tam nao for maior que o primeiro elemento, entao add no inicio
						posInsert = 1;
					}
					else if(tam > vetRum[k].tam){ //adiciona no final
						posInsert = 2;
					}
					else 					      //senao, procurar a melhor posicao para add o aplicativo
					{
						posInsert = 3;			  //adiciona no meio
						for(int i = *ILr; i <= *FLr; i++){
							if(tam < vetRum[i].tam){
								armPos = i;
								break;
							}
						}
					}
				}
				else
				{
					posInsert = 1;
				}
				switch(posInsert)
				{
				case 1:
					inserirInicio(vetRum, IAr, FAr, ILr, FLr, id, tam, nome);
					break;
				case 2:
					inserirFim(vetRum, IAr, FAr, ILr, FLr, id, tam, nome);
					break;
				case 3:
					inserirMeio(vetRum, IAr, FAr, ILr, FLr, id, tam, nome, armPos);
					break;
				default:
					break;
				}
			}
			break;
		}
	}
	if(valid)
	printf("\t -- O Aplicativo %s esta em Execucao! -- \n\n\t", nome);
	system("pause");
}

void stop(Aplic vetRum[], int *IAr, int *FAr, int *ILr, int *FLr, int id1){
	char nome[N];
	int valid = 0;
	for(int i = *ILr; i <= *FLr; i++){
		//verificar se o id consta na lista de app em execucao
		if(vetRum[i].id == id1){
			strcpy(nome, vetRum[i].nome);
			valid = 1;
			//excluir
			remover(vetRum, IAr, FAr, ILr, FLr, i);
			break;
		}
	}
	if(valid){
		printf("\n\t");
		printf("Aplicativo %s foi parado!\n", nome);
	}
	else{
		printf("\n\t");
		printf("Aplicativo Não esta em execucao para para-lo!\n");
	}
}

void erase(Aplic vetMob[], int *IAm, int *FAm, int *ILm, int *FLm, Aplic vetrum[], int *IAr, int *FAr, int *ILr, int *FLr, int id){
	char nome[N];
	FILE *arq;
	int resp;
	printf("antes de remover -- IL = %i, FL = %i\n\n", *ILm, *FLm);
	//Para o Aplicativo antes de desistalar, deletando o aplicativo da estrutura Rum
	for(int i = *ILr; i <= *FLr; i++){
		if(vetrum[i].id == id){
			remover(vetrum, IAr, FAr, ILr, FLr, i);
			break;
		}
	}
	//Apaga o aplicativo da estrutura MobileED
	for(int i = *ILm; i <= *FLm; i++){
		if(vetMob[i].id == id){
			strcpy(nome, vetMob[i].nome);
			remover(vetMob, IAm, FAm, ILm, FLm, i);
			break;
		}
	}
	//Opcional. Salvar os dados
	printf("depois de remover -- IL = %i, FL = %i\n\n", *ILm, *FLm);
	do{
		printf("\n\t Deseja Salvar os Dados?(1-s, 0-n) --> ");
		scanf("%i", &resp);
		if(resp){
			arq = fopen("MobileED.txt", "w");
			for(int i = *ILm; i <= *FLm; i++){
				fprintf(arq, "%i %s %.2f\n", vetMob[i].id, vetMob[i].nome, vetMob[i].tam);
			}
			fclose(arq);
			system("cls");
			printf("\n\t -- Dados salvos com sucesso! -- \n");
		}
		else if(resp < 0 || resp > 1){
			system("cls");
			printf("\n\t -- Opcao Invalida! -- \n");
		}
	}while(resp < 0 || resp > 1);
	
	printf("\n\t");
	printf("\n\t -- O aplicativo %s foi Desinstalado! -- \n\n\t", nome);
	system("pause");
}

void AppStore(Aplic vetStore[], int *IAs, int *FAs, int *ILs, int *FLs, Aplic vetMob[], int *IAm, int *FAm, int *ILm, int *FLm){
	int resp, arq;
	int r, validSalvaDados;//validaSalvaDados verifica se existe dados errados a serem salvos no arquivo
	int id;
	float tam;
	char nome[N];
	
	system("cls");
	printf("\t\t -- LOJA DE APLICATIVOS ED --\n");
	printf("\n\n");
	printf("\tDeseja Instalar um Aplicativo(1 - s, 0 - n) --> ");
	scanf("%i", &resp);
	
	arq = resp;//armazena a primera resposta, caso for 0 nao entrará na parte de salvar dados no arquivo
	
	while(resp){
		validSalvaDados = 0;
		system("cls");
		printf("\t\t -- LOJA DE APLICATIVOS ED --\n");
				
		for(int i = *ILs; i < *FLs; i++){
			if((i)%3 == 0){
				printf("\n");
			}
			printf("\t| ID: %i - NOME: %s - TAMANHO: %.2f\n", vetStore[i].id, vetStore[i].nome, vetStore[i].tam);
		}
		
		//int pos = *FLm;
		int invalid = 0;//verifica se o id selecionado ja esta instalado na struct MobileED[]
		int id1, idInvalid = 1;//idValid verifica se o id digitado consta no struct StoreED[]
		
		printf("\n\tDIGITE O ID DO APP A SER INSTALADO: ");
		scanf("%i", &id1);
		
		for(int i = *ILs; i < *FLs; i++){
			if(vetStore[i].id == id1){
				//verifica se o aplicativo ja esta instalado
				for(int z = *ILm; z < *FLm; z++){
					if(id1 == vetMob[z].id){
						invalid = 1;
						break;
					}	
				}
				
				if(invalid){
					printf("\t -- Aplicativo ja Instalado! -- \n\n");
					idInvalid = 0;
					break;
				}
				//se nao tiver algum app com o mesmo id na Struct MobileED[], entao sera add um novo app
				//na ultima posicao disponivel --> pos
				id = id1;
				tam = vetStore[i].tam;
				strcpy(nome, vetStore[i].nome);
				idInvalid = 0;
				
				int posInsert;
				int armPos;
				if(*ILm >= 0){
					int j = *ILm;
					int k = *FLm;
					
					if(tam < vetMob[j].tam){      //se o tam nao for maior que o primeiro elemento, entao add no inicio
						posInsert = 1;
					}
					else if(tam > vetMob[k].tam){ //adiciona no final
						posInsert = 2;
					}
					else 					      //senao, procurar a melhor posicao para add o aplicativo
					{
						posInsert = 3;			  //adiciona no meio
						for(int i = *ILm; i < *FLm; i++){
							if(tam < vetMob[i].tam){
								armPos = i;
								break;
							}
						}
					}
				}
				else
				{
					posInsert = 1;
				}
				switch(posInsert)
				{
				case 1:
					inserirInicio(vetMob, IAm, FAm, ILm, FLm, id, tam, nome);
					break;
				case 2:
					inserirFim(vetMob, IAm, FAm, ILm, FLm, id, tam, nome);
					break;
				case 3:
					inserirMeio(vetMob, IAm, FAm, ILm, FLm, id, tam, nome, armPos);
					break;
				default:
					break;
				}
				
				printf("\n\t -- Aplicativo %s foi Instalado com sucesso! -- \n\n", nome);
				validSalvaDados = 1;
				
				break;
			}
		}
		
		if(idInvalid){
			printf("\n\t -- O aplicativo com o ID = %i nao foi encontrado! -- \n", id);
			invalid = 1;
		}
		
		printf("\tDeseja Instalar Outro Aplicativo? (1 - s, 0 - n) --> ");
		scanf("%i", &resp);
	}
	system("cls");
	//salvar no arquivo
	//se a primeira resposta for 0 entao nao entrarar aqui
	if(arq) do{
		printf("\n\n\tDeseja salvar os dados no arquivo?(1-s, 0-n): ");
		scanf("%i", &r);
		if(r && validSalvaDados){
			FILE *arq;
			arq = fopen("MobileED.txt", "w");
			for(int i = *ILm; i < *FLm; i++){
				fprintf(arq, "%i %s %.2f\n", vetMob[i].id, vetMob[i].nome, vetMob[i].tam);
			}
			fclose(arq);
			printf("\n\t -- Dados Salvo com sucesso! -- \n");	
		}
		else if(r < 0 || r > 1){
			system("cls");
			printf("\n\t -- Opcao Invalida! -- \n");
		}
		else
		{
			system("cls");
			printf("\n\t -- Dado invalido para ser salvo! -- \n");
			break;
		}
	}while(r < 0 || r > 1);

	printf("\n\n\t");
	system("pause");
}

void MeusAppED(Aplic vetMob[], int *IAm, int *FAm, int *ILm, int *FLm, Aplic vetrum[], int *IAr, int *FAr, int *ILr, int *FLr){
	int resp;
	int id;
	int valid = 0;
	
	system("cls");
	printf("\t -- MEUS APLICATIVOS -- \n\n");
	//imprime na tela a lista de meus aplicativos
	for(int i = *ILm; i <= *FLm; i++){
		printf("\t%i -- %.2f -- %s \n", vetMob[i].id, vetMob[i].tam, vetMob[i].nome);
	}
	//validacao de consulta
	do{
		printf("\n\n\tConsultar Aplicativo(1 - s, 0 - n) --> ");
		scanf("%i", &resp);
		if(resp > 1 || resp < 0){
			printf("\n\t -- Resposta Invalida! -- \n\n");
		}
		else if(resp)
		{
			printf("\n\tDigite o id do aplicativo: ");
			scanf("%i", &id); 
		}
	}while(resp > 1 || resp < 0);
	
	while(resp){
		//verifica se o id consta na lista
		valid = 0;
		for(int i = *ILm; i < *FLm; i++){
			if(vetMob[i].id == id){
				consultar(vetMob, IAm, FAm, ILm, FLm, vetrum, IAr, FAr, ILr, FLr, i);
				valid = 1;
				break;
			}
		}
		
		if(!valid){
			printf("\n\t -- Id Nao Encontrado! -- ");
		}
		
		do{			
			printf("\n\n\tConsultar Outro Aplicativo(1 - s, 0 - n) --> ");
			scanf("%i", &resp);
			
			if(resp > 1 || resp < 0){
				printf("\n\t -- Resposta Invalida! -- \n\n");
			}
			else if(resp){
				system("cls");
				for(int i = *ILm; i <= *FLm; i++){
		   	   		printf("\t%i -- %.2f -- %s \n", vetMob[i].id, vetMob[i].tam, vetMob[i].nome);
				}
				printf("\n\tDigite o id do aplicativo: ");
				scanf("%i", &id);	
			}
		}while(resp > 1 || resp < 0);
	}
	printf("\n\t");
	system("pause");
}	

void AppRum(Aplic vetRum[], int *ILr, int *FLr){	
	system("cls");
	printf("\t -- Aplicativos em execucao! -- \n\n");
	
	if(*ILr == -1){
		printf("\t\t-- VAZIO --\n\n");
	}
	else
	for(int i = *ILr; i <= *FLr; i++){
		printf("\t%i -- %s -- %.2f\n", vetRum[i].id, vetRum[i].nome, vetRum[i].tam);
	}
	printf("\n\t");
	system("pause");
}



