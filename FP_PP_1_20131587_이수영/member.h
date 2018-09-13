#include <iostream>
#include <string>

#define LENMIL 11
#define STDMAXBUF 256

using namespace std;

class Member {

private:
	string ID;
	string Password;
	string Name;
	string	Phone_Number;
	string Address;
	char Mileage[11];	

public:
	Member();
	Member(const char* new_id);
	Member(const Member &s);

	Member & operator = (const Member &s);
	bool operator == (const Member &s);
	bool operator != (const Member &s);

	friend istream & operator >> (istream &is, Member &s);
	friend ostream & operator << (ostream &os, Member &s);

	void update_ID(const string new_id) { ID = new_id; }
	void update_Password(const string new_password) { Password = new_password; }
	void update_Name(const string new_name) { Name = new_name; }
	void update_PhoneNumber(const string new_phone_number) { Phone_Number = new_phone_number; }
	void update_Address(const string new_address) { Address = new_address; }
	void update_Mileage(const char * new_mileage) { memcpy(Mileage, new_mileage, 11); }

	string get_id() {
		return ID;
	}
	string get_password() {
		return Password;
	}
	string get_name() {
		return Name;
	}
	string get_number() {
		return Phone_Number;
	}
	string get_address() {
		return Address;
	}
	char *get_mileage() {
		return Mileage;
	}
	int get_length() {
		return ID.size() + Password.size() + Name.size() + Phone_Number.size() + Address.size() + strlen(Mileage);
	}

	bool Pack(IOBuffer &Buffer) const;
	bool Unpack(IOBuffer &);

};


istream & operator >> (istream &is, Member &s);
ostream & operator << (ostream &os, Member &s);