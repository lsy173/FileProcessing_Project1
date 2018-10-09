#include <iostream>
#include <fstream>
#include <string>
#include "deltext.h"
#include "iobuffer.h"
#include "member.h"
#include "lecture.h"
#include "purchase.h"
#include "buffile.h"
#include "recfile.h"

using namespace std;

void showMenu(void);
void showMember(void);
void showLecture(void);
void showPurchase(void);
void MemberTest(int print_flag);
void LectureTest(int print_flag);
void PurchaseTest(int print_flag);
void LecturePurchaseSystem(void);
void showSystemMenu(void);
int SearchingByID(int flag, string filename, string ID);
void InsertingByID(void);
void DeletingByID(void);
void ModifyingByID(void);
void DeleteMember(string ID);
void DeleteLecture(string ID);
void DeletePurchase(string ID);

Member* memberArr = new Member[12000];
Lecture* lectureArr = new Lecture[12000];
Purchase* purchaseArr = new Purchase[12000];
int index;

int main(void) {
	string input;
	int input_int;
	while (1) {
		showMenu();
		cin >> input;
		cout << "*************************************" << endl;
		input_int = atoi(input.c_str());
		switch (input_int) {
		case 1: showMember(); break;
		case 2: showLecture(); break;
		case 3: showPurchase(); break;
		case 4: MemberTest(1); break;
		case 5: LectureTest(1); break;
		case 6: PurchaseTest(1); break;
		case 7: LecturePurchaseSystem(); break;
		case 8: return 0;
		default: break;
		}
	}
	return 0;
}

void showMenu() {
	cout << "*************************************" << endl;
	cout << "* 1. showMember           ***********" << endl;
	cout << "* 2. showLecture          ***********" << endl;
	cout << "* 3. showPurchase         ***********" << endl;
	cout << "* 4. MemberTest           ***********" << endl;
	cout << "* 5. LectureTest          ***********" << endl;
	cout << "* 6. PurchaseTest         ***********" << endl;
	cout << "* 7. LecturePurchaseSystem***********" << endl;
	cout << "* 8. Exit                 ***********" << endl;
	cout << "*************************************" << endl;
	cout <<  "input : ";
}


void showMember() {
	ifstream ifs("listOfMember.txt");
	if (ifs.fail())
	{
		cout << "listOfMember.txt File Open Error!" << endl << endl;
		return;
	}
	
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');
	
	for (int i = 0; i<10; i++)
	{
		Member M;
		ifs >> M;
		cout << M << endl;
	}
	ifs.close();
	return;
}


void showLecture() {
	ifstream ifs("listOfLecture.txt");
	if (ifs.fail())
	{
		cout << "listOfLetcure.txt File Open Error!" << endl;
		return;
	}

	ifs.ignore(numeric_limits<streamsize>::max(), '\n');
	
	for (int i = 0; i<10; i++)
	{
		Lecture M;
		ifs >> M;
		cout << M << endl;
	}
	ifs.close();
	return;
}

void showPurchase() {
	ifstream ifs("listOfPurchase.txt");
	if (ifs.fail())
	{
		cout << "listOfPurchase.txt File Open Error!" << endl;
		return;
	}
	int temp;
	ifs >> temp;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');
	
	for (int i = 0; i<10; i++)
	{
		Purchase M;
		ifs >> M;
		cout << M << endl;
	}
	ifs.close();
	return;
}

void MemberTest(int print_flag) {
	ifstream ifs("listOfMember.txt");
	if (ifs.fail()) {
		cout << "listOfMember.txt File Open Error!" << endl;
		return;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', 1000);
	RecordFile <Member> MemberFile(buffer);

	// Write test
	MemberFile.Create("fileOfMember.dat", ios::out | ios::trunc);
	for (int i = 0; i < n; i++) {
		Member s;
		ifs >> s;
		int recaddr;
		if ((recaddr = MemberFile.Write(s)) == -1)
			if (print_flag)
				cout << "Write Error!" << endl;
			else
				if (print_flag)
					cout << "Write at " << recaddr << endl;
	}
	MemberFile.Close();

	// Read test
	MemberFile.Open("fileOfMember.dat", ios::in);
	for (int i = 0; i < 10; i++) {
		Member s;
		MemberFile.Read(s);
		if (print_flag)
			cout << s << endl;
	}
	MemberFile.Close();
	ifs.close();
	return;
}

void LectureTest(int print_flag) {
	ifstream ifs("listOfLecture.txt");
	if (ifs.fail())
	{
		cout << "listOfLecture.txt File Open Error!" << endl;
		return;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', 1000);
	RecordFile <Lecture> LectureFile(buffer);

	// Write test
	LectureFile.Create("fileOfLecture.dat", ios::out | ios::trunc);
	for (int i = 0; i < n; i++) {
		Lecture s;
		ifs >> s;
		int recaddr;
		if ((recaddr = LectureFile.Write(s)) == -1)
			if (print_flag)
				cout << "Write Error!" << endl;
			else
				if (print_flag)
					cout << "Write at " << recaddr << endl;
	}
	LectureFile.Close();

	// Read test
	LectureFile.Open("fileOfLecture.dat", ios::in);
	for (int i = 0; i < 10; i++) {
		Lecture s;
		LectureFile.Read(s);
		if (print_flag)
			cout << s << endl;
	}
	LectureFile.Close();
	ifs.close();
	return;
}

void PurchaseTest(int print_flag) {
	ifstream ifs("listOfPurchase.txt");
	if (ifs.fail())
	{
		cout << "listOfPurchase.txt File Open Error!" << endl;
		return;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', 10000);
	RecordFile <Purchase> PurchaseFile(buffer);

	// Write test
	PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);
	for (int i = 0; i < n; i++) {
		Purchase s;
		ifs >> s;
		int recaddr;
		if ((recaddr = PurchaseFile.Write(s)) == -1)
			if (print_flag)
				cout << "Write Error!" << endl;
			else
				if (print_flag)
					cout << "Write at " << recaddr << endl;
	}
	PurchaseFile.Close();

	// Read test
	PurchaseFile.Open("fileOfPurchase.dat", ios::in);
	for (int i = 0; i < 10; i++) {
		Purchase s;
		PurchaseFile.Read(s);
		if (print_flag)
			cout << s << endl;
	}
	PurchaseFile.Close();
	ifs.close();
	return;
}

void LecturePurchaseSystem() {
	string input;
	int input_int;
	string filename;
	string want_ID;
	static int test = 0;

	if (!test) {
		MemberTest(0);
		LectureTest(0);
		PurchaseTest(0);
		test = 1;
	}

	while (1) {
		showSystemMenu();
		cin >> input;
		cout << "*************************************" << endl;
		input_int = atoi(input.c_str());
		switch (input_int) {
		case 1:
			cout << "Enter file name : ";
			cin >> filename;
			cout << "Enter ID : ";
			cin >> want_ID;
			SearchingByID(1, filename, want_ID); break;
		case 2: InsertingByID(); break;
		case 3: DeletingByID(); break;
		case 4: ModifyingByID(); break;
		default: return;
		}
	}
}


void showSystemMenu() {
	cout << endl;
	cout << "#####################################" << endl;
	cout << "# 1. Search               ###########" << endl;
	cout << "# 2. Insert               ###########" << endl;
	cout << "# 3. Delete               ###########" << endl;
	cout << "# 4. Modify               ###########" << endl;
	cout << "# The Others. Exit        ###########" << endl;
	cout << "#####################################" << endl;
	cout << "input : ";

	return;
}


int SearchingByID(int flag, string filename, string want_ID) {
	Member m;
	Purchase p;
	Lecture l;
	Purchase* p_arr = new Purchase[30];

	//string filename;
	//string want_ID;
	int find_ID = 0;
	ifstream ifs(filename);
	int ifs_last;
	int find_Addr = 0;
	int* addr_arr = (int*)malloc(sizeof(int));
	int id_cnt = 0;
	if (ifs.fail()) {
		cout << filename << " open error!" << endl;
		return 0;
	}
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	if (filename.compare("fileOfMember.dat") == 0) {
		DelimFieldBuffer buffer('|', 1000);
		RecordFile <Member> MemberFile(buffer);
		MemberFile.Open("fileOfMember.dat", ios::in);
		ifs.clear();
		ifs.seekg(0, ifs.end);
		ifs_last = ifs.tellg();
		ifs.seekg(0, ifs.beg);
		while (ifs.tellg() < ifs_last) {
			MemberFile.Read(m);
			ifs.seekg(m.getLength(), ifs.cur);
			if (!m.getID().compare(want_ID)) {
				find_ID = 1;
				id_cnt += 1;
				break;
			}
			find_Addr += m.getLength();
		}
		MemberFile.Close();
		ifs.close();
	}
	else if (filename.compare("fileOfLecture.dat") == 0) {
		DelimFieldBuffer buffer('|', 1000);
		RecordFile <Lecture> LectureFile(buffer);
		LectureFile.Open("fileOfLecture.dat", ios::in);
		ifs.clear();
		ifs.seekg(0, ifs.end);
		ifs_last = ifs.tellg();
		ifs.seekg(0, ifs.beg);
		while (ifs.tellg() < ifs_last) {
			LectureFile.Read(l);
			ifs.seekg(l.getLength(), ifs.cur);
			if (!memcmp(l.getLectureID(), want_ID.c_str(), strlen(l.getLectureID()))) {
				find_ID = 2;
				id_cnt += 1;
				break;
			}
			find_Addr += l.getLength();
		}
		LectureFile.Close();
		ifs.close();

	}
	else if (filename.compare("fileOfPurchase.dat") == 0) {
		DelimFieldBuffer buffer('|', 10000);
		RecordFile <Purchase> PurchaseFile(buffer);
		PurchaseFile.Open("fileOfPurchase.dat", ios::in);
		ifs.clear();
		ifs.seekg(0, ifs.end);
		ifs_last = ifs.tellg();
		ifs.seekg(0, ifs.beg);

		while (ifs.tellg() < ifs_last) {
			PurchaseFile.Read(p);
			ifs.seekg(p.getLength(), ifs.cur);
			if (!strcmp(p.getPurchaseID(), want_ID.c_str())) {
				find_ID = 3;
				id_cnt += 1;
				break;
			}
			else if (!strcmp(p.getLectureID(), want_ID.c_str())) {
				find_ID = 3;
				id_cnt += 1;
				break;
			}
			else if (!p.getMemberID().compare(want_ID)) {
				find_ID = 3;
				id_cnt += 1;

				addr_arr = (int*)realloc(addr_arr, id_cnt * sizeof(int));
				p_arr[id_cnt - 1] = p;
				addr_arr[id_cnt - 1] = find_Addr;
			}
			find_Addr += p.getLength();
		}
		PurchaseFile.Close();
		ifs.close();
	}
	else {
		cout << "You have wrong file." << endl;
		ifs.close();
	}

	if (find_ID) {
		if (flag) {
			cout << endl << "Searching Complete" << endl << endl;
			cout << "From " << filename << endl;
			switch (find_ID) {
			case 1:	cout << m; break;
			case 2: cout << l; break;
			case 3:
				if (id_cnt == 1) {
					cout << p;
				}
				else {
					for (int i = 0; i < id_cnt; i++) {
						cout << p_arr[i] << endl;
						cout << " ****************** " << endl;
						cout << "start addr : " << addr_arr[i] << endl;
					}
				}

				break;
			}
			if (id_cnt == 1) {
				cout << " ****************** " << endl;
				cout << "start addr : " << find_Addr << endl;
			}
		}
		return 1;
	}
	else {
		if (flag)
			cout << "This id doesn't exist in DB." << endl;
		return 0;
	}
	return 0;
}

void InsertingByID() {
	string want_ID;
	string filename;
	int find;
	cout << "Enter ID : ";
	cin >> want_ID;
	cout << "Enter file name : ";
	cin >> filename;
	find = SearchingByID(0, filename, want_ID);
	if (find) {
		cout << "**********************" << endl;
		cout << "this id already exist." << endl;
		cout << "**********************" << endl;
	}
	else {
		if (filename.compare("fileOfMember.dat") == 0) {
			index = 0;
			ifstream ifs("fileOfMember.dat");
			if (ifs.fail()) {
				cout << "fileOfMember.dat open error!" << endl;
				return;
			}
			ifs.ignore(numeric_limits<streamsize>::max(), '\n');

			Member m;
			int ifs_last;
			DelimFieldBuffer buffer('|', 1000);
			RecordFile <Member> MemberFile(buffer);
			MemberFile.Open("fileOfMember.dat", ios::in);
			//MemberFile.
			ifs.clear();	//because of c++98
			ifs.seekg(0, ifs.end);
			ifs_last = ifs.tellg();
			ifs.seekg(0, ifs.beg);
			Member m_temp;
			while (ifs.tellg() < ifs_last) {
				MemberFile.Read(m);

				if (!m_temp.getID().compare(m.getID())) {
					break;
				}
				memberArr[index] = m;
				m_temp = m;
				index += 1;
				ifs.seekg(m.getLength(), ifs.cur);
			}
			Member n;
			string temp;
			char* update_temp = new char(100);

			n.setID(want_ID);

			cout << "New Password : ";
			cin >> temp;
			n.setPassword(temp);

			cout << "New Name : ";
			cin >> temp;
			n.setName(temp);

			cout << "New Phone Number : ";
			cin >> temp;
			n.setPhoneNumber(temp);

			cout << "New Address : ";
			cin >> temp;
			n.setAddress(temp);

			cout << "New Mileage : ";
			cin >> update_temp;
			if (strlen(update_temp) != 10) {
				cout << "Wrong length" << endl;
				return;
			}
			n.setMileage(update_temp);

			memberArr[index] = n;
			index += 1;

			MemberFile.Close();
			MemberFile.Create("fileOfMember.dat", ios::out | ios::trunc);
			int recaddr;
			for (int i = 0; i < index; i++) {
				if ((recaddr = MemberFile.Write(memberArr[i])) == -1)
					cout << "Write Error!" << endl;
			}
			MemberFile.Close();
			ifs.close();


		}
		else if (filename.compare("fileOfLecture.dat") == 0) {
			index = 0;
			ifstream ifs("fileOfLecture.dat");
			if (ifs.fail()) {
				cout << "fileOfLecture.dat open error!" << endl;
				return;
			}
			ifs.ignore(numeric_limits<streamsize>::max(), '\n');

			Lecture m;
			int ifs_last;
			DelimFieldBuffer buffer('|', 1000);
			RecordFile <Lecture> LectureFile(buffer);
			LectureFile.Open("fileOfLecture.dat", ios::in);
			//LectureFile.
			ifs.clear();	//because of c++98
			ifs.seekg(0, ifs.end);
			ifs_last = ifs.tellg();
			ifs.seekg(0, ifs.beg);
			Lecture m_temp;
			while (ifs.tellg() < ifs_last) {
				LectureFile.Read(m);
				if (!strcmp(m_temp.getLectureID(), m.getLectureID())) {
					break;
				}
				lectureArr[index] = m;
				m_temp = m;
				index += 1;
				ifs.seekg(m.getLength(), ifs.cur);
			}
			Lecture n;

			string temp;
			char* update_temp = new char(100);
			int temp_i;

			if (strlen(want_ID.c_str()) != 12) {
				cout << "Wrong length" << endl;
				return;
			}
			n.setLectureID(want_ID.c_str());

			cout << "New Subject : ";
			cin >> update_temp;
			n.setSubject(update_temp);

			cout << "New Level : ";
			cin >> update_temp;
			if (strlen(update_temp) != 1) {
				cout << "Wrong length" << endl;
				return;
			}
			n.setLevel(temp.c_str());

			cout << "New Price : ";
			cin >> temp_i;
			n.setPrice(temp_i);

			cout << "New Extension : ";
			cin >> update_temp;
			if (strlen(update_temp) != 1) {
				cout << "Wrong length" << endl;
				return;
			}
			n.setExtension(update_temp);

			cout << "New DueDate : ";
			cin >> temp_i;
			n.setDueDate(temp_i);

			cout << "New NameOfTeacher : ";
			cin >> update_temp;
			n.setNameOfTeacher(update_temp);

			cout << "New TextBook : ";
			cin >> update_temp;
			n.setTextBook(update_temp);

			lectureArr[index] = n;
			index += 1;

			LectureFile.Close();

			LectureFile.Create("fileOfLecture.dat", ios::out | ios::trunc);
			int recaddr;
			for (int i = 0; i < index; i++) {
				if ((recaddr = LectureFile.Write(lectureArr[i])) == -1)
					cout << "Write Error!" << endl;
			}
			LectureFile.Close();

			ifs.close();
		}
		else if (filename.compare("fileOfPurchase.dat") == 0) {
			index = 0;
			ifstream ifs("fileOfPurchase.dat");
			if (ifs.fail()) {
				cout << "fileOfPurchase.dat open error!" << endl;
				return;
			}
			ifs.ignore(numeric_limits<streamsize>::max(), '\n');

			Purchase m;
			int ifs_last;
			DelimFieldBuffer buffer('|', 10000);
			RecordFile <Purchase> PurchaseFile(buffer);
			PurchaseFile.Open("fileOfPurchase.dat", ios::in);
			//PurchaseFile.
			ifs.clear();	//because of c++98
			ifs.seekg(0, ifs.end);
			ifs_last = ifs.tellg();
			ifs.seekg(0, ifs.beg);
			Purchase m_temp;
			while (ifs.tellg() < ifs_last) {
				PurchaseFile.Read(m);
				if (!strcmp(m_temp.getPurchaseID(), m.getPurchaseID())) {
					break;
				}
				m_temp = m;
				//free(update_temp);
				purchaseArr[index] = m;
				index += 1;
				ifs.seekg(m.getLength(), ifs.cur);
			}

			Purchase p;
			char* update_temp = new char(100);
			string temp;

			if (strlen(want_ID.c_str()) != 16) {
				cout << "Wrong PID length" << endl;
				return;
			}
			p.setPurchaseID(want_ID.c_str());

			cout << "New Ticket ID : ";
			cin >> temp;
			if (strlen(temp.c_str()) != 12) {
				cout << "Wrong TID length" << endl;
				return;
			}
			int find_flag = SearchingByID(0, "fileOfTicket.dat", temp);
			if (!find_flag) {
				cout << "This Ticket ID doesn't exist" << endl;
				return;
			}
			p.setPurchaseID(temp.c_str());

			cout << "New Member ID : ";
			cin >> temp;
			find_flag = SearchingByID(0, "fileOfMember.dat", temp);
			if (!find_flag) {
				cout << "This Member ID doesn't exist" << endl;
				return;
			}
			p.setMemberID(temp);

			cout << "New Mileage : ";
			cin >> update_temp;
			if (strlen(update_temp) != 10) {
				cout << "Wrong length" << endl;
				return;
			}
			p.setMileage(update_temp);

			purchaseArr[index] = p;
			index += 1;

			PurchaseFile.Close();
			PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);
			int recaddr;
			for (int i = 0; i < index; i++) {
				if ((recaddr = PurchaseFile.Write(purchaseArr[i])) == -1)
					cout << "Write Error!" << endl;
			}
			PurchaseFile.Close();

			ifs.close();

		}
		cout << endl << "Inserting Complete" << endl << endl;
	}
}

void DeletingByID(void) {
	string want_ID;
	cout << "Enter ID : ";
	cin >> want_ID;
	DeleteMember(want_ID);
	DeleteLecture(want_ID);
	DeletePurchase(want_ID);
}

void DeleteMember(string want_ID) {
	index = 0;
	ifstream ifs("fileOfMember.dat");
	if (ifs.fail()) {
		cout << "fileOfMember.dat open error!" << endl;
		return;
	}
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	Member m;
	int ifs_last;
	int find_ID = 0;
	DelimFieldBuffer buffer('|', 1000);
	RecordFile <Member> MemberFile(buffer);
	MemberFile.Open("fileOfMember.dat", ios::in);
	ifs.clear();
	ifs.seekg(0, ifs.end);
	ifs_last = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	while (ifs.tellg() < ifs_last) {
		MemberFile.Read(m);
		if (!m.getID().compare(want_ID)) {
			find_ID = 1;
			ifs.seekg(m.getLength(), ifs.cur);
		}
		else {
			memberArr[index] = m;
			index += 1;
		}
		ifs.seekg(m.getLength(), ifs.cur);
	}
	MemberFile.Close();

	if (find_ID) {
		MemberFile.Open("fileOfMember.dat", ios::out | ios::trunc);
		int recaddr;
		for (int i = 0; i < index; i++) {
			if ((recaddr = MemberFile.Write(memberArr[i])) == -1)
				cout << "Write Error!" << endl;
		}
		MemberFile.Close();
		cout << "Deleting Complete from fileOfMember.dat" << endl;
	}
	ifs.close();
}

void DeleteLecture(string want_ID) {
	index = 0;
	ifstream ifs("fileOfLecture.dat");
	if (ifs.fail()) {
		cout << "fileOfLecture.dat open error!" << endl;
		return;
	}
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	Lecture m;
	int ifs_last;
	int find_ID = 0;
	DelimFieldBuffer buffer('|', 1000);
	RecordFile <Lecture> LectureFile(buffer);
	LectureFile.Open("fileOfLecture.dat", ios::in);
	//LectureFile.
	ifs.clear();	//because of c++98
	ifs.seekg(0, ifs.end);
	ifs_last = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	while (ifs.tellg() < ifs_last) {
		LectureFile.Read(m);
		if (!memcmp(m.getLectureID(), want_ID.c_str(), strlen(m.getLectureID()))) {
			find_ID = 1;
			ifs.seekg(m.getLength(), ifs.cur);
		}
		else {
			lectureArr[index] = m;
			index += 1;
		}
		ifs.seekg(m.getLength(), ifs.cur);
	}
	LectureFile.Close();


	if (find_ID) {
		LectureFile.Create("fileOfLecture.dat", ios::out | ios::trunc);
		int recaddr;
		for (int i = 0; i < index; i++) {
			if ((recaddr = LectureFile.Write(lectureArr[i])) == -1)
				cout << "Write Error!" << endl;
		}
		LectureFile.Close();
		cout << "Deleting Complete from fileOfLecture.dat" << endl;
	}
	ifs.close();
}

void DeletePurchase(string want_ID) {
	index = 0;
	ifstream ifs("fileOfPurchase.dat");
	if (ifs.fail()) {
		cout << "fileOfPurchase.dat open error!" << endl;
		return;
	}
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	Purchase m;
	int ifs_last;
	int find_ID = 0;
	DelimFieldBuffer buffer('|', 1000);
	RecordFile <Purchase> PurchaseFile(buffer);
	PurchaseFile.Open("fileOfPurchase.dat", ios::in);
	//PurchaseFile.
	ifs.clear();	//because of c++98
	ifs.seekg(0, ifs.end);
	ifs_last = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	while (ifs.tellg() < ifs_last) {
		PurchaseFile.Read(m);
		if (!strcmp(m.getPurchaseID(), want_ID.c_str())) {
			find_ID = 1;
			ifs.seekg(m.getLength(), ifs.cur);
		}
		else if (!strcmp(m.getLectureID(), want_ID.c_str())) {
			find_ID = 1;
			ifs.seekg(m.getLength(), ifs.cur);
		}
		else if (!m.getMemberID().compare(want_ID)) {
			find_ID = 1;
			ifs.seekg(m.getLength(), ifs.cur);
		}
		else {
			purchaseArr[index] = m;
			index += 1;
		}
		ifs.seekg(m.getLength(), ifs.cur);
	}
	PurchaseFile.Close();


	if (find_ID) {
		PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);
		int recaddr;
		for (int i = 0; i < index; i++) {
			if ((recaddr = PurchaseFile.Write(purchaseArr[i])) == -1)
				cout << "Write Error!" << endl;
		}
		PurchaseFile.Close();
		cout << "Deleting Complete from fileOfPurchase.dat" << endl;
	}
	ifs.close();
}

void ModifyingByID() {
	string want_ID;
	string filename;
	int find;
	cout << "Enter ID : ";
	cin >> want_ID;
	cout << "Enter file name : ";
	cin >> filename;
	find = SearchingByID(0, filename, want_ID);
	if (find == 1) {
		if (filename.compare("fileOfMember.dat") == 0) {
			index = 0;
			ifstream ifs("fileOfMember.dat");
			if (ifs.fail()) {
				cout << "fileOfMember.dat open error!" << endl;
				return;
			}
			ifs.ignore(numeric_limits<streamsize>::max(), '\n');

			Member m;
			int ifs_last;
			int find_ID = 0;
			DelimFieldBuffer buffer('|', 1000);
			RecordFile <Member> MemberFile(buffer);
			MemberFile.Open("fileOfMember.dat", ios::in);
			//MemberFile.
			ifs.clear();	//because of c++98
			ifs.seekg(0, ifs.end);
			ifs_last = ifs.tellg();
			ifs.seekg(0, ifs.beg);
			while (ifs.tellg() < ifs_last) {
				MemberFile.Read(m);
				if (!m.getID().compare(want_ID)) {
					find_ID = 1;
					string temp;
					char* update_temp = new char(100);
					cout << "New Password : ";
					cin >> temp;
					getchar();
					m.setPassword(temp);
					//fflush(stdin);

					cout << "New Name : ";
					cin.getline(update_temp, 100);
					temp = update_temp;
					m.setName(temp);
					//fflush(stdin);

					cout << "New Phone Number : ";
					cin >> temp;
					m.setPhoneNumber(temp);
					//fflush(stdin);

					cout << "New Address : ";
					cin >> temp;
					m.setAddress(temp);
					//fflush(stdin);

					cout << "New Mileage : ";
					cin >> update_temp;
					if (strlen(update_temp) != 10) {
						cout << "Wrong length" << endl;
						return;
					}
					m.setMileage(update_temp);
					//free(update_temp);
					ifs.seekg(m.getLength(), ifs.cur);
					cout << endl << endl;;
					cout << "update success!!!" << endl;
					cout << endl;
					cout << m;

				}
				memberArr[index] = m;
				index += 1;
				ifs.seekg(m.getLength(), ifs.cur);
				cout << ifs.tellg() << endl;
			}
			
			//MemberFile.Close();
			
			if (find_ID) {
				MemberFile.Create("fileOfMember.dat", ios::out | ios::trunc);
				int recaddr;
				for (int i = 0; i < index; i++) {
					if ((recaddr = MemberFile.Write(memberArr[i])) == -1)
						cout << "Write Error!" << endl;
				}
				MemberFile.Close();
			}
			ifs.close();
		}
		if (filename.compare("fileOfLecture.dat") == 0) {
			index = 0;
			ifstream ifs("fileOfLecture.dat");
			if (ifs.fail()) {
				cout << "fileOfLecture.dat open error!" << endl;
				return;
			}
			ifs.ignore(numeric_limits<streamsize>::max(), '\n');

			Lecture m;
			int ifs_last;
			int find_ID = 0;
			DelimFieldBuffer buffer('|', 1000);
			RecordFile <Lecture> LectureFile(buffer);
			LectureFile.Open("fileOfLecture.dat", ios::in);
			//TicketFile.
			ifs.clear();	//because of c++98
			ifs.seekg(0, ifs.end);
			ifs_last = ifs.tellg();
			ifs.seekg(0, ifs.beg);
			while (ifs.tellg() < ifs_last) {
				LectureFile.Read(m);
				if (!memcmp(m.getLectureID(), want_ID.c_str(), strlen(m.getLectureID()))) {
					find_ID = 1;
					string temp;
					char* update_temp = new char(100);
					int temp_i;
					cout << "New Subject : ";
					cin >> temp;
					m.setSubject(temp);

					cout << "New Level : ";
					cin >> update_temp;
					if (strlen(update_temp) != 1) {
						cout << "Wrong length" << endl;
						return;
					}
					m.setLevel(update_temp);

					cout << "New Price : ";
					cin >> temp_i;
					m.setPrice(temp_i);

					cout << "New Extension : ";
					cin >> update_temp;
					if (strlen(update_temp) != 1) {
						cout << "Wrong length" << endl;
						return;
					}
					m.setExtension(update_temp);

					cout << "New Due Date : ";
					cin >> temp_i;
					m.setDueDate(temp_i);
					
					cout << "New NameOfTeacher : ";
					cin >> temp;
					m.setNameOfTeacher(temp);

					cout << "New TextBook : ";
					cin >> temp;
					m.setTextBook(temp);

					ifs.seekg(m.getLength(), ifs.cur);

					cout << endl << endl;;
					cout << "update success!!!" << endl;
					cout << endl;
					cout << m;
				}
				lectureArr[index] = m;
				index += 1;
				ifs.seekg(m.getLength(), ifs.cur);
			}
			LectureFile.Close();


			if (find_ID) {
				LectureFile.Create("fileOfLecture.dat", ios::out | ios::trunc);
				int recaddr;
				for (int i = 0; i < index; i++) {
					if ((recaddr = LectureFile.Write(lectureArr[i])) == -1)
						cout << "Write Error!" << endl;
				}
				LectureFile.Close();
			}
			ifs.close();
		}
		if (filename.compare("fileOfPurchase.dat") == 0) {
			index = 0;
			ifstream ifs("fileOfPurchase.dat");
			if (ifs.fail()) {
				cout << "fileOfPurchase.dat open error!" << endl;
				return;
			}
			ifs.ignore(numeric_limits<streamsize>::max(), '\n');

			Purchase m;
			int ifs_last;
			int find_ID = 0;
			DelimFieldBuffer buffer('|', 10000);
			RecordFile <Purchase> PurchaseFile(buffer);
			PurchaseFile.Open("fileOfPurchase.dat", ios::in);
			//PurchaseFile.
			ifs.clear();	//because of c++98
			ifs.seekg(0, ifs.end);
			ifs_last = ifs.tellg();
			ifs.seekg(0, ifs.beg);
			while (ifs.tellg() < ifs_last) {
				PurchaseFile.Read(m);
				if (!strcmp(m.getPurchaseID(), want_ID.c_str()) || !strcmp(m.getLectureID(), want_ID.c_str()) || !m.getMemberID().compare(want_ID)) {
					find_ID = 1;
					char* update_temp = new char(100);
					cout << "New Mileage : ";
					cin >> update_temp;
					if (strlen(update_temp) != 10) {
						cout << "Wrong length" << endl;
						return;
					}
					m.setMileage(update_temp);
					//free(update_temp);
					ifs.seekg(m.getLength(), ifs.cur);
					cout << endl << endl;;
					cout << "update success!!!" << endl;
					cout << endl;
					cout << m;
				}
				purchaseArr[index] = m;
				index += 1;
				ifs.seekg(m.getLength(), ifs.cur);
			}
			PurchaseFile.Close();
			if (find_ID) {
				PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);
				int recaddr;
				for (int i = 0; i < index; i++) {
					if ((recaddr = PurchaseFile.Write(purchaseArr[i])) == -1)
						cout << "Write Error!" << endl;
				}
				PurchaseFile.Close();
			}
			ifs.close();
		}
		cout << endl << "Modifying Complete" << endl << endl;
	}
	else
		cout << "This id doesn't exist." << endl;
}
