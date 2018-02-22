// Zadatak sa studentima i ispitima (operator).cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class Student {
	char * _imePrezime;

public:
	Student(const char * ip = "Nepoznato")
	{
		_imePrezime = new char[strlen(ip) + 1];
		strcpy_s(_imePrezime, strlen(ip) + 1, ip);
	}
	~Student()
	{
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	void info()
	{
		cout << "Student: " << _imePrezime << endl;
	}
};

class IspitnePrijave {

	Student * _niz[50];
	int trenutno;
public:
	IspitnePrijave()
	{
		trenutno = 0;
		for (int i = 0; i < 50; i++)
			_niz[i] = nullptr;
	}
	~IspitnePrijave()
	{
		for (int i = 0; i < trenutno; i++)
		{
			delete[] _niz[i]; _niz[i] = nullptr;
		}
	}
	bool AddStudent(Student * s)
	{
		if (trenutno >= 50)
			return false;
		_niz[trenutno++] = s;
		return true;
	}

	void info()
	{
		cout << "Ispite su prijavili sljedeci studenti: "<<endl;
		for (int i = 0; i < trenutno; i++)
		{
			_niz[i]->info();
		}
	}
};





int main()
{
	Student * s1 = new Student("Velid Duranovic");
	Student * s2 = new Student("Jusuf Duranovic");
	Student *s3 = new Student("Salvedin Duranovic");

	IspitnePrijave ispit;
	if (ispit.AddStudent(new Student("Velid Duranovic")))
		cout << "Student Velid je prijavio ispit\n";

	if (ispit.AddStudent(new Student("Jusuf Duranovic")))
		cout << "Student Jusuf je prijavio ispit\n";

	if (ispit.AddStudent(new Student("Salvedin Duranovic")))
		cout << "Student Salvedin je prijavio ispit\n";
	cout << endl << endl;
	ispit.info();

	system("pause>0");
    return 0;
}

