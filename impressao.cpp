#include <iostream>
#include <string.h>
#include <thread>
using namespace std;

struct sUser;

//==================================== ARQUIVO ==================================================

typedef struct sArq{
	char nome[20];
	bool impresso;
}arquivo;

//==================================== IMPLEMENTACAO DA FILA ====================================
typedef struct sFila{
	arquivo* vet[3];
	int inicio, fim;
}fila;

void inicializar(fila *Q){
	Q->inicio = 0;
	Q->fim = 0;
}
int vazia(fila *Q){
	if (Q->inicio == Q->fim)
		return 1;
	return 0;
}
int cheia(fila *Q){
	if ((Q->fim+1)%3 == Q->inicio)
		return 1;
	return 0;
}
int enfileirar(fila *Q, arquivo *arq){
	if(cheia(Q))
		return 0;
	Q->fim = (Q->fim+1)%3;
	Q->vet[Q->fim] = arq;
	return 1;
}
int desenfileirar(fila *Q){
	if (vazia(Q))
		return 0;
	Q->inicio = (Q->inicio+1)%3;
	return 1;
}

//====================================== SEMAFORO ==============================================
typedef struct sSem{
	int recurso;
	fila Q;

	int wait(arquivo *arq){
		if(recurso > 0)
		{
			recurso--;
			return 1;
		}
		else
		{
			enfileirar(&Q, arq);
		}
		return 1;
	}
	
}semaforo;

void MandarParaImpressora(semaforo*, sUser*, int);

//==================================== USUARIO =================================================

typedef struct sUser{
	char nome[15];
	arquivo arquivos[3];
	int prioridade;

	void imprimir(semaforo *S1){
		MandarParaImpressora(S1,this, prioridade);
	}

}usuario;

//==================================== IMPRESSAO ================================================

void MandarParaImpressora(semaforo *S1, sUser *user, int prioridade){

	int i=0;
	while(user->arquivos[i].impresso == true && i < 3)
	{
		i++;
	}

	int control = S1->wait(&user->arquivos[i]);

	if(control == 1)
	{
		cout << S1->recurso << endl;
		cout << "ARQUIVO [" << user->arquivos[i].nome <<"] - ";
		cout << "[" << user->nome <<"]" << endl;
		user->arquivos[i].impresso = true;
	}
	

	

}


//==================================== 

void imprimir_user0(usuario *users, semaforo *S1){
	users[0].imprimir(S1);
}

void imprimir_user1(usuario *users, semaforo *S1){
	users[1].imprimir(S1);
}

void imprimir_user2(usuario *users, semaforo *S1){
	users[2].imprimir(S1);
}

int main(){
	
	semaforo S1;
	S1.recurso = 3;
	inicializar(&S1.Q);

	usuario users[3];

	strcpy(users[0].nome, "Usuario 0");
	strcpy(users[0].arquivos[0].nome, "arq 0 - user 0");
	strcpy(users[0].arquivos[1].nome, "arq 1 - user 0");
	strcpy(users[0].arquivos[2].nome, "arq 2 - user 0");
	users[0].prioridade = 1;
	for (int i = 0; i < 3; ++i)
		users[0].arquivos[i].impresso = false;

	strcpy(users[1].nome, "Usuario 1");
	strcpy(users[1].arquivos[0].nome, "arq 0 - user 1");
	strcpy(users[1].arquivos[1].nome, "arq 1 - user 1");
	strcpy(users[1].arquivos[2].nome, "arq 2 - user 1");
	users[1].prioridade = 3;
	for (int i = 0; i < 3; ++i)
		users[1].arquivos[i].impresso = false;

	strcpy(users[2].nome, "Usuario 2");
	strcpy(users[2].arquivos[0].nome, "arq 0 - user 2");
	strcpy(users[2].arquivos[1].nome, "arq 1 - user 2");
	strcpy(users[2].arquivos[2].nome, "arq 2 - user 2");
	users[2].prioridade = 2;
	for (int i = 0; i < 3; ++i)
		users[2].arquivos[i].impresso = false;


	users[0].imprimir(&S1);
	users[1].imprimir(&S1);
	users[2].imprimir(&S1);
	users[0].imprimir(&S1);
	users[1].imprimir(&S1);
	users[2].imprimir(&S1);

	// thread t1(imprimir_user0, users, &S1);
	// thread t2(imprimir_user1, users, &S1);
	// thread t3(imprimir_user2, users, &S1);
	// thread t4(imprimir_user0, users, &S1);
	// thread t5(imprimir_user1, users, &S1);
	// thread t6(imprimir_user2, users, &S1);
	// t1.join();
	// t2.join();
	// t3.join();
	// t4.join();
	// t5.join();
	// t6.join();

}