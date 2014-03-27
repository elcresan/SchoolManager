#include <iostream>
#include <string.h>
#include "school.h"
using namespace std;

//----------- School methods
school::school(int id, char *n, char *ad, float mon){
	money = mon;
	address = new char[strlen(ad)+1];
	name = new char[strlen(n)+1];
	strcpy(address, ad);
	strcpy(name, n);
	idSchool = id;
	nProf = nStud = nCour = nSubj = 0;
	profList = NULL;
	courList = NULL;
}
school::~school(){

	course *c = courList;
	for(int i=0; i< nCour; ++i){
		student *s;
		subject *su;
		for(int j=0; j<c->nSubj; j++){
			su = c->subList;
			c->removeSub(su);
		}
		for(int j=0; j<c->nStud; j++){
			s = c->stuList;
			c->removeStu(s);
		}
		c->stuList = NULL;
		c->subList = NULL;
		c->sch = NULL;
		c=c->next;
	}
	courList = NULL;
	professor *p;
	p = profList;
	for(int i=0; i<nProf; ++i){
		p->sch = NULL;
		p=p->next;
	}
	nProf=0;
	profList = NULL;
	nCour = 0;
	nStud = 0;
	nSubj = 0;
	cout << "School " << name << " was removed." << endl;
}

void school::plusSub(){
	nSubj++;
}
void school::minusSub(){
	nSubj--;
}
void school::plusStu(){
	nStud++;
}
void school::minusStu(){
	nStud--;
}
void school::addProfessor(professor *p, float wage){
	if(p == NULL){
		cout << "Error adding professor (Invalid input)." << endl;
		return;
	}
	if(p->sch != NULL){
		cout << "Error adding professor (Professor has already a school)." << endl;
		return;
	}

	else{
		p->wage = wage;
		p->next = profList;
		p->sch = this;
		profList = p;
		nProf++;
	}
}

void school::delProf(professor *p){
	if(p==NULL || p->sch != this)
		cout << "Error removing profesor from school (If from other school)." << endl;
	else{
		nProf--;
		professor *q = profList;
		for(int i=0; i<nProf; ++i){
			if(q->next == p)
				q->next = p->next;
		}
		p->sch = NULL;
	}
}
void school::addCourse(course *c){
	if(c==NULL){
		cout << "Error adding course to school (Invalid input)." << endl;
		return;
	}
	if(c->sch != NULL){
		cout << "Error adding course to school (Course is already in a school)." << endl;
		return;
	}
	c->sch = this;
	nCour++;
	nSubj += c->nSubj;
	c->next = courList;
	courList = c;
}
void school::delCour(course *c){
	if(c == NULL || c->sch != this || c->sch == NULL)
		cout << "Error removing course from school because course is from different school or he hasn't school." << endl;
	else{
		c->sch = NULL;
		nCour--;
		course *q = courList;
		for(int i=0; i<nCour; ++i){
			if(q->next == c)
				q->next = c->next;
		}
		c->sch = NULL;
	}

}
void school::delSub(subject *s){
	professor *p = profList;
	for(int i = 0; i< nProf; ++i)
		p->delSubject(s);
	nSubj--;
}
void school::pay(){
	for(professor *p = profList; p!= NULL; p=p->next)
		money-=p->wage;
	if(money <= 0)
		cout << "Note: School has negative balance!" << endl;
}
void school::gain(float mon){
	money += mon;
	cout << "School gain "<< mon << " and has " << money << " of money." << endl;
}
void school::showBalance(){
	cout << "----Balance of school is :" << money <<endl;
}
void school::showProf(){
	if(profList == NULL)
		cout << name << " hasn't professors yet." << endl;
		else{
		professor *a = profList;
		cout << "---------List of professors of " << name << "-------" << endl;
		while(a != NULL){
			a->showInfo();
			a=a->next;
		}
		cout << "----------------------------------------------" << endl;
		}
}
void school::showStu(){
	if(courList == NULL)
		cout << "There isn't students at school yet." << endl;
	else{
		course *c = courList;
		cout << "-----------List of students: " << endl;
		while(c){
			c->showStu();
			c=c->next;
		}
		cout << "-------------------------" << endl;
	}
}
void school::showCour(){
	if(courList == NULL)
		cout << name << " hasn't courses yet." << endl;
	else{
		course *c = courList;
		cout << "-----------List of courses " << endl;
		while(c){
			c->showInfo();
			c=c->next;
		}
		cout << "-------------------------" << endl;
	}
}
void school::showSub(){
	if(this->courList == NULL)
		cout << name << "hasn't subjects yet." << endl;
	else{
		course *c = courList;
		cout << "-----------List of subjects " << endl;
		while(c){
			c->showSub();
			c=c->next;
		}
		cout << "-------------------------" << endl;
	}
}
//-----------------Professor methods
professor::professor(char *n, char *sn, int ph, int ag, char *add, char *ma){
	name = new char[strlen(n)+1];
	surname = new char[strlen(sn)+1];
	address = new char[strlen(add)+1];
	email = new char[strlen(ma)+1];

	strcpy(name, n);
	strcpy(surname, sn);
	strcpy(address, add);
	strcpy(email, ma);
	phone = ph;
	age = ag;
	while(age < 18){
		cout << "Input a correct age.(More than 18)" << endl ;
		cin >> age;
	}
	next = NULL;
	nSubj = 0;
	wage = 0.0;
	teach = NULL;
	sch = NULL;
	tutor = NULL;
}

professor::~professor(){
	if(sch != NULL)
		sch->delProf(this);
	sch = NULL;
	teach = NULL;
	if(tutor != NULL)
		tutor->removeTutor();
	delete teach;
	teach = NULL;
	cout << "Profesor " << name << "was removed." << endl;
}

void professor::showInfo(){
	cout << "----------Professor--------------" << endl;
	cout << "Name: " << name << " " << surname << endl;
	cout << "Phone: " << phone << endl;
	cout << "Age: " << age << endl;
	cout << "Address: " << address << endl;
	cout << "Email: " << email << endl;
	cout << "Wage: " << wage << endl;
	if(tutor != NULL)
		cout << "Tutor of the course: " << tutor->getLevel() << endl;
	else
		cout << "No tutor." << endl;
	if(nSubj){
		cout << "Subjects tought by him:" << endl;
		for(int i=0; i< nSubj; ++i)
			cout <<"     " << teach[i]->getName() << endl;
	}
	else
		cout << "No subjects tough by him." << endl;
	cout << "---------------------------------" << endl;
}
void professor::addSubject(subject *sub){
	if(sub == NULL || sch == NULL || sub->sch != sch)
		cout << "Error adding a subject to the professor." << endl;
	else{
		nSubj++;
		subject **t = new subject*[nSubj];
		t[0] = sub;
		for(int i=0; i< nSubj-1; ++i)
			t[i+1] = teach[i];
		teach = t;
	}
}
void professor::delSubject(subject *s){
	if(s == NULL || s->sch != sch || sch == NULL)
		cout << "Error removing a subject from professor." << endl;
	for(int j=0; j < nSubj; ++j)		//Checking if professor teaches this subject.
		if(teach[j] == s){
			nSubj--;
			subject **t = new subject*[nSubj];
			for(int i=0; i < nSubj+1; ++i)
				if(teach[i] != s)
					t[i] = teach[i];
			teach = t;
		}
}

void professor::setGrade(student *s, subject *su, float gr){
	if(s == NULL || su == NULL){
		cout << "Error setting grades to student: you must input a correct student/subject." << endl;
		return;
	}
	if(s->sch != su ->sch || s->sch != sch){
		cout << " Error setting grades to student: Subject, professor and student must belong to the same school." << endl;
		return;
	}
	if(s->cour != su->cour){
		cout << "Error setting grades to student: Student and subject must belong to the same course." << endl;
		return;
	}
	if(professor::nSubj == 0){
		cout << "Error setting grades to student: Professor hasn't taught any subject." << endl;
		return;
	}
	if(gr < 0 || gr > 10){
		cout << "Error setting grades to student: Grade should be from 0 to 10" << endl;
		return;
	}
	subject *aux;
	for(int i=0; i <nSubj;++i){
		aux = teach[i];
		if(aux = su)
			break;
		if(i == nSubj-1){
			cout << "Error setting grades to student: Professor hasn't taught this subject." << endl;
			return;
		}
	}

	student::grades *g = s->grad;
	if(g == NULL){
		g = new student::grades;
		g->grade = gr;
		g->next = NULL;
		g->sub = su;
		s->grad = g;
	}
	else{
		if(g->sub = su)
			g->grade = gr;
		else
			while(g != NULL){
				if(g->next = NULL){
					g->next = new student::grades;
					g = g->next;
					g->grade = gr;
					g->next = NULL;
					g->sub = su;
					g = NULL;
				}
				else{
					if(g->next->sub = su){
						g = g->next;
						g->grade = gr;
						g = NULL;
					}
					else
						g=g->next;
				}
			}
	}
}

void professor::showsub(){
	if(teach == NULL)
		cout << "Profesor doesn't teach any subject yet." << endl;
	else{
		cout << "------Subjects of professor " << name << surname << "------" << endl;
		for(int i=0; i<nSubj;++i)
			cout << teach[i]->getName() << endl;
		cout << "-----------------------------------------" << endl;
	}
}
//------------------Student methods:
student::student(char *n, char *sn,int ph, int ag, char *addr, char *ema){
	name = new char[strlen(n)];
	surname = new char[strlen(sn)];
	address = new char[strlen(addr)];
	email = new char[strlen(ema)];

	strcpy(name, n);
	strcpy(surname, sn);
	strcpy(address, addr);
	strcpy(email, ema);

	phone = ph;
	while(ag < 5){
		cout << "Input a correct age (More than 5)" << endl ;
		cin >> ag;
	}
	age = ag;
	grad = NULL;
	next = NULL;
	cour = NULL;
	grad = NULL;
	sch = NULL;
}
student::~student(){
	if(sch)
		sch->minusStu();
	if(cour)
		cour->delStu(this);
	cout << "Student " << name << " was removed." << endl;
	this->cour = NULL;
	this->sch = NULL;
}
void student::showInfo(){
	cout << "----------Student--------------" << endl;
	cout << "Name: " << name <<" "<< surname << endl;
	cout << "Phone: " << phone << endl;
	cout << "Age: " << age << endl;
	cout << "Address: " << address << endl;
	cout << "Email: " << email << endl;
	if(cour != NULL)
		cout << "Course: " << cour->getLevel() << endl;
	else
		cout << "No Course." << endl;
	cout << "-------------------------------" << endl;
}
void student::showGrades(){
	grades *g = grad;
	if(g == NULL)
		cout << "No grades yet." << endl;
	else{
		cout << "------Grades of " << name << "------" << endl;
		while(g){
			cout << g->sub->getName() << ": " << g->grade << endl;
			g = g->next;
		}
		cout << "------------------------" << endl;
	}
}
//----------------Subject methods:
subject::subject(char *n, char *desc){
	name = new char[strlen(n)];
	descr = new char[strlen(desc)];
	strcpy(name, n);
	strcpy(descr, desc);
	next = NULL;
	cour = NULL;
	sch = NULL;
}
subject::~subject(){
	if(sch != NULL)
		sch->delSub(this);
	if(cour != NULL)
		cour->removeSub(this);
	cout << "Subject "<< name << " removed." << endl;
	cour = NULL;
	next = NULL;
	sch = NULL;
}
void subject::showInfo(){
	cout << "--------Subject----------" << endl;
	cout << "Name: " << name << endl;
	cout << "-------------------------" << endl;
}
char* subject::getName(){
	return this->name;
}
//----------------Course methods:
course::course(int lev){
	level = lev;
	next = NULL;
	tutor = NULL;
	nSubj = 0;
	nStud = 0;
	stuList = NULL;
	subList = NULL;
	maxSub = 8;
	maxStu = 27;
	sch = NULL;
}
course::~course(){
	student *s = stuList;	// Removing pointers of student to course
	student *aux = s;
	for(int i=0; i< nStud; ++i){
		aux = s;
		s->sch->minusStu();
		s->cour = NULL;
		s->sch = NULL;
		s = s->next;
		aux->next =  NULL; 
	}
	nStud = 0;
	if(tutor){			//Removing pointers of tutor
		tutor->tutor = NULL;
		tutor = NULL;
	}
	subject *q = subList;	// Removing pointers of subject to course
	subject *ax = q;
	for(int i=0; i < nSubj; ++i){
		ax = q;
		q->sch->delSub(q);
		q->cour = NULL;
		q->sch = NULL;
		q = q->next;
		ax->next =  NULL; 
	}
	nSubj = 0;
	sch->delCour(this);
	sch = NULL;
	stuList = NULL;
	subList = NULL;
	cout << "Course " << level << " has been removed." << endl;
}

void course::showInfo(){
	cout << "--------Course----------" << endl;
	cout << "Course "<< level<< endl;
	cout << "Number of subjects: " << nSubj << endl;
	if(nSubj>0){
		subject *s = subList;
		while(s){
			cout <<"  " << s->name << endl;
			s = s->next;
		}
	}
	cout << "Number of students: " << nStud << endl;
	if(nStud>0){
		student *st = stuList;
		while(st){
			cout <<"  " << st->name << endl;
			st = st->next;
		}
	}
	cout << "------------------------" << endl;
}
int course::getLevel(){
	return level;
}



void course::addSub(subject *s){
	if(s == NULL){
		cout << "Error adding subject to course. Invalid subject." << endl;
		return;
	}
	if( nSubj >= maxSub){
		cout << "Error adding subject to course (Too much subjects)." << endl;
		return;
	}
	if ( s->cour != NULL){
		cout << "Error adding subject to course (Subject is already in one course)." << endl;
		return;
	}
	if(sch == NULL){
		cout << "Error adding subject to course (Course hasn't school assigned)." << endl;
		return;
	}
	s->next = subList;
	s->sch = sch;
	s->cour = this;
	subList = s;
	nSubj++;
	if(sch!=NULL)
		sch->plusSub();
}

void course::delStu(student *s){
	if(s != NULL && this != NULL){
		student *p = stuList;
		if(p == s)
			stuList = p->next;
		else{
			for(p; p->next != NULL; p=p->next)
				if(p->next == s)
					p->next = p->next->next;
			}
		nStud--;
	}
}
void course::removeSub(subject *s){
	subject *p, *q;
	if(s->cour != this){
		cout << "Error removing subject from course: Subject doesn't belong to the course " << level << endl;
		return;
	}
	if(this->subList == NULL){
		cout << "Error removing subject from course: Course hasn't subjects. " << endl;
		return;
	}
	p = subList;
	if(p == s){
		subList = subList->next;
		s->cour = NULL;
		s->sch->minusSub();
		s->sch = NULL;
		nSubj--;
		return;
	}
	else{
		q = p;
		p = p->next;
		while(p != s){
			q = p;
			p = p->next;
			if(p == NULL){
				cout << "Error removing subject from course: Subject doesn't belong to this course." << endl;
				return;
			}
		}
		q->next = p->next;
		nSubj--;
		s->sch->minusSub();
		s->cour = NULL;
		s->sch = NULL;
	}
}
void course::removeStu(student *s){
	student *p, *q;
	if(s->cour != this){
		cout << "Error removing student from course: Student doesn't belong to this course. " << level << endl;
		return;
	}
	if(this->stuList == NULL){
		cout << "Error removing student from course: Course hasn't students. " << endl;
		return;
	}
	p = stuList;
	if(p == s){
		stuList = stuList->next;
		s->cour = NULL;
		s->sch->minusStu();
		s->sch = NULL;
		nStud--;
		return;
	}
	else{
		q = p;
		p = p->next;
		while(p != s){
			q = p;
			p = p->next;
			if(p == NULL){
				cout << "Error removing student from course: Student doesn't belong to this course." << endl;
				return;
		}
		q->next = p->next;
		nStud--;
		s->sch->minusStu();
		s->cour = NULL;
		s->sch = NULL;
		}
	}
	cout << "Student removed from course." << endl;
}
void course::setTutor(professor *p){
	if(p == NULL){
		cout << "Error setting tutor to course(Invalid input). " << level << endl;
		return;
	}
	if(p->tutor != NULL){
		cout << "Error setting tutor to course(Professor is already tutor). " << level << endl;
		return;
	}
	if(tutor != NULL){
		cout << "Error setting tutor to course(Course has already tutor). " << endl;
		return;
	}
	if(p->sch != sch){
		cout << "Error setting tutor to course(Course and professor are from different school). " << endl;
		return;
	}
	p->tutor = this;
	tutor = p;
}
void course::removeTutor(){
	if(this->tutor != NULL)
		tutor = NULL;
}
void course::addStu(student *s){
	if(s==NULL || (s->sch != NULL && s->sch != sch))
		cout << "Error adding student to course because are from different schools." << endl;
	else
		if(sch == NULL)
			cout << "Error adding student to course because the course hasn't school assigned." << endl;
		else
			if(nStud >= maxStu)
				cout << "Error adding student to course because the course is full." << endl;
			else
				if(s->cour == this)
					cout << "Error adding student to course because the student is already in the course." << endl;
				else{
					if(s->sch == NULL){
						sch->plusStu();
						s->sch = sch;
					}
					s->cour = this;
					nStud++;
					s->next = stuList;
					stuList = s;
					cout << "Student added to course." << endl;
				}
}

void course::showStu(){
	if(stuList == NULL)
		cout << "Course " << level << " hasn't students yet." << endl;
	else{
		student *s = stuList;
		for(int i=0; i<nStud; i++){
			s->showInfo();
			s=s->next;
		}
	}
}
void course::showSub(){
	if(subList == NULL)
		cout << level << "hasn't subjects yet." << endl;
	else{
		subject *s = subList;
		while(s){
			s->showInfo();
			s=s->next;
		}
	}
}
//------------------Main------------
int main(){
	school sc(0, "Public School", "Ul. Jana Pawla 2",50000);

	student s1("Eliu","Perez", 645955720, 21, "Ul.Przasnyska", "elcre@gmail.com");
	student s2("Nicolas","Forlan", 645955721, 21, "Ul.Przasnyska", "nidebo@gmail.com");
	student s3("Jose","Panadero", 645955722, 22, "Ul.Brownskiego", "Josepa@gmail.com");
	student s4("Jorge", "Gomez", 645955723, 22, "Ul.Brownskiego", "Jorgo@gmail.com");

	professor p1("Cris", "Jorda", 689546212, 57,"Ul.Kino Femina", "Crisjo@gmail.com");
	professor p2("Berto", "Conejo", 689546213, 35,"Ul. Sady", "Berco@gmail.com");
	professor p3("Raul", "Ramiro", 689546214, 42,"Ul.Marymont", "Rauro@gmail.com");

	course c1(1);
	course c2(2);

	subject su1("Maths", "First level of maths.");
	subject su2("English", "First level of english.");
	subject su3("Maths 2", "Second level of maths.");
	subject su4("English 2", "Second level of english.");
	subject su5("Physic", "Basic knowledge of classical physics.");
	subject su6("Chemistry", "First approach to chemistry.");



	sc.addCourse(&c1);
	c1.addStu(&s1);
	c1.addSub(&su1);
	cout << "****** Remove School ******** " << endl;
	sc.~school();
	c1.showInfo();
// Remaking school
	sc.addCourse(&c1);
	c1.addStu(&s1);
	c1.addSub(&su1);
	c1.showInfo();
	sc.addProfessor(&p1,1500);
	p1.addSubject(&su1);
	cout << "**************Profesor set grades*******" << endl;
	p1.setGrade(&s1, &su1, 5);
	s1.showGrades();

	c1.addStu(&s1);
	s1.~student();
	c1.showInfo();

	c1.addStu(&s1);
	c1.addSub(&su1);

	sc.addCourse(&c1);
	sc.addCourse(&c2);

	c1.addSub(&su1);
	c1.addSub(&su2);
	c1.showInfo();

	c2.addSub(&su2);
	c2.addSub(&su4);
	c2.addSub(&su5);
	c2.addSub(&su6);
	c2.showInfo();

	c2.removeSub(&su2);
	c2.showInfo();
	c2.addSub(&su3);

	sc.addProfessor(&p1, 1200);
	sc.addProfessor(&p2,1200);
	sc.addProfessor(&p3, 2500);

	c1.setTutor(&p1); 

	c1.setTutor(&p2);
	c1.addStu(&s1);
	c1.addStu(&s2);
	c1.showInfo();
	s1.showGrades();
	c2.addStu(&s3);
	c2.addStu(&s4);
	c2.setTutor(&p2);
	p1.addSubject(&su2);
	p1.addSubject(&su4);
	p1.showsub();
	p2.addSubject(&su1);
	p2.addSubject(&su3);
	p2.showsub();
	p3.addSubject(&su5);
	p3.addSubject(&su6);
	p3.showsub();
	c1.showInfo();
	c2.showInfo();
	sc.showBalance();
	sc.pay();
	sc.showBalance();
	sc.gain(4500);
	sc.showBalance();
	sc.showProf();

	system("pause");
}
