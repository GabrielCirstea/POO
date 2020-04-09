#include <iostream>
#pragma once
using namespace std;

class Abonament{
private:
	static int nrAbonamente;
protected:
	string nume_abonament;
	float pret;
	int perioada; //in luni
public:
	Abonament(string,float,int);
	Abonament(const Abonament&);
	virtual ~Abonament();
	//get-eri
	const string& get_nume()const {return nume_abonament;};
	float get_pret()const{return pret;};
	int get_prioada()const{return perioada;};
  virtual float get_suma()const{return pret*perioada;}; // pretul abonamentului platit lunar
  static int get_count() {return nrAbonamente;};
  void set_nume(const string&);
  void set_pret(float);
  void set_perioada(int);
  virtual void citire(istream& in);
	virtual void afisare(ostream& out)const;

	friend istream& operator>>(istream&,Abonament&);
	friend ostream& operator<<(ostream&,Abonament&);
	void operator=(const Abonament& a);
};
int Abonament::nrAbonamente;
Abonament::Abonament(string nume="", float pret=0, int perioada=0)
{
	nrAbonamente++;
	this->nume_abonament = nume;
	this->pret = pret;
	this->perioada = perioada;
}
Abonament::Abonament(const Abonament& a)
{
	nrAbonamente++;
	this->nume_abonament = a.nume_abonament;
	this->pret = a.pret;
	this->perioada = a.perioada;
}
Abonament::~Abonament()
{
	nrAbonamente--;
	pret = 0;
	perioada = 0;
}
void Abonament::citire(istream& in)
{
  cout<<"nume ";
	getline(in,nume_abonament);
	cout<<"pret ";
	in>>pret;
	cout<<"perioada ";
	in>>perioada;
  in.get();
}
void Abonament::afisare(ostream& out) const
{
	out<<"Nume abonament: "<<nume_abonament<<endl;
	out<<"Pret: "<<pret<<endl;
	out<<"Perioada: "<<perioada<<endl;
}
ostream& operator<<(ostream& out,Abonament &a)
{
	a.afisare(out);
	return out;
}
istream& operator>>(istream& in,Abonament& a)
{
	a.citire(in);
	return in;
}
void Abonament::operator=(const Abonament& a)
{
	this->nume_abonament = a.nume_abonament;
	this->pret = a.pret;
	this->perioada = a.perioada;
}
void Abonament::set_nume(const string& nume)
{
  nume_abonament = nume;
}
void Abonament::set_pret(float pret)
{
  this->pret = pret;
}
void Abonament::set_perioada(int perioada)
{
  this->perioada = perioada;
}
//---------------
//class PREMIUM
//---------------
class AbonamentPremium : public Abonament
{
private:
	static int nrPremium;
private:
	int reducere;
public:
	AbonamentPremium(int,string,float,int);
	AbonamentPremium(const AbonamentPremium&);
  AbonamentPremium(int,const Abonament& a);
  ~AbonamentPremium();

	int get_reducere() const {return reducere;};
  float get_suma() const;
  static int get_count(){return nrPremium;};
  void set_discount(int);
  void citire(istream& in);
	void afisare(ostream& out) const;

	friend istream& operator>>(istream&,AbonamentPremium&);
	friend ostream& operator<<(ostream&,const AbonamentPremium&);
	void operator=(const AbonamentPremium& a);

};
int AbonamentPremium::nrPremium;
AbonamentPremium::AbonamentPremium(int discount=0,
                                   string nume="",float pret=0, int perioada=0):Abonament(nume,pret,perioada)
{
  nrPremium++;
  reducere = discount;
}
AbonamentPremium::AbonamentPremium(const AbonamentPremium& a) : Abonament(a)
{
  nrPremium++;
  this->reducere = a.reducere;
}
void AbonamentPremium::citire(istream& in)
{
  Abonament::citire(in);
  cout<<"Reducere ";
  in>>reducere;
  in.get();  //sa golim buff-erul
}
AbonamentPremium::AbonamentPremium(int discount,const Abonament& a)
{
  nrPremium++;
  (Abonament&)(*this) = a;
  reducere = discount;
}
AbonamentPremium::~AbonamentPremium()
{//trebuie doar sa scada nr de abonamente
  //toate atributele sunt alocate static
  nrPremium--;
}
istream& operator>>(istream& in,AbonamentPremium& a)
{
  a.citire(in);
  return in;
}
void AbonamentPremium::afisare(ostream& out) const
{
  Abonament::afisare(out);
  out<<"Reducere: "<<reducere<<endl;
}
ostream& operator<<(ostream& out,AbonamentPremium& a)
{
  a.afisare(out);
  return out;
}
void AbonamentPremium::operator=(const AbonamentPremium& a)
{
  (Abonament&)(*this) = a;
  this->reducere = a.reducere;
}
float AbonamentPremium::get_suma() const
{
  float suma = Abonament::get_suma();
  suma -= reducere*suma/100;
  return suma;
}
void AbonamentPremium::set_discount(int discount)
{
  reducere = discount;
}
