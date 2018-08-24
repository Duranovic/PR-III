// Zadatak 001 - Printer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <regex>
#include <exception>
#include <thread>


using namespace std;



const char *crt = "\n---------------------------------------\n";

class DatumVrijeme {
	int *_dan, *_mjesec, *_godina, *_sati, *_minuti;
public:
	// Konstruktor
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minuti = new int(minuti);
	}
	// Konstruktor kopije
	DatumVrijeme(const DatumVrijeme & obj)
	{
		_dan = new int (*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
		_sati = new int(*obj._sati);
		_minuti = new int(*obj._minuti);
	}
	// Destruktor
	~DatumVrijeme() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;

	}
	// Operator <<
	friend ostream& operator<< (ostream &COUT, const DatumVrijeme &obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti;
		return COUT;
	}
	// Operator =
	DatumVrijeme & operator = (const DatumVrijeme & obj)
	{
		if (this != &obj)
		{
			delete _dan, _mjesec, _godina, _sati, _minuti;
			_dan = new int(*obj._dan);
			_mjesec = new int(*obj._mjesec);
			_godina = new int(*obj._godina);
			_sati = new int(*obj._sati);
			_minuti = new int(*obj._minuti);
		}
		return *this;
	}

	bool Isti(const DatumVrijeme &dv)
	{
		if (*_godina == *dv._godina && *_mjesec == *dv._mjesec && *_dan == *dv._dan && *_sati == *dv._sati)
			return true;
		return false;
	}

};

template<class T1, class T2 = int>
class FITKolekcija {
	T1 * _elementi1;
	T2 * _elementi2;
	int _trenutno;
public:
	// Defaultni konstruktor
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

	// Geteri
	T1 * GetT1()const { return _elementi1; }
	T2 * GetT2()const { return _elementi2; }
	int GetTrenutno() const { return _trenutno; }

	// Operator <<
	friend ostream& operator<< (ostream &COUT, const FITKolekcija &obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj._elementi1[i] << " " << obj._elementi2[i] << endl;
		return COUT;
	}

	// Funkcija dodaj
	void Dodaj(const T1 &element1, const T2 &element2)
	{
		T1 * temp1 = new T1[_trenutno + 1];
		T2 * temp2 = new T2[_trenutno + 1];
		for (size_t i = 0; i < _trenutno; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		temp1[_trenutno] = element1;
		temp2[_trenutno] = element2;
		
		delete[] _elementi1; _elementi1 = temp1;
		delete[] _elementi2; _elementi2 = temp2;

		temp1 = nullptr;
		temp2 = nullptr;
		_trenutno++;
	}

	// Funkcija dodaj na lokaciju
	void DodajNaLokaciju(const T1 &element1, const T2 &element2, int lokacija)
	{
		if (lokacija > _trenutno - 1)
			return;
		_elementi1[lokacija] = element1;
		_elementi2[lokacija] = element2;
	}

	// Funkcija Soritraj
	void Sortiraj()
	{
		for (size_t i = 1; i < _trenutno; i++)
		{
			int j = i;
			while (j > 0)
			{
				if (_elementi1[j - 1] > _elementi1[j])
				{
					T1 temp1 = _elementi1[j - 1];
					_elementi1[j - 1] = _elementi1[j];
					_elementi1[j] = temp1;
					T2 temp2 = _elementi2[j - 1];
					_elementi2[j - 1] = _elementi2[j];
					_elementi2[j] = temp2;
				}
				j--;
			}
		}
	}

	FITKolekcija<T1, T2> * GetJedinstveni()
	{
		FITKolekcija<T1, T2> * povratna = new FITKolekcija<T1, T2>;
		for (size_t i = 0; i < _trenutno - 1; i++)
		{
			for (size_t j = i + 1; j < _trenutno; j++)
			{
				if ((_elementi1[i] != _elementi1[j]) || (_elementi2[i] != _elementi2[j]))
				{
					povratna->Dodaj(_elementi1[i], _elementi2[i]);
				}

			}
			// Kraj j for petlje
		}
		// Kraj i for petlje

		return povratna;
		// Kraj funkcije
	}


};

enum vrstaDokumenta { PDF, DOC, TXT, HTML };
string vrstaDokumentaString[4] = { "pdf", "doc", "txt", "html" };

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
	string GetNaziv() { return _naziv; };
	string GetSadrzaj() { return _sadrzaj; };
	vrstaDokumenta GetVrsta() { return _vrsta; };
	void UvecajBrojStranica() { _brojStranica++; }
	int GetBrojStranica() { return _brojStranica; }

	// Operator <<
	friend ostream & operator<<(ostream&COUT, Dokument & obj) {
		COUT << obj._naziv << "." << obj._vrsta << " (" << obj._brojStranica << ")\n" << obj._sadrzaj << endl;
		return COUT;
	}


	// Funkcija Dodaj Sadrzaj
	void DodajSadrzaj(string sadrzaj)
	{
		if (_sadrzaj.empty())
			_sadrzaj = sadrzaj;
		else
			_sadrzaj += sadrzaj;

		int velicinaSadrzaja = _sadrzaj.length();
		while (velicinaSadrzaja > 0)
		{
			_brojStranica++;
			velicinaSadrzaja -= 30;
		}
	}

};
class Uredjaj {
protected:
	char * _proizvodjac;
	char * _model;
public:
	// Konstruktor sa parametrima
	Uredjaj(const char * proizvodjac, const char * model) {
		int vel = strlen(proizvodjac) + 1;
		_proizvodjac = new char[vel];
		strcpy_s(_proizvodjac, vel, proizvodjac);
		vel = strlen(model) + 1;
		_model = new char[vel];
		strcpy_s(_model, vel, model);
	}

	// Destruktor
	~Uredjaj() {
		delete[] _proizvodjac; _proizvodjac = nullptr;
		delete[] _model; _model = nullptr;
	}

	// Operator <<
	friend ostream & operator<<(ostream&COUT, Uredjaj & obj) {
		COUT << obj._proizvodjac << "." << obj._model << endl;
		return COUT;
	}
};
class Printer : public Uredjaj {
	FITKolekcija<DatumVrijeme, Dokument> _printaniDokumenti;
	vector<string> _zabranjeneRijeci;
public:
	// Konstruktor
	Printer(const char * proizvodjac, const char * model) :Uredjaj(proizvodjac, model)
	{

	}
	// Funkcija Dodaj Zabranjenu Rijec
	void DodajZabranjenuRijec(string rijec)
	{
		vector<string>::iterator it (_zabranjeneRijeci.begin());
		while (it != _zabranjeneRijeci.end())
		{
			if (*it == rijec)
			{
				cout << "Zabranjena rijec: " << rijec << " vec posotji!\n";
				return;
			}
			it++;
		}
		_zabranjeneRijeci.push_back(rijec);
		cout << "Dodana zabranjena rijec: " << rijec << ".\n";
		
	}

	void Printaj(const DatumVrijeme &dv, Dokument d)
	{
		bool ne_valja = false;
		string praviloNazivDokumenta =  ".*\\.(" + vrstaDokumentaString[0] + "|" + vrstaDokumentaString[1] + "|" + vrstaDokumentaString[2] + vrstaDokumentaString[3] + ")";
		string praviloSLova = "(?=.*[a-zA-Z]{5,15})";

		if (regex_search(d.GetNaziv(), regex(praviloSLova)) == false)
		{
			cout << "Naziv dokumenta ne zadovoljava sljedece pravilo: "<< praviloSLova<<"\n";
			ne_valja = true;
		}
		if (regex_search(d.GetNaziv(), regex(praviloNazivDokumenta)) == false)
		{
			cout << "Naziv dokumenta ne zadovoljava sljedece pravilo: " << praviloNazivDokumenta << "\n";
			ne_valja = true;
		}
		if (ne_valja == true)
		{
			return;
		}

		string praviloZabranjeneRijeci = "(";

		vector<string>::iterator it(_zabranjeneRijeci.begin());
		while (it != _zabranjeneRijeci.end())
		{
			praviloZabranjeneRijeci += ("\\b" + (*it) + "\\b");
			if (it != _zabranjeneRijeci.end() - 1)
				praviloZabranjeneRijeci += "|";
			it++;
		}
		praviloZabranjeneRijeci += ")";



		if (regex_search(d.GetSadrzaj(), regex(praviloZabranjeneRijeci)) == true)
		{
			_printaniDokumenti.Dodaj(dv, d);
			exception izuzetak("Pronadjene zabranjene rijeci!\n");
			throw izuzetak;
		}
		else
		{
			cout<<d.GetSadrzaj();
		}


		/*
			2. SADRŽAJ DOKUMENTA U SEBI NE SMIJE POSJEDOVATI NITI JEDNU ZABRANJENU RIJEČ
			UKOLIKO NEKI OD NAVEDENIH USLOVA NIJE ZADOVOLJEN FUNKCIJA TREBA DA BACI EXCEPTION SA
			ODGOVARAJUĆOM PORUKOM, ALI ĆE DOKUMENT BITI POHRANJEN U KOLEKCIJU _printaniDokumenti.
			UKOLIKO DOKUMENT ISPUNJAVA SVE USLOVE ZA PRINTANJE POTREBNO JE NA KONZOLU ISPISATI
			SADRŽAJ DOKUMENTA KOJI SE PRINTA
		*/




	}

	float GetProsjecanBrojStranicaPoDatumu(const DatumVrijeme &datum)
	{
		DatumVrijeme * datumi = _printaniDokumenti.GetT1();
		Dokument * dokumenti = _printaniDokumenti.GetT2();
		int suma = 0;
		int brojDatuma = 0;
		float prosjek = 0;
		
		for (size_t i = 0; i < _printaniDokumenti.GetTrenutno(); i++)
		{
			if (datumi[i].Isti(datum))
			{
				suma += dokumenti->GetBrojStranica();
				brojDatuma++;
			}
		}

		prosjek = (float)suma / (float)brojDatuma;
		datumi = nullptr;
		dokumenti = nullptr;
		return prosjek;
	}

	string GetTopZabranjenuRijec()
	{
		Dokument * dokumenti = _printaniDokumenti.GetT2();
		return "NisamSiguranStaTreba:)";
	}

	void UkloniDokumente()
	{

	}

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

	Printer hp3200("HP", "3200");
	//PRINTER NEĆE DOZVOLITI PRINTANJE DOKUMENATA U ČIJEM SADRŽAJU SE NALAZI NEKA OD ZABRANJENIH RIJEČI
	hp3200.DodajZabranjenuRijec("RE");// :)
	hp3200.DodajZabranjenuRijec("RAT");
	hp3200.DodajZabranjenuRijec("UBITI");
	hp3200.DodajZabranjenuRijec("RE");// ONEMOGUĆITI PONAVLJANJE ZABRANJENIH RIJEČI, KORISTITI ITERATORE
	hp3200.DodajZabranjenuRijec("MRZITI");
	try
	{
		/*
		DA BI PRINTER ISPRINTAO NEKI DOKUMENT MORAJU BITI ZADOVOLJENA SLJEDEĆA PRAVILA:
		1. NAZIV DOKUMENTA MORA BITI U SLJEDEĆEM FORMATU npr: ispitPRIII.doc
		NAZIV DOKUMENTA MOŽE SADRŽAVATI SAMO SLOVA (NAJMANJE 5, NAJVIŠE 15), A EKSTENZIJA MOŽE
		BITI SAMO NEKA OD DOZVOLJENIH VRSTOMDOKUMENTA
		2. SADRŽAJ DOKUMENTA U SEBI NE SMIJE POSJEDOVATI NITI JEDNU ZABRANJENU RIJEČ
		UKOLIKO NEKI OD NAVEDENIH USLOVA NIJE ZADOVOLJEN FUNKCIJA TREBA DA BACI EXCEPTION SA
		ODGOVARAJUĆOM PORUKOM, ALI ĆE DOKUMENT BITI POHRANJEN U KOLEKCIJU _printaniDokumenti.
		UKOLIKO DOKUMENT ISPUNJAVA SVE USLOVE ZA PRINTANJE POTREBNO JE NA KONZOLU ISPISATI
		SADRŽAJ DOKUMENTA KOJI SE PRINTA

		*/

		/*thread thread_print_1(&Printer::Printaj, hp3200, danas, ispitPRIII);
		thread thread_print_2(&Printer::Printaj, hp3200, danas, ispitBaze);*/
		hp3200.Printaj(danas, ispitPRIII);
		hp3200.Printaj(danas, ispitBaze);

		/*
		IMPLEMENTIRATI PRINTANJE U ZASEBNIM NITIMA UZ KORIŠTENJE sleep_for FUNKCIJE
		VODITI RAČUNA O DIJELJENJU ZAJEDNIČKIH RESURSA
		*/

	}
	catch (exception& err)
	{
		cout << err.what() << endl;
	}

	//KOD POREĐENJA DATUMA PRINTANJA NIJE POTREBNO POREDITI MINUTE, SAMO DATUM I SATE
	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp3200.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	cout << "Najcesce koristena zabranjena rijec je -> " << hp3200.GetTopZabranjenuRijec() << crt;

	Printer hp4000(hp3200);
	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp4000.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	cout << "Najcesce koristena zabranjena rijec je -> " << hp4000.GetTopZabranjenuRijec() << crt;
	hp4000.UkloniDokumente();//UKLANJA SVE DOKUMENTE KOJI NISU ZADOVOLJILI USLOVE ZA PRINTANJE
	cout << hp4000 << crt;

#pragma endregion

	system("pause>0");
}