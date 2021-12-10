//Kishan Patel
#include <algorithm>
#include <fstream>
#include <vector>
#include <cstring>
#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <iomanip>
using namespace std;

void set_oldfriends(vector <string> &name, vector < set <int> > &friends, int M0, int M1) {
	int N = (int)name.size();
	// initialize 2D-vector-array friends (hint: use vector::assign())
	friends.assign(N, set<int>());
	int j;
	set<int>::iterator ii;

	for (int i=0; i<N; i++) {
		//declare std::set called doknow
		set <int> doknow;
		//initialize M (random number of friends: function of M0, M1)
		int M = M0 +  rand() % (M1);

		while ((int)doknow.size() < M) {
			//compute j (random friend index: hint j != i)
			do{
				j = rand() % N;
			}while(i == j);

			doknow.insert(j);
		}
		
		for(ii = doknow.begin(); ii != doknow.end(); ii++){
			//friends[i][*ii] = friends[*ii][i] = 1;
			friends[i].insert(*ii);
			friends[*ii].insert(i);
		}
	}	
}

void set_newfriends(vector < set <int> > &friends, vector < set <int> > &new_friends) {
	int N = (int)friends.size();
	//initialize 2D-vector-array new_friends (hint: use vector::assign())
	new_friends.assign(N, set<int>());
	set<int>::iterator j;
	set<int>::iterator k;

	for (int i=0; i<N; i++) {

		for (j = friends[i].begin(); j != friends[i].end(); ++j) {
			//if( i != *j ){
				for (k = friends[*j].begin(); k != friends[*j].end(); ++k) {
					if (*k != i && find(friends[*k].begin(),friends[*k].end(),i) == friends[*k].end()){
					//update the corresponding pairs of new_friends entries
					//new_friends[i][k] = new_friends[k][i] = 1;
						new_friends[i].insert(*k);
						new_friends[*k].insert(i);
					}
				}
			//}	
		}
	}
}

void writetofile(const char *fname, vector<string> &name, vector < set <int> > &friends) {
	ofstream outfile;
	outfile.open(fname);

	int N = (int)name.size();
	//determine max name length
	int max = (int)name[0].length();
	for(int i = 0; i < N; i++){
		if(name[i].length() > max){
			max = name[i].length();
		}
	}

	set<int>::iterator j;
	for (int i=0; i<N; i++) {
		int count = 0;
		outfile << left << setw(max) << name[i] << " :";

		for (j = friends[i].begin(); j != friends[i].end(); j++) {
			if(count == 8){
				outfile << endl << left << setw(max) << name[i] << " :";
				count = 0;
			}
			outfile << " " << left <<  setw(max) << name[*j];
			count++;
		}
		outfile << endl;
	}

	outfile.close();
}

int main(int argc, char *argv[]) {
	//parse argc, argv arguments
	//print usage message and exit if invalid
	if(argc != 3 && argc != 1){
	  cerr << "Usage: ./Friendnet1 [-seed N] \n";
	  return -1;
	}
	if(argc == 3){
		if(strcmp(argv[1], "-seed") != 0){
			cerr << "Error\n";
			exit (0);
		}
		srand(atoi(argv[2]));
	}
	else{
		srand(time(0));
	}
	//seed random number generator
	
	string temp;
	vector<string> name;
	//read strings from stdin into name vector
	while(getline(cin, temp)){
		name.push_back(temp);
	}

	int M0 = 1; // min number of friends
	int M1 = 3; // potential extra friends

	//declare 2D-vector-array called friends
	vector < set <int> > friends;

	//declare 2D-vector-array called new_friends
	vector < set <int> > new_friends;

	set_oldfriends(name, friends, M0, M1);
	writetofile("doknow3.txt", name, friends);

	set_newfriends(friends, new_friends);
	writetofile("mightknow3.txt", name, new_friends);
}
