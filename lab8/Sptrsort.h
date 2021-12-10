//WRITE THIS BASED ON SMART POINTER CLASS
#ifndef SPTRSORT_H
#define SPTRSORT_H	
#include <vector>
#include <algorithm>
#include <iostream>
template <typename T>
class sptr {
	public:
		sptr(T * _ptr = NULL) { ptr = _ptr; }

		bool operator< (const sptr &rhs) const{
			return *ptr < *rhs.ptr;
		}
		operator T * ( ) const { return ptr;}
	private:
		T *ptr;
  
};


template <typename T>
void sptrsort(std::vector<T *> &A) {
	size_t a_sz, i;
	vector < sptr <T> > ptrs;
	
	a_sz = A.size();
	ptrs.resize(a_sz);
	//ptr2sptr(A, Ap);
	for(int i = 0; i < a_sz; i++){
		ptrs[i] = sptr<T>(A[i]);
	}
	std::sort(ptrs.begin(), ptrs.end());
	
	for(int i = 0; i < a_sz; i++){
		A[i] = ptrs[i];
	}
}
/*
template <typename T>
void ptr2sptr(vector <T> &A, vector < sptr <T> > &Ap) {
	Ap.resize(A.size());
	for(int i = 0; i < A.size(); i++){
		Ap[i] = &A[i];
	}
}
*/
#endif 
