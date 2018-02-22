// Objekat klase u drugoj klasi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

//Jednostavna klasa Student
class Student {
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

	//Funkcija za ispis studenta
	void info()
	{
		cout << "Student ime: "<<_ime<<endl;
	}
};

class Projekat {
	char * _naziv;
	Student s1; // Objekat u statickoj memoriji
	Student * s2; // Objekat u dinamickoj memoriji

public:
	//Konstruktor
	Projekat(const char * naziv, const char * ime1, const char * ime2) : s1(ime1) // , s2(new Student(ime2)),,,moze i ovo
	{
		_naziv = new char[strlen(naziv) + 1];
		strcpy_s(_naziv, strlen(naziv) + 1, naziv);
		s2 = new Student(ime2);
	}

	//Destruktor
	~Projekat()
	{
		delete[] _naziv; _naziv = NULL;
		delete s2; s2 = NULL;
	}

	//Funkcija za ispis
	void Info()
	{
		cout << "Naziv projekta: " << _naziv << endl;
		s1.info();
		s2->info();
	}

};



int main()
{
	Projekat p("Ucenje", "Velid", "Salvedin");
	p.Info();





	system("pause>0");
    return 0;
}

