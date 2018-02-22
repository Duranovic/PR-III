// Konstruktori.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

const char * crt = "\n-----------------------------------------------\n";



class Covjek {
	char * _ime;
	char * _prezime;
	int _godina;

public:
	//Defaultni konstruktor
	Covjek()
	{
		_ime = new char[2];
		strcpy_s(_ime, 2, "-");

		_prezime = new char[2];
		strcpy_s(_prezime, 2, "-");
		_godina = 0;
	}

	// Konstruktor koji prima 1 parametar
	Covjek(const char * ime)
	{
		_ime = new char[strlen(ime) + 1];
		strcpy_s(_ime, strlen(ime) + 1, ime);

		_prezime = new char[2];
		strcpy_s(_prezime, 2, "-");
		_godina = 18;
	}

	//Konstruktor koji prima 2 parametra
	Covjek(const char * ime, const char * prezime)
	{
		_ime = new char[strlen(ime) + 1];
		strcpy_s(_ime, strlen(ime) + 1, ime);
		_prezime = new char[strlen(prezime) + 1];
		strcpy_s(_prezime, strlen(prezime) + 1, prezime);
		_godina = 18;
	}

	//Konstruktor koji prima sve parametre
	Covjek(const char * ime, const char * prezime, int godina)
	{
		_ime = new char[strlen(ime) + 1];
		strcpy_s(_ime, strlen(ime) + 1, ime);
		_prezime = new char[strlen(prezime) + 1];
		strcpy_s(_prezime, strlen(prezime) + 1, prezime);
		_godina = godina;
	}

	//Konstruktor Kopije
	Covjek(Covjek & original)
	{
		_ime = new char[strlen(original._ime) + 1];
		strcpy_s(_ime, strlen(original._ime) + 1, original._ime);
		_prezime = new char[strlen(original._prezime) + 1];
		strcpy_s(_prezime, strlen(original._prezime) + 1, original._prezime);
		_godina = original._godina;
	}

	//Destruktor
	~Covjek()
	{
		delete[] _ime; _ime = nullptr;
		delete[] _prezime; _prezime = nullptr;
	}

	//Jednostavna f-ja za ispis
	void info()
	{
		cout << "Ime: " << _ime<<endl<<"Prezime: "<<_prezime<<endl<<"Godina: "<<_godina<<crt;
	}

};

int main()
{
	//Objekat se kreira bez argumenata
	Covjek c1; c1.info();
	
	//Objekat se kreira pomocu jednog argumenta
	Covjek c2("Velid"); c2.info();

	//Objekat se kreira pomocu dva argumenta
	Covjek c3("Velid", "Duranovic"); c3.info();

	//Objekat se kreira pomocu svih argumenata
	Covjek c4("Velid", "Duranovic", 19); c4.info();

	// Objekat se kreira pomocu drugog objekta
	Covjek c5(c4); c5.info();
	

	system("pause>0");
    return 0;
}

