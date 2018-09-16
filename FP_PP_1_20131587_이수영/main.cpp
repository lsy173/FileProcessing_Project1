#include <iostream>
#include <fstream>
#include <string>
#include "deltext.h"
#include "iobuffer.h"
#include "member.h"
#include "lecture.h"
#include "purchase.h"
#include "buffile.h"

using namespace std;

void showMenu(void);
void showMember(void);
void showLecture(void);
void showPurchase(void);
void MemberTest(void);
void LectureTest(void);
void PurchaseTest(void);
void LecturePurchaseSystem(void);
void showSystemMenu(void);
int SearchingByID(int flag, string filename, string ID);
void InsertingByID(void);
void DeletingByID(void);
void ModifyingByID(void);
void DeleteMember(string ID);
void DeleteLecture(char* ID);
void DeletePurchase(char* ID);

Member* meberArr = new Member[12000];
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
		input = atoi(input.c_str());
		switch (input_int) {
		case 1: showMember(); break;
		case 2: showLecture(); break;
		case 3: showPurchase(); break;
		case 4: MemberTest(); break;
		case 5: LectureTest(); break;
		case 6: PurchaseTest(); break;
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
	cout << : "input : ";
}


void showMember() {
	ifstream ifs("listOfMember.txt");
	if (ifs.fail())
	{
		cout << "listOfMember.txt File Open Error!" << endl << endl;
		return;
	}
	int temp;
	ifs >> temp;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');
	//cout << temp << endl;
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
	int temp;
	ifs >> temp;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');
	//cout << temp << endl;
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
	//cout << temp << endl;
	for (int i = 0; i<10; i++)
	{
		Purchase M;
		ifs >> M;
		cout << M << endl;
	}
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
		MemberTest();
		LectureTest();
		PurchaseTest();
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
			ifs.seekg(m.get_length(), ifs.cur);
			if (!m.get_id().compare(want_ID)) {
				find_ID = 1;
				id_cnt += 1;
				break;
			}
			find_Addr += m.get_length();
		}
		MemberFile.Close();
		ifs.close();
	}
	else if (filename.compare("fileOfTicket.dat") == 0) {
		DelimFieldBuffer buffer('|', 1000);
		RecordFile <Ticket> TicketFile(buffer);
		TicketFile.Open("fileOfTicket.dat", ios::in);
		ifs.clear();
		ifs.seekg(0, ifs.end);
		ifs_last = ifs.tellg();
		ifs.seekg(0, ifs.beg);
		while (ifs.tellg() < ifs_last) {
			TicketFile.Read(t);
			ifs.seekg(t.get_length(), ifs.cur);
			if (!memcmp(t.get_id(), want_ID.c_str(), strlen(t.get_id()))) {
				find_ID = 2;
				id_cnt += 1;
				break;
			}
			find_Addr += t.get_length();
		}
		TicketFile.Close();
		ifs.close();

	}
	else if (filename.compare("fileOfPurchase.dat") == 0) {
		DelimFieldBuffer buffer('|', 1000);
		RecordFile <Purchase> PurchaseFile(buffer);
		PurchaseFile.Open("fileOfPurchase.dat", ios::in);
		ifs.clear();
		ifs.seekg(0, ifs.end);
		ifs_last = ifs.tellg();
		ifs.seekg(0, ifs.beg);

		while (ifs.tellg() < ifs_last) {
			PurchaseFile.Read(p);
			ifs.seekg(p.get_length(), ifs.cur);
			if (!strcmp(p.getPurchaseID(), want_ID.c_str())) {
				find_ID = 3;
				id_cnt += 1;
				break;
			}
			else if (!strcmp(p.get_TID(), want_ID.c_str())) {
				find_ID = 3;
				id_cnt += 1;
				break;
			}
			else if (!p.get_MID().compare(want_ID)) {
				find_ID = 3;
				id_cnt += 1;

				addr_arr = (int*)realloc(addr_arr, id_cnt * sizeof(int));
				p_arr[id_cnt - 1] = p;
				addr_arr[id_cnt - 1] = find_Addr;
			}
			find_Addr += p.get_length();
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
			case 2: cout << t; break;
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
