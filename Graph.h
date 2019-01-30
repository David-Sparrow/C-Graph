#pragma once

#include "HeadFIFO.h"
#include "priorQueue.h"

#define PREDKOSC 7 //prêdkoœæ chodzenia = 7km/h
#define REALLOC 3

typedef struct tagLista
{
	int nNumer;
	double dDlugosc;
	double dCzas;
	tagLista* pNast;
}Sasiedzi;

typedef struct
{
	int nNumer; //nr wierzcho³ka
	int nTyp; // dom - 0, sklep - 1
	int nSklep; //indeks najbli¿szego sklepu
	double dDyst;
	int* Trasa;
	double dCzasCalk;
	int nLiczbaSasiadow;
	Sasiedzi* pLista; //lista s¹siedztwa
}Punkt;

int CzytDane( FILE*, Punkt*** );
int DodajPamiec( Punkt***, int );
void ZwolnijPamiec( Punkt***, int );
void WyswietlWyniki( Punkt**, int );
//void BFS( Punkt**, int, int* );
void DFS( Punkt**, int , int*  );
double Dijkstra( Punkt**, int, int );