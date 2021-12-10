#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string.h>

#include <stddef.h>

typedef unsigned char uchar;
extern const char ETX;

template <typename T>
class matrix { 

	public:
		matrix(int n_Ncols, int n_Nrows) {
			Ncols = n_Ncols;
			Nrows = n_Nrows;

			buf = new T *[Ncols];
			for(int i = 0; i < Ncols; i++){
				buf[i] = new T[Nrows];
			}
		}
		
		~matrix() {
			for(int i = 0; i < Ncols; i++)
				delete [] buf[i];
			delete [] buf;
			
		}
		
		void assign(int n_Ncols, int n_Nrows){
			if(n_Nrows <= 0 || n_Ncols <= 0)
				buf = new T [Nrows*Ncols];
			else
				buf = new T [n_Nrows*n_Ncols];
		}

		T* data() const { return buf; }
		
		int get_Nrows() const { 
			return Nrows;
		}
		int get_Ncols() const {
			return Ncols;
		}

		//overloaded operator 
		T * operator[] (int i){ 
			return buf[i]; 
		}
	private:
		int Nrows, Ncols;
		T **buf;
		
};

struct pixel { 
	pixel(int = 0, int = 0); 
	int x, y;
};

struct RGB { 
	RGB(uchar = 0, uchar = 0, uchar = 0);
	uchar r, g, b;
};

class ppm { 
	public:
		ppm();
		void read(const char*);
		void write(const char*);
		int get_Nrows() const;
		int get_Ncols() const;
		RGB * operator[] (int i);
	private:
		matrix<RGB> *pixels;
		void new_image(int, int);
};

class rnumgen{
	public:
		rnumgen(int, std::vector<int> & );
		int rand();
	private:
		std::vector<float> F;
};
#endif
