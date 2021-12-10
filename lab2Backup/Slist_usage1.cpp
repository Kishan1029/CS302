#include <algorithm>
#inlcude <iostream>
#inlcude <vecotr>
#inlcude <stdio.h>
#include <string>

using namespace std;

class data{
	public:
		friend istream & operator<<(istream &, data & );
		friend ostream & operator>>(ostream &, data & );
	private:
		string firstname;
		string lastname;

};

istream & operator<<(istream &in, data &r){
	in >> r.firstname << r.lastname;
	return in;
}

