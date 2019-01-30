#include "HeadFIFO.h"

int QFCreate( QueueFIFO** q )
{
	*q = (QueueFIFO*)calloc( 1, sizeof( QueueFIFO ) );
	if (!*q)
	{
		printf( "\nQFCreate: Blad alokacji miejsca dla struktury kolejki!!\n" );
		return 0;
	}

	(*q)->pHead = (*q)->pTail = (QFIFOItem*)calloc( 1, sizeof( QFIFOItem ) );
	if (!(*q)->pHead)
	{
		printf( "\nQFCreate: Blad alokacji miejsca dla glowy!!\n" );
		return 0;
	}
	return 1;
}
//-----------------------------
int QFEmpty( QueueFIFO* q )
{
	return !(q->pHead->pNext);
}
//-----------------------------
void QFEnqueue( QueueFIFO*q, int x )
{
	QFIFOItem* v = (QFIFOItem*)calloc( 1, sizeof( QFIFOItem ) );
	if (!v)
	{
		printf( "\nQFEnqueue: Blad alokacji miejsca!\n" );
		return;
	}
	v->key = x;
	q->pTail->pNext = v;
	q->pTail = v;
}
//-----------------------------
int QFDequeue( QueueFIFO* q )
{
	if (!QFEmpty( q ))
	{
		int tmp = q->pHead->pNext->key;
		QFIFOItem* temp = q->pHead->pNext;

		q->pHead->pNext = temp->pNext;
		free( temp );
		if (q->pHead->pNext == NULL) q->pTail = q->pHead;
		return tmp;
	}
	else
	{
		printf( "\nQFDequeue: Blad! Kolejka jest pusta!\n" );
		return 0;
	}
}
//-----------------------------
void QFClear( QueueFIFO* q )
{
	while (!QFEmpty( q ))
		QFDel( q );
}
//-----------------------------
void QFRemove( QueueFIFO** q )
{
	QFClear( *q );
	free( (*q)->pHead ); //usuwanie glowy
	free( *q ); //usuwanie struktury kolejki
	*q = NULL;
}
//-----------------------------
void QFDel( QueueFIFO* q )
{
	if (!QFEmpty( q ))
	{
		QFIFOItem* tmp = q->pHead->pNext;
		q->pHead->pNext = q->pHead->pNext->pNext;

		free( tmp );

		if (q->pHead->pNext == NULL) q->pTail = NULL;
	}
	else
	{
		printf( "QFDel: Blad! Kolejka jest pusta!!" );
		return;
	}
}
//-----------------------------
void QFPrint( QueueFIFO* q )
{
	if (QFEmpty( q ))
	{
		printf( "Kolejka jest pusta!!" );
		return;
	}
	QFIFOItem* tmp = q->pHead->pNext;
	int i = 1;
	while(tmp)
	{
		printf( "\n%d.\t%d\n", i++, tmp->key );
		tmp = tmp->pNext;
	}
}
//-----------------------------