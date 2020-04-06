#include <iostream>

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
	Abonament(Abonament&);
	~Abonament();
	//get-eri
	const string& get_nume(){return nume_abonament;};
	float get_pret(){return pret;};
	int get_prioada(){return perioada;};
	static int get_count(){return nrAbonamente;};
	virtual void citire(istream& in);
	virtual void afisare(ostream& out);

	friend istream& operator>>(istream&,Abonament&);
	friend ostream& operator<<(ostream&,Abonament&);
	void operator=(Abonament& a);
};
int Abonament::nrAbonamente;
Abonament::Abonament(string nume="", float pret=0, int perioada=0)
{
	nrAbonamente++;
	this->nume_abonament = nume;
	this->pret = pret;
	this->perioada = perioada;
}
Abonament::Abonament(Abonament& a)
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
}
void Abonament::afisare(ostream& out)
{
	out<<"Nume abonament: "<<nume_abonament<<endl;
	out<<"Pret: "<<pret<<endl;
	out<<"Perioada"<<perioada<<endl;
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
void Abonament::operator=(Abonament& a)
{
	this->nume_abonament = a.nume_abonament;
	this->pret = a.pret;
	this->perioada = a.perioada;
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
	AbonamentPremium(AbonamentPremium&);
  AbonamentPremium(int,Abonament& a);
  ~AbonamentPremium();

	int get_reducere(){return reducere;};
	static int get_count(){return nrPremium;};
	void citire(istream& in);
	void afisare(ostream& out);

	friend istream& operator>>(istream&,AbonamentPremium&);
	friend ostream& operator<<(ostream&,AbonamentPremium&);
	void operator=(AbonamentPremium& a);

};
int AbonamentPremium::nrPremium;
AbonamentPremium::AbonamentPremium(int discount=0,
                                   string nume="",float pret=0, int perioada=0):Abonament(nume,pret,perioada)
{
  reducere = discount;
}
AbonamentPremium::AbonamentPremium(AbonamentPremium& a) : Abonament(a)
{
  this->reducere = a.reducere;
}
void AbonamentPremium::citire(istream& in)
{
  Abonament::citire(in);
  cout<<"Reducere: ";
  in>>reducere;
}
AbonamentPremium::AbonamentPremium(int discount,Abonament& a)
{
  (Abonament&)(*this) = a;
  reducere = discount;
}
AbonamentPremium::~AbonamentPremium()
{
  nrPremium--;
}
istream& operator>>(istream& in,AbonamentPremium& a)
{
  a.citire(in);
  return in;
}
void AbonamentPremium::afisare(ostream& out)
{
  Abonament::afisare(out);
  out<<"Reducere: "<<reducere<<endl;
}
ostream& operator<<(ostream& out,AbonamentPremium& a)
{
  a.afisare(out);
  return out;
}
void AbonamentPremium::operator=(AbonamentPremium& a)
{
  (Abonament&)(*this) = a;
  this->reducere = a.reducere;
}
