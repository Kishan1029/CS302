#include "dset.h"

void dset_setup(dset *ds, int N){
	unsigned int i;

	ds->S = (node *) malloc(N * sizeof(node));
	ds->Nset = N;

	for(i = 0; i < ds->Nset; i++){
		node_setup(&(ds->S[i]));
	}
}

void dset_free(dset *ds){
	if(ds->S != NULL)
		free(ds->S);
}

int dset_size(dset *ds){
	return ds->Nset;
}

int dset_merge(dset *ds, int i, int j){
	i = dset_find(ds, i);
	j = dset_find(ds, j);

	if(i != j){
		node &Si = ds->S[i];
		node &Sj = ds->S[j];

		if(Si.rank > Sj.rank)		Sj.parent = i;
		else if(Si.rank < Sj.rank) Si.parent = j;
		else { Sj.parent = i; Si.rank += 1;}

		ds->Nset -= 1;
	}
	return dset_find(ds, i);
}

int dset_find(dset *ds, int N){
	if(ds->S[N].parent == -1)
		return N;
	ds->S[N].parent = dset_find(ds, ds->S[N].parent);
	return ds->S[N].parent;
}

void node_setup(node *n){
	n->rank = 0;
	n->parent = -1;
}
