#include "produs.h"

using namespace std;

#define forit(it,lista) for(list<ingredient>::iterator it=lista.begin();it!=lista.end();it++)

ingredient::ingredient(string nume="", int cant=0, float pret=0):denumire(nume),cantitate(cant),pret(pret)
{}

ingredient::ingredient(const ingredient& ing):denumire(ing.denumire),cantitate(ing.cantitate),pret(ing.pret)
{}

void ingredient::operator=(const ingredient& ing)
{
  this->denumire = ing.denumire;
  this->cantitate = ing.cantitate;
  this->pret = ing.pret;
}

bool ingredient::operator==(const ingredient& ing) const
{
  if(denumire != ing.denumire)
    return false;
  if(cantitate != ing.cantitate)
    return false;
  if(pret != ing.pret)
    return false;
  return true;
}

void ingredient::citire(istream& in)
{
  cout<<"Denumire: ";
  getline(in,denumire);
  cout<<"Cantitate: ";
  in>>cantitate;
  cout<<"Pret: ";
  in>>pret;
  in.get();  // curatam buffer-ul dupa noi
}

void ingredient::afisare(ostream& out) const
{
  cout<<"Denumire: "<<denumire<<endl;
  cout<<"Cantitate: "<<cantitate<<endl;
  cout<<"Pret: "<<pret<<endl;
}

ostream& operator<<(ostream& out,const ingredient& ing)
{
  ing.afisare(out);
  return out;
}

istream& operator>>(istream& in, ingredient& ing)
{
  ing.citire(in);
  return in;
}

// _________PIZZA__________
//_________________________
Pizza::Pizza(string nume,float pret):manopera(pret),denumire(nume)
{cout<<"Piza goala\n";}

Pizza::Pizza(string nume,list<ingredient> &ingred, float pret):manopera(pret),denumire(nume)
{
  cout<<"Pizza facuta\n";
  set_ingred(ingred); // ca sa folosim metoda
}

Pizza::Pizza(const Pizza& P):manopera(P.manopera),denumire(P.denumire),reteta(P.reteta)
{}

void Pizza::set_ingred(list<ingredient> &ingred)
{
  reteta.clear(); // sa stergem ce aveam inainte, in caz ca nu se sterge singur
  reteta = ingred;
}

void Pizza::add_ingred(ingredient &ingred)
{
  reteta.push_back(ingred);
}

void Pizza::remove_ingred(int index)
{
  if(index<0 || index> reteta.size())
    return;
  list<ingredient>::iterator it = reteta.begin(); // luam inceputul listei
  advance(it,index);  // avansam pana la index
  reteta.erase(it);   // stergem elementul
}

void Pizza::remove_ingred(const string& denumire)
{
  forit(it,reteta)
    {
      if(it->get_name() == denumire)
        {
          reteta.erase(it);
          return;
        }
    }
}

void Pizza::list_ingred() const
{
  int nr = 0;
  for(const ingredient &i:reteta)
    {
      cout<<"Ingredient "<<++nr<<":\n";
      cout<<i;
      cout<<"------\n";
    }
}

void Pizza::afisare(ostream& out) const
{
  out<<"Pizza: "<<denumire<<endl;
  out<<"Ingrediente:\n";
  list_ingred();
  cout<<"Manopera: "<<manopera<<endl;
  cout<<"Pret total: "<<calc_pret()<<endl;
}

 ostream& operator<<(ostream& out,const produs& P)
{
  P.afisare(out);
  return out;
}

void Pizza::citire(istream& in)
{
  reteta.clear();
  cout<<"Titlul Pizzei: ";
  getline(in,denumire);
  cout<<"Ingredientele.\nCate ingrediente ati vrea sa introduceti?\n";
  int n;
  in>>n;
  in.get();
  while(n)
    {
      ingredient ing;
      in>>ing;
      reteta.push_back(ing);
      n--;
      if(!n)
        {
          cout<<"Mai vreti sa introduceti si alte ingrediente?\n";
          cout<<"Introduceti numarul acestora(0 - daca vreti sa va opriti)\n";
          cin>>n;
          cin.get();
        }
    }
}

istream& operator>>(istream& in,produs& P)
{
  P.citire(in);
  return in;
}

void Pizza::operator=(const Pizza& P)
{// se copiaza denumirea si reteta
  denumire = P.denumire;
  reteta = P.reteta;
  // manopera = P.manopera;  // nu prea putem copia pizza asa
  // e variabila const
}

float Pizza::calc_pret() const
{
  float pret=0;
  for(const ingredient &i:reteta)
    {
      pret+=i.get_price()*i.get_cant();
    }
  pret+=manopera;
  return pret;
}

//------vegetariana---------
int PizzaVegetariana::numarVegetale = 0;

PizzaVegetariana::PizzaVegetariana(string nume, list<ingredient>& ingred, float pret):Pizza(nume,ingred,pret)   // pret manopera
{
  cout<<"Alta vegetala alocata\n";
  numarVegetale++;
}

PizzaVegetariana::PizzaVegetariana(string nume,float pret):Pizza(nume,pret)
{
  numarVegetale++;
}

PizzaVegetariana::PizzaVegetariana(const PizzaVegetariana& p):Pizza(p)
{
  numarVegetale++;
}

PizzaVegetariana::PizzaVegetariana(const Pizza& p):Pizza(p)
{
  numarVegetale++;
}

PizzaVegetariana::~PizzaVegetariana()
{
  numarVegetale--;
}

int PizzaVegetariana::numar()
{
  return numarVegetale;
}

void PizzaVegetariana::afisare(ostream& out) const
{
  out<<"E vegetala"<<endl;
  Pizza::afisare(out);
}

void PizzaVegetariana::citire(istream& in)
{
  cout<<"E vegetala"<<endl;
  Pizza::citire(in);
}

void PizzaVegetariana::operator=(const PizzaVegetariana& p)
{
  this->Pizza::operator=(p);
  // nu cred ca mai dam nrVegetale++
}

//---------------Online-------------
//Pizza Onlie
PizzaOnline::PizzaOnline(string nume, list<ingredient>& ingred, float pret, float dist):Pizza(nume,ingred,pret),produsOnline(dist)
{}

PizzaOnline::PizzaOnline(string nume ,float pret ,float dist):Pizza(nume,pret),produsOnline(dist)
{}

PizzaOnline::PizzaOnline(Pizza& p, float dist):Pizza(p),produsOnline(dist)
{}

PizzaOnline::PizzaOnline(PizzaOnline& p):Pizza(p),produsOnline(p.distanta)
{}

float PizzaOnline::calc_pret() const
{
	int pret = Pizza::calc_pret();
	pret+= distanta/10 * pret/20;
	return pret;
}

void PizzaOnline::afisare(ostream& out) const
{
  Pizza::afisare(out);
  out<<"Distanta: "<<distanta<<endl;
}

void PizzaOnline::citire(istream& in)
{
  Pizza::citire(in);
  cout<<"Distanta: ";
  in>>distanta;
}

void PizzaOnline::operator=(const PizzaOnline& p)
{
  this->Pizza::operator=(p);
  distanta = p.distanta;
}

//Pizza vegetariana online
PizzaVegOnline::PizzaVegOnline(string nume, list<ingredient>& ingred, float pret, float dist):PizzaVegetariana(nume,ingred,pret),PizzaOnline(nume,ingred,pret,dist)
{}

PizzaVegOnline::PizzaVegOnline(string nume,float pret, float dist):PizzaVegetariana(nume,pret),PizzaOnline(nume,pret,dist)
{}

PizzaVegOnline::PizzaVegOnline(Pizza& p, float dist):PizzaVegetariana(p),PizzaOnline(p,dist)
{}

PizzaVegOnline::PizzaVegOnline(PizzaOnline& p):PizzaVegetariana(p),PizzaOnline(p)
{}

float PizzaVegOnline::calc_pret() const
{
  return PizzaOnline::calc_pret();
}

void PizzaVegOnline::afisare(ostream& out) const
{
  PizzaVegetariana::afisare(out);
  out<<"Distanta: "<<distanta<<endl;
}

void PizzaVegOnline::citire(istream& in)
{
  PizzaVegetariana::citire(in);
  cout<<"Distanta: ";
  in>>distanta;
}

void PizzaVegOnline::operator=(const PizzaVegOnline& p)
{
  this->PizzaOnline::operator=(p);
}
