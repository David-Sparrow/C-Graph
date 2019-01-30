#include "priorQueue.h"

//-------------------------------
void UpdateDown( PQueue* q, int l, int p )
{
	if (l == p) return;
	int i = l;
	int j = 2 * i + 1;
	PQItem temp = q->queue[i];
	while (j <= p)
	{
		if (j < p && q->queue[j].nPrior > q->queue[j + 1].nPrior) j++;//////////////////////
		if (temp.nPrior < q->queue[j].nPrior) break;//////////////
		q->queue[i] = q->queue[j];
		i = j;
		j = 2 * i + 1;
	}
	q->queue[i] = temp;
}
//-------------------------------
void UpdateUp( PQueue* q, int l, int p )
{
	if (l == p) return;
	int i = p;
	int j = (i - 1) / 2;
	PQItem temp = q->queue[i];
	while (i > l  && q->queue[j].nPrior > temp.nPrior) /////////////////
	{
		q->queue[i] = q->queue[j];
		i = j;
		j = (i - 1) / 2;
	}
	q->queue[i] = temp;
}
//-------------------------------
PQueue* PQInit( /*PQueue* q,*/ int nSize )
{
	//-----------------------
	PQueue* q = (PQueue*)calloc( 1, sizeof( PQueue ) );
	if (!q)
	{
		printf( "\nPQInit: Blad alokacji miejsca!!\n" );
		return NULL;
	}
	//-----------------------
	q->queue = (PQItem*)calloc( nSize, sizeof( PQItem ) );
	if (!q->queue)
	{
		printf( "\nPQInit: Blad alokacji miejsca!!\n" );
		return NULL;
	}
	q->nSize = nSize;
	return q;
}
//-------------------------------
int PQIsEmpty( PQueue* q )
{
	return !q->CurrentSize;
}
//-------------------------------
void PQEnQueue( PQueue* q, int nKey, double nPrior )
{
	if (q->CurrentSize == q->nSize)
	{
		printf( "\nPQEnqueue: Blad, kolejka przepelniona!!\n" );
		return;
	}
	q->queue[q->CurrentSize].nKey = nKey;
	q->queue[q->CurrentSize].nPrior = nPrior;
	q->CurrentSize++;
	UpdateUp( q, 0, q->CurrentSize - 1 );
}
//-------------------------------
int PQDeQueue( PQueue* q )
{
	if (PQIsEmpty( q ))
	{
		printf( "\nPQDeQueue: Blad, kolejka jest pusta!!\n" );
		return 0;
	}
	int tmp = q->queue[0].nKey;
	q->CurrentSize--;
	q->queue[0] = q->queue[q->CurrentSize];
	UpdateDown( q, 0, q->CurrentSize - 1 );
	return tmp;
}
//-------------------------------
void PQClearQueue( PQueue* q )
{
	if (!q->CurrentSize)
	{
		printf( "\nPQClearQueue: Kolejka jest pusta!!\n" );
		return;
	}
	memset( q->queue, 0, q->nSize * sizeof( PQItem ) );
	q->CurrentSize = 0;
}
//-------------------------------
void PQRelease( PQueue** q )
{
	if (!*q) return;
	if ((*q)->queue)
	{
		free( (*q)->queue );
	}
	free( *q );
	*q = NULL;
}
//-------------------------------
void PQPrint( PQueue* q )
{
	if (!q->CurrentSize)
	{
		printf( "\nPQPrint: Kolejka jest pusta!!\n" );
		return;
	}
	PQItem* p = q->queue;
	printf( "\nLp.\tKLUCZ\tPriorytet\n" );
	for (int i = 1; i <= q->CurrentSize; i++)
	{
		printf( "\n%d\t%d\t%lf", i,p->nKey, p->nPrior);
		p++;
	}
}
//-------------------------------

