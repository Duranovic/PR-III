// Operator dodjele (=).cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

const char * crt = "\n-------------------------------------\n";
class Student {
	char * _ime;
	int _godina;

public:
	//Konstruktor
	Student(int godina,const char * ime = "-")
	{
		_ime = new char[strlen(ime) + 1];
		strcpy_s(_ime, strlen(ime) + 1, ime);
		_godina = godina;
	}
	//Konstruktor kopije
	Student (const Student & original)
	{
		_ime = new char[strlen(original._ime) + 1];
		strcpy_s(_ime, strlen(original._ime) + 1, original._ime);
		_godina = original._godina;
	}
	//Destruktor
	~Student()
	{
		delete[] _ime; _ime = nullptr;
	}
	//Funkcija za ispis
	void info()
	{
		cout << "Ime: " << _ime << "   Godina: " << _godina<<crt;
	}
	//Funkcija Set
	void podesi(int godina, const char * ime)
	{
		_ime = new char[strlen(ime) + 1];
		strcpy_s(_ime, strlen(ime) + 1, ime);
		_godina = godina;
		
	}
	//Operator dodjele '='
	Student &operator = (const Student &original)
	{
		if (this != &original)
		{
			delete[] _ime; _ime = NULL;
			_ime = new char[strlen(original._ime) + 1];
			strcpy_s(_ime, strlen(original._ime) + 1, original._ime);
			_godina = original._godina;
			return *this;
		}
	}
};

int main()
{
	Student a(19, "Velid");
	a.info();
	Student b(a);
	b.info();
	a.podesi(27,"Sicko");
	cout << crt << crt;
	a.info();
	b.info();




	Student v(19, "Velid");
	v.info();
	Student s(26, "Salvedin");
	s.info();
	cout << crt <<"V = S"<< crt;
	v = s;
	v.info();
	s.info();

	system("pause>0");
    return 0;
}

