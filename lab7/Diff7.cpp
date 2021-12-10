//Kishan Patel
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <iomanip>
#include <fstream>
#include <stack>
using namespace std;
template <typename T>
class matrix {
	// see handout from class or make your own
	public:
		void assign(int n_Ncols, int n_Nrows){
			Ncols = n_Ncols;
			Nrows = n_Nrows;

			buf = new T *[Ncols];
			for(int i = 0; i < Ncols; i++){
				buf[i] = new T[Nrows];
			}
		}
		matrix(){
			Ncols = 0;
			Nrows = 0;
		}
		~matrix() {
			for(int i = 0; i < Ncols; i++)
				delete [] buf[i];
			delete [] buf;
		}
		/*
		void assign(int n_Ncols, int n_Nrows){
			if(n_Nrows <= 0 || n_Ncols <= 0)
				buf = new T*[Nrows*Ncols];
			else
				buf = new T*[n_Nrows*n_Ncols];
		}*/
		T* data() const { return buf; } 
	
		int get_Nrows() const {
			return Nrows;
		}
		int get_Ncols() const {
			return Ncols;
		}
		T * operator[] (int i){
			return buf[i];
		}
	private:
		int Nrows, Ncols;
		T **buf;

};
class LCS {
  public:
	LCS();
	void text1_push_back(string in) { text1.push_back(in); }
    void text2_push_back(string in){ text2.push_back(in); }
	
	void compute_alignment();
	void report_difference();
	void print_alignment();
	
	int getlenght_text1() { return text1.size(); }
	int getlenght_text2() { return text2.size(); }
  private:
	// support functions
	vector <string> text1;
	vector <string> text2;
	string ex;
	string ey;
	matrix<int> cost;
	matrix<int> link;
	int m,n;

	const int VERT; 
	const int HORZ;
	const int DIAG;

	enum OP_T {
		OP_NULL = -1,
		OP_INS, OP_DEL, OP_SUB, OP_CHNG };

	struct step {
		step();
		step(int l, int k, OP_T d){
			i = l;
			j = k;
			op = d; 
		}
		void push(int,int);

		int count;
		int i, j;
		OP_T op;
	};

	//int DELcost = 1;
	//int INScost = 1;
	int DEL(string c) { return 1; }
	int INS(string c) { return 1; }



};
LCS::LCS() : VERT(1), HORZ(2), DIAG(4){
}

void LCS::compute_alignment(){
	ofstream file;
	file.open("test.txt");
	m = getlenght_text1()+1;
	//int m = text1.size() + 1; 
	//int n = text2.size() + 1;
	n = getlenght_text2()+1;
	//int longz;
	//if(m > n)
	//	longz = m;
	//else
	//	longz = n;
	cost.assign(m+1, n+1);
	link.assign(m+1, n+1);
	cost[0][0] = 0;
	link[0][0] = 0;

		for(int i = 1; i <= m; i++){
			cost[i][0] = cost[i-1][0] + 1;
			link[i][0] = VERT;
		}

		for(int j = 1; j <= n; j++){
			cost[0][j] = cost[0][j-1] + 1;
			link[0][j] = HORZ;
		}
		for(int i = 1; i < m; i++){
			for(int j = 1; j < n; j++){
				if(text1[i-1] == text2[j-1]){
					cost[i][j] = cost[i-1][j-1];
					link[i][j] = DIAG;
				}
				else
					cost[i][j] = INT_MAX;
	

				int inscost = cost[i][j-1] + 1; //INScost(ey[j]);
				if(inscost < cost[i][j]){
					cost[i][j] = inscost;
					link[i][j] = HORZ;
				}
				int delcost = cost[i-1][j] + 1;
				if(delcost < cost[i][j]){
					cost[i][j] = delcost;
					link[i][j] = VERT;
				}
			}
		}
	//cout << "m = " << m << "\n"
	//	 << "n = " << n << "\n";
	/*
		file << "alignment cost = " << cost[m-1][n-1] << "\n";
		file << " cost Matrix: \n";
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				file << setw(4) << right << cost[i][j];
			}
			file <<  endl;
		}
		file << " Link Matrix: \n";
		for (int i = 0 ; i < m; i++){
			for(int j = 0; j < n; j++){
				file << setw(4) << right << link[i][j];
			}	
			file << endl;
		}*/
}

//void LCS::print_alignment(){
void LCS::report_difference() {
	stack <int> alignment_x;
	stack <int> alignment_y;
	stack <int> op;
	vector <int> a_x, a_y, op2;

	int i = m-1, j = n-1, link_ij = 0;
	
	while((link_ij = link[i][j]) != 0){
		alignment_x.push(i);
		alignment_y.push(j);
		op.push(link_ij);
		//cout <<" inside\n";	
		if(link_ij == DIAG){
			i = i-1, j = j-1;
		} else if(link_ij == VERT) {
			
			i = i-1;
		
		} else { //link_ij == HORz
			j = j-1;
		}
	}
	//cout << "** ";
	
	while (!alignment_x.empty()){
		a_x.push_back( alignment_x.top());
		a_y.push_back(alignment_y.top());
		op2.push_back(op.top());

		alignment_x.pop();
		alignment_y.pop();
		op.pop();

	}
	//for(int k = 0; k < a_x.size(); k++){
	//	cout << "( " << a_x[k] << ", " << a_y[k] << ") " << op2[k] << endl;
	//}

	i = 0, j = 0;
	int insert = 0, deletion = 0;
	for(int k = 0; k < (int)op2.size(); k++){
		//cout << k << endl;
		if(op2[k] == DIAG){
			if(insert && deletion) {
				if(i != i-deletion+1) cout << i-deletion+1 << ",";
				cout << i << "c" << j-insert+1;
				if(j != j-insert+1) cout << "," << j;
				cout << endl;
			}
			//cout << "DIAG\n";
			for(int y = i - deletion+1 ; y <= i; y++){
				if(y == i-deletion+1 && !insert && deletion){
					if(i != i-deletion+1) cout << i-deletion+1 << ",";
					cout << i << "d" << j << endl;
				}
				//prition delete texts
				cout << "< " << text1[y-1] << endl;
			
			}
			if(insert && deletion) cout << "---" << endl;

			for(int x = j - insert+1 ; x <= j; x++){
				if(x == j-insert+1 && !deletion && insert){
					cout << i << "a" << j-insert+1;
					if(j != j-insert+1) cout << "," << j;
					cout << endl;
				}
				cout << "> " << text2[x-1] << endl;
			}
			
			deletion = 0;
			insert = 0;
			i = i+1, j = j+1;
			if(insert == 0 && deletion == 0) { continue; }
		}
		if(op2[k] == VERT){
			deletion++;

			i = i+1;
			//out << "VERT\n";
		}
		else {
			insert++;
			j = j+1;
			//cout << "insert\n";
		}
		
	}
	if(insert && deletion) {
		if(i != i-deletion+1) cout << i-deletion+1 << ",";
			cout << i << "c" << j-insert+1;
		if(j != j-insert+1) cout << "," << j;
		cout << endl;
	}

	for(int y = i - deletion+1 ; y <= i; y++){
		if(y == i-deletion+1 && !insert && deletion){
			if(i != i-deletion+1) cout << i-deletion+1 << ",";
				cout << i << "d" << j << endl;
			}
				//prition delete texts
		cout << "< " << text1[y-1] << endl;
			
	}
	if(insert && deletion) cout << "---" << endl;
	
	for(int x = j - insert+1 ; x <= j; x++){
		if(x == j-insert+1 && !deletion && insert){
			cout << i << "a" << j-insert+1;
			if(j != j-insert+1) cout << "," << j;
				cout << endl;
		}
		cout << "> " << text2[x-1] << endl;
	}

}

int main(int argc, char *argv[])
{
	// check two input files are specified on command line
	ifstream file1, file2; 
	if(argc != 3){
		cerr << "usage: file1 file2 \n";
		return -1;
	}
	file1.open(argv[1]);

	file2.open(argv[2]);

	string buf;
	LCS lcs;  // instantiate your "LCS based diff" object

	// read the text from file1 into the lcs.text1 buffer
	while(getline(file1,buf)){
		lcs.text1_push_back(buf);
	}
	while(getline(file2, buf)){
		lcs.text2_push_back(buf);
	}
	
	lcs.compute_alignment();
	//lcs.print_alignment();
	lcs.report_difference();
}
