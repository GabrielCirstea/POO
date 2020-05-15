#pragma once
#include <iostream>
#include <list>
#include <unordered_map>
#include "produs.h"
#include "miVectoro.h"

using namespace std;

template<class T>
class Meniu
{
private:
  // deci structura e un rahat
  unordered_map<int,list<ingredient> > lista;
  // la citire bagam ingredientele
  // la comenzi facem Pizza si calculam pretul
  // sa retinem si Pizza intr-un vector pt RTTI?
  // si ce mai facem cu map ?
};

//-------comanda---------
template <class T>
class Comanda
{ // construieste Pizza din ingredientele date  si calculeaza pretul
  myVector<T> v;
public:
  Comanda();
  Comanda(const T&);
  Comanda(const Comanda&);
  ~Comanda();
  const myVector<T>& get_list() const {return v;};
  int size() const {return v.size();};
  virtual float calc_pret() const;
  virtual void afisare(ostream&) const;
  void insert(const T&);    // adaugam Pizza in comanda
  void operator+=(const T&);
};
//------specializare online--------
template <class T> class Comanda_Online: public Comanda<T>
{
private:
  static int vanzariOnline;
  //distanta
public:
  Comanda_Online();
  Comanda_Online(const T&);
  Comanda_Online(const Comanda_Online&);
  ~Comanda_Online();
  float calc_pret() const;
  void add_to_order(const T&);  // se mai adauga un produs in comanda
};
template <>
class Comanda_Online<PizzaVegetariana>:public Comanda<PizzaVegetariana>
{
  static int vegetaleOnline;  // tinem minte cat am facut din vegetale
public:
  Comanda_Online();
  Comanda_Online(const PizzaVegetariana&);
  Comanda_Online(const Comanda_Online&);
  ~Comanda_Online();
  float calc_pret() const;
};
