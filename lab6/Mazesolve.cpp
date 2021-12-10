//Kishan Patel
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

struct cell { 
	cell(int i = 0, int j = 0){
		row = i;
		col = j;
	}
	int row;
	int col;


};

int main(int argc, char *argv[]) {
	if (argc != 3) {
		//print usage error message to stderr
		printf("usage: ./Mazeslove maze.txt path.txt\n");
		return 0;
	}	 

	//open input file for reading
	FILE *file, *out; 
	file = fopen(argv[1], "r");
	
	//open output file for writing
	out = fopen(argv[2], "w");

	int Nrow;
	int Ncol;
	int i, j, k;
	char maze[7];	

	fscanf(file, "%s %d  %d", maze, &Nrow, &Ncol);
	
	bool ***wall;
	wall = new bool** [Nrow];
	for(i = 0; i < Nrow; i++){
		wall[i] = new bool*[Ncol];
	}
	for(i = 0; i < Nrow; i++){
		for(j = 0; j < Ncol; j++){
			wall[i][j]= new bool[4];
		}
	}
	
	for( i = 0; i < Nrow; i++){
		for(j =0; j < Ncol; j++){
			for(k = 0; k < 4; k++){
				wall[i][j][k] = 0;
			}
		}
	}

	for(i = 0 ; i < Nrow; i++){
		for(j = 0; j < Ncol; j++){
			if(i == 0){
				//North
				wall[i][j][0] = 1;
			}
			if(j == 0){
				//West
				wall[i][j][3] = 1;
			}
			if(j == (Ncol -1)){
				//East
				wall[i][j][1] = 1;
			}
			if(i == (Nrow - 1)){

				//South
				wall[i][j][2] = 1;
			}
		}
	}
			
	cell one, two;
	
	//read input file, set interior walls
	while(fscanf(file, "%d %d %d %d", &one.row, &one.col, &two.row, &two.col) == 4) {
		if(one.row < two.row){
			wall[one.row][one.col][2] = 1;
			wall[two.row][two.col][0] = 1;
		}
		else{
			wall[one.row][one.col][1] = 1;
			wall[two.row][two.col][3] = 1;
		}
	}
	/*
		for(i = 0; i < Nrow; i++){
			for(j = 0; j < Ncol; j++){

				printf( "%d %d %d %d \n", wall[i][j][0], wall[i][j][1], wall[i][j][2], wall[i][j][3]);
			}
		}*/


	//initalize DFS path computation
	cell stack[Nrow * Ncol];
	cell source = cell (0,0);
	cell curcell = source;
	cell sink(Nrow-1, Ncol-1);
	
	bool isWhite[Nrow][Ncol];
	
	for(i = 0; i < Nrow; i++){
		for(j = 0; j < Ncol; j++){
			isWhite[i][j] = 0;
		}
	}
	
	isWhite[0][0] = 1;
	
	cell link[Nrow][Ncol];
	
	int ptr = 0, count = 0;
	
	//cell x = sink;
	//cell arry[Nrow*Ncol];
	//arry[count++] = sink;
	
	while(1){

		int prevPtr = ptr;
		curcell = stack[ptr];

		
		if(wall[curcell.row][curcell.col][1] == 0){		//East
			
			if(isWhite[curcell.row][curcell.col+1] != 1){
				++ptr;
				stack[ptr] = cell(curcell.row,curcell.col+1);
				link[curcell.row][curcell.col+1] = curcell;
				isWhite[curcell.row][curcell.col+1] = 1;
				//link[curcell.row][curcell.col+1] = 1;
			}
		}
	
		if(wall[curcell.row][curcell.col][2] == 0){    //South
			
			if(isWhite[curcell.row+1][curcell.col] != 1){
				++ptr;
				stack[ptr] = cell(curcell.row+1,curcell.col);
				link[curcell.row+1][curcell.col] = curcell;
				isWhite[curcell.row+1][curcell.col] = 1;
				//link[curcell.row+1][curcell.col] = 1;
			}
		}
		
		if(wall[curcell.row][curcell.col][3] == 0){		//West
			
			if(isWhite[curcell.row][curcell.col-1] != 1){
				++ptr;
				stack[ptr] = cell(curcell.row,curcell.col-1);
				link[curcell.row][curcell.col-1] = curcell;
				isWhite[curcell.row][curcell.col-1] = 1;		
				
			}
		}

		if(wall[curcell.row][curcell.col][0] == 0){		//North
			
			if(isWhite[curcell.row-1][curcell.col] != 1 ){

				++ptr;
				stack[ptr] = cell(curcell.row-1,curcell.col);
				link[curcell.row-1][curcell.col] = curcell;
				isWhite[curcell.row-1][curcell.col] = 1;

			}
		}

		if(ptr == prevPtr) {
			ptr--;
		}
		
		if(curcell.row == sink.row && curcell.col == sink.col) { break; }
	
		//printf("%d %d\n", curcell.row, curcell.col);	
	}

	cell x = sink;
	cell arry[Nrow*Ncol];
	arry[count++] = sink;
	while(x.row != source.row || x.col != source.col){
		x = link[x.row][x.col];
		arry[count++] = x;
	}

	fprintf(out, "PATH %d %d\n", Nrow, Ncol);
	for(i = count-1; i >= 0;  i--){
		fprintf(out, "%d %d\n", arry[i].row, arry[i].col );
	}
	
	for(i = 0; i < Nrow; i++){
		for(j = 0; j < Ncol; j++){
			delete[] wall[i][j];
		}
	}
	for(i = 0; i < Nrow; i++){
		delete[] wall[i];
	}
	delete[] wall;


	//close open files
	fclose(file);
	fclose(out);
}
