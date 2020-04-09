#include <iostream>
#include "abonament.h"
#pragma once
using namespace std;

class Persoana{
private:
		static int nrPers;
protected:
		int id;
		string nume, cnp;
public:
		//nu o sa construim persoane goale
		Persoana(int,string,string);
		Persoana(const Persoana &p);
		~Persoana();
		//get-eri
		int get_id() const {return id;};
		// referinta - nu apeleaza constructorul de sting, e mai rapid
		// const, sa nu modifice numele: p.get_nume() = "Andrei";
		const string& get_nume() const {return nume;};
		const string& get_CNP() const {return cnp;};
		int static get_count(){return Persoana::nrPers;};
    //set-eri
    void set_nume(string& numeNou){nume=numeNou;};
    bool set_CNP(string& cnpNou);
    virtual void operator=(const Persoana &p);
		virtual void citire(istream &in);
		virtual	void afisare(ostream &out) const;
		friend istream& operator>>(istream &in,Persoana &p);
		friend ostream& operator<<(ostream &in,Persoana &p);
};
int Persoana::nrPers; // variabila statica
Persoana::Persoana(int id = 0,string nume = "", string cnp = ""){
	nrPers++;
	if(!id)
		this->id = nrPers;	//ii punem in ordinea sosirii
	else
		this->id = id; //il punem cate e setat, desi nu as face asta
	this->nume = nume;
	this->cnp = cnp;
}
Persoana::Persoana(const Persoana &p){
	nrPers++;		//se creaza o persoana noua;
	this->id = p.id;
	this->nume = p.nume;
	this->cnp = p.cnp;
}
Persoana::~Persoana(){
	nrPers--;
	id = 0;
	// atribitele sunt alocate static
	// practic nu trebuie destructor explicit, am pus doar pt nrPers.
}
bool Persoana::set_CNP(string& cnpNou)
{//schimba CNP-ul cu cel dat doar daca are formatul valid
	bool ok = true;
  if(cnpNou.size()!=13)
    ok = false;
  else
    for(int i=0;cnpNou[i];i++)
      {
        if(cnpNou[i]<'0' || cnpNou[i]>'9')
          {
            ok = false;
            break;
          }
      }
  if(ok)
    cnp=cnpNou;
  return ok;
}
void Persoana::citire(istream &in){
	cout<<"id: ";
	in>>id;
	in.get();
	cout<<"nume: ";
	getline(in,nume);
	cout<<"cnp: ";
  string CNP;
  in>>CNP;
  cnp = CNP;
  /*while(!set_CNP(CNP))
    {
      cout<<"CNP-ul trebuie sa aiba 13 cifre, nu litere sau alte caractere\n";
      cout<<"CNP: ";
      in>>CNP;
      }*/
}
istream& operator>>(istream &in,Persoana &p){
	p.citire(in);
	return  in;
}
void Persoana::afisare(ostream &out) const{
	out<<"id: "<<id<<endl;
	out<<"nume: "<<nume<<endl;
	out<<"cnp: "<<cnp<<endl;
}
ostream& operator<<(ostream &out,Persoana &p){
	p.afisare(out);
	return out;
}
void Persoana::operator=(const Persoana &p){
	nrPers++; 	// se  creaza o persoana nou
	this->id = p.id;
	this->nume = p.nume;
	this->cnp = p.cnp;

}
void testPersoana(){
	Persoana a(1,"Andrei","1234567890123");
	cout<<a;
	Persoana b(a);
	cout<<"------\n";
	cout<<b;
	cin>>b;
	cout<<b;
	cout<<Persoana::get_count();
}
//-----------------------
// clasa ABONAT
//-----------------------
class Abonat: public Persoana{
private:
	string nr_tel;
  Abonament *abon;    //fiecare abonat are abonamentul lui
  void set_readAbon(istream& in);  //la citirea abonatului se va crea si abonamentul lui personal si unic(in limita imaginatiei)
public:
	Abonat(string,int,string,string);
	Abonat(string,const Persoana &p);
	Abonat(const Abonat &a);
	~Abonat(); // daca o fi nevoie....cred ca se descurca si fara sa-l fac eu
	//poate un get-er
	const string& get_phone() const {return nr_tel;};
  float get_total(){return abon ? abon->get_suma() : 0;};
  bool set_number(const string& number);
	void afisare(ostream &out) const;
  void set_abonament(Abonament*);
  void set_abonament(Abonament&);
  void set_abonament(AbonamentPremium&);
	void citire(istream &in);
	friend ostream& operator<<(ostream &out,Abonat &a);
	friend istream& operator>>(istream &in,Abonat &a);
  void operator=(const Abonat&);
  Abonat& operator[](int i)
  {
    return this[i];
  }
};
Abonat::Abonat(string nr_tel="-",int id=0,string nume="",string cnp=""):Persoana(id,nume,cnp)
{
	this->nr_tel = nr_tel;
  abon = NULL;
}
//daca ai persoana ar trebui sa vi si cu numar de telefon;
Abonat::Abonat(string tel,const Persoana &p):Persoana(p)
{
	this->nr_tel = tel;
  abon = NULL;  //nullptr;
}
Abonat::Abonat(const Abonat &a):Persoana(a)
{
	this->nr_tel = a.nr_tel;
  abon = NULL;
  this->set_abonament(*a.abon);
}
Abonat::~Abonat()
{
  if(abon)
    delete abon;
}
void Abonat::set_readAbon(istream& in)
{
  cout<<"Ce abonament doriti?(1-premium,0-normal):";
  int opt;
  in>>opt;
  in.get();
  switch(opt)
    {
    case 1:
      {
        this->abon = new AbonamentPremium;
        in>>*this->abon;
      }break;
    case 0:
      {
        this->abon = new Abonament;
        cin>>*this->abon;
      }break;
    }
}
void Abonat::afisare(ostream &out) const
{
	Persoana::afisare(out);
	out<<"nr_tel: "<<nr_tel<<endl;
  if(abon)
    out<<"---Abonament:---\n"<<*abon;
  else
    out<<"---Fara abonament---\n";
}
bool Abonat::set_number(const string& number)
{//seteaza numarul de telefon doar daca are 10 "cifre"
  if(number.size() == 10)
  {
   nr_tel = number;
   return true;
  }
  return false;
}
void Abonat::citire(istream &in)
{
	Persoana::citire(in);
	cout<<"numar telefon: ";
	string numer;
	in>>numer;
  nr_tel = numer;
	/*while(!set_number(numer))
	{
		cout<<"Numarul trebuie sa fie de 10 caractere\n";
    cout<<"Numar: ";
		in>>numer;
    }*/
  this->set_readAbon(in);
}
istream& operator>>(istream &in,Abonat &a)
{
	a.citire(in);
	return in;
}
ostream& operator<<(ostream &out,Abonat &a)
{
	a.afisare(out);
	return out;
}
void Abonat::operator=(const Abonat& a)
{
  (Persoana&)(*this) = a;
  this->nr_tel = a.nr_tel;
  if(a.abon)
    {
      this->set_abonament(a.abon);
    }
}
void Abonat::set_abonament(Abonament* a)
{
  if(abon)
    delete abon;
  if(dynamic_cast<AbonamentPremium*>(a))
    abon = new AbonamentPremium(*(AbonamentPremium*)a);
  else
    abon = new Abonament(*a);
}
void Abonat::set_abonament(Abonament& a)
{
  if(abon)
    delete abon;
  abon = new Abonament(a);
}
void Abonat::set_abonament(AbonamentPremium& a)
{
  if(abon)
    delete abon;
  abon = new AbonamentPremium(a);
}
