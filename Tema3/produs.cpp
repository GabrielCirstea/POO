#include "produs.h"
using namespace std;
#define forit(it,lista) for(list<ingredient>::iterator it=lista.begin();it!=lista.end();it++)
ingredient::ingredient(string nume="", int cant=0, float pret=0)
{
  denumire = nume;
  cantitate = cant;
  this->pret = pret;
}
ingredient::ingredient(const ingredient& ing)
{
  this->denumire = ing.denumire;
  this->cantitate = ing.cantitate;
  this->pret = ing.pret;
}
void ingredient::operator=(const ingredient& ing)
{
  this->denumire = ing.denumire;
  this->cantitate = ing.cantitate;
  this->pret = ing.pret;
}
void ingredient::citire(istream& in)
{
  cout<<"Denumire: ";
  getline(in,denumire);
  cout<<"Cantitate: ";
  cin>>cantitate;
  cout<<"Pret: ";
  cin>>pret;
}
void ingredient::afisare(ostream& out)
{
  cout<<"Denumire: "<<denumire<<endl;
  cout<<"Cantitate: "<<cantitate<<endl;
  cout<<"Pret: "<<pret<<endl;
}
ostream& operator<<(ostream& out, ingredient& ing)
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
Pizza::Pizza(string nume="",float pret=0)
{
  denumire = nume;
  manopera = pret;
}
Pizza::Pizza(string nume,list<ingredient> &ingred, float pret=0)
{
  denumire = nume;
  manopera = pret;
  set_ingred(ingred);
}
Pizza::Pizza(Pizza& P)
{
  denumire = P.denumire;
  reteta = P.reteta;
  manopera = P.manopera;
}
void Pizza::set_ingred(list<ingredient> &ingred)
{
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
void Pizza::list_ingred()
{
  int nr = 0;
  for(ingredient i:reteta)
    {
      cout<<"Ingredient "<<nr++<<":\n";
      cout<<i;
      cout<<"------\n";
    }
}
void Pizza::afisare(ostream& out)
{
  out<<"Pizza: "<<denumire<<endl;
  out<<"Ingrediente:\n";
  list_ingred();
  cout<<"Manopera: "<<manopera<<endl;
  cout<<"Pret total(va urma)\n";
}
 ostream& operator<<(ostream& out, Pizza& P)
{
  P.afisare(out);
  return out;
}
void Pizza::citire(istream& in)
{
  cout<<"Titlul Pizzei:";
  in>>denumire;
  cout<<"Ingredientele.\nCate ingrediente ati vrea sa introduceti?";
  int n;
  in>>n;
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
        }
    }
}
istream& operator>>(istream& in,Pizza& P)
{
  P.citire(in);
  return in;
}
void Pizza::operator=(Pizza& P)
{
  denumire = P.denumire;
  reteta = P.reteta;
  manopera = P.manopera;
}
