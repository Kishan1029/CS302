#ifndef __PERSON_H__ 
#define __PERSON_H__

#include <string>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <iterator>
#include <iomanip>

using namespace std;

enum type_enum { UNKNOWN=-1, FACULTY=0,  ASST_PROF=1, ASSOC_PROF=2, FULL_PROF=3,
	STUDENT=10, FRESHMAN=11, SOPHOMORE=12, JUNIOR=13, SENIOR=14 };

class person {
	public: 
		person();
		person(const string&, type_enum = UNKNOWN);

		string &get_name();
		type_enum &get_type();

		bool operator<(const person &);
		friend ostream &operator<<(ostream &, person &);

	protected:
		string name;
		type_enum type;
		virtual void print_person_info(ostream &) = 0;
		virtual void print_course_info(ostream &) = 0;
};
class faculty : public person {
	public:
		faculty();
		faculty(const string&, type_enum = UNKNOWN);
		void add_course(const string &);

		bool operator<(const faculty &);

	private:
		multiset<string> courses;
		void print_person_info(ostream &) ;
		void print_course_info(ostream &) ;

};
class student : public person {
	public:
		student();
		student(const string&, type_enum = UNKNOWN);
		virtual ~student () { ; }
		void add_course(const string &, float);

		bool operator<(const student &);
	private:
		multimap<string, float> courses;
		void print_person_info(ostream &) ;
		void print_course_info(ostream &);

};

//class student DEFINITION -- derived class

#endif

