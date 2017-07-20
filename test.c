#include <stdio.h>
#define SR 256
#define IRASTER 5
#define TAM  (SR/IRASTER)*2
#define AREA TAM/4

void busca(int meio, int distance);

int matrix[TAM][TAM];


int main(){
	int i, j;

	int meio = TAM/2;

	for (i=0; i<TAM; i++){
		for (j=0; j<TAM; j++){
			matrix[i][j] = 0;
		}
	}

	for(i=0; i<meio-1; i++){
		busca(meio, i+1);
	}

	printf("\n");
	for (i=0; i<TAM; i++){
		for (j=0; j<TAM; j++){
			printf("%2d ", matrix[i][j]);
		}
		printf("\n");
	}	
	printf("\n");
	return 0;
}

void busca(int meio, int distance){
	int i, j, k, l, flag=1;

	if(distance <= AREA){
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

	else{
		if(distance+1==meio)
			flag = 0;

		i=meio-distance;
		j=meio;
		matrix[i][j] = distance;
		matrix[i][j-1] = distance;
		matrix[i][j+1] = distance;

		i=meio;
		j=meio+distance;
		matrix[i][j] = distance;
		matrix[i-1][j] = distance;
		matrix[i+1][j] = distance;

		i=meio+distance;
		j=meio;
		matrix[i][j] = distance;
		matrix[i][j-1] = distance;
		matrix[i][j+1] = distance;


		i=meio;
		j=meio-distance;
		matrix[i][j] = distance;
		matrix[i-1][j] = distance;
		matrix[i+1][j] = distance;
	}
	
	if(!flag){
		for(k=0; k<7; k++){
			i=meio-(distance/2);
			j=meio+k+1;
			do{
				matrix[i][j] = distance+1+k;
				i++;
				j++;
			} while (i!=meio && j!=meio+(distance/2)+1);

			i=meio+k+1;
			j=meio+(distance/2);
			do{
				matrix[i][j] = distance+1+k;
				i++;
				j--;
			} while (i != meio+(distance/2)+1 && j!=meio);
	

			i=meio+(distance/2);
			j=meio-k-1;
			do{
				matrix[i][j] = distance+1+k;
				i--;
				j--;
			} while (i!=meio && j!=meio-(distance/2)-1);

			i=meio-k-1;
			j=meio-(distance/2);
			do{
				matrix[i][j] = distance+1+k;
				i--;
				j++;
			} while (i != meio-(distance/2)-1 && j!=meio);
			
		}
	}
}