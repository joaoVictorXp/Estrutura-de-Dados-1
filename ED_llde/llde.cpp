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
	No L[N];
	int disp;
	int IL;
	int FL;
	int total;
}LLSE;

void start(LLSE *list);
void addCres(LLSE *list, int id, float tam, char nome[]);
void add(LLSE *list, int id, float tam, char nome[]);
void remover(LLSE *list, int pos);
void ler(LLSE *MyApp, LLSE *Store);
void menu(LLSE *MyApp, LLSE *Store, LLSE *Rum);
void consultar(LLSE *MyApp, LLSE *Rum, int pos);
void AppStore(LLSE *Store, LLSE *MyApp);
void MeusAppED(LLSE *MyApp, LLSE *Rum);
void AppRum(LLSE *Rum);
int RumAppED(LLSE *MyApp, LLSE *Rum, int id, int pos);
void Stop(LLSE *Rum, int id);
void Erase(LLSE *MyApp, LLSE *Rum, int id, int pos);

int main(int argc, char** argv)
{
	system("color 3f"); system("title Trabalho de Estrutura de Dados");
	//Declaração dos Vetores de Estruturas
	LLSE MyApp, Store, Rum;
	
	start(&MyApp);
	start(&Store);
	start(&Rum);
	ler(&MyApp, &Store);
	
	for(int i = MyApp.IL, j = i; i != -1 ; i = MyApp.L[j].prox){
		printf("i == %i\n", i);
		printf("id = %i -- Tam = %.2f -- Nome = %s\n\n", MyApp.L[i].app.id, MyApp.L[i].app.tam, MyApp.L[i].app.nome);
		j = i;
	}
	

		// printf("\n\nsegundo for\n");
		// 	for(int i = 0; i < MyApp.disp; i++){
		//    	printf("id = %i -- Tam = %.2f -- Nome = %s\n\n", MyApp.L[i].app.id, MyApp.L[i].app.tam, MyApp.L[i].app.nome);
		// }
	system("pause");
	menu(&MyApp, &Store, &Rum);
	return 0;
}

void start(LLSE *list){
	list->disp = 1;
	list->L[0].prox = -1;
	list->L[0].back = -2;
	list->IL = -5;
	list->FL = -5;
	list->total = 0;
}

void addCres(LLSE *list, int id, float tam, char nome[]){
	int i = list->disp;
	int k2, k3;
	printf("entrou?");
	if(list->IL == -5)
	{ //PRIMEIRO ELEMENTO
		list->total++;
		
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
		for(int k = list->IL; k != -1; k = list->L[k].prox)
		{
			if(id == list->L[k].app.id){
				return;		//se existir algum app semelhante ja instalado ele para
			}
		}
		
		list->L[i].app.id = id;
		list->L[i].app.tam = tam;
		strcpy(list->L[i].app.nome, nome);
		
		list->total++;
		//inicio
		if(list->L[list->IL].app.tam >= tam)
		{
			list->L[list->IL].back = i;
			list->L[i].prox = list->IL;
			list->L[i].back = -2;
			
			list->IL = i;
		}
		//fim
		else if(list->L[list->FL].app.tam <= tam)
		{
			list->L[i].back = list->FL;
			list->L[i].prox = -1;
			list->L[list->FL].prox = i;
			list->FL = i;
		}
		//meio
		else{
			k2 = list->IL;
			k3 = list->FL;
			for(int k = list->IL, n = list->FL; k != -1 || n != -2; k = list->L[k].prox, n = list->L[n].back)
			{				
				printf("for");
				if(list->L[k].app.tam >= tam)//meio
				{					
					list->L[i].prox = k;
					list->L[i].back = list->L[k].back;
					list->L[k].back = i;
					list->L[k2].prox = i;
					break;
				}
				else if(list->L[n].app.id <= tam)
				{
					list->L[i].prox = list->L[n].prox;
					list->L[n].prox = i;
					list->L[i].back = n;
					list->L[k3].back = i;
					break;
				}
				else{ //armazena o valor prox do anterior
					k2 = k;
					k3 = n;
				}	
			}
		}
		list->disp++;
	}
	else
		return;
}

void add(LLSE *list, int id, float tam, char nome[]){
	int i = list->disp;
	int k2;
	if(list->L[i].prox == -1){ //PRIMEIRO ELEMENTO
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

void remover(LLSE *list, int pos){
	list->total--;
	if(pos == list->IL){
		list->IL = list->L[pos].prox;
		return;
	}
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
			addCres(MyApp, id, tam, nome);
			//addCres(MyApp, id, tam, nome);
		}
	}
	else{
		printf("\t-- Meus Aplicativos nao Foram Carregados! -- \n\n\t");
		system("pause");
	}
	
	fclose(arq);
	fclose(arqMob);
	
}

void menu(LLSE *MyApp, LLSE *Store, LLSE *Rum){
	int resp;	
	do{
		int i = 0, vet[9];
		int j = MyApp->IL;
		int control = MyApp->total;
		system("cls");
		//imprime de forma matricial 3x3 os aplicativos
		//caso tenha menos aplicativos que a capacidade
		//a matriz sera preenchida com espacos em branco
		while(control > 0 && i < 9){
			printf("\t%i - %s", i+1 , MyApp->L[j].app.nome);
			vet[i] = j;
			j = MyApp->L[j].prox;
			control-=1;
			i++;
			if(i%3 == 0) printf("\n\n");
		}
		while(i < 9)
		{
			printf("\t%i - \t", i+1);
			i++;
			if(i%3 == 0) printf("\n\n");
		}
		//Menus principais
		printf("\t10 - AppStore");
		printf("\t11 - Meus App");
		printf("\t12 - AppRum\n\n");
		// for(int i = 0; i < 9; i++){
		// 	printf("%i - ", vet[i]);
		// }
		// system("pause");
		printf("\n\t(Digite 0 para Desligar) --> ");
		
		scanf("%i", &resp);
		if(resp > 0 && resp <= 9){
			//caso digite um valos que nao corresponda a nenhum aplicativo na matriz 3x3
			if(resp > MyApp->total){
				printf("\n\t -- APLICATIVO NAO INSTALADO! -- \n\n");
				continue;
			}
			//senao sera chamado o menu interno do aplicativo
			consultar(MyApp, Rum, vet[resp - 1]);
		}
		//caso o valor nao esteja na matriz 3x3, sera chamado uma das tres funcoes principais
		else
		{
			switch(resp)
			{
			case 10:
				AppStore(Store, MyApp);
				break;
			case 11:
				MeusAppED(MyApp, Rum);
				break;
			case 12:
				AppRum(Rum);
				break;
			case 0:
				//resp = 0;
				break;
			default:
				printf("Opcao invalida!\n");
				break;
			}
		}
		
	}while(resp != 0);
	system("cls");
	printf("Bye!");
}

void consultar(LLSE *MyApp, LLSE *Rum, int pos){
	system("cls");
	int resp, x;
	//Armazena o id da estrutura na posicao vetorial pos
	//int id = MobileED[pos].id;
	
	do{
		system("cls");
		x = 0;
		printf("\t -- %i -- %s -- \n\n", MyApp->L[pos].app.id, MyApp->L[pos].app.nome);
		printf("\t1 - Executar o aplicativo\n");
		printf("\t2 - Parar o Aplicativo\n");
		printf("\t3 - Desistalar o Aplicativo\n");
		printf("\t0 - SAIR\n\n"); 
		printf("\t--> ");
		scanf("%i", &resp);
		int id = MyApp->L[pos].app.id;
		switch(resp)
		{
		case 1:
			if(RumAppED(MyApp, Rum, id , pos)){
				printf("\t -- Aplicativo %s esta executando com sucesso! -- \n\n", MyApp->L[pos].app.nome);
			}
			else
			{
				printf("\t -- Aplicativo %s ja esta executando! -- \n\n", MyApp->L[pos].app.nome);				
			};
			break;
		case 2:
			Stop(Rum, id);
			break;
		case 3:
			Erase(MyApp, Rum, id, pos);
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

void AppStore(LLSE *Store, LLSE *MyApp){
	system("cls");
	printf("\t\t -- LOJA DE APLICATIVOS ED --\n");
	printf("\n\n");
	int resp, arq;
	int r, validSalvaDados;//validaSalvaDados verifica se existe dados errados a serem salvos no arquivo
	printf("\tDeseja Instalar um Aplicativo(1 - s, 0 - n) --> ");
	scanf("%i", &resp);
	arq = resp;//armazena a primera resposta, caso for 0 nao entrará na parte de salvar dados no arquivo
	
	while(resp){
		validSalvaDados = 0;
		system("cls");
		printf("\t\t -- LOJA DE APLICATIVOS ED --\n");
				
		for(int i = 0; i != Store->disp; i++){
			if((i)%3 == 0){
				printf("\n");
			}
			printf("\t| ID: %i - NOME: %s - TAMANHO: %.2f\n", Store->L[i].app.id, Store->L[i].app.nome, Store->L[i].app.tam);
		}
		int pos = MyApp->disp;
		int invalid = 0;//verifica se o id selecionado ja esta instalado na struct MobileED[]
		int id, idInvalid = 1;//idValid verifica se o id digitado consta no struct StoreED[]
		
		printf("\n\tDIGITE O ID DO APP A SER INSTALADO: ");
		scanf("%i", &id);
		
		for(int i = 0; i < Store->disp; i++){
			if(Store->L[i].app.id == id){
				//verifica se o aplicativo ja esta instalado
				for(int z = 0; z < MyApp->disp; z++){
					if(id == MyApp->L[z].app.id){
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
				add(MyApp, id, Store->L[i].app.tam, Store->L[i].app.nome);
				
				idInvalid = 0;
				
				printf("\n\t -- Aplicativo %s foi Instalado com sucesso! -- \n\n", MyApp->L[pos].app.nome);
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
			for(int i = 0; i < MyApp->disp; i++){
				fprintf(arq, "%i %s %.2f\n", MyApp->L[i].app.id, MyApp->L[i].app.nome, MyApp->L[i].app.tam);
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

void MeusAppED(LLSE *MyApp, LLSE *Rum){
	int resp;
	int id;
	int valid = 0;
	
	system("cls");
	printf("\t -- MEUS APLICATIVOS -- \n\n");
	//imprime na tela a lista de meus aplicativos
	for(int i = MyApp->IL; i != -1; i = MyApp->L[i].prox){
		printf("\t%i -- %.2f -- %s \n", MyApp->L[i].app.id, MyApp->L[i].app.tam, MyApp->L[i].app.nome);
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
		for(int i = MyApp->IL; i != -1; i = MyApp->L[i].prox){
			if(MyApp->L[i].app.id == id){
				consultar(MyApp, Rum, i);
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
				printf("\t -- MEUS APLICATIVOS -- \n\n");
				for(int i = MyApp->IL; i != -1; i = MyApp->L[i].prox){
					printf("\t%i -- %.2f -- %s \n", MyApp->L[i].app.id, MyApp->L[i].app.tam, MyApp->L[i].app.nome);
				}
				printf("\n\tDigite o id do aplicativo: ");
				scanf("%i", &id);	
			}
		}while(resp > 1 || resp < 0);
	}
	printf("\n\t");
	system("pause");
}

void AppRum(LLSE *Rum){	
	system("cls");
	printf("\t -- Aplicativos em execucao! -- \n\n");
	
	if(Rum->IL == -5){
		printf("\t\t-- VAZIO --\n\n");
	}
	else
	for(int i = Rum->IL; i != -1; i = Rum->L[i].prox){
		printf("\t%i -- %s -- %.2f\n", Rum->L[i].app.id, Rum->L[i].app.nome, Rum->L[i].app.tam);
	}
	printf("\n\t");
	system("pause");
}

int RumAppED(LLSE *MyApp, LLSE *Rum, int id, int pos){
	if(Rum->IL == -5){
		printf("Pirmeiro elementos a ser adicinado\n\n");
		add(Rum, MyApp->L[pos].app.id, MyApp->L[pos].app.tam, MyApp->L[pos].app.nome);	
		return 1;	
	}
	for(int j = Rum->IL; j != -1; j = Rum->L[j].prox)
	{
		if(Rum->L[j].app.id == id){
			printf("\t -- O aplicativo %s ja esta em execucao! -- \n\n\t", Rum->L[j].app.nome);
			system("pause");
			return 0;
		}
	}
	
	add(Rum, MyApp->L[pos].app.id, MyApp->L[pos].app.tam, MyApp->L[pos].app.nome);
	//printf("\t -- O Aplicativo %s esta em Execucao! -- \n\n\t", MyApp->L[pos].app.nome);
	system("pause");
	return 1;
}

void Stop(LLSE *Rum, int id){
	char nome[N];
	system("cls");
	if(Rum->IL == -5){
		printf("Nenhum Aplicativo Em Execucao\n");
		return;
	}
	
	for(int i = Rum->IL; i != -1; i = Rum->L[i].prox){
		//verificar se o id consta na lista de app em execucao
		if(Rum->L[i].app.id == id){
			strcpy(nome, Rum->L[i].app.nome);
			remover(Rum, i);
			break;
		}
	}
	printf("\n\t");
	printf("Aplicativo %s foi parado!\n", nome);
}

void Erase(LLSE *MyApp, LLSE *Rum, int id, int pos){
	char nome[N];
	FILE *arq;
	int resp;
	strcpy(nome, MyApp->L[pos].app.nome);
	//Para o Aplicativo antes de desistalar, deletando o aplicativo da estrutura RumED
	Stop(Rum, id);
	//Apaga o aplicativo da estrutura MobileED
	remover(MyApp, pos);
	//Opcional. Salvar os dados
	do{
		printf("\n\t Deseja Salvar os Dados?(1-s, 0-n) --> ");
		scanf("%i", &resp);
		if(resp){
			arq = fopen("MobileED.txt", "w");
			for(int i = MyApp->IL; i != -1; i = MyApp->L[i].prox){
				fprintf(arq, "%i %s %.2f\n", MyApp->L[i].app.id, MyApp->L[i].app.nome, MyApp->L[i].app.tam);
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


