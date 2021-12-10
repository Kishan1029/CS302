//Kishan Patel
//lab8- cs302

using namespace std;

#include "Person.h"
#include "Sptrsort.h"

enum mode_enum{ MODE_NULL = -1, MODE_PERSON = 0, 
	MODE_FACULTY = 1, MODE_STUDENT = 2 };

//string to type;
type_enum str2type(string s){
	if(s == "Faculty") return FACULTY;
	else if(s == "Assistant Professor") 
		return ASST_PROF;
	else if(s == "Associate Professor") 
		return ASSOC_PROF;
	else if(s == "Full Professor") 
		return FULL_PROF;
	else if(s == "Student") 
		return STUDENT;
	else if(s == "Freshman") 
		return FRESHMAN;
	else if(s == "Sophomore") 
		return SOPHOMORE;
	else if(s == "Junior") 
		return JUNIOR;
	else if(s == "Senior") 
		return SENIOR;
	else return UNKNOWN;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		//output error message
		cerr << "usage: -faculty|student\n";
		return 0;
	}

	mode_enum mode = MODE_NULL;
	if(strcmp(argv[1], "-person") == 0) mode = MODE_PERSON;
	if(strcmp(argv[1], "-faculty") == 0) mode = MODE_FACULTY;
	if(strcmp(argv[1], "-student") == 0) mode = MODE_STUDENT;

	if(mode == MODE_NULL){
		cerr << "usage\n";
		return -1;
	}

	person *n_person;
	faculty *f_person;
	student *s_person;

	vector<person *> person_list;
	vector<faculty *> faculty_list;
	vector<student *> student_list;

	type_enum type = UNKNOWN;
	//type_enum g = UNKNOWN;

	int line = 1;
	size_t iL, iR;
	string input;

	//CS307: CHECK CORRECTESS OF XML HEADER 

	while (getline(cin, input)) {
		++line;

		if ((iL = input.find('<')) == string::npos) {
			continue;

		} else if (input.compare(iL,9,"<faculty>") == 0) {
			//set type 
			type = FACULTY;
			//course.clear();
			n_person = new faculty("", type);
			f_person = static_cast<faculty *> (n_person);
			s_person = NULL;
		} else if (input.compare(iL,10,"</faculty>") == 0) {

			//CODE FOR ADDING FACULTY PERSON TO DATABASE
			person_list.push_back(n_person);
			faculty_list.push_back(f_person);

			type = UNKNOWN;
			//reset subtype
			continue;

		} else if (input.compare(iL,9,"<student>") == 0) {
			//set type
			type = STUDENT;

			n_person = new student("", type);
			s_person = static_cast<student *>(n_person);
			f_person = NULL;

			//course.clear();
			//gp.clear();

		} else if (input.compare(iL,10,"</student>") == 0) {

			//CODE FOR ADDING STUDENT PERSON TO DATABASE
			person_list.push_back(n_person);
			student_list.push_back(s_person);

			type = UNKNOWN;

			continue;

		} else if (input.compare(iL,5,"<name") == 0) {
			iL = input.find("=\"", iL);
			iR = input.find("\"/>", iL+2);

			//CODE FOR EXTRACTING NAME (using iL, iR)
			n_person->get_name() = input.substr(iL + 2, iR - 2 - iL);

		} else if (input.compare(iL,10,"<category=") == 0) {
			iL = input.find("=\"", iL);
			iR = input.find("\"/>", iL+2);
			
			//CODE FOR EXTRACTING NAME
			//
			n_person->get_type() =	str2type(input.substr(iL + 2, iR - 2 - iL) );

		} else if(input.compare(iL,7,"<course") == 0){
			iL = input.find("=\"", iL);
			iR = input.find("\"", iL+2);

			//CODE FOR EXTRACTING COURSE (using iL, iR)
			float gpa = 0.0f;
			string course = input.substr(iL + 2, iR - 2 - iL);

			//iL = iR;
			if (type == FACULTY) {
				iR = input.find("/>", iL+1);
				f_person->add_course(course);

			} else if (type == STUDENT) {
				iL = input.find("gp=\"", iL);
				iR = input.find("\"/>", iL+4);

				//CODE FOR EXTRACTING GRADE (using iL, iR)
				string x = input.substr(iL + 4, iR - 4 - iL);
				gpa = ::atof(x.c_str());

				s_person->add_course(course, gpa);
			}
		}
	}

	/*	cout << "STUDENTS:\n";
		for(int i = 0; i < student_list.size(); i++){
		cout << student_list[i]->get_type() << endl;
		}
		cout << "FACULTY:\n";
		for(int i = 0; i < faculty_list.size(); i++){
		cout << faculty_list[i]->get_type() << endl;
		}*/


	sptrsort(person_list);
	sptrsort(student_list);
	sptrsort(faculty_list);
	
	//-person option
	if(mode == MODE_PERSON){
		for(int i = 0; i < (int)person_list.size(); i++){
			cout << *person_list[i] << endl;
		}
	}
	//-faculty option
	else if(mode == MODE_FACULTY){
		for(int i = 0; i < (int)faculty_list.size(); i++){
			cout << *faculty_list[i] << endl;
		}
	}
	//-student option
	else if(mode == MODE_STUDENT){
		for(int i = 0; i < (int)student_list.size(); i++){
			cout << *student_list[i] << endl;
		}
	}
	else{
		cerr << "usage: ./sdata_processor -person|faculty|student < file.xml\n";
		return -1;		
	}

}
