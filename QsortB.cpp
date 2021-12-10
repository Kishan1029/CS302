//Kishan P Patel
// include header files needed
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

class data {
  public: 
	friend istream & operator>>(istream &, data &);
	friend ostream & operator<<(ostream &, const data & );
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
void printlist(T begin, T end) {
	for( T it = begin ; it != end; ++it){
		cout << *it;
	}
 }

template <typename T>
void quicksort(std::vector<T> &A, int left, int right) { 
	if(left < right ){
        	int pindex = rand() % (right - left+1 ) + left; 
        	T pivot = A[pindex];
        
        	swap(A[pindex], A[right]);
        
        	int i = left-1;
        	int j = right;

		while (1){
		
 			while (A[++i] < pivot){
            	if(i == right) 
					break;
			}
			while (pivot < A[--j]){
				if(j == left)
					break;
			}
            		if (i>=j)
						break;
            		swap(A[i], A[j]);
        }

		pindex = i;
		swap(A[pindex], A[right]);		

        	quicksort(A, left, pindex-1);
        	quicksort(A, pindex+1, right);
    	} 
}

template <typename T>
void quickselect(std::vector<T> &A, int left, int k, int right) {
	while(left < right){
		
        	int pindex = rand()%(right - left+1 ) + left; 
        	T pivot = A[pindex];
        
        	swap(A[pindex], A[right]);
        
        	int i = left - 1;
        	int j = right;

		while (1){
		
 			while (A[++i] < pivot){
            	if(i == right) 
					break;
			}
			while (pivot < A[--j]){
				if(j == left)
					break;
			}
            		if (i>=j)
						break;
            		swap(A[i], A[j]);
        }

		pindex = i;
		swap(A[pindex], A[right]);

         	if(pindex == k){ return; }
         	if(k < pindex) { right = pindex-1;}
         	else { left = pindex+1; }
    }
}

int main(int argc, char *argv[]) {
	// perform command-line error checking
	// usage: QsortB -stl | -rpivot [k0 k1]
    	string input;

    if(argc != 2 && argc != 4){

        cerr << "usage: QsortB -stl | -rpivot [k0 k1]" << endl;
        return -1;
	}
	vector<data> A;
	data din;
 	while (cin >> din)
 	A.push_back(din);
  
    input = argv[1];

  	// add selection between sorting options

  	// option -stl
    	if(input == "-stl"){
        	std::sort(A.begin(), A.end());
    	}
  	

  	// option -rpivot
	/*
	int N = (int)A.size();
	int k0 = 0;
	int k1 = N-1;
	*/
    	if(input == "-rpivot"){
        	int N = (int)A.size();
        	int k0 = 0;
        	int k1 = N-1;
        	if(argc == 4){
            		sscanf(argv[2], "%d", &k0);
            		sscanf(argv[3], "%d", &k1);
			
			if(k0 < 0) { 
				 k0 = 0;
				//cout << k0 << endl;

			}
			if(k1 >= N) { 
				 k1 = N-1; 
			}
			quickselect(A,0,k0,N-1);
			quickselect(A,k0,k1,N-1);
			}
	
		//quickselect(A, 0, k0, N-1);
		//quickselect(A, k0, k1, N-1);	
        	quicksort(A, k0, k1);
		
    	}    
  	// update k0, k1 if given as command-line arguments, 
  	// then apply quickselect to partition A accordingly
  	// A[0:N-1] --> A[0:k0-1] <= A[k0:k1] <= A[k1+1:N-1]

  	

  	printlist(A.begin(), A.end());
}
