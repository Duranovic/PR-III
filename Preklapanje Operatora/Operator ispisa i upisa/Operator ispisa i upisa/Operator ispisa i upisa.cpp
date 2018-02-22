// Operat*or ispisa i upisa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class  Student {
	char * _ime;
public:
	//Konstruktor
	Student(const char * ime)
	{
		_ime = new char[strlen(ime) + 1];
		strcpy_s(_ime, strlen(ime) + 1, ime);
	}
	//Destruktor
	~Student()
	{
		delete[] _ime; _ime = NULL;
	}
	//Ispis
	void info()
	{
		cout << "Ime: " << _ime << endl;
	}
	//Operator ispisa
	friend ostream & operator << (ostream &COUT, const Student &s);
	friend istream & operator >> (istream &CIN, Student & s);
	char * getIme()
	{
		return _ime;
	}
};

ostream & operator << (ostream &COUT, const Student & s)
{
	COUT <<"Ime: "<< s._ime << endl;
	return COUT;
}
istream & operator >> (istream &CIN, Student & s)
{
	int vel;
	char * temp = new char[50];
	cout << "Unesi ime: ";
	cin >> temp;
	vel = strlen(temp) + 1;
	delete[]s._ime;
	s._ime = new char[vel];
	strcpy_s(s.getIme(), vel, temp);
	return CIN;
}

int main()
{
	Student s("Salvedin");
	Student v("Velid");
	cout << s;
	cout << v;
	cin >> s >> v;
	cout << s<<v;

	system("pause>0");
    return 0;
}

