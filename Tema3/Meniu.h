#pragma once
#include <iostream>
#include <list>
#include <unordered_set>
#include "produs.h"
#include "miVectoro.h"

using namespace std;

//-------comanda---------
template <class T>
class Comanda
{ // construieste Pizza din ingredientele date  si calculeaza pretul
protected:
  myVector<T> v;
public:
  Comanda(){};
  Comanda(const Comanda&);
  ~Comanda(){cout<<"Comanda finalizata\n";};
  const myVector<T>& get_list() const {return v;};
  int size() const {return v.size();};
  virtual float calc_pret() const;
  virtual void afisare(ostream&) const;
  void insert(const T&);    // adaugam Pizza in comanda
  void operator+=(const T& elem){this->insert(elem);};
};
template<class T>
Comanda<T>::Comanda(const Comanda& C)
{
  v = C.v;
}
template<class T>
float Comanda<T>::calc_pret() const
{
  int n=v.size();
  float pret=0;
  for(int i=0;i<n;i++)
    {
      pret+=v[i].calc_pret();
    }
  return pret;
}
template<class T>
void Comanda<T>::afisare(ostream& out) const
{
  v.poster(out);
}
template<class T>
void Comanda<T>::insert(const T& elem)
{
  v.push_back(elem);
}
template<class T>
ostream& operator<<(ostream& out,Comanda<T> C)
{
  C.afisare(out);
  return out;
}
//------specializare online--------
template <class T> class Comanda_Online: public Comanda<T>
{
protected:
  static int vanzariOnline;
  //distanta
public:
  Comanda_Online(){vanzariOnline++;};
  Comanda_Online(const Comanda_Online&);
  ~Comanda_Online(){vanzariOnline--;};
  // float calc_pret() const;
  virtual int get_number(){return vanzariOnline;};
};
template<class T>
int Comanda_Online<T>::vanzariOnline;
template<class T>
Comanda_Online<T>::Comanda_Online(const Comanda_Online& C):Comanda<T>(C)
{
  vanzariOnline++;
}
template <>
class Comanda_Online<PizzaVegOnline>:public Comanda<PizzaVegetariana>
{
  static int vegetaleOnline;
  static float total_income;
public:
  Comanda_Online(){vegetaleOnline++;};
  Comanda_Online(const Comanda_Online& C)
  {
    v = C.v;
    vegetaleOnline++;
  }
  ~Comanda_Online(){};
  float get_total_income()const{return total_income;};
  int get_number()const{return vegetaleOnline;};
  void insert(const PizzaVegOnline& elem)
  {
    v.push_back(elem);
    total_income+=elem.calc_pret();
  }
  void operator+=(const PizzaVegOnline& elem){this->insert(elem);};
};
template<>
int Comanda_Online<PizzaVegOnline>::vegetaleOnline;
template<>
float Comanda_Online<PizzaVegOnline>::total_income;
template<class T>




class Meniu
{
private:
  // deci structura e un rahat
  T **v;
  int nr;
  // la citire bagam ingredientele
  // la comenzi facem Pizza si calculam pretul
  // sa retinem si Pizza intr-un vector pt RTTI?
  // si ce mai facem cu map ?
public:
  Meniu(int n = 0)
  {
    nr = n;
    if(n)
      v = new T*[n];
    else
      v = NULL;
  }
  ~Meniu()
  {
    if(nr)
      {
        for(int i=0;i<nr;i++)
          {
            delete v[i];
          }
      }
    delete[] v;
  }
  void citire(istream& in)
  {
    for(int i=0;i<nr;)
      {
        cout<<"Ce tip de pizza doriti?\n";
        cout<<"Normala - 1, Vegetariana - 2\n";
        int optiune;
        in>>optiune;
        switch(optiune)
          {
          case 1:
            {
              v[i] = new Pizza;
              in>>v[i];
              i++;
            }break;
          case 2:
            {
              v[i] = new PizzaVegetariana;
              in>>v[i];
              i++;
            }break;
          default:
            cout<<"Alegere incorecta\n";
          }
      }
  }
  void afisare(ostream& out)
  {
    for(int i=0;i<nr;i++)
      {
        cout<<"#"<<i+1<<endl;
        out<<*v[i]<<endl;
      }
  }
  void comanda_online()
  {
    int ok = 1;
    Comanda_Online<PizzaOnline> C;
    Comanda_Online<PizzaVegOnline> CV;
    while(ok)
      {
        afisare(cout);
        cout<<"Ce pita doriti sa comandati?\n";
        cout<<"Introduceti id-ul\n";
        int id;
        cin>>id;
        if(id<0 || id >= nr)
          cout<<"Index out of range\n";
        T* elem = v[id];
        Pizza* p = dynamic_cast<Pizza*>(elem);
        if(p)
          {
            Pizza P= *new Pizza(*p);
            C+=P;
          }
        PizzaVegetariana *pv = dynamic_cast<PizzaVegetariana*>(elem);
        if(pv)
          {
            PizzaVegetariana PV = *new PizzaVegetariana(*pv);
            CV += PV;
          }
        cout<<"Mai doriti sa comandati ceva?[1/0]\n";
        cin>>ok;
      }
    cout<<"Comanda dumneavoastra:\n";
    if(C.size())
      {
        cout<<"Normal:\n";
        C.afisare(cout);
      }
    if(CV.size())
      {
        cout<<"Vegetariana:\n";
        CV.afisare(cout);
      }
    cout<<"Total de plata: "<<C.calc_pret() + CV.get_total_income()<<endl;
  }
  void comanda_standard()
  {
    int ok = 1;
    Comanda<Pizza> C;
    Comanda<PizzaVegetariana> CV;
    while(ok)
      {
        afisare(cout);
        cout<<"Ce pita doriti sa comandati?\n";
        cout<<"Introduceti id-ul\n";
        int id;
        cin>>id;
        if(id<0 || id >= nr)
          cout<<"Index out of range\n";
        T* elem = v[id];
        Pizza* p = dynamic_cast<Pizza*>(elem);
        if(p)
          {
            Pizza P = *new Pizza(*p);
            C+=P;
          }
        PizzaVegetariana *pv = dynamic_cast<PizzaVegetariana*>(elem);
        if(pv)
          {
            PizzaVegetariana PV = *new PizzaVegetariana(*pv);
            CV += PV;
          }
        cout<<"Mai doriti sa comandati ceva?[1/0]\n";
        cin>>ok;
      }
    cout<<"Comanda dumneavoastra:\n";
    if(C.size())
      {
        cout<<"Normal:\n";
        C.afisare(cout);
        cout<<endl;
      }
    if(CV.size())
      {
        cout<<"Vegetariana:\n";
        CV.afisare(cout);
        cout<<endl;
      }
    cout<<"Total de plata: "<<C.calc_pret() + CV.calc_pret()<<endl;
  }
  void comanda()
  {
    cout<<"Doriti sa comandati Online(1) sau la magazin(2)";
    int optiune;
    cin>>optiune;
    switch(optiune)
      {
      case 1:
        {
          comanda_online();
        }break;
      case 2:
        {
          comanda_standard();
        }break;
      default:
        cout<<"Nu avem aceasta optiune.\n";
      }
  }
  void insert(const T& elem)
  {
    T** buff = new T*[nr+1];
    for(int i=0;i<nr;i++)
      {
        buff[i] = v[i];
      }
    if(v)
      delete[] v;
    v = buff;
    const Pizza* p = dynamic_cast<const Pizza*>(&elem);
    if(p)
      {
        v[nr] = new Pizza(*p);
      }
    const PizzaVegetariana *pv = dynamic_cast<const PizzaVegetariana*>(&elem);
    if(pv)
      {
        v[nr] = new PizzaVegetariana(*pv);
      }
    *v[nr] = elem;
    nr++;
  }
  void operator+=(const T& elem)
  {
    this->insert(elem);
  }
};
template<class T>
ostream& operator<<(ostream& out,Meniu<T>& M)
{
  M.afisare(out);
  return out;
}
