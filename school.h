#include <iostream>
using namespace std;

class student;
class course;
class professor;
class subject;

class school{
	int idSchool;
	float money;
	char *name;
	char *address;
	int nProf;
	int nStud;
	int nCour;
	int nSubj;

	professor *profList;
	course *courList;

public:
	school(int id, char *name, char *address, float mon);
	~school();

	void showProf();
	void showStu();
	void showCour();
	void showSub();
	void addCourse();
	void addProfessor();
	void plusSub();
	void minusSub();
	void plusStu();
	void minusStu();
	void addProfessor(professor *p, float wage);
	void addCourse(course *c);
	void delProf(professor *p);
	void delCour(course *c);
	void delSub(subject *s);
	void pay();
	void gain(float mon);
	void showBalance();
};

class course{
	int level;	// The level is also the Id of the course.
	int nSubj;	// The number of subjects of the course.
	int nStud;	// The number of students on the course.
	int maxSub;
	int maxStu;
	school *sch;
	professor *tutor;
	course *next;
	student *stuList;
	subject *subList;

public:
	course(int lev);
	~course();
	int getLevel();
	friend void school::showCour();
	friend void school::showStu();
	friend void school::showSub();
	friend void school::addCourse();
	friend void school::addCourse(course *c);
	friend void school::delCour(course *c);
	friend school::~school();

	void showInfo();
	void addSub(subject *s);
	void removeSub(subject *s);
	void removeStu(student *s);
	void setTutor(professor *p);
	void addStu(student *s);
	void delStu(student *s);
	void removeTutor();
	void showStu();
	void showSub();
};
class professor{
	int profId;
	char *name;
	char *surname;
	int phone;
	int age;
	char *address;
	char *email;
	int nSubj;
	float wage;
	professor *next;
	school *sch;
	course *tutor;
	subject **teach;

public:
	professor(char *n, char *sn, int ph, int ag, char *add, char *ma);
	~professor();
	void showInfo();
	friend void school::showProf();
	friend void course::setTutor(professor *p);
	friend void school::addProfessor(professor *p, float wage);
	friend void school::delProf(professor *p);
	friend void school::pay();
	friend course::~course();
	friend school::~school();

	void addSubject(subject *sub);
	void delSubject(subject *s);
	void setGrade(student *s, subject *su, float gr);
	void showsub();
};
class subject{
	char *name;
	char *descr;

	subject *next;
	school *sch;
	course *cour;

public:
	subject(char *name, char *desc);
	~subject();
	friend void school::showSub();
	friend void course::showSub();
	friend void course::addSub(subject *s);
	friend void course::removeSub(subject *s);
	friend void professor::addSubject(subject *sub);
	friend void professor::delSubject(subject *s);
	friend void professor::setGrade(student *s, subject *su, float gr);
	friend course::~course();
	friend void course::showInfo();

	void showInfo();
	char* getName();
};
class student{
	char *name;
	char *surname;
	int phone;
	int age;
	char *address;
	char *email;

	student *next;
	school *sch;
	course *cour;

	struct grades{
		subject *sub;
		float grade;
		grades *next;
	};
	grades *grad;
public:

	student::student(char *n, char *sn,int ph, int ag, char *addr, char *ema);
	~student();
	friend void school::showStu();
	friend void course::addStu(student *s);
	friend course::~course();
	friend void course::showStu();
	friend void course::delStu(student *s);
	friend void course::removeStu(student *s);
	friend void course::showInfo();
	friend void professor::setGrade(student *s, subject *su, float gr);
	friend school::~school();

	void showInfo();
	void showGrades();
};
