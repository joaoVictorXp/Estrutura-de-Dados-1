#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "StructData.h"
#define N 100
#define AP 20

void Menu(LLSE *MyApp, LLDE *Rum , LLV *Store, LLDE *Fila, LLSE *Pilha);
void Consult(LLSE *MyApp, LLDE *Rum, LLSE *Pilha, int pos);
void AppStore(LLV *Store, LLSE *MyApp, LLDE *Fila);
void MyAppED(LLSE *MyApp, LLDE *Rum, LLSE *Pilha);
void AppRum(LLDE *Rum, LLSE *Pilha);
void RumAppED(LLSE *MyApp, LLDE *Rum, LLSE *Pilha, int id, int pos);
void Stop(LLDE *Rum, LLSE *Pilha, int id);
void Erase(LLSE *MyApp, LLDE *Rum, LLSE *Pilha, int id, int pos);

int main(int argc, char** argv)
{
	system("color 3f"); system("title Trabalho Final de Estrutura de Dados");
	char arquivo1[N], arquivo2[N];
	strcpy(arquivo1, "StoreED.txt");
	strcpy(arquivo2, "MobiED.txt");
	
	LLV Store;
	LLSE MyApp, Pilha;
	LLDE Rum, Fila;
	
	Start_LLV(&Store);
	Start_LLSE(&MyApp);
	Start_LLDE(&Fila);
	Start_LLSE(&Pilha);
	Start_LLDE(&Rum);
	
	Ler_LLV(&Store, arquivo1);
	Ler_LLSE(&MyApp, arquivo2);
	
	Menu(&MyApp, &Rum, &Store, &Fila, &Pilha);
	
	system("pause");
	return 0;
}


void Menu(LLSE *MyApp, LLDE *Rum , LLV *Store, LLDE *Fila, LLSE *Pilha){
	int resp;	
	do{
		int i = 0, vet[9];
		int j = MyApp->IL;
		int control = MyApp->total;                                         
		system("cls");
		//imprime de forma matricial 3x3 os aplicativos
		//caso tenha menos aplicativos que a capacidade
		//a matriz sera preenchida com espacos em branco
		while((control > 0 && i < 9) && j != -1){
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
		printf("\n\t(Digite 0 para Desligar) --> ");
		
		scanf("%i", &resp);
		if(resp > 0 && resp <= 9){
			//caso digite um valos que nao corresponda a nenhum aplicativo na matriz 3x3
			if(resp > MyApp->total){
				printf("\n\t -- APLICATIVO NAO INSTALADO! -- \n\n");
				continue;
			}
			//senao sera chamado o menu interno do aplicativo
			Consult(MyApp, Rum,Pilha, vet[resp - 1]);
		}
		//caso o valor nao esteja na matriz 3x3, sera chamado uma das tres funcoes principais
		else
		{
			switch(resp)
			{
			case 10:
				AppStore(Store, MyApp, Fila);
				break;
			case 11:
				MyAppED(MyApp, Rum, Pilha);
				break;
			case 12:
				AppRum(Rum, Pilha);
				break;
			case 0:
				break;
			default:
				printf("Opcao invalida!\n");
				break;
			}
		}
		
	}while(resp != 0);
	system("cls");
	printf("\n\t -- Bye! -- ");
}

void Consult(LLSE *MyApp, LLDE *Rum,LLSE *Pilha, int pos){
	system("cls");
	int resp, x;
	do{
		system("cls");
		x = 0;
		printf("\t -- %i -- %s -- ", MyApp->L[pos].app.id, MyApp->L[pos].app.nome);
		if(MyApp->L[pos].app.id == 99){
			printf("%i abas abertas\n\n", Pilha->total);
		}
		printf("\n\n\t1 - Executar o aplicativo\n");
		printf("\t2 - Parar o Aplicativo\n");
		printf("\t3 - Desistalar o Aplicativo\n");
		printf("\t0 - SAIR\n\n"); 
		printf("\t--> ");
		scanf("%i", &resp);
		
		switch(resp)
		{
		case 1:
			RumAppED(MyApp, Rum, Pilha, MyApp->L[pos].app.id, pos);
			break;
		case 2:
			Stop(Rum, Pilha, MyApp->L[pos].app.id);
			break;
		case 3:
			Erase(MyApp, Rum, Pilha, MyApp->L[pos].app.id, pos);
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


void AppStore(LLV *Store, LLSE *MyApp, LLDE *Fila){
	int resp, arq;
	int r, validSalvaDados;//validaSalvaDados verifica se existe dados errados a serem salvos no arquivo
	system("cls");
	printf("\t\t -- LOJA DE APLICATIVOS ED --\n\n");
	printf("\tDeseja Instalar um Aplicativo(1 - s, 0 - n) --> ");
	scanf("%i", &resp);
	
	arq = resp;//armazena a primera resposta, caso for 0 nao entrará na parte de salvar dados no arquivo
	
	while(resp){
		validSalvaDados = 0;
		system("cls");
		printf("\t\t -- LOJA DE APLICATIVOS ED --\n\n");
				
		for(int i = Store->IL; i < Store->FL; i++){
			printf("\t| ID: %.3i - TAMANHO: %.2f - NOME: %s \n", Store->app[i].id, Store->app[i].tam, Store->app[i].nome);
		}
		
		int invalid = 0;//verifica se o id selecionado ja esta instalado na struct MobiED[]
		int id1, idInvalid = 1;//idValid verifica se o id digitado consta no struct StoreED[]
		
		printf("\n\tDIGITE O ID DO APP A SER INSTALADO: ");
		scanf("%i", &id1);

		for(int i = Store->IL; i < Store->FL; i++){
			if(Store->app[i].id == id1){
				//verifica se o aplicativo ja esta instalado
				for(int z = MyApp->IL; z != -1; z = MyApp->L[z].prox){
					if(id1 == MyApp->L[z].app.id){
						invalid = 1;
						break;
					}	
				}
				if(invalid){
					idInvalid = 0;
					break;
				}
				else{
					idInvalid = 0;
					Add_LLDE_FILA(Fila, Store->app[i].id, Store->app[i].tam, Store->app[i].nome);
					if(Fila->total > 3){
						int pos = MyApp->disp;
						Add_LLSE(MyApp, Fila->L[Fila->IL].app.id, Fila->L[Fila->IL].app.tam, Fila->L[Fila->IL].app.nome);
						
						Remove_LLDE_FILA(Fila);
						
						printf("\n\t -- O aplicativo %s foi instalado! -- \n\n", MyApp->L[pos].app.nome);
						validSalvaDados = 1;
					}
				}
				break;
			}
		}		
		if(invalid == 1){
			printf("\n\t -- Aplicativo ja instalado! -- \n\n");
			invalid = 1;
		}
		else if(idInvalid == 1){
			printf("\n\t -- O aplicativo com o ID = %i nao foi encontrado! -- \n\n", id1);
			invalid = 1;
		}
		else
		{
			printf("\n\t -- Aplicativos na fila: --\n\n");
			for(int i = Fila->IL; i != -1; i = Fila->L[i].prox){
				printf("\t - %s -- POSICAO = %i\n", Fila->L[i].app.nome, i);
			}
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
			arq = fopen("MobiED.txt", "w");
			for(int i = MyApp->IL; i != -1; i = MyApp->L[i].prox){
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

void MyAppED(LLSE *MyApp, LLDE *Rum, LLSE *Pilha){
	int resp;
	int id;
	int valid = 0;
	
	system("cls");
	printf("\t -- MEUS APLICATIVOS -- \n\n");
	//imprime na tela a lista de meus aplicativos
	for(int i = MyApp->IL; i != -1; i = MyApp->L[i].prox){
		printf("\tID: %.3i -- TAMANHO: %.2f -- NOME: %s \n", MyApp->L[i].app.id, MyApp->L[i].app.tam, MyApp->L[i].app.nome);
	}
	//validacao de consulta
	do{
		printf("\n\n\tConsult Aplicativo(1 - s, 0 - n) --> ");
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
				Consult(MyApp, Rum, Pilha, i);
				valid = 1;
				break;
			}
		}
		
		if(!valid){
			printf("\n\t -- Id Nao Encontrado! -- ");
		}
		
		do{			
			printf("\n\n\tConsult Outro Aplicativo(1 - s, 0 - n) --> ");
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

void AppRum(LLDE *Rum, LLSE *Pilha){	
	system("cls");
	printf("\t -- Aplicativos em execucao! -- \n\n");
	
	if(Rum->IL == -5 && Pilha->IL == -5){
		printf("\t\t-- VAZIO --\n\n");
	}
	else if(Rum->IL != -5){
		for(int i = Rum->IL; i != -1; i = Rum->L[i].prox){
			printf("\t%i -- %s -- %.2f\n", Rum->L[i].app.id, Rum->L[i].app.nome, Rum->L[i].app.tam);
		}
	}
	if(Pilha->IL != -5){
		printf("\t%i -- %s -- %.2f -- %i abas\n", Pilha->L[Pilha->IL].app.id, Pilha->L[Pilha->IL].app.nome, Pilha->L[Pilha->IL].app.tam, Pilha->total);
	}
	printf("\n\t");
	system("pause");
}

void RumAppED(LLSE *MyApp, LLDE *Rum, LLSE *Pilha, int id, int pos){
	int valid = 1;//variavel de validacao de aplicativos ja em execucao
	if(id == 99){
		Add_LLSE_PILHA(Pilha, MyApp->L[pos].app.id, MyApp->L[pos].app.tam, MyApp->L[pos].app.nome);
		return;
	}
	for(int j = Rum->IL; j != -1; j = Rum->L[j].prox){
		if(Rum->L[j].app.id == id){
			printf("\t -- O aplicativo %s ja esta em execucao! -- \n\n\t", Rum->L[j].app.nome);
			system("pause");
			return;
		}
	}

	Add_LLDE(Rum, MyApp->L[pos].app.id, MyApp->L[pos].app.tam, MyApp->L[pos].app.nome);
			
	if(valid)
	printf("\t -- O Aplicativo %s esta em Execucao! -- \n\n\t", MyApp->L[pos].app.nome);
	system("pause");
}

void Stop(LLDE *Rum, LLSE *Pilha, int id){
	char nome[N];
	system("cls");
	if(Rum->IL == -5 && Pilha->IL == -5){
		printf("\n\tNenhum Aplicativo Em Execucao\n");
		return;
	}
	
	if(id == 99){
		if(Pilha->total > 1){
			printf("\n\tExistem muitas abas abertas, deseja fechar todas?(1-sim/0-nao):\n");
			int resp;
			scanf("%i", &resp);
			if(resp){
				Start_LLSE(Pilha);
				return;
			}
		}
		Remove_LLSE(Pilha, Pilha->IL);
		return;
	}
	
	for(int i = Rum->IL; i != -1 ; i = Rum->L[i].prox){
		//verificar se o id consta na lista de app em execucao
		if(Rum->L[i].app.id == id){
			strcpy(nome, Rum->L[i].app.nome);
			Remove_LLDE(Rum, i);
			printf("\n\tAplicativo %s foi parado!\n", nome);
			break;
		}
	}
	printf("\n\t");
	system("pause");
}

void Erase(LLSE *MyApp, LLDE *Rum, LLSE *Pilha, int id, int pos){
	char nome[N];
	FILE *arq;
	int resp;
	strcpy(nome, MyApp->L[pos].app.nome);
	if(id == 99){
		Start_LLSE(Pilha);
	}
	else{
		//Para o Aplicativo antes de desistalar, deletando o aplicativo da estrutura RumED
		Stop(Rum, Pilha, id);
	}
	//Apaga o aplicativo da estrutura MobiED
	Remove_LLSE(MyApp, pos);
	//Opcional. Salvar os dados
	do{
		printf("\n\t Deseja Salvar os Dados?(1-s, 0-n) --> ");
		scanf("%i", &resp);
		if(resp){
			arq = fopen("MobiED.txt", "w");
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

