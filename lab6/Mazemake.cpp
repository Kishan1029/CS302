//Kishan Patel
#include <cstdlib>
#include <ctime>
#include <cstdio>

#include "dset.h"
struct cell {
		//cell() { row = 0; col = 0;}
		cell (int i=0, int j=0) {
			row = i;
			col = j;
		}

		int row;
		int col;
};

void swap(cell &c1, cell &c2) {
	cell temp;
	temp = c1;
	c1 = c2;
	c2 = temp;
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		//print usage error message to stderr
		printf("usage: ./Mazemake nrow ncol Maze.txt\n");
		return 0;
	}	

	int Nrow = atoi(argv[1]);
	int Ncol = atoi(argv[2]);

	// Grid wall:     (i0,j0) | (i1,j1)
	// Horizontal wall: (i,j) | (i+1,j) 
	int h_a = (Nrow -1) * Ncol;
	// Vertical wall:   (i,j) | (i,j+1) 
	int v_a = (Ncol -1) * Nrow;

	//int N = number of interior grid walls
	int N = v_a + h_a;

	//cell wall[N][2];
	cell** wall = new cell*[N];
	for(int i = 0; i < N; i++){
		wall[i] = new cell [2];
	}
	//populate wall[][] with interior grid walls
	int i, j;
	int k = 0;
	//horizontal
	for(i = 0; i < Nrow-1 ; i++){
		for(j = 0; j < Ncol; j++){
			wall[k][0] = cell (i,j);
			wall[k][1] = cell(i+1,j);
			k++;
		}
	}
	//vertical 
	for(i = 0; i < Nrow; i++){
		for(j = 0; j < Ncol - 1; j++){
			wall[k][0] = cell(i,j);
			wall[k][1] = cell(i,j+1);
			k++;
		}
	}
	//randomly perturb list order: swap based
	srand(time(NULL));

	for(i = N-1; i > 0; --i){
		int r = rand() % (i+1);
		swap(wall[i][0], wall[r][0]);
		swap(wall[i][1], wall[r][1]);
	}
	//open output file for writing (argv[3])
	FILE *file;

	file = fopen(argv[3], "w" ) ;

	//write MAZE, N`row, Ncol header 
	fprintf(file, "MAZE %d %d\n", Nrow, Ncol );

	dset ds;
	dset_setup(&ds, Ncol * Nrow);
	int k0, k1;	
	for (k=0; k<N; k++) {
		//if: pair of cells given by wall[k][] are not connected (belong to different disjoint sets) merge them
		k0 = (wall[k][0].row * Ncol) + wall[k][0].col;
		k1 = (wall[k][1].row * Ncol) + wall[k][1].col;
		if(dset_find(&ds, k0) != dset_find(&ds, k1)){	
			dset_merge(&ds, k0, k1);
		}
		//else: write wall to file in the form of the two pairs of cell indices (i0,j0) (i1,j1)
		else
			fprintf(file, " %2d  %2d  %2d  %2d\n", wall[k][0].row, wall[k][0].col, wall[k][1].row, wall[k][1].col);

		//if: all cells belong to the same set, break
		if(dset_size(&ds) == 1) { break; }
	}
	k++;
	for(;k < N; k++){
		fprintf(file, " %2d  %2d  %2d  %2d\n", wall[k][0].row, wall[k][0].col, wall[k][1].row, wall[k][1].col);
	}


	fclose(file);
	dset_free(&ds);
}
