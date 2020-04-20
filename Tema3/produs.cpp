#include "produs.h"
using namespace std;

ingredient::ingredient(string nume="", int cant=0, float pret=0)
{
  denumire = nume;
  cantitate = cant;
  this->pret = pret;
}
ingredient::ingredient(ingredient& ing)
// {
//   this->denumire = ing.denumire;
//   this->cantitate = ing.cantitate;
//   this->pret = ing.pret;
// }
void ingredient::operator=(ingredient& ing)
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
