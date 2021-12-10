//Kishan Patel
#include <limits>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <bits/stdc++.h> 
#include <sstream>
#include <stack>
using namespace std;

const int EARTH_RAD = 3982;

class city {
	public:
		
		string get_names() const {
			return name;
		}
		string get_types() const {
			return type;
		}
		int get_zones() const {
			return zone;
		}
		float get_latitudes() const {
			return lat;
		}
		float get_longitudes() const {
			return lon;
		}
		int get_populations() const {
			return popu;
		}
		friend istream & operator>>(istream &, city &);
		friend ostream & operator<<(ostream &, const city & );

	private:
		string name;
		string type;
		int zone;
		float lat, latra;
		float lon, lonra;
		int popu;

	
	
};

istream& operator>>(istream &fin, city &city ) {
	fin >> city.zone >> city.name >> city.type >> city.lat >> city.lon >> city.popu;
	city.latra = city.lat * (M_PI / 180);
	city.lonra = city.lon * (M_PI / 180);
	return fin;
}

ostream& operator<<(ostream &fout, const city &city ) {
	fout << left << setw(18) << city.name << left << setw(12) << city.type << left << setw(2) << city.zone << right << setw(10) << 
		city.popu << right << setw(8) << fixed << setprecision(2) << city.lat << right << setw(8) << fixed << setprecision(2) << city.lon << endl;
	return fout;

}

class travelcost{
	public:
		enum mode {
			NONE = -1,
			DISTANCE,
			TIME,
			GRAPHINFO
		};
	
		void City_graph_Proc(const vector<city> &);
		float &operator() (travelcost::mode, int, int);

	private:
		vector<float> table[2];
		
};
static float haversine ( float lon1, float lat1, float lon2, float lat2){
	float flat = (lat2 - lat1) * (M_PI / 180.0f);
	float flon = (lon2 - lon1) * (M_PI / 180.0f);
	lat1 = (lat1) * M_PI / 180.0f;
	lat2 = (lat2) * M_PI / 180.0f;
	float a = pow(sin(flat / 2), 2) + pow(sin(flon / 2), 2) * cos(lat1) * cos(lat2);
	float c = 2 * asin(sqrt(a));
	return EARTH_RAD * c;
}
				
void travelcost::City_graph_Proc(const vector<city> &city_graph){
	vector<float> &distance_table = table[DISTANCE];
	vector<float> &time_table = table[TIME];

	unsigned int gph_sz;
	unsigned int i, j;
	bool ig, jg;

	gph_sz = city_graph.size();
	distance_table.resize((gph_sz * (gph_sz + 1)) / 2, 0.0f);
	time_table.resize((gph_sz * (gph_sz + 1)) / 2, 0.0f);

	//Distance Table
	for( i = 1; i < gph_sz; i++){
		for(j = 0; j < i; j++){
			//compute distance 
			
			(*this)(DISTANCE, i, j) = haversine (
				city_graph[i].get_longitudes(), city_graph[i].get_latitudes(),
				city_graph[j].get_longitudes(), city_graph[j].get_latitudes()
			);
			(*this)(DISTANCE, i, j) = 25.0*round((*this)(DISTANCE, i, j)/25.0);
			table[travelcost::DISTANCE][i*(i+1)/2+j] = (*this)(DISTANCE, i, j);
			/*
			float distance = haversine (
				city_graph[i].get_longitudes(), city_graph[i].get_latitudes(),
				city_graph[j].get_longitudes(), city_graph[j].get_latitudes()
			);
			distance = 25.0*round(distance/25.0);
			table[travelcost::DISTANCE][i*(i+1)/2+j] = distance;
			*/
		}
	}

	for(i = 1; i < gph_sz; i++){
		for(j = 0; j < i; j++){
			ig = (city_graph[i].get_types() == "GATEWAY");
			jg = (city_graph[j].get_types() == "GATEWAY");
			float &time_ref = (*this)(TIME, i, j);
			float &dist_ref = (*this)(DISTANCE, i, j);

			if(!ig && !jg)
				time_ref = dist_ref / 65.0f;
			else
			if(ig && jg)
				time_ref = dist_ref / 520.0f;
			else
				time_ref = dist_ref / 520.0f;
		}
	}
}

float& travelcost::operator()(travelcost::mode m, int i, int j){
	return(i < j)
		? table[m][((j * (j +1)) / 2 ) + i]
		: table[m][((i * ( i + 1)) / 2) + j];
}
void read_cityinfo(vector <city> &city_vector ) {
	ifstream fin;
	string line;
	city temp_city;

	city_vector.clear();
	fin.open("city_list.txt");

	while(getline(fin, line)){
		if(line.length() == 0 || line[0] == '#' ){
			continue;
		}
		istringstream iss(line);
		iss >> temp_city;

		city_vector.push_back(temp_city);
	}
	fin.close();
		


}

void write_cityinfo(const vector<city> &city_vector){
	ofstream fout("city_info.txt");
	unsigned int i, size;

	size = city_vector.size();
	fout << "CITY INFO (N=" << size << "):" << endl << endl; 
	for(i = 0; i < size; i++){
		fout << setw(3) << i << right << " " << city_vector[i];
	}
	
}
void write_traveldistance( const vector<city> &CT_vector, travelcost tc){
	ofstream fout;
	fout.open("city_distancetable1.txt");
	unsigned int i, j, size;
	size = CT_vector.size();
	for(i = 1; i < size; i++){
		for(j = 0; j < i; j++)
		fout << CT_vector[i].get_names() << " to " <<  CT_vector[j].get_names() << " " << setw(8) << fixed << setprecision(1) << tc(travelcost::DISTANCE, i, j) << endl;
	}
	fout.close();
}

void write_time( const vector<city> &CT_vector, travelcost tc){
	//ofstream fout("city_distancetable1.txt");
	unsigned int i, j, size;
	size = CT_vector.size();
	for(i = 1; i < size; i++){
		for(j = 0; j < i; j++)
		cout << CT_vector[i].get_names() << " to " <<  CT_vector[j].get_names() << " " << setw(8) << fixed << setprecision(1) << tc(travelcost::TIME, i, j) << endl;
	}
}

void write_city_graph( const vector<city> &CT_vector, travelcost &tc, vector< vector<int> >&graph){
	ofstream out;
	out.open("city_graph1.txt");
	unsigned int i, j, size, jsize, cid;
	size = graph.size();

	out << "CITY GRAPH:\n";

	for(i = 0; i < size; i++){
		jsize = graph[i].size();
		out << "\n"; 
		out << CT_vector[i].get_names() << endl;
		for( j = 0; j < jsize; j++){
			cid = graph[i][j];
			out << setw(6) << right << cid << " " << setw(18) << left << CT_vector[cid].get_names() << " "
				<< fixed << setprecision(1) 
				<< setw(7) << right << tc(travelcost::DISTANCE, i, cid) << " miles "
				<< setw(5) << right << tc(travelcost::TIME, i, cid) << " hours\n";
		
		}
	}
	out.close();
}

void create_citygraph(vector<city> &CT_vector, travelcost &tc, vector< vector<int> > &graph) {
	size_t graph_sz, zone_count;
	unsigned int i, j , k;
	travelcost::mode distM = travelcost::DISTANCE;
	graph_sz = CT_vector.size();

	//The numbers of zones
	zone_count = 0;

	for(i = 0, j = 0; i < graph_sz; i++){
		if(CT_vector[i].get_zones() != j){
			zone_count++;
			j = CT_vector[i].get_zones();
		}
	}
	zone_count++;
	
	//setuping the graph
	graph.clear();
	graph.resize(graph_sz, vector<int> () );

	for(i = 0; i < graph_sz; i++){
		if(CT_vector[i].get_types() == "REGIONAL") {
			k = -1; //gateway index

			for(j = 0; j < graph_sz; j++){
				if(CT_vector[j].get_types() == "GATEWAY" && CT_vector[i].get_zones() == CT_vector[j].get_zones() &&
						(k == -1 || tc(distM, i, j) < tc(distM, i, k)) 
					)
					k = j;
			}
			
			for(j = 0; j < graph_sz; j++){
				if(i == j)
					continue;
				if	( CT_vector[j].get_types() == "REGIONAL" &&
						CT_vector[i].get_zones() == CT_vector[j].get_zones()
					){
						graph[i].push_back(j);
						graph[j].push_back(i);
					}
				if( j == k){
					graph[i].push_back(j);
					graph[j].push_back(i);
				}

			}
		}
		else{
			//adding all gateway cities in the same zone
			for( j = 0; j < graph_sz; j++){
				if(i == j)
					continue;
				if( CT_vector[j].get_types() == "GATEWAY" && 
						CT_vector[i].get_zones() == CT_vector[j].get_zones()
				){
					graph[i].push_back(j);
					graph[j].push_back(i);
				}
			}

			//adding all adjacent gateway in other zones of <= 6000 miles.
			vector<int> zones_short (zone_count, -1);

			for(j = 0; j < graph_sz; j++){
				if(CT_vector[j].get_types() != "GATEWAY")
					continue;
				if(CT_vector[i].get_zones() == CT_vector[j].get_zones() )
					continue;
				k = CT_vector[j].get_zones();
				if(zones_short[k] == -1 || tc(travelcost::DISTANCE, i, j) < tc(travelcost::DISTANCE, i, zones_short[k]) )
					zones_short[k] = j;

			}
			for(j = 0; j < zone_count; j++){
				if(j == CT_vector[i].get_zones())
					continue;
				if(zones_short[j] == -1)
					continue;

				if(tc(travelcost::DISTANCE, i, zones_short[j]) <= 6000.0f){
					graph[i].push_back(zones_short[j]);
					graph[zones_short[j]].push_back(i);
				}
			}
		}
	}
	for(j = 0; j < graph_sz; j++){
		sort(graph[j].begin(), graph[j].end());
		graph[j].erase(unique(graph[j].begin(), graph[j].end()), graph[j].end());
	}
	
}
enum Dijkstra_color {
	WHITE,
	BLACK
};

void dijkstra_route(int source, int sink, vector<city> &citys, int mode, vector<vector<int> > &graph, travelcost &t) { 
	vector<Dijkstra_color> vcolor;
	vector<float> vdist;
	vector<float> vtime;
	vector<int> vlink;
	vector<float> wij_list (citys.size(), 0);
	vector<float> wit_list ( citys.size(), 0);
	float wij,wit;
	vcolor.assign(citys.size(), WHITE); 
	
	vdist.assign(citys.size(), numeric_limits<float>::max());
	vdist[source] = 0;

	vtime.assign(citys.size(), numeric_limits<float>::max());
	vtime[source] = 0;
	
	vlink.assign(citys.size(), -1);
	vlink[source] = source;

	while(1){
		int next_i = -1;
		float mindist = numeric_limits<float>::max();
		for(int i = 0; i < (int)vcolor.size(); i++){
			if(vcolor[i] == WHITE && mindist > vdist[i]) {
				next_i = i;
				mindist = vdist[i];
			}
		}
		int i = next_i;
		if(i == -1)
			return;

		vcolor[i] = BLACK;

		if(i == sink )
			break;
		for(int k = 0; k < (int)graph[i].size(); k++){
			int j = graph[i][k];
			if(mode == 0){
				wij = t(travelcost::DISTANCE, i, j);
				wit = t(travelcost::TIME, i, j);
			}
			if(mode == 1){
				wij = t(travelcost::TIME, i, j);
				wit = t(travelcost::DISTANCE, i, j);
			}
			if(vcolor[j] == WHITE){
				//cout << j << endl;
				if(vdist[j] > vdist[i] + wij){
					vdist[j] = vdist[i] + wij;
					vtime[j] = vtime[i]+ wit;
					wij_list[j] = wij;
					wit_list[j] = wit;
					vlink[j] = i;

				}
			}
		}
	}

	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	if(vdist[sink] == INT_MAX) {
		cout << "No path from " << citys[source].get_names()
			<< " to " << citys[source].get_names() << "\n";
		return;
	}
	stack<int> S;

	for(int i = sink; i != source; i = vlink[i] )
		S.push(i);
	S.push(source);

	if(mode == 0){
		while(!S.empty() ) {
			int i = S.top();
			S.pop();
		
			cout << right  
				<< setw(7) << fixed << setprecision(1) << vdist[i] << " miles " 
				<< setw(5) << fixed << setprecision(1) << vtime[i] << " hours : " 
				<< setw(2) << i << " " 
				<< setw(18) << left << citys[i].get_names();
				if(wij_list[i] != 0){
					cout << right 
						<< setw(7) << fixed << wij_list[i] << " miles "   
						<< setw(5) << fixed << wit_list[i] << " hours" 
						<< endl; 
				}
				else{
					cout << endl;
				}
		}
	}
	if(mode == 1){
		while(!S.empty() ) {
			int i = S.top();
			S.pop();
			cout << right  
				<< setw(7) << fixed << setprecision(1) << vtime[i] << " miles " 
				<< setw(5) << fixed << setprecision(1) << vdist[i] << " hours : " 
				<< setw(2) << i << " " 
				<< setw(18) << left << citys[i].get_names();
				if(wij_list[i] != 0){
					cout << right 
						<< setw(7) << fixed << wit_list[i] << " miles "   
						<< setw(5) << fixed << wij_list[i] << " hours" 
						<< endl; 
				}
			else{
					cout << endl;
				}
		}
	}
		
}
void dijkstra_route(const string city1, const string city2,
					vector<city> &citys, int mode, vector< vector<int> > &graph, travelcost &t){
	int source,sink;
	for(int i=0 ; i < (int) citys.size(); i++){
		if(citys[i].get_names() == city1) source = i;
		if(citys[i].get_names() == city2) sink = i;
	}
	dijkstra_route(source,sink, citys,mode, graph,t); 
	//diskstra_route(source, sink, citys, mode, graph, t);
}
int main(int argc, char *argv[])
{
	//option decoding
	if(argc != 2 ){
		cout << "Usage: ./Citysim -distance|time " << endl;
		return(0);
	}
//Kishan Patel
#include <limits>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <bits/stdc++.h> 
#include <sstream>
#include <stack>
using namespace std;

const int EARTH_RAD = 3982;

class city {
	public:
		
		string get_names() const {
			return name;
		}
		string get_types() const {
			return type;
		}
		int get_zones() const {
			return zone;
		}
		float get_latitudes() const {
			return lat;
		}
		float get_longitudes() const {
			return lon;
		}
		int get_populations() const {
			return popu;
		}
		friend istream & operator>>(istream &, city &);
		friend ostream & operator<<(ostream &, const city & );

	private:
		string name;
		string type;
		int zone;
		float lat, latra;
		float lon, lonra;
		int popu;

	
	
};

istream& operator>>(istream &fin, city &city ) {
	fin >> city.zone >> city.name >> city.type >> city.lat >> city.lon >> city.popu;
	city.latra = city.lat * (M_PI / 180);
	city.lonra = city.lon * (M_PI / 180);
	return fin;
}

ostream& operator<<(ostream &fout, const city &city ) {
	fout << left << setw(18) << city.name << left << setw(12) << city.type << left << setw(2) << city.zone << right << setw(10) << 
		city.popu << right << setw(8) << fixed << setprecision(2) << city.lat << right << setw(8) << fixed << setprecision(2) << city.lon << endl;
	return fout;

}

class travelcost{
	public:
		enum mode {
			NONE = -1,
			DISTANCE,
			TIME,
			GRAPHINFO
		};
	
		void City_graph_Proc(const vector<city> &);
		float &operator() (travelcost::mode, int, int);

	private:
		vector<float> table[2];
		
};
static float haversine ( float lon1, float lat1, float lon2, float lat2){
	float flat = (lat2 - lat1) * (M_PI / 180.0f);
	float flon = (lon2 - lon1) * (M_PI / 180.0f);
	lat1 = (lat1) * M_PI / 180.0f;
	lat2 = (lat2) * M_PI / 180.0f;
	float a = pow(sin(flat / 2), 2) + pow(sin(flon / 2), 2) * cos(lat1) * cos(lat2);
	float c = 2 * asin(sqrt(a));
	return EARTH_RAD * c;
}
				
void travelcost::City_graph_Proc(const vector<city> &city_graph){
	vector<float> &distance_table = table[DISTANCE];
	vector<float> &time_table = table[TIME];

	unsigned int gph_sz;
	unsigned int i, j;
	bool ig, jg;

	gph_sz = city_graph.size();
	distance_table.resize((gph_sz * (gph_sz + 1)) / 2, 0.0f);
	time_table.resize((gph_sz * (gph_sz + 1)) / 2, 0.0f);

	//Distance Table
	for( i = 1; i < gph_sz; i++){
		for(j = 0; j < i; j++){
			//compute distance 
			
			(*this)(DISTANCE, i, j) = haversine (
				city_graph[i].get_longitudes(), city_graph[i].get_latitudes(),
				city_graph[j].get_longitudes(), city_graph[j].get_latitudes()
			);
			(*this)(DISTANCE, i, j) = 25.0*round((*this)(DISTANCE, i, j)/25.0);
			table[travelcost::DISTANCE][i*(i+1)/2+j] = (*this)(DISTANCE, i, j);
			/*
			float distance = haversine (
				city_graph[i].get_longitudes(), city_graph[i].get_latitudes(),
				city_graph[j].get_longitudes(), city_graph[j].get_latitudes()
			);
			distance = 25.0*round(distance/25.0);
			table[travelcost::DISTANCE][i*(i+1)/2+j] = distance;
			*/
		}
	}

	for(i = 1; i < gph_sz; i++){
		for(j = 0; j < i; j++){
			ig = (city_graph[i].get_types() == "GATEWAY");
			jg = (city_graph[j].get_types() == "GATEWAY");
			float &time_ref = (*this)(TIME, i, j);
			float &dist_ref = (*this)(DISTANCE, i, j);

			if(!ig && !jg)
				time_ref = dist_ref / 65.0f;
			else
			if(ig && jg)
				time_ref = dist_ref / 520.0f;
			else
				time_ref = dist_ref / 520.0f;
		}
	}
}

float& travelcost::operator()(travelcost::mode m, int i, int j){
	return(i < j)
		? table[m][((j * (j +1)) / 2 ) + i]
		: table[m][((i * ( i + 1)) / 2) + j];
}
void read_cityinfo(vector <city> &city_vector ) {
	ifstream fin;
	string line;
	city temp_city;

	city_vector.clear();
	fin.open("city_list.txt");

	while(getline(fin, line)){
		if(line.length() == 0 || line[0] == '#' ){
			continue;
		}
		istringstream iss(line);
		iss >> temp_city;

		city_vector.push_back(temp_city);
	}
	fin.close();
		


}

void write_cityinfo(const vector<city> &city_vector){
	ofstream fout("city_info.txt");
	unsigned int i, size;

	size = city_vector.size();
	fout << "CITY INFO (N=" << size << "):" << endl << endl; 
	for(i = 0; i < size; i++){
		fout << setw(3) << i << right << " " << city_vector[i];
	}
	
}
void write_traveldistance( const vector<city> &CT_vector, travelcost tc){
	ofstream fout;
	fout.open("city_distancetable1.txt");
	unsigned int i, j, size;
	size = CT_vector.size();
	for(i = 1; i < size; i++){
		for(j = 0; j < i; j++)
		fout << CT_vector[i].get_names() << " to " <<  CT_vector[j].get_names() << " " << setw(8) << fixed << setprecision(1) << tc(travelcost::DISTANCE, i, j) << endl;
	}
	fout.close();
}

void write_time( const vector<city> &CT_vector, travelcost tc){
	//ofstream fout("city_distancetable1.txt");
	unsigned int i, j, size;
	size = CT_vector.size();
	for(i = 1; i < size; i++){
		for(j = 0; j < i; j++)
		cout << CT_vector[i].get_names() << " to " <<  CT_vector[j].get_names() << " " << setw(8) << fixed << setprecision(1) << tc(travelcost::TIME, i, j) << endl;
	}
}

void write_city_graph( const vector<city> &CT_vector, travelcost &tc, vector< vector<int> >&graph){
	ofstream out;
	out.open("city_graph1.txt");
	unsigned int i, j, size, jsize, cid;
	size = graph.size();

	out << "CITY GRAPH:\n";

	for(i = 0; i < size; i++){
		jsize = graph[i].size();
		out << "\n"; 
		out << CT_vector[i].get_names() << endl;
		for( j = 0; j < jsize; j++){
			cid = graph[i][j];
			out << setw(6) << right << cid << " " << setw(18) << left << CT_vector[cid].get_names() << " "
				<< fixed << setprecision(1) 
				<< setw(7) << right << tc(travelcost::DISTANCE, i, cid) << " miles "
				<< setw(5) << right << tc(travelcost::TIME, i, cid) << " hours\n";
		
		}
	}
	out.close();
}

void create_citygraph(vector<city> &CT_vector, travelcost &tc, vector< vector<int> > &graph) {
	size_t graph_sz, zone_count;
	unsigned int i, j , k;
	travelcost::mode distM = travelcost::DISTANCE;
	graph_sz = CT_vector.size();

	//The numbers of zones
	zone_count = 0;

	for(i = 0, j = 0; i < graph_sz; i++){
		if(CT_vector[i].get_zones() != j){
			zone_count++;
			j = CT_vector[i].get_zones();
		}
	}
	zone_count++;
	
	//setuping the graph
	graph.clear();
	graph.resize(graph_sz, vector<int> () );

	for(i = 0; i < graph_sz; i++){
		if(CT_vector[i].get_types() == "REGIONAL") {
			k = -1; //gateway index

			for(j = 0; j < graph_sz; j++){
				if(CT_vector[j].get_types() == "GATEWAY" && CT_vector[i].get_zones() == CT_vector[j].get_zones() &&
						(k == -1 || tc(distM, i, j) < tc(distM, i, k)) 
					)
					k = j;
			}
			
			for(j = 0; j < graph_sz; j++){
				if(i == j)
					continue;
				if	( CT_vector[j].get_types() == "REGIONAL" &&
						CT_vector[i].get_zones() == CT_vector[j].get_zones()
					){
						graph[i].push_back(j);
						graph[j].push_back(i);
					}
				if( j == k){
					graph[i].push_back(j);
					graph[j].push_back(i);
				}

			}
		}
		else{
			//adding all gateway cities in the same zone
			for( j = 0; j < graph_sz; j++){
				if(i == j)
					continue;
				if( CT_vector[j].get_types() == "GATEWAY" && 
						CT_vector[i].get_zones() == CT_vector[j].get_zones()
				){
					graph[i].push_back(j);
					graph[j].push_back(i);
				}
			}

			//adding all adjacent gateway in other zones of <= 6000 miles.
			vector<int> zones_short (zone_count, -1);

			for(j = 0; j < graph_sz; j++){
				if(CT_vector[j].get_types() != "GATEWAY")
					continue;
				if(CT_vector[i].get_zones() == CT_vector[j].get_zones() )
					continue;
				k = CT_vector[j].get_zones();
				if(zones_short[k] == -1 || tc(travelcost::DISTANCE, i, j) < tc(travelcost::DISTANCE, i, zones_short[k]) )
					zones_short[k] = j;

			}
			for(j = 0; j < zone_count; j++){
				if(j == CT_vector[i].get_zones())
					continue;
				if(zones_short[j] == -1)
					continue;

				if(tc(travelcost::DISTANCE, i, zones_short[j]) <= 6000.0f){
					graph[i].push_back(zones_short[j]);
					graph[zones_short[j]].push_back(i);
				}
			}
		}
	}
	for(j = 0; j < graph_sz; j++){
		sort(graph[j].begin(), graph[j].end());
		graph[j].erase(unique(graph[j].begin(), graph[j].end()), graph[j].end());
	}
	
}
enum Dijkstra_color {
	WHITE,
	BLACK
};

void dijkstra_route(int source, int sink, vector<city> &citys, int mode, vector<vector<int> > &graph, travelcost &t) { 
	vector<Dijkstra_color> vcolor;
	vector<float> vdist;
	vector<float> vtime;
	vector<int> vlink;
	vector<float> wij_list (citys.size(), 0);
	vector<float> wit_list ( citys.size(), 0);
	float wij,wit;
	vcolor.assign(citys.size(), WHITE); 
	
	vdist.assign(citys.size(), numeric_limits<float>::max());
	vdist[source] = 0;

	vtime.assign(citys.size(), numeric_limits<float>::max());
	vtime[source] = 0;
	
	vlink.assign(citys.size(), -1);
	vlink[source] = source;

	while(1){
		int next_i = -1;
		float mindist = numeric_limits<float>::max();
		for(int i = 0; i < (int)vcolor.size(); i++){
			if(vcolor[i] == WHITE && mindist > vdist[i]) {
				next_i = i;
				mindist = vdist[i];
			}
		}
		int i = next_i;
		if(i == -1)
			return;

		vcolor[i] = BLACK;

		if(i == sink )
			break;
		for(int k = 0; k < (int)graph[i].size(); k++){
			int j = graph[i][k];
			if(mode == 0){
				wij = t(travelcost::DISTANCE, i, j);
				wit = t(travelcost::TIME, i, j);
			}
			if(mode == 1){
				wij = t(travelcost::TIME, i, j);
				wit = t(travelcost::DISTANCE, i, j);
			}
			if(vcolor[j] == WHITE){
				//cout << j << endl;
				if(vdist[j] > vdist[i] + wij){
					vdist[j] = vdist[i] + wij;
					vtime[j] = vtime[i]+ wit;
					wij_list[j] = wij;
					wit_list[j] = wit;
					vlink[j] = i;

				}
			}
		}
	}

	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	if(vdist[sink] == INT_MAX) {
		cout << "No path from " << citys[source].get_names()
			<< " to " << citys[source].get_names() << "\n";
		return;
	}
	stack<int> S;

	for(int i = sink; i != source; i = vlink[i] )
		S.push(i);
	S.push(source);

	if(mode == 0){
		while(!S.empty() ) {
			int i = S.top();
			S.pop();
		
			cout << right  
				<< setw(7) << fixed << setprecision(1) << vdist[i] << " miles " 
				<< setw(5) << fixed << setprecision(1) << vtime[i] << " hours : " 
				<< setw(2) << i << " " 
				<< setw(18) << left << citys[i].get_names();
				if(wij_list[i] != 0){
					cout << right 
						<< setw(7) << fixed << wij_list[i] << " miles "   
						<< setw(5) << fixed << wit_list[i] << " hours" 
						<< endl; 
				}
				else{
					cout << endl;
				}
		}
	}
	if(mode == 1){
		while(!S.empty() ) {
			int i = S.top();
			S.pop();
			cout << right  
				<< setw(7) << fixed << setprecision(1) << vtime[i] << " miles " 
				<< setw(5) << fixed << setprecision(1) << vdist[i] << " hours : " 
				<< setw(2) << i << " " 
				<< setw(18) << left << citys[i].get_names();
				if(wij_list[i] != 0){
					cout << right 
						<< setw(7) << fixed << wit_list[i] << " miles "   
						<< setw(5) << fixed << wij_list[i] << " hours" 
						<< endl; 
				}
			else{
					cout << endl;
				}
		}
	}
		
}
void dijkstra_route(const string city1, const string city2,
					vector<city> &citys, int mode, vector< vector<int> > &graph, travelcost &t){
	int source,sink;
	for(int i=0 ; i < (int) citys.size(); i++){
		if(citys[i].get_names() == city1) source = i;
		if(citys[i].get_names() == city2) sink = i;
	}
	dijkstra_route(source,sink, citys,mode, graph,t); 
	//diskstra_route(source, sink, citys, mode, graph, t);
}
int main(int argc, char *argv[])
{
	//option decoding
	if(argc != 2 ){
		cout << "Usage: ./Citysim -distance|time " << endl;
		return(0);
	}
	//object declarations
	vector<city> citys;
	vector< vector<int> > graph;

	read_cityinfo(citys);
	//write_cityinfo(citys);

	//set up travelcosts
	travelcost tc;
	tc.City_graph_Proc(citys);
//	write_traveldistance(citys, tc);
//	write_traveltime(citys, tc);

	create_citygraph(citys, tc, graph);
	//write_city_graph(citys, tc, graph);
	
	string tmp1, city1, city2;
	if(strcmp(argv[1], "-distance") == 0 ){
		cout << "Enter> "  ;
		while(getline(cin,tmp1)){
			istringstream iss(tmp1);
			iss >> city1;
			iss >> city2;
			dijkstra_route(city1, city2, citys, 0, graph, tc);
			cout << endl;
			cout << "Enter> ";
		}
	}
	//cout << endl;

	if(strcmp(argv[1], "-time") == 0 ){
		cout << "Enter> "  ;
		while(getline(cin,tmp1)){
			istringstream iss(tmp1);
			iss >> city1;
			iss >> city2;
			dijkstra_route(city1, city2, citys, 1, graph, tc);
			cout << endl;
			cout << "Enter> ";
		}
	}
	cout << endl;
}
	//object declarations
	vector<city> citys;
	vector< vector<int> > graph;

	read_cityinfo(citys);
	//write_cityinfo(citys);

	//set up travelcosts
	travelcost tc;
	tc.City_graph_Proc(citys);
//	write_traveldistance(citys, tc);
//	write_traveltime(citys, tc);

	create_citygraph(citys, tc, graph);
	//write_city_graph(citys, tc, graph);
	
	string tmp1, city1, city2;
	if(strcmp(argv[1], "-distance") == 0 ){
		cout << "Enter> "  ;
		while(getline(cin,tmp1)){
			istringstream iss(tmp1);
			iss >> city1;
			iss >> city2;
			dijkstra_route(city1, city2, citys, 0, graph, tc);
			cout << endl;
			cout << "Enter> ";
		}
	}
	//cout << endl;

	if(strcmp(argv[1], "-time") == 0 ){
		cout << "Enter> "  ;
		while(getline(cin,tmp1)){
			istringstream iss(tmp1);
			iss >> city1;
			iss >> city2;
			dijkstra_route(city1, city2, citys, 1, graph, tc);
			cout << endl;
			cout << "Enter> ";
		}
	}
	cout << endl;
}
