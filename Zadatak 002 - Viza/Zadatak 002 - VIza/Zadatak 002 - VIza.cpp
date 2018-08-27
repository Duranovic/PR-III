// Zadatak 002 - VIza.cpp : Defines the entry point for the console application.
// FEBRUARSKI ROK

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

const char *crt = "\n-----------------------------------------------\n";

enum Status { ZAHTJEV_ZAPRIMLJEN, ODUSTAO, ODBIJENA, IZDATA, ISTEKLA, PONISTENA };
enum Sortiranje { RASTUCI, OPADAJUCI };
enum Drzava { SAD, AUSTRALIJA, ENGLESKA };

class Datum {
	int *_dan, *_mjesec, *_godina;
public:
	// Konstruktor
	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}
	// Konstruktor kopije
	Datum(const Datum & obj)
	{
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
	}

	//Destruktor
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}

	// Operator =
	Datum & operator = (const Datum & obj)
	{
		if (this != &obj)
		{
			*_dan = *obj._dan;
			*_mjesec = *obj._mjesec;
			*_godina = *obj._godina;
		}
		return *this;
	}

	// Operator <<
	friend ostream& operator<< (ostream &COUT, Datum &obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
		return COUT;
	}

	// Operator >
	bool operator < (const Datum & datum2)
	{
		if (*_godina <= *datum2._godina)
		{
			if (*_mjesec <= *datum2._mjesec)
			{
				if (*_dan < *datum2._dan)
					return true;
			}
		}
		return false;
	}

	// Operator ==
	friend bool operator == (const Datum & d1, const Datum & d2)
	{
		if (*d1._dan == *d2._dan && *d1._mjesec == *d2._mjesec && *d1._godina == *d2._godina)
		{
			return true;
		}
		return false;
	}

	// Operator ++obj
	Datum & operator ++ ()
	{
		if (*_dan == 30)
		{
			if (*_mjesec == 12)
			{
				*_godina = *_godina + 1;
			}
			else
			{
				*_mjesec = *_mjesec + 1;
			}
		}
		else
		{
			*_dan = *_dan + 1;
		}

		return *this;
	}

	// Geteri
	int GetDan() { return *_dan; }
	int GetMjesec() { return *_mjesec; }
	int GetGodina() { return *_godina; }

};

template<class T1, class T2, int max>
class FITKolekcija {
	T1 * _elementi1[max];
	T2 * _elementi2[max];
	int _trenutno;
public:
	// Defaultni konstruktor
	FITKolekcija() {
		for (size_t i = 0; i < max; i++) {
			_elementi1[i] = nullptr;
			_elementi2[i] = nullptr;
		}
		_trenutno = 0;
	}

	// Destruktor
	~FITKolekcija() {
		for (size_t i = 0; i < max; i++) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}
	}

	// Funkcija Dodaj
	void Dodaj(T1 element1, T2 element2)
	{
		if (_trenutno == max)
		{
			exception Izuzetak ("ERROR::Kolekcija je puna!\n");
			throw Izuzetak;
		}
		_elementi1[_trenutno] = new T1(element1);
		_elementi2[_trenutno] = new T2(element2);
		_trenutno++;
	}

	// Funkcija Sortiraj
	void Sortiraj(Sortiranje _sort)
	{
		for (size_t i = 0; i < _trenutno; i++)
		{
			int j = i;
			while (j > 0)
			{
				if ((_sort == RASTUCI && *_elementi1[j - 1] > *_elementi1[j]) || (_sort == OPADAJUCI && *_elementi1[j-1] < *_elementi1[j]))
				{
					T1 temp1 = *_elementi1[j - 1];
					*_elementi1[j - 1] = *_elementi1[j];
					*_elementi1[j] = temp1;

					T2 temp2 = *_elementi2[j - 1];
					*_elementi2[j - 1] = *_elementi2[j];
					*_elementi2[j] = temp2;
				}
				j--;
			}
		}
	}

	// Geteri
	T1 ** GetT1() { return _elementi1; }
	T2 ** GetT2() { return _elementi2; }
	int GetTrenutno() { return _trenutno; }


	// Operator <<
	friend ostream& operator<< (ostream &COUT, FITKolekcija &obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << *obj._elementi1[i] << " " << *obj._elementi2[i] << endl;
		return COUT;
	}
};


class Viza {
protected:
	Drzava _drzava;
	Datum _vazenjeOD;
	Datum _vazenjeDO;
	char * _napomena;
	// string se odnosi na razlog promjene statusa, a moguće je samo 10 izmjena statusa
	FITKolekcija<Status, string, 10> _statusi;
public:
	// Konstruktor
	Viza(Drzava drzava, Datum _OD, Datum _DO, const char * napomena = nullptr) :_vazenjeDO(_DO), _vazenjeOD(_OD)
	{
		if (napomena != nullptr) {
			_napomena = new char[strlen(napomena) + 1];
			strcpy_s(_napomena, strlen(napomena) + 1, napomena);
		}
		else
			_napomena = nullptr;
		_drzava = drzava;
	}

	Viza(const Viza &obj)
		:_vazenjeOD(obj._vazenjeOD), _vazenjeDO(obj._vazenjeDO)
	{
		this->_drzava = obj._drzava;
		this->_statusi = obj._statusi;
		_napomena = new char[strlen(obj._napomena) + 1];
		strcpy_s(_napomena, strlen(obj._napomena) + 1, obj._napomena);
	}

	// Destruktor
	~Viza() { delete[] _napomena; _napomena = nullptr; }

	// Geteri
	Datum GetVazenjeOD() { return _vazenjeOD; }
	Datum GetVazenjeDO() { return _vazenjeDO; }
	char * GetNapomena() { return _napomena; }
	Drzava GetDrzava() { return _drzava; }
	FITKolekcija<Status, string, 10> & GetStatuse() { return _statusi; }

	// Ispis
	virtual void Info() = 0;
};

class PoslovnaViza :public Viza {
	string _kompanija; //naziv kompanije koja potvrđuje da posluje sa aplikantom
public:

	// Konstruktor *************FITKOLEKCIJA****************
	PoslovnaViza(Drzava drzava, Datum _OD, Datum _DO, string kompanija, const char * napomena = nullptr) : Viza(drzava, _OD, _DO, napomena) {
		_kompanija = kompanija;
	}

	PoslovnaViza(const PoslovnaViza &obj )
		:Viza(obj._drzava, obj._vazenjeOD, obj._vazenjeDO, obj._napomena)
	{
		_kompanija = obj._kompanija;
	}

	// Operator <<
	friend ostream & operator << (ostream & COUT, PoslovnaViza & obj) {
		COUT << obj._drzava << " " << obj._vazenjeOD << " " << obj._vazenjeDO << " " << obj._kompanija << endl;
		COUT << ((obj._napomena != nullptr) ? obj._napomena : "") << endl;
		COUT << "STATUSI -> " << obj._statusi << endl;
		return COUT;
	}

	void Info()
	{
		cout << _drzava << " " << _vazenjeOD << " " << _vazenjeDO << " " << _kompanija << endl;
		cout << ((_napomena != nullptr) ? _napomena : "") << endl;
		cout << "STATUSI -> " << _statusi << endl;
	}

};
class TuristickaViza : public Viza {
	string _adresa; //adresa hotele ili drugog smještaja na kojoj će aplikant boraviti
public:
	// Konstruktor ********* FITKOLEKCIJA**************
	TuristickaViza(Drzava drzava, Datum _OD, Datum _DO, string adresa, char * napomena = nullptr) : Viza(drzava, _OD, _DO, napomena) {
		_adresa = adresa;
	}

	TuristickaViza(const TuristickaViza & obj)
		:Viza(obj._drzava, obj._vazenjeOD, obj._vazenjeDO, obj._napomena)
	{
		_adresa = obj._adresa;
	}

	// Operator <<
	friend ostream & operator << (ostream & COUT, TuristickaViza & obj) {
		COUT << obj._drzava << " " << obj._vazenjeOD << " " << obj._vazenjeDO << " " << obj._adresa << endl;
		COUT << ((obj._napomena != nullptr) ? obj._napomena : "") << endl;
		COUT << "STATUSI -> " << obj._statusi << endl;
		return COUT;
	}

	void Info()
	{
		cout << _drzava << " " << _vazenjeOD << " " << _vazenjeDO << " " << _adresa << endl;
		cout << ((_napomena != nullptr) ? _napomena : "") << endl;
		cout << "STATUSI -> " << _statusi << endl;
	}
};

class Aplikant {
	char * _imePrezime;
	Datum * _datumRodjenja;
	char * _brojPasosa;
	vector<Viza *> _vize;
public:
	// Konstruktor sa parametrima
	Aplikant(const char * imePrezime, Datum datumRodjenja, const char * brPasosa) {
		int vel = strlen(imePrezime) + 1;
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, imePrezime);
		vel = strlen(brPasosa) + 1;
		_brojPasosa = new char[vel];
		strcpy_s(_brojPasosa, vel, brPasosa);
		_datumRodjenja = new Datum(datumRodjenja);
	}

	// Destruktor
	~Aplikant() {
		delete[]_imePrezime; _imePrezime = nullptr;
		delete[]_brojPasosa; _brojPasosa = nullptr;
		delete _datumRodjenja; _datumRodjenja = nullptr;
		for (size_t i = 0; i < _vize.size(); i++)
		{
			delete _vize[i]; _vize[i] = nullptr;
		}
	}

	// Operator <<
	friend ostream & operator << (ostream & COUT, const Aplikant & obj) {
		COUT << obj._imePrezime << " " << obj._datumRodjenja << " " << obj._brojPasosa << endl;
		COUT << "VIZE -> " << endl;
		for (size_t i = 0; i < obj._vize.size(); i++)
			COUT << obj._vize[i] << endl;
		return COUT;
	}

	bool DodajVizu(Viza * viza)
	{
		// Pravilo 1
		if ((viza->GetVazenjeOD().GetGodina() - _datumRodjenja->GetGodina()) < 10)
		{
			return false;
		}

		// Pravilo 2
		for (size_t i = 0; i < _vize.size(); i++)
		{
			if (!(_vize[i]->GetVazenjeOD() < viza->GetVazenjeOD()) && _vize[i]->GetVazenjeOD() < viza->GetVazenjeDO())
			{
				for (size_t j = 0; j < _vize[i]->GetStatuse().GetTrenutno(); j++)
				{
					if (*_vize[i]->GetStatuse().GetT1()[j] == ISTEKLA || *_vize[i]->GetStatuse().GetT1()[j] == PONISTENA || *_vize[i]->GetStatuse().GetT1()[j] != IZDATA)
					{
						if (_vize[i]->GetDrzava() == viza->GetDrzava())
						{
							return false;
						}

					}
				}
			}
		}
		

		// Pravilo 3
		for (size_t i = 0; i < _vize.size(); i++)
		{
			for (size_t j = 0; j < _vize[i]->GetStatuse().GetTrenutno(); j++)
			{
				if (_vize[i]->GetDrzava() == SAD && *_vize[i]->GetStatuse().GetT1()[j] == PONISTENA)
				{
					return false;
				}
			}
		}

		if (dynamic_cast<TuristickaViza*>(viza))
			_vize.push_back(new TuristickaViza(*dynamic_cast<TuristickaViza*>(viza)));
		else if (dynamic_cast<PoslovnaViza*>(viza))
			_vize.push_back(new PoslovnaViza(*dynamic_cast<PoslovnaViza*>(viza)));
		return true;
	}

	bool DodajStatus(Viza * viza, Status status, string komentar = "")
	{
		for (size_t i = 0; i < _vize.size(); i++)
		{
			if (_vize[i] == viza)
			{
				for (size_t j = 0; j < _vize[i]->GetStatuse().GetTrenutno(); j++)
				{
					if (status == ZAHTJEV_ZAPRIMLJEN)
					{
						_vize[i]->GetStatuse().Dodaj(status, komentar);
						return true;
					}
					else if ((status == ODUSTAO || status == ODBIJENA || status == IZDATA) && *_vize[i]->GetStatuse().GetT1()[j] == ZAHTJEV_ZAPRIMLJEN)
					{
						_vize[i]->GetStatuse().Dodaj(status, komentar);
						return true;
					}
					else if ((status == ISTEKLA || status == PONISTENA) && *_vize[i]->GetStatuse().GetT1()[j] == IZDATA)
					{
						_vize[i]->GetStatuse().Dodaj(status, komentar);
						return true;
					}

				}
			}
		}
		return false;
	}

	void PrintajVizu(Viza * viza)
	{
		for (size_t i = 0; i < _vize.size(); i++)
		{
			if (viza == _vize[i])
			{
				
			}
		}
	}

	// Geteri
	vector<Viza * > GetVize() { return _vize; }
};

void main() {

	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
	****************************************************************************/



	Datum danas(15, 2, 2017);
	Datum sutra(++danas); // inkrementiranjem se uvecava dan za 1
	Datum prekosutra;
	Datum dat15022017(15, 2, 2017), dat18082017(18, 8, 2017), dat11052018(11, 5, 2018), dat11122017(11, 12, 2017);


	prekosutra = danas;
	if (prekosutra == danas)
		cout << "Datumi su jednaki" << endl;
	cout << danas << endl << sutra << endl << prekosutra << crt;

	int v6 = 6, v13 = 13, v32 = 32, v63 = 63, v98 = 98, v109 = 109, v196 = 196;

	FITKolekcija<int, int, 7> brojevi;
	brojevi.Dodaj(v196, v6);
	brojevi.Dodaj(v13, v32);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v63, v13);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v196, v6);

	cout << brojevi << crt;
	//NA KOJI NAČIN ĆE SE VRŠITI SORTIRANJE PRVENSTVENO ZAVISI OD VRIJEDNOSTI PARAMETRA, A VRŠI SE NA OSNOVU VRIJEDNOSTI TIPA T1
	brojevi.Sortiraj(RASTUCI);
	cout << brojevi << crt;
	brojevi.Sortiraj(OPADAJUCI);
	cout << brojevi << crt;

	try
	{
		//U SLUČAJU PREKORAČENJA DEFINISANE VELIČINE KOLEKCIJE, POTREBNO JE BACITI IZUZETAK
		brojevi.Dodaj(v13, v196);
	}
	catch (exception & err)
	{
		cout << "Error -> " << err.what() << endl;
	}

	Aplikant jasmin("Jasmin Azemovic", Datum(15, 5, 1979), "BS6985645");
	PoslovnaViza poslovna(SAD, dat15022017, dat18082017, "Microsoft");

	/*
	NOVA VIZA SE NE MOŽE DODATI UKOLIKO:
	- JE APLIKANT MLAĐI OD 10 GODINA
	- U TOM PERIODU (ODNOSI SE NA PERIOD VIZE OD - DO) NE POSTOJI VAŽEĆA (POJAM VAŽEĆA PODRAZUMIJEVA DA JE POSLJEDNJI STATUS VIZE BIO IZDATA TJ. DA VIZA NIJE PONIŠTENA ILI ISTEKLA) VIZA ZA TU DRŽAVU, BEZ OBZIRA NA NJENU VRSTU.
	- JE NEKA OD RANIJIH VIZA PONIŠTENA (OVO SE ODNOSI SAMO NA VIZE ZA DRŽAVU: SAD)
	*/
	if (jasmin.DodajVizu(&poslovna))
		cout << "Podaci o vizi uspješno zaprimljeni" << endl;
	/*
	STATUSI SE MOGU DODAVATI SAMO U REDOSLIJEDU U KOJEM SE NALAZE U ENUMERACIJI NPR.
	- NIJE MOGUĆE ODBITI VIZU AKO PRETHODNO NIJE IMALA STATUS DA JE ZAHTJEV_ZAPRIMLJEN;
	- NIJE MOGUĆE PONIŠTITI VIZU KOJA PRETHODNO NIJE IZDATA
	*/
	if (jasmin.DodajStatus(&poslovna, ZAHTJEV_ZAPRIMLJEN, "provjeriti navode sa predstavnicima kompanije Microsoft"))
		cout << "Status vize uspijesno promijenjen" << endl;
	else
		cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;


	if (jasmin.DodajStatus(&poslovna, PONISTENA, "predstavnicima kompanije Microsoft nemaju informaciju o posjeti navedenog aplikanta"))
		cout << "Status vize uspijesno promijenjen" << endl;
	else
		cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;

	TuristickaViza turisticka(ENGLESKA, dat18082017, dat11122017, "Whitehall Pl, London SW1A 2BD, UK");

	if (jasmin.DodajStatus(&turisticka, ZAHTJEV_ZAPRIMLJEN))
		cout << "Status vize uspijesno promijenjen" << endl;
	else
		cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;

	//if (jasmin.DodajStatus(&turisticka, IZDATA)) {
	//	cout << "Status vize uspijesno promijenjen" << endl;
	//	//U ZASEBNOJ NITI URADITI PRINTANJE VIZE...KORISTITI METODU SLEEP_FOR
	//	jasmin.PrintajVizu(&turisticka);
	//}
	//else
	//	cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;
	////VRAĆA PODATKE O SVIM VIZAMA KOJE SU IZDATE ZA ODREĐENU DRŽAVU, A KOJE SU IMALE ODREĐENI STATUS
	//vector<Viza *> jasminVize = jasmin.GetVizeByDrzava(SAD, PONISTENA);

	////UNUTAR NAPOMENE MIJENJA SADRŽAJ "nemaju informaciju" SA "su upoznti sa" - KORISTITI REGEX
	//jasmin.ZamijeniRijec("nemaju informaciju", "su upoznti sa");

	system("pause>0");
}
