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
  unordered_map<int,list<ingredient> > lista;
  // la citire bagam ingredientele
  // la comenzi facem Pizza si calculam pretul
};

//-------comanda---------
template <class T>
class Comanda
{
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
};
template <>
class Comanda_Online<PizzaVegetariana>:public Comanda<PizzaVegetariana>
{
  static int vegetaleOnline;
  //distata
public:
  Comanda_Online();
  Comanda_Online(const PizzaVegetariana&);
  Comanda_Online(const Comanda_Online&);
  ~Comanda_Online();
  float calc_pret() const;
};
