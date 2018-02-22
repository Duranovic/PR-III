// ConsoleApplication1.cpp : Defines the entry point for the console application.
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
	//Operator provjere '=='
	friend bool operator == (const Student &, const Student & );
};

bool operator== (const Student  &obj1, const Student &obj2)
{
	if (strcmp(obj1._ime, obj2._ime) == 0)
		return true;
	return false;
}


int main()
{
	Student a("Velid");
	Student b("Jusuf");
	Student c("Velid");
	cout << "a: "; a.info();
	cout << "b: "; b.info();
	cout << "c: "; c.info();

	if (a == b)
		cout << "a == b";
	else if (a == c)
		cout << "a = c";



	system("pause>0");
    return 0;
}

