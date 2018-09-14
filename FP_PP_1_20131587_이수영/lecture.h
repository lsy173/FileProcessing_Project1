#ifndef LECTURE_H
#define LECTURE_H

#include <iostream>
#include <fstream>
#include "iobuffer.h"
#include "deltext.h"

using namespace std;

class Lecture {
private: // fields.
	char LectureID[13];
	string Subject;
	char Level[2];
	int Price;
	char Extension[2];
	int DueDate;
	string NameOfTeacher;
	string TextBook;

public: // operations.
	Lecture();
	Lecture(const char * newlectureID);
	Lecture(const Lecture &s);
	
	Lecture & operator=(const Lecture &);
	bool operator == (const Lecture &);
	bool operator != (const Lecture &);

	friend istream & operator >> (istream &is, Lecture &s);
	friend ostream & operator << (ostream &os, Lecture &s);

	void update_LectureID(const char* newLectureID) { memcpy(LectureID, newLectureID, sizeof(LectureID)); }
	void update_Subject(const string  newSubject) { Subject = newSubject; }
	void update_Level(const char* newLevel) { memcpy(Level, newLevel, sizeof(newLevel)); }
	void update_Price(const int newPrice) { Price = newPrice; }
	void update_Extension(const char* newExtension) { memcpy(Extension, newExtension, sizeof(Extension)); }
	void update_DueDate(const int newDueDate) { DueDate = newDueDate; }
	void update_NameOfTeacher(const string newNameOfTeacher) { NameOfTeacher = newNameOfTeacher; }
	void update_TextBook(const string newTextBook) { TextBook = newTextBook; }

	char* getLectureID(void) {
		return LectureID;
	}
	string getSubject(void) {
		return Subject;
	}
	char* getLevel(void) {
		return Level;
	}
	int getPrice(void) {
		return Price;
	}
	char* getExtension(void) {
		return Extension;
	}
	int getDueDate(void) {
		return DueDate;
	}
	string getNameOfTeacher(void) {
		return NameOfTeacher;
	}
	string getTextBook(void) {
		return TextBook;
	}
	int getLength(void) {
		return strlen(LectureID) + Subject.length() + strlen(Level) + sizeof(Price) + strlen(Extension) + sizeof(DueDate) + NameOfTeacher.length() + TextBook.length();
	}

	bool Pack(IOBuffer &Buffer) const;
	bool Unpack(IOBuffer &);
};

istream & operator >> (istream &is, Lecture &s);
ostream & operator << (ostream &os, Lecture &s);
#endif