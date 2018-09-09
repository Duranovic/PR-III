// Zadatak 001 - Printer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;


const char *crt = "\n---------------------------------------\n";

class DatumVrijeme {
	int *_dan, *_mjesec, *_godina, *_sati, *_minuti;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minuti = new int(minuti);

	}

	// Konstruktor kopije
	DatumVrijeme(const DatumVrijeme & obj) {
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
		_sati = new int(*obj._sati);
		_minuti = new int(*obj._minuti);
	}
	~DatumVrijeme() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;

	}

	// Operator dodjele
	DatumVrijeme & operator = (const DatumVrijeme & obj) {
		if (this != &obj)
		{
			*_dan = *obj._dan;
			*_mjesec = *obj._mjesec;
			*_godina = *obj._minuti;
			*_sati = *obj._sati;
			*_minuti = *obj._minuti;
		}
		return *this;
	}
	friend ostream& operator<< (ostream &COUT, DatumVrijeme &obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti;
		return COUT;
	}
};



template<class T1, class T2 = int>
class FITKolekcija {
	T1 * _elementi1;
	T2 * _elementi2;
	int _trenutno;
public:
	// Konstruktor
	FITKolekcija() {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}

	// Destruktor
	~FITKolekcija() {
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi2 = nullptr;
	}

	// Metoda dodaj
	void Dodaj(T1 el1, T2 el2) {
		T1 * temp1 = new T1[_trenutno + 1];
		T2 * temp2 = new T2[_trenutno + 1];

		for (size_t i = 0; i < _trenutno; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		temp1[_trenutno] = el1;
		temp2[_trenutno] = el2;
		_trenutno++;

		delete[] _elementi1; _elementi1 = temp1;
		delete[] _elementi2; _elementi2 = temp2;
		temp1 = nullptr;
		temp2 = nullptr;
	}

	// Metoda dodaj na lokaciju proširuje niz i dodaje element na lokaciju, svi elemenit iza se pomijeraju za jedan index
	void DodajNaLokaciju(T1 ele1, T2 ele2, int lokacija) {
		if (lokacija >= _trenutno || lokacija < 0)
			return;
		T1 * temp1 = new T1[_trenutno + 1];
		T2 * temp2 = new T2[_trenutno + 1];
		_trenutno++;
		for (size_t i = 0; i < lokacija; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		temp1[lokacija] = ele1;
		temp2[lokacija] = ele2;
		for (size_t i = lokacija + 1; i < _trenutno; i++)
		{
			temp1[i] = _elementi1[i - 1];
			temp2[i] = _elementi2[i - 1];
		}

		_elementi1 = temp1;
		_elementi2 = temp2;
	}
	
	// Metoda dodaj na lokaciju - metoda je uradjena na način da samo prepiše vrijednost koja se nalazi na zadanoj lokaciji
	// Ako je na lokaciji 2 bila vrijednost 5, sada ce biti vrijednost recimo 18, vrijednosti na ostalim lokacijama se ne mijenjaju
	void DodajNaLokacijuRewrite(T1 ele1, T2 ele2, int lokacija)
	{
		if (lokacija >= _trenutno || lokacija < 0)
			return;
		_elementi1[lokacija] = ele1;
		_elementi2[lokacija] = ele2;
	}

	// Metoda sortiraj
	void Sortiraj()
	{
		for (size_t i = 1; i < _trenutno; i++)
		{
			int j = i;
			while (j > 0 && _elementi1[j-1] > _elementi1[j])
			{
				T1 temp1 = _elementi1[j];
				_elementi1[j] = _elementi1[j - 1];
				_elementi1[j - 1] = temp1;
				T2 temp2 = _elementi2[j];
				_elementi2[j] = _elementi2[j - 1];
				_elementi2[j - 1] = temp2;
				j--;
			}
		}
	}

	// Metoda GetJedinstveni
	FITKolekcija<T1, T2> * GetJedinstveni() {
		FITKolekcija<T1, T2>* povratnaKolekcija = nullptr;
		int brojac = 0;
	
		for (size_t i = 0; i < _trenutno; i++)
		{
			bool jedinstven = true;

			for (size_t j = 0; j < _trenutno; j++)
			{
				if (i != j)
				{
					if (_elementi1[i] == _elementi1[j] && _elementi2[i] == _elementi2[j])
					{
						jedinstven = false;
					}
				}
			} // kraj j petlje
			if (povratnaKolekcija == nullptr)
			{
				povratnaKolekcija = new FITKolekcija<T1, T2>;
			}
			if (jedinstven == true)
			{
				povratnaKolekcija->Dodaj(_elementi1[i], _elementi2[i]);
			}

		} // kraj i petlje

		return povratnaKolekcija;

	}

	//Geteri
	T1 * GetT1() { return _elementi1; }
	T2 * GetT2() { return _elementi2; }
	int GetTrenutno() { return _trenutno; }

	// Operator ispisa
	friend ostream& operator<< (ostream &COUT, FITKolekcija &obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj._elementi1[i] << " " << obj._elementi2[i] << endl;
		return COUT;
	}

	/*FITKolekcija<T1, T2> operator = (const FITKolekcija<T1, T2> & obj)
	{
		
	}*/
};

enum vrstaDokumenta { PDF, DOC, TXT, HTML };

class Dokument {
	vrstaDokumenta _vrsta;
	string _naziv;
	string _sadrzaj;
	int _brojStranica;
public:
	// Defaultni konstruktor
	Dokument() { _brojStranica = 0; }

	// Konstruktor sa parametrima
	Dokument(vrstaDokumenta vrsta, string naziv) {
		_naziv = naziv; _vrsta = vrsta; _brojStranica = 0;
	}

	//  Geteri
	string GetNaziv() { return _naziv; };
	string GetSadrzaj() { return _sadrzaj; };
	vrstaDokumenta GetVrsta() { return _vrsta; };
	void UvecajBrojStranica() { _brojStranica++; }
	int GetBrojStranica() { return _brojStranica; }

	// Operator ispisa
	friend ostream & operator<<(ostream&COUT, Dokument & obj) {
		COUT << obj._naziv << "." << obj._vrsta << " (" << obj._brojStranica << ")\n" << obj._sadrzaj << endl;
		return COUT;
	}

	// Funkcija dodaj sadrzaj
	void DodajSadrzaj(string sadrzaj)
	{
		_sadrzaj += sadrzaj;
		int brojac = _sadrzaj.size();
		while (brojac > 0)
		{
			UvecajBrojStranica();
			brojac -= 30;
		}
	
	}
};
class Uredjaj {
protected:
	char * _proizvodjac;
	char * _model;
public:
	Uredjaj(char * proizvodjac, char * model) {
		int vel = strlen(proizvodjac) + 1;
		_proizvodjac = new char[vel];
		strcpy_s(_proizvodjac, vel, proizvodjac);
		vel = strlen(model) + 1;
		_model = new char[vel];
		strcpy_s(_model, vel, model);
	}
	~Uredjaj() {
		delete[] _proizvodjac; _proizvodjac = nullptr;
		delete[] _model; _model = nullptr;
	}
	friend ostream & operator<<(ostream&COUT, Uredjaj & obj) {
		COUT << obj._proizvodjac << "." << obj._model << endl;
		return COUT;
	}
};
class Printer {
	FITKolekcija<DatumVrijeme, Dokument> _printaniDokumenti;
	vector<string> _zabranjeneRijeci;
public:
	FITKolekcija<DatumVrijeme, Dokument> & GetPrintaniDokumenti() { return _printaniDokumenti; };
	vector<string> & GetZabranjeneRijeci() { return _zabranjeneRijeci; };
};

void main()
{
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
	****************************************************************************/

#pragma region TestiranjeDatumVrijeme
	DatumVrijeme danas(1, 2, 2017, 10, 15);
	DatumVrijeme sutra(danas);
	DatumVrijeme prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region FITKolekcija
	int v6 = 6, v13 = 13, v32 = 32, v63 = 63, v98 = 98, v109 = 109, v196 = 196;

	FITKolekcija<int, int> brojevi;
	brojevi.Dodaj(v196, v6);
	brojevi.Dodaj(v13, v32);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v63, v13);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v196, v6);

	cout << brojevi << crt;
	//SORTIRANJE ČLANOVA KOLEKCIJE SE VRŠI U RASTUĆEM REDOSLIJEDU NA OSNOVU VRIJEDNOSTI ELEMENTA TIPA T1
	brojevi.Sortiraj();
	cout << brojevi << crt;
	//BROJ 2 SE ODNOSI NA LOKACIJU/INDEKS UNUTAR LISTE NA KOJI JE POTREBNO DODATI NOVE ELEMENTE
	brojevi.DodajNaLokaciju(v109, v6, 2);
	cout << brojevi << crt;
	brojevi.Sortiraj();
	cout << brojevi << crt;
	/*METODA GetJedinstveni VRAĆA LISTU JEDINSTVENIH ELEMENATA TJ. ELEMENATA KOJI NE SADRŽE DUPLIKATE (POJAM DUPLIKAT SE ODNOSI NA ISTE VRIJEDNOSTI ELEMENATA T1 I T2). ELEMENTI KOJI SE DUPLIRAJU SE U OVOJ LISTI TREBAJU POJAVITI SAMO JEDNOM.*/
	FITKolekcija<int, int> * jedinstveni = brojevi.GetJedinstveni();
	cout << *jedinstveni << crt;
	*jedinstveni = brojevi;
	cout << *jedinstveni << crt;

	Dokument ispitPRIII(DOC, "ispitPRIII.doc");
	//BROJ STRANICA DOKUMENTA SE AUTOMATSKI ODREĐUJE PRILIKOM DODAVANJA SADRŽAJA. ZA POTREBE ISPITA PRETPOSTAVLJAMO DA NA JEDNU STRANICU MOŽE STATI 30 ZNAKOVA UKLJUČUJUĆI I RAZMAKE
	ispitPRIII.DodajSadrzaj("NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO RE");
	cout << "Broj stranica -> " << ispitPRIII.GetBrojStranica() << endl;
	Dokument ispitBaze(DOC, "ispitBaze.doc");
	ispitBaze.DodajSadrzaj("PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT");
	cout << ispitBaze << endl;//ISPISUJE SVE DOSTUPNE PODATKE O DOKUMENTU

	//Printer hp3200("HP", "3200");
	////PRINTER NEĆE DOZVOLITI PRINTANJE DOKUMENATA U ČIJEM SADRŽAJU SE NALAZI NEKA OD ZABRANJENIH RIJEČI
	//hp3200.DodajZabranjenuRijec("RE");// :)
	//hp3200.DodajZabranjenuRijec("RAT");
	//hp3200.DodajZabranjenuRijec("UBITI");
	//hp3200.DodajZabranjenuRijec("RE");// ONEMOGUĆITI PONAVLJANJE ZABRANJENIH RIJEČI, KORISTITI ITERATORE
	//hp3200.DodajZabranjenuRijec("MRZITI");
	//try
	//{
	//	/*
	//	DA BI PRINTER ISPRINTAO NEKI DOKUMENT MORAJU BITI ZADOVOLJENA SLJEDEĆA PRAVILA:
	//	1. NAZIV DOKUMENTA MORA BITI U SLJEDEĆEM FORMATU npr: ispitPRIII.doc
	//	NAZIV DOKUMENTA MOŽE SADRŽAVATI SAMO SLOVA (NAJMANJE 5, NAJVIŠE 15), A EKSTENZIJA MOŽE
	//	BITI SAMO NEKA OD DOZVOLJENIH VRSTOMDOKUMENTA
	//	2. SADRŽAJ DOKUMENTA U SEBI NE SMIJE POSJEDOVATI NITI JEDNU ZABRANJENU RIJEČ
	//	UKOLIKO NEKI OD NAVEDENIH USLOVA NIJE ZADOVOLJEN FUNKCIJA TREBA DA BACI EXCEPTION SA
	//	ODGOVARAJUĆOM PORUKOM, ALI ĆE DOKUMENT BITI POHRANJEN U KOLEKCIJU _printaniDokumenti.
	//	UKOLIKO DOKUMENT ISPUNJAVA SVE USLOVE ZA PRINTANJE POTREBNO JE NA KONZOLU ISPISATI
	//	SADRŽAJ DOKUMENTA KOJI SE PRINTA

	//	*/
	//	hp3200.Printaj(danas, ispitPRIII);
	//	hp3200.Printaj(danas, ispitBaze);

	//	/*
	//	IMPLEMENTIRATI PRINTANJE U ZASEBNIM NITIMA UZ KORIŠTENJE sleep_for FUNKCIJE
	//	VODITI RAČUNA O DIJELJENJU ZAJEDNIČKIH RESURSA
	//	*/

	//}
	//catch (exception& err)
	//{
	//	cout << err.what() << endl;
	//}

	////KOD POREĐENJA DATUMA PRINTANJA NIJE POTREBNO POREDITI MINUTE, SAMO DATUM I SATE
	//cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp3200.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	//cout << "Najcesce koristena zabranjena rijec je -> " << hp3200.GetTopZabranjenuRijec() << crt;

	//Printer hp4000(hp3200);
	//cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp4000.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	//cout << "Najcesce koristena zabranjena rijec je -> " << hp4000.GetTopZabranjenuRijec() << crt;
	//hp4000.UkloniDokumente();//UKLANJA SVE DOKUMENTE KOJI NISU ZADOVOLJILI USLOVE ZA PRINTANJE
	//cout << hp4000 << crt;
	system("pause>0");
#pragma endregion

}






















// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
