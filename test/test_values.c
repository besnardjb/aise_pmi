#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pmi.h"


int main(int argc, char ** argv )
{
	if( PMI_Init() != PMI_SUCCESS )
	{
		fprintf(stderr, "Could not init PMI\n");
		return 1;
	}

	int rank = 0;
        int size = 1;
	if( PMI_Get_size(&size) != PMI_SUCCESS )
	{
		fprintf(stderr, "Could not get PMI size\n");
		return 1;
	}

	if( PMI_Get_rank(&rank) != PMI_SUCCESS )
	{
		fprintf(stderr, "Could not get PMI rank\n");
		return 1;
	}

	char key[PMI_STRING_LEN];
	char val[PMI_STRING_LEN];

	/* Set 3 random values for this rank */
	srand(rank);
	int i;
	for( i = 0 ; i < 3; i++)
	{
		snprintf(key, PMI_STRING_LEN, "rank_%d_iter_%d", rank, i);
		snprintf(val, PMI_STRING_LEN, "%d", rand());
		printf("RANK %d SET %s = %s\n", rank, key, val);
		if( PMI_KVS_Put(key, val) != PMI_SUCCESS)
		{
			fprintf(stderr, "Could not put key\n");
			return 1;
		}
	}


	printf("%d/%d ----- BARRIER -----\n", rank, size );
	/* Do a BARRIER */
	PMI_Barrier();


	/* Check values for the next rank with a modulo */
	srand((rank + 1)%size);
	int error = 0;
	for( i = 0 ; i < 3; i++)
	{
		snprintf(key, PMI_STRING_LEN, "rank_%d_iter_%d", (rank+1)%size, i);
		snprintf(val, PMI_STRING_LEN, "%d", rand());
		char returned_val[PMI_STRING_LEN];
		returned_val[0]='\0';
		
		if( PMI_KVS_Get(key, returned_val, PMI_STRING_LEN) != PMI_SUCCESS)
		{
			fprintf(stderr, "Could not get key\n");
			return 1;
		}

		printf("RANK %d check for %d GET %s = %s expexted %s\n", rank, (rank + 1)%size, key, returned_val, val);
		if(strcmp(val, returned_val))
		{
			fprintf(stderr," !! Bad value\n");
			error = 1;
		}
	}

	if( PMI_Finalize() != PMI_SUCCESS )
	{
		fprintf(stderr, "Could not finalize PMI\n");
	}

	return error;
}
