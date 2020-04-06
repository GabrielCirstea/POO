#include <iostream>
#include <stdlib.h>

#include "abonament.h"
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
		Persoana(Persoana &p);
		~Persoana();
		//get-eri
		int get_id(){return id;};
		// referinta - nu apeleaza constructorul de sting, e mai rapid
		// const, sa nu modifice numele: p.get_nume() = "Andrei";
		const string& get_nume(){return nume;};
		const string& get_CNP(){return cnp;};
		int static get_count(){return Persoana::nrPers;};
		Persoana& operator=(Persoana &p);
		virtual void citire(istream &in);
		virtual	void afisare(ostream &out);
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
Persoana::Persoana(Persoana &p){
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
void Persoana::citire(istream &in){
	cout<<"id";
	in>>id;
	in.get();
	cout<<"nume ";
	getline(in,nume);
	cout<<"cnp";
	string cnp;
	bool ok = false;
	in>>cnp;
	while(!ok){
		ok = true;
		if(cnp.size()!=13)
			cout<<"cnp invalid, trebuie sa aiba 13 caractere: ",ok = false;
		else
		for(int i=0;cnp[i];i++)
		{
			if(cnp[i]<'0' || cnp[i]>'9')
			{
				cout<<"cnp-ul contine doar cifre";
				ok = false;
				break;
			}
		}
		if(!ok) in>>cnp;
}
	this->cnp = cnp;
}
istream& operator>>(istream &in,Persoana &p){
	p.citire(in);
	return  in;
}
void Persoana::afisare(ostream &out){
	out<<"id: "<<id<<endl;
	out<<"nume: "<<nume<<endl;
	out<<"cnp: "<<cnp<<endl;
}
ostream& operator<<(ostream &out,Persoana &p){
	p.afisare(out);
	return out;
}
 Persoana& Persoana::operator=(Persoana &p){
	nrPers++; 	// se  creaza o persoana nou
	this->id = p.id;
	this->nume = p.nume;
	this->cnp = p.cnp;

	return *this;
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
  Abonament *abon;
  void set_abonament(istream& in);  //la citirea abonatului se va crea si abonamentul lui personal si unic(in limita imaginatiei)
public:
	Abonat(string,int,string,string);
	Abonat(string,Persoana &p);
	Abonat(Abonat &a);
	//~Abonat // daca o fi nevoie....cred ca se descurca si fara sa-l fac eu
	//poate un get-er
	const string& get_phone(){return nr_tel;};
	Abonat& operator=(Abonat &a);
	void afisare(ostream &out);
	void citire(istream &in);
	friend ostream& operator<<(ostream &out,Abonat &a);
	friend istream& operator>>(istream &in,Abonat &a);
};
Abonat::Abonat(string nr_tel="-",int id=0,string nume="",string cnp=""):Persoana(id,nume,cnp)
{
	this->nr_tel = nr_tel;
}
//daca ai persoana ar trebui sa vi si cu numar de telefon;
Abonat::Abonat(string tel,Persoana &p):Persoana(p)
{
	this->nr_tel = tel;
  abon = nullptr;
}
Abonat::Abonat(Abonat &a):Persoana(a)
{
	this->nr_tel = a.nr_tel;
  abon = nullptr;
}
void Abonat::set_abonament(istream& in)
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
Abonat& Abonat::operator=(Abonat &a)
{
	(Persoana&)(*this) = a;
	this->nr_tel = a.nr_tel;

	return *this;
}
void Abonat::afisare(ostream &out)
{
	Persoana::afisare(out);
	out<<"nr_tel: "<<nr_tel<<endl;
  if(abon)
    cout<<*abon;
}
void Abonat::citire(istream &in)
{
	Persoana::citire(in);
	cout<<"numar telefon: ";
	string numer;
	in>>numer;
	while(numer.size()!=10)
	{
		cout<<"Numarul trebuie sa fie de 10 caractere\n";
		in>>numer;
	}
	nr_tel = numer;
  this->set_abonament(in);
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
void testAbonat()
{
	Abonat a("12",1,"darve","ceva cenp");
  Abonat b(a);
	system("clear");
	cout<<b<<endl;
	cin>>b;
	cout<<"----\n";
	cout<<b;
}
void testAbonament()
{
	Abonament ab("primul abonament",24.7f,23);
	cout<<ab;
	AbonamentPremium ac(20,ab);
	cout<<ab;
	cout<<Abonament::get_count()<<endl;
	cin>>ac;
	cout<<"---\n"<<ac;
}
int main(){
	cout<<"Salutare lume!\n";
  testAbonat();
	return 0;
}
