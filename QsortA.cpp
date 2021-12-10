/* First Name: Kishan
   last Name: Patel
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <iomanip>
// include header files needed
using namespace std;

class data {
  public:
	//add operator<using lastname, firstname, phone number

 	friend istream & operator>>(istream &, data &);
 	friend ostream & operator<<(ostream &, const data &);
 	bool operator<(const data &) const;

  private:
    string firstname;
    string lastname;
    string phonenum;
};
 
istream & operator>>(istream &in, data &r) { 
 	//write this to read data object data
	in >> r.firstname >> r.lastname >> r.phonenum;
	return (in);
}

ostream & operator<<(ostream &out, const data &r) {
 	//write this to write data object data
	out << setw(24) << left << (r.lastname + " " + r.firstname ) << r.phonenum;
	out << endl;
	return (out);
}
bool data::operator<(const data &rhs) const {
	if(lastname != rhs.lastname){
		return lastname < rhs.lastname;
	}
	if(firstname != rhs.firstname){
		return firstname < rhs.firstname;
	}
	return phonenum < rhs.phonenum;
}
template<typename T>
void printlist(T begin, T end ) { 
	// template based iterator code for printing data to stdout
	
	for (T it = begin ; it != end; ++it){
		cout << *it;
	}

}

int main(int argc, char *argv[]) {
	vector<data> A;

	data din;
	while (cin >> din)
		A.push_back(din);
	
	std::sort(A.begin(), A.end());

	printlist(A.begin(), A.end());
}
