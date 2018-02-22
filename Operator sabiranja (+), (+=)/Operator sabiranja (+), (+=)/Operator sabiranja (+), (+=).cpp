// Operator sabiranja (+), (+=).cpp : Defines the entry point for the console application.
//
// Operator uglaste zagrade '()'.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;


class Broj {
	int broj;

public:
	//KONSTRUKTORI
	//.............................................................
	Broj()
	{
		broj = 0;
	}
	Broj(int b)
	{
		broj = b;
	}
	//.............................................................

	friend ostream &operator << (ostream &, const Broj &);
	friend istream & operator >> (istream &, Broj &);

	//operator sabiranja '+' mozemo kreirati kao globalnu f-ju sto je i bolje.
	Broj operator + (const Broj &broj)
	{
		return Broj(this->broj + broj.broj);
	}

	//drugi nacin implementacije
	friend Broj operator + (const Broj &, const Broj &);

	//OPERATOR '+='
	void operator += (const Broj &b)
	{
		this->broj += b.broj;
	}
};

//OPERATIR ISPISA
ostream &operator << (ostream & COUT, const Broj &b)
{
	COUT << b.broj;
	return COUT;
}

//OPERATOR UNOSA
istream & operator >> (istream & CIN, Broj &b)
{
	cout << "Unesi broj: ";
	CIN >> b.broj;
	return CIN;
}

//OPERATOR '+' 2.ver
Broj operator+(const Broj &lijevi, const Broj & desni)
{
	return Broj(lijevi.broj + desni.broj);
}






int main()
{
	// Bilo bi pozeljno da se kreira genericka klasa // int - float - ...

	Broj a, b, c;
	cin >> a >> b;
	c = a + b;
	cout << c;
	c += a;
	cout << endl<<c;



	system("pause>0");
	return 0;
}

