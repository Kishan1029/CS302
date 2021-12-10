#ifndef SLIST_H
#define SLIST_H

// include header file(s) needed
#include <list>
#include <stdio.h>
#include <cstring>
// template <typename T>
template <class T>
class slist {
  private:
    struct node {
		node() { data = T(); next = NULL; }
	// add node(const T &key) { write this }
		node(const T &key) { next = NULL; data = key; } 
	 // add overloaded operator< code
		bool operator<(const node &d) const{
			return data < d.data;
		}
		T data;
		node *next;
	
    };

   // add class sptr { write this for node data }
	class sptr{
		public: 
				sptr(node * _ptr = NULL) { ptr = _ptr; }
				bool operator< (const sptr &rhs) const{
					return *ptr < *rhs.ptr;
				}
				operator node * () const { return ptr; }
		private:
				node *ptr;
	};
  public:
	class iterator {
	  public:
	    iterator() { p = NULL; }
	    T & operator*() { return p->data; }
	    iterator & operator++() { p = p->next; return *this; }
	    bool operator!=(const iterator & rhs) const { return p != rhs.p; }

	  private:
	    iterator(node *n_p) { p = n_p; }
	    node *p;

	  friend class slist<T>;
	};

  public:
    slist();
	~slist();
    void push_back(const T &);
	void sort(const string &);

	iterator begin() { return iterator(head->next); }
	iterator end() { return iterator(NULL); }
//	int N = 0;
  private:
	node *head;
	node *tail;
	//int N = 0;
};

template <typename T>
slist<T>::slist() {
  head = new node();
  tail = head;
}

template <typename T>
slist<T>::~slist() {
  while (head->next != NULL) {
    node *p = head->next;
    head->next = p->next;
    delete p;
  }
  delete head;

  head = NULL;
  tail = NULL;
}

template <typename T>
void slist<T>::push_back(const T &din) {
  tail->next = new node(din);
  tail = tail->next;
}
template <typename T>
void slist<T>::sort(const string &algname) {
  // determine number of list elements
	 
	int lsz;
	vector<sptr> Ap;
	node* p;
  // set up smart pointer array called Ap
	for(p = head; p->next != NULL; p = p->next ){
		Ap.push_back(sptr(p->next));
	}
	lsz = Ap.size();
  // if quicksort, apply std::sort(...)
	if(algname == "-quicksort"){
		std::sort(Ap.begin(), Ap.end());
	}
	if(algname == "-mergesort"){
		std::stable_sort(Ap.begin(), Ap.end());
	}
  // if mergesort, apply std::stable_sort(...)
  // use sorted Ap array to relink list
	p = head;
	for(int i = 0; i < lsz; i++){
		p->next = Ap[i];
		p = p->next;
	}
	p->next = NULL;
}

#endif // SLIST_H
