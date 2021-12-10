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

class data { 
	public:
		friend istream & operator<<(istream &, data &);
		friend ostream & operator>>(ostream &, const data & );
		bool operator<(const data &, const data & ) ;
	private:
		string firstname;
		string lastname;
		string phonenum;
};
bool data::operator<(const data &rhs1, const data &rsh2 ) const {
	if(lastname != rhs.lastname){
		return lastname < rhs.lastname;
	}
	if(firstname != rhs.firstname){
		return firstname < rhs.firstname;
	}
	return phonenum < rhs.phonenum;
	
}
istream& operator>>(istream& in, data& r) {
	in >> r.firstname; 
	in >> r.lastname;
	in >> r.phonenum;
	return in;
}
ostream& operator<<(ostream& out, const data& r) {
	out << setw(24)	<< left << (r.lastname + " " + r.firstname ) << r.phonenum;
	out << endl;
	return out;
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
	if(argc != 4 && argc != 4){
		cerr << "usage: " << endl;
		return -1;
	}
	input = argv[1];
  slist<data> A;

  data din;
  while (cin >> din)
  A.push_back(din);

//  A.sort(command line mode option);

  printlist(A.begin(), A.end());
}
