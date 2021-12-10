
using namespace std;

#include "Support.h"
vector<pixel> set_pixel_list(ppm &img){
	vector<pixel> list;
	int x, y, wi, he;

	wi = img.get_Ncols();
	he = img.get_Nrows();
	
	vector<int> histogram(1 << 15, 0);
	int color;
	for(y = 0; y < he; y++){
		for(x = 0; x < wi; x++){
			RGB &ref = img[x][y];
			color = ((ref.r >> 3) << 10) | ((ref.g >> 3) << 5) | (ref.b >> 3);
			histogram[color]++;
			list.push_back(pixel(x, y));
		}
	}
/*
	for(y = 0; y < he; y += 2)
		for(x = 0; x < wi; x += 2){
			list.push_back(pixel(x, y));
		}
*/

	rnumgen RNG(0, histogram);
	for(int i = (int)list.size()-1; i > 0; --i){
		int perm_num = (RNG.rand() << 15) | (RNG.rand());
		swap(list[i], list[perm_num % (i+1)]);
	}

	return list;
}

void encode(ppm &img, const vector<pixel> &pix) {
	char c;
	int x, y, i_col, i_pix, i_bit, pisz;
	bool insert;

	i_col = 0;
	i_pix = 0;
	insert = false;
	pisz = pix.size();

	while ( insert == false){
	//while(cin.get(c)) {
		if(!cin.get(c)){
			c = ETX;
			insert = true;
			//break;
		}
		for(i_bit = 0; i_bit < 7; i_bit++){
		
			if(i_pix >= pisz){
				cout << "Error: pixel_list exhausted\n";
				return;
			}
			x = pix[i_pix].x;
			y = pix[i_pix].y;

			RGB &ref = img[x][y];

			switch(i_col){
				case 0: 
					ref.r &= 0xFE;
					ref.r |= ((c >> i_bit) & 0x1);
					break;
				case 1:
					ref.g &= 0xFE;
					ref.g |= ((c >> i_bit) & 0x1);
					break;
				case 2:
					ref.b &= 0xFE;
					ref.b |= ((c >> i_bit) & 0x1);

					break;
			}
			i_col++;
			if(i_col == 3)
				i_col = 0;

			i_pix++;
		}
	}

}

void decode(ppm &img, const vector<pixel> &pix) {
	char c = 0;
	int x, y, i_col, i_pix, i_bit, pisz;
	bool insert;

	i_col = 0;
	i_pix = 0;
	insert = false;
	pisz = pix.size();

	while ( insert == false){
		c = 0;
		for(i_bit = 0; i_bit < 7; i_bit++){
		
			if(i_pix >= pisz){
				cerr << "Error: pixel_list exhausted\n";
				exit(0);
			}
			x = pix[i_pix].x;
			y = pix[i_pix].y;

			RGB &ref = img[x][y];
		
			switch(i_col){
				case 0: 
					c |= ((ref.r & 0x01) << i_bit);
					break;
				case 1:
					c |= ((ref.g & 0x01) << i_bit);
					break;
				case 2:
					c |= ((ref.b & 0x01) << i_bit);
					break;
			}
			i_col++;
			if(i_col == 3)
				i_col = 0;

			i_pix++;
			
		}
		if(c == ETX){
			insert = true;
			break;
		}
		cout.put(c);
	}
}


int main(int argc, char *argv[]) {

	if(argc != 3){
		cerr << "usage: Crypto -encode|decode image.ppm " << endl;
		return 0;
	}

	ppm img;
	//MODE mode;
	vector<pixel> proc_pix;
	img.read(argv[2]);
	proc_pix = set_pixel_list(img);

	 //for (int i = 0; i < proc_pix.size(); i++) cout << proc_pix[i].x << " " << proc_pix[i].y << endl;
	
	string filename = argv[2];
	for(int i = 0; i < 4; i++){
		filename.pop_back();
	}
	filename += "_wmsg.ppm";
	if(strcmp("-encode", argv[1]) == 0 ){ 
		//mode = MODE_EN; else
		encode(img, proc_pix);
		img.write(filename.c_str());
		//img.write("inject_wmsg.ppm");
	}
	if(strcmp("-decode", argv[1]) == 0){
		decode(img, proc_pix);
		return 0;
}

	return 0;
	//encode(img,proc_pix);
	//img.write("inject_wmsg.ppm");


}
