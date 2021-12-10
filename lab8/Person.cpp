//#include  WHAT'S NEEDED
using namespace std;

#include "Person.h"
string type2str(type_enum t){
	if(t == FACULTY) return "Faculty";
	else if(t == ASST_PROF) return "Assistant Professor";
	else if(t == ASSOC_PROF) return "Associate Professor";
	else if(t == FULL_PROF) return "Full Professor";
	else if(t == STUDENT) return "Student";
	else if(t == FRESHMAN) return "Freshman";
	else if(t == SOPHOMORE) return "Sophomore";
	else if(t == JUNIOR) return "Junior";
	else if(t == SENIOR) return "Senior";
	else return "Unknown";
}

//PERSON CLASS MEMBER FUNCTION IMPLEMENTATION
person::person(){
	name = "";
	type = UNKNOWN;
}
person::person(const string &n, type_enum t){
	name = n;
	type = t;
}
string & person::get_name(){
	return name;
}
type_enum & person::get_type(){
	return type;
}
bool person::operator<(const person &rhs){
	bool a, b;
	a = ( type >= STUDENT);
	b = (rhs.type >= STUDENT);
	if((a && b) || (!a && !b))
		return (name < rhs.name);
	else
		if( a && !b)
			return false;
		else
			if(!a && b)
				return true;

}

ostream &operator<<(ostream &os, person &p){
	p.print_person_info(os);
	p.print_course_info(os);
	return os;
}

//FACULTY CLASS MEMBER FUNCTION IMPLEMENTATION
faculty::faculty(){
	name = "";
	type = UNKNOWN;
}

faculty::faculty(const string &n, type_enum t){
	name = n;
	type = t;
}
void faculty::add_course(const string &n){
	courses.insert(n);
}
bool faculty::operator<(const faculty &rhs){
	if(type!= rhs.type)
		return type < rhs.type;
	else
		return name < rhs.name;
}
void faculty::print_person_info(ostream& os ) {
	os << right << setw(12) << "Name: " << "Dr. " << get_name() << endl;
	os << right << setw(12) << "Category: " << type2str(get_type()) << endl;
} 
void faculty::print_course_info(ostream& os) {
	multiset<string>:: iterator it;
	for(it = courses.begin(); it != courses.end(); ++it){
		os << right << setw(12) << "Course: " << *it << endl;
	}
}

//STUDENT CLASS MEMBER FUNCTION IMPLEMENTATION
student::student(){
	name = "";
	type = UNKNOWN;
}
student::student(const string &n, type_enum t){
	name = n;
	type = t;
}
void student::add_course(const string &name, float fl){
	courses.insert(std::pair<string,float>(name, fl));
}
bool student::operator<(const student &rhs){

	if(type != rhs.type)
		return type < rhs.type;
	else
		return name < rhs.name;
}

void student::print_person_info(ostream& os) {
	os << right << setw(12) << "Name: " << get_name() << endl;
	os << right << setw(12) << "Category: " << type2str(get_type()) << endl;
}
void student::print_course_info(ostream& os) {
	multimap<string, float>:: iterator it;
	float fl = 0.0;
	int i = 1;
	for(it = courses.begin(); it != courses.end(); ++it){
		fl += it->second;
		os << right << setw(12) << "Course: " << left << setw(26) << it->first
			<< right << setw(4) << fixed << setprecision(2) << it->second << setw(5) << (fl / i) << endl;
		i++;
	}
}

