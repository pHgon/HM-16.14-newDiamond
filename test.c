#include <stdio.h>
#define SR 256
#define IRASTER 5

void busca(int meio, int distance);
int matrix[51][51];

int main(){
	int i, j, count;
	int meio = (SR/(IRASTER*2)), tam = SR/IRASTER;
	//printf("%d\n", meio);

	for (i=0; i<tam; i++){
		for (j=0; j<tam; j++){
			matrix[i][j] = 0;
		}
	}

	matrix[meio][meio] = 0;

	for(i=0; i<meio+5; i++){
		busca(meio, i+1);
	}

	printf("\n");
	for (i=0; i<tam; i++){
		for (j=0; j<tam; j++){
			printf("%2d ", matrix[i][j]);
		}
		printf("\n");
	}	
	printf("\n");
	return 0;
}

void busca(int meio, int distance){
	int i, j;

	i=meio-distance;
	j=meio;
	do{
		matrix[i][j] = distance;
		i++;
		j++;
	} while (i != meio && j!=meio);

	i=meio;
	j=meio+distance;
	do{
		matrix[i][j] = distance;
		i++;
		j--;
	} while (i != meio && j!=meio);

	i=meio+distance;
	j=meio;
	do{
		matrix[i][j] = distance;
		i--;
		j--;
	} while (i != meio && j!=meio);

	i=meio;
	j=meio-distance;
	do{
		matrix[i][j] = distance;
		i--;
		j++;
	} while (i != meio && j!=meio);
}