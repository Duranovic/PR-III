// Operator uglaste zagrade '()'.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;


class Broj {
	int broj;

public:
	Broj()
	{
		broj = 0;
	}
	Broj(int b)
	{
		broj = b;
	}

	int info()
	{
		return broj;
	}
	friend ostream &operator << (ostream &,const Broj &);
	friend istream & operator >> (istream &, Broj &);

	//OPERATOR '()'
	void operator ()(const Broj broj1, const Broj broj2)
	{
		cout << "Primjenjuje se operator '()' za  ("<<broj1<<", "<<broj2<<")\n";
		int s = broj1.broj;
		for (int i = 0; i < broj2.broj; i++)
		{
			Sleep(3000);
			cout <<"("<<i+1<<")  "<< s << " * " << broj1.broj;
			s *= broj1.broj;
			cout<< " = " << s << endl;
		}
		broj = s;
		cout << "Broj je: " << broj;
	}

};

//OPERATIR ISPISA
ostream &operator << (ostream & COUT, const Broj &b)
{
	COUT << b.broj;
	return COUT;
}

//OPERATOR UNOSA
istream & operator >> (istream & CIN,  Broj &b)
{
	cout << "Unesi broj: ";
	CIN >> b.broj;
	return CIN;
}



int main()
{
	// Bilo bi pozeljno da se kreira genericka klasa // int - float - ...
	
	Broj a, b, c;
	cin >> a >> b;
	c(a, b);

	

	system("pause>0");
    return 0;
}

