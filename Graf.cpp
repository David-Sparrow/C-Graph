#include "Graph.h"


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf( "\nUzyj: <nazwa_programu> <plik_wejsciowy>\n" );
		return 1;
	}
	
	FILE* fin = NULL;
	if (!(fin = fopen( argv[1], "r" )))
	{
		printf( "\nNie udalo sie otworzyc pliku!\n" );
		return 1;
	}

	Punkt** pMiejsca = NULL;
	int LiczbaMiejsc = CzytDane( fin, &pMiejsca );
	fclose( fin );

	int* V = (int*)calloc( LiczbaMiejsc, sizeof( int ) );
	if (!V)
	{
		printf( "\nBlad alokacji miejsca!!\n" );
		return 1;
	}
	DFS( pMiejsca, 0, V );
	free( V );

	for (int i = 0; i < LiczbaMiejsc; i++)
	{
		if (!pMiejsca[i]->nTyp)
		{
			pMiejsca[i]->dDyst = Dijkstra( pMiejsca, LiczbaMiejsc, i );
			pMiejsca[i]->dCzasCalk = pMiejsca[i]->dDyst / PREDKOSC;

			int* Trasa = (int*)calloc( LiczbaMiejsc, sizeof( int ) );
			if (!Trasa)
			{
				printf( "\nBlad alokacji miejsca!!\n" );
				return 1;
			}

			int temp = pMiejsca[i]->nSklep;		
			int p = 0;
			while (Trasa[p - 1] != i && p < LiczbaMiejsc)
			{
				Trasa[p] = temp;
				temp = pMiejsca[i]->Trasa[temp];	
				p++;
			}

			for (int k = 0; k < p / 2; k++)
			{
				int temp = Trasa[p - k - 1];
				Trasa[p - k - 1] = Trasa[k];
				Trasa[k] = temp;
			}

			pMiejsca[i]->Trasa = Trasa;
		}
	}

	WyswietlWyniki( pMiejsca, LiczbaMiejsc );
	ZwolnijPamiec( &pMiejsca, LiczbaMiejsc );

	return 0;
}

