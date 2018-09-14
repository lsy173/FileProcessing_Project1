#include "lecture.h"
#include <sstream>

Lecture::Lecture() {};
Lecture::Lecture(const char* newLectureID) {
	update_LectureID(newLectureID);
}
Lecture::Lecture(const Lecture & s) {
	update_LectureID(s.LectureID);
	update_Subject(s.Subject);
	update_Level(s.Level);
	update_Price(s.Price);
	update_Extension(s.Extension);
	update_DueDate(s.DueDate);
	update_NameOfTeacher(s.NameOfTeacher);
	update_TextBook(s.TextBook);
}

Lecture & Lecture::operator=(const Lecture &s) {
	update_LectureID(s.LectureID);
	update_Subject(s.Subject);
	update_Level(s.Level);
	update_Price(s.Price);
	update_Extension(s.Extension);
	update_DueDate(s.DueDate);
	update_NameOfTeacher(s.NameOfTeacher);
	update_TextBook(s.TextBook);
	return *this;
}

bool Lecture::operator==(const Lecture &s) {
	if (strcmp(LectureID, s.LectureID) == 0) return true;
	else return false;
}

bool Lecture::operator!=(const Lecture &s) {
	if (strcmp(LectureID, s.LectureID) == 0) return false;
	else return true;
}

bool Lecture::Pack(IOBuffer &Buffer) const {
	int numBytes;

	Buffer.Clear();
	string s_mileage(Mileage, LENMIL);

	numBytes = Buffer.Pack(ID.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Password.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Name.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Phone_Number.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Address.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(s_mileage.c_str());
	if (numBytes == -1) return false;
	return true;
}

bool Member::Unpack(IOBuffer &Buffer) {
	int numBytes;
	char buf[STDMAXBUF];

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	ID = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Password = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Name = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Phone_Number = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Address = buf;
	numBytes = Buffer.Unpack(Mileage, LENMIL);
	if (numBytes == -1) return false;

	return true;
}

istream & operator >> (istream & is, Member &s) {

	string st;

	is.exceptions(istream::failbit | istream::badbit);

	try {
		getline(is, st);
	}
	catch (istream::failure e) {
		return is;
	}

	istringstream iss(st);
	string token;

	getline(iss, token, '|');
	s.update_ID(token.data());
	getline(iss, token, '|');
	s.update_Password(token.data());
	getline(iss, token, '|');
	s.update_Name(token.data());
	getline(iss, token, '|');
	s.update_PhoneNumber(token.data());
	getline(iss, token, '|');
	s.update_Address(token.data());
	getline(iss, token, '|');
	s.update_Mileage(token.data());

	return is;

}

ostream & operator << (ostream &os, Member &s) {
	string Mileage(s.Mileage, LENMIL);

	os << "ID : " << s.ID << endl;
	os << "Password : " << s.Password << endl;
	os << "Name : " << s.Name << endl;
	os << "Phone_Number : " << s.Phone_Number << endl;
	os << "Address : " << s.Address << endl;
	os << "Mileage : " << Mileage << endl;

	return os;
}
