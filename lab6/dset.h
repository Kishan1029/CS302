#ifndef DSET_H
#define DSET_H
#include <stdlib.h>
typedef struct NODE {
	//void node_setup(node * ) ;
	int rank;
	int parent;
}node;

typedef struct DSET {
	int Nset;
	node *S;
}dset;
void node_setup(node *);

void dset_setup(dset *, int);
void dset_free (dset *);
int dset_size (dset *);
int dset_merge(dset *, int, int);
int dset_find(dset *, int);


#endif
