//Kishan Patel
#include  "Support.h"
using namespace std;

const char ETX = 0x3;

pixel::pixel(int _x, int _y){
	x = _x;
	y = _y;
}

RGB::RGB(uchar _r, uchar _g, uchar _b){
		r = _r;
		g = _g;
		b = _b;

}

ppm::ppm(){
	pixels = NULL;
}

void ppm::read(const char* fname) {
	ifstream f;
	string p6;
	int depth;
	int w, h, x, y;

	f.open(fname);

	if(!f.is_open()){
		cout << "Error: cannot open " <<  fname <<  " for reading\n";
		exit(0);
	}

	f >> p6;
	
	if(p6 != "P6" ){
		cout << "Erro: magicid not P6\n";
		exit(0);
	}

	if(!(f >> w >> h >> depth)){
		cout << "Error: invaild width, height, or maxvalue\n";
		exit(0);
	}

	if(depth != 255){
		cerr << "Error: maxvalue " << depth << " not support\n" ;
		exit(0);
	}

	//new line
	f.get();

	new_image(w, h);

	for(y = 0 ; y < h; y++){
		for(x = 0; x < w; x++){
			RGB &ref = (*pixels)[x][y];
			
			ref.r = f.get();
			ref.g = f.get();
			ref.b = f.get();

			//cout << "In for reading\n";
		}

	}
	f.close();
}

void ppm::write(const char* fname) {
	ofstream op;
	int x, y;
	
	op.open(fname);

	op << "P6\n" << get_Ncols() << " " << get_Nrows() << "\n255\n";

	for(y=0; y < get_Nrows(); y++){
		for(x=0; x < get_Ncols(); x++){
			RGB &ref = (*pixels)[x][y];
			op << ref.r << ref.g << ref.b;
		}
	}
	op.close();


}

int ppm::get_Ncols() const {
	if(pixels != NULL){
		return pixels->get_Ncols();
	}
	return 0;
}

int ppm::get_Nrows() const {
	if(pixels != NULL){
		return pixels->get_Nrows();
	}
	return 0 ;
}

RGB * ppm::operator[](int r) {
	return (*pixels)[r];
}

void ppm::new_image(int wi, int he){
	if(pixels != NULL)
		delete pixels;

	pixels = new matrix<RGB>(wi, he);
}

rnumgen::rnumgen(int seedvalue, vector<int> &v){
	srand(seedvalue);
	F.resize(v.size());
	partial_sum(v.begin(), v.end(), F.begin());

	transform(
			F.begin(),
			F.end(),
			F.begin(),
			bind2nd(divides<float>(), F.back())
	);
}
int rnumgen::rand() {
	const double randmax = RAND_MAX + 1.0;
	const double p = (double) std::rand() / randmax;

	return upper_bound(F.begin(), F.end(), p) - F.begin();
}
