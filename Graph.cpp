#include "Graph.h"

int CzytDane( FILE* fin, Punkt*** pTab )
{
	int nMiejsca = 0;
	Punkt** pMiejsce = NULL;

	while (!feof( fin ))
	{
		if (!(nMiejsca % REALLOC))
		{
			DodajPamiec( pTab,nMiejsca );
			pMiejsce = *pTab + nMiejsca;
		}

		fscanf( fin, "%d %d %d", &(*pMiejsce)->nNumer, &(*pMiejsce)->nTyp, &(*pMiejsce)->nLiczbaSasiadow );

		Sasiedzi* temp = NULL;
		for (int i = 0; i < (*pMiejsce)->nLiczbaSasiadow; i++)
		{
			Sasiedzi* v = (Sasiedzi*)calloc( 1, sizeof( Sasiedzi ) );
			if (!v)
			{
				printf( "\nBlad alokacji miejsca dla listy sasiedztwa!!\n" );
				return 0;
			}
			fscanf( fin, "%d %lf", &(v->nNumer), &(v->dDlugosc) );
			v->dCzas = v->dDlugosc / PREDKOSC;

			if (!temp)
			{
				(*pMiejsce)->pLista = temp = v;
			}
			else
			{
				temp->pNast = v;
				temp = temp->pNast;
			}
		}
		fscanf( fin, "\n" );
		pMiejsce++;
		nMiejsca++;
	}
	return nMiejsca;
}
//-----------------------
int DodajPamiec( Punkt*** pTab, int nRozmiar )
{
	Punkt** temp = (Punkt**)realloc( *pTab, ( nRozmiar+REALLOC ) * sizeof(Punkt*) );
	if (!temp)
	{
		printf( "\nBlad alokacji pamieci!!\n" );
		return 0;
	}
	*pTab = temp;
	temp = *pTab + nRozmiar;

	for (int i = 0; i < REALLOC; i++, temp++)
	{
		*temp = (Punkt*)calloc( 1, sizeof( Punkt ) );
		if (!(*temp))
		{
			printf( "\nBlad alokacji pamieci!!\n" );
			return 0;
		}
	}
	return nRozmiar + REALLOC;
}
//-----------------------
void ZwolnijPamiec( Punkt*** pTab, int nRozmiar ) 
{
	for (int i = 0; i < nRozmiar; i++)
	{
		Sasiedzi* temp = (*pTab)[i]->pLista;
		while (temp)
		{
			(*pTab)[i]->pLista = temp->pNast;
			free( temp );
			temp = (*pTab)[i]->pLista;
		}
	}
	free( *pTab );
	*pTab = NULL;
}
//-----------------------
void WyswietlWyniki( Punkt** pMiejsce, int nRozmiar )
{
	for (int i = 0; i < nRozmiar; i++)
	{
		printf( "\n======================================================\n" );
		printf( "\nNumer wierzcholka: %d\n", i );

		if (pMiejsce[i]->nTyp)
			printf( "Typ: SKLEP\n" );
		else
		{
			printf( "Typ: DOM\n" );
			printf( "Najblizszy sklep: %d\n", pMiejsce[i]->nSklep );
			printf( "Dystans do sklepu: %0.2f km\n", pMiejsce[i]->dDyst );
			printf( "Czas dotarcia do sklepu: %0.2f min\n", pMiejsce[i]->dCzasCalk * 60 );
			printf( "Trasa do sklepu: " );
			int j = 0;
			while( pMiejsce[i]->Trasa[j] != pMiejsce[i]->nSklep )
				printf("%d -> ", pMiejsce[i]->Trasa[j++]);
			printf( "%d\n", pMiejsce[i]->Trasa[j] );
		}
	}
}
//-----------------------
//void BFS( Punkt** pTab, int u, int* v)
//{
//	QueueFIFO* q = (QueueFIFO*)calloc( 1, sizeof( QueueFIFO ) );
//	if (!q)
//	{
//		printf( "\nBlad alokacji miejsca dla FIFO!!\n" );
//		return;
//	}
//	QFCreate( &q );
//
//	v[u] = -1;
//	QFEnqueue( q, u );
//
//	while (!QFEmpty( q ))
//	{
//		u = QFDequeue( q );
//		Sasiedzi* temp = pTab[u]->pLista;
//		while (temp)
//		{
//			if (!v[temp->nNumer])
//			{
//				v[temp->nNumer] = -1;
//				QFEnqueue( q, temp->nNumer );
//			}
//			temp = temp->pNast;
//		}
//		v[u] = 1;
//	}
//}
//-----------------------
void DFS( Punkt** pTab, int nPierwszy, int* v )
{
	v[nPierwszy] = 1;
	Sasiedzi* temp = pTab[nPierwszy]->pLista;
	while (temp)
	{
		if (!v[temp->nNumer])
		{
			DFS( pTab, temp->nNumer, v );
		}
		temp = temp->pNast;
	}

}
//-----------------------
double Dijkstra( Punkt** pTab, int nRozmiar, int nPierwszy )
{
	PQueue* q = PQInit( nRozmiar );
	int* Trasa = (int*)calloc( nRozmiar, sizeof( int ) );
	double* Dyst = (double*)calloc( nRozmiar, sizeof( double ) );
	if (!Dyst || !Trasa)
	{
		printf( "\nBlad alokacji pamieci - Dijkstra\n" );
		return 0;
	}

	pTab[nPierwszy]->Trasa = Trasa;
	for (int i = 0; i < nRozmiar; i++)
	{
		Dyst[i] = INT_MAX;
	}
	PQEnQueue( q, nPierwszy, 0 );
	Dyst[nPierwszy] = 0;
	double odleglosc = 0;

	while (!PQIsEmpty( q ))
	{
		int i = PQDeQueue( q );

		if (pTab[i]->nTyp)
		{
			pTab[nPierwszy]->nSklep = i;
			PQRelease( &q );
			odleglosc = Dyst[i];
			break;
		}
		else
		{
			Sasiedzi* temp = pTab[i]->pLista;
			while (temp)
			{
				int nPunkt = temp->nNumer;

				if (Dyst[i] + temp->dDlugosc < Dyst[nPunkt])
				{
					Dyst[nPunkt] = Dyst[i] + temp->dDlugosc;
					pTab[nPierwszy]->Trasa[nPunkt] = i;
					PQEnQueue( q, nPunkt, Dyst[nPunkt] );
				}
				temp = temp->pNast;
			}
		}
	}
	free( Dyst );
	return odleglosc;
}