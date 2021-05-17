#include <iostream>
#include <pthread.h>
#include <windows.h>
#include <ctime>
using namespace std;

struct Nodo{
	int valor;
	Nodo *siguiente;
};
Nodo *fin1=NULL;
Nodo *fin2=NULL;
Nodo *fin3=NULL;
Nodo *fin4=NULL;
Nodo *inicio1 = NULL;
Nodo *iniico2 = NULL;
Nodo *inicio3 = NULL;
Nodo *inicio4 = NULL;
Nodo *cajero1 = NULL;
Nodo *cajero2 = NULL;
Nodo *cajero3 = NULL;
Nodo *cajero4 = NULL;
Nodo *pila1 = NULL;
Nodo *pila2 = NULL;
Nodo *pila3 = NULL;
Nodo *pila4 = NULL;

void* ingresarAleatorio(void*);
void* atenderCaja(void*);
void entrarPila();
bool ingreso();
bool atender();
int contador = 0;

int main(){
	pthread_t hilo1, hilo2;
	Sleep(1000);
	pthread_create(&hilo1,NULL,ingresarAleatorio,NULL);
	Sleep(2000);
	pthread_create(&hilo2,NULL,atenderCaja,NULL);
	Sleep(1000);
	pthread_join(hilo1, NULL);
	Sleep(2000);
	pthread_join(hilo2, NULL);
}

void Push(Nodo *&pila,int v){
	Nodo *push = new Nodo();
	push->valor = v;
	push->siguiente = pila;
	pila = push;
}

void Pop(Nodo *&pila){
	int v=NULL;
	Nodo *pop = pila;
	v = pop->valor;
	pila = pop->siguiente;
	delete pop;
}
int sumaPila(Nodo *&pila, int cajero){
	int suma = 0;
	Nodo *pointer = pila;
	cout<<"Numeros atendidos cajero "<<cajero<<": ";
	while(pointer != NULL){
		cout<<pointer->valor<<" | ";
		suma += pointer->valor;
		pointer = pointer->siguiente;
	}
	cout<<"       *Total cajero "<<cajero<<": "<<suma<<endl;
}
void Add(Nodo *&inicio,Nodo *&fin, int v){
	Nodo *add = new Nodo();
	add->valor = v;
	add->siguiente = NULL;
	if (inicio== NULL){
		inicio = add;
	}else{
		fin->siguiente=add;
	}
	fin = add;
}
void Remove(Nodo *&inicio, Nodo *&fin){
	int v;
	v = inicio->valor;
	Nodo *cola = inicio;
	
	if(inicio == fin){
		inicio = NULL;
		fin = NULL;
	}
	else{
		inicio = inicio->siguiente;
	}
	delete cola;
}

bool ingreso(){
	bool ingreso = true;
	if(contador != 200){
		srand(time(NULL));
		int dato = rand()%(90-1+1)+1;
		bool stop = false;
		while(!stop){
			int cola = rand()%(4-1+1)+1;
			switch(cola){
				case 1: Add(cajero1,fin1,dato);
					cout<<"Nuevo dato en cajero 1: "<<dato<<endl;
					stop = true;
					break;
				case 2: Add(cajero2,fin2, dato);
					cout<<"Nuevo dato en cajero 2: "<<dato<<endl;
					stop = true;
					break;
				case 3: Add(cajero3,fin3, dato);
					cout<<"Nuevo dato en cajero 3: "<<dato<<endl;
					stop = true;
					break; 
				case 4: Add(cajero4,fin4, dato);
					cout<<"Nuevo dato en cajero 4: "<<dato<<endl;
					stop = true;
					break;
			}
		}
		contador++;
	} else {
		ingreso = false;
	}
	return ingreso;
}

bool atender(){
	bool atender = true;
	bool vacio1 = false;
	bool vacio2 = false;
	bool vacio3 = false;
	bool vacio4 = false;
	
	if(cajero1 == NULL){
		vacio1 = true;
	} else {
		Push(pila1, cajero1->valor);
		Remove(cajero1,fin1); 
		sumaPila(pila1, 1);
		vacio1 = false;	
	}
	
	if(cajero2 == NULL){
		vacio2 = true;
	} else {
		Push(pila2, cajero2->valor);
		Remove(cajero2,fin2);
		sumaPila(pila2,2);
		vacio2 = false;	
	}
	
	if(cajero3 == NULL){
		vacio3 = true;
	} else {
		Push(pila3, cajero3->valor);
		Remove(cajero3,fin3);
		sumaPila(pila3,3);
		vacio3 = false;	
	}
	
	if(cajero4 == NULL){
		vacio4 = true;
	} else {
		Push(pila4, cajero4->valor);
		Remove(cajero4,fin4);
		sumaPila(pila4,4);
		vacio4 = false;
	}
	
	if(vacio1 && vacio2 && vacio3 && vacio4){
		cout<<"Todos los numeros han sido atendidos"<<endl;
		atender = false;
	}
	
	return atender;
}
void* ingresarAleatorio(void* data){
	bool seguir = true;
	while(seguir){
		seguir = ingreso();
		Sleep(1000);
	}
}

void* atenderCaja(void* data){
	bool seguir = true;
	while(seguir){
		seguir = atender();
		Sleep(2000);
	}
}
