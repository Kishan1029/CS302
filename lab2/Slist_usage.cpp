//Kishan Patel
// include header file(s) needed
#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <iomanip>
#include <string>
using namespace std;

#include "Slist.h"

// modify the data class and the associated input 
// and output operators to store, set and print a 
// line number identifier called ID

class data{
	public:
		bool operator<(const data & ) const ;
		friend istream & operator>>(istream &, data &);
		friend ostream & operator<<(ostream &, const data &);
	private:
		string firstname;
		string lastname;
		string phonenum;
		int ID;
};

bool data::operator<(const data &rhs) const {
	if(lastname != rhs.lastname){
		return lastname < rhs.lastname;
	}
	if(firstname != rhs.firstname){
		return firstname < rhs.firstname;
	}
	return phonenum < rhs.phonenum;
	
}

istream& operator>>(istream &in, data &r) {
	static int i;
	r.ID = ++i;
	return(
		in >> r.firstname >> r.lastname >> r.phonenum
	);
}

ostream& operator<< (ostream &out, const data &r) {
	out << " " << setw(24)	<< left << (r.lastname + " " + r.firstname ) << r.phonenum  << " " << setw(8) << right << r.ID;
	out << endl;
	return(out);
}

template<typename T>
void printlist(T begin, T end) { 
	for( T it = begin ; it != end; ++it){
		cout << *it;
	}
}

int main(int argc, char *argv[]) {
  // copy command-line check from QsortB.cpp,
 // then modify to apply to this assignment
	string input;
	if(argc != 2){
		cerr << "usage: " << endl;
		return -1;
	}
	input = argv[1];
	if(input != "-quicksort" && input != "-mergesort"){
		cerr << "usage: " << endl;
		return -1;
	}

	slist<data> A;
   
  data din;
  while (cin >> din)
  A.push_back(din);

  A.sort(input);
  printlist(A.begin(), A.end());
}
