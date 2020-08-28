#pragma once
using namespace std;
#include <iostream>
#include <list>
#include <unordered_map>
class ingredient
{
 private:
  string denumire;
  int cantitate;
  float pret;
 public:
  ingredient(string,int,float);
  ingredient(const ingredient&);
  //~ingredient() // elementele sunt alocate static
  //get-eri
  const string& get_name()const{return denumire;};
  int get_cant()const{return cantitate;};
  float get_price()const{return pret;};
  //set-eri
  void set_name(string name){denumire = name;};
  void set_cant(int cant){cantitate = cant;};
  void set_price(float price){pret = price;};
  void operator=(const ingredient&);
  bool operator==(const ingredient&) const;
  void afisare(ostream&) const;
  void citire(istream&);
};
ostream& operator<<(ostream&,const ingredient&);
istream& operator>>(istream&,ingredient&);
//----PRODUS-----
class produs
{
 public:
  // produs(){cout<<"produs\n";};
  virtual float calc_pret() const = 0;
  virtual void afisare(ostream&) const = 0;
  virtual void citire(istream&) = 0;
};
// nu e nevoie de firend, in >>/<< apelez functia de citire/afisare
// print virtual pe afisare/citire in produs, nu e nevoie sa supra incarc operatorii <</>> si pt clasele derivate
ostream& operator<<(ostream&,const produs&);
istream& operator>>(istream&,produs&);
//----PIZZA-----
class Pizza:virtual public produs
{
protected:
  string denumire;
  // ceva ingrediente
  list<ingredient> reteta;
  const float manopera;  // poate ca o putem face statica, sa fie acceasi pt toate pizza
 public:
  Pizza(string, list<ingredient>&, float pret = 0);   // pret manopera
  Pizza(string nume = "",float pret = 0);
  Pizza(const Pizza&);
  //~Pizza();  // elementele sunt alocate static
  //get-eri
  float get_manopera() const {return manopera;};
  const list<ingredient>& get_ingred() const {return reteta;};
  float calc_pret() const; // pretul total al produsului
  //set-eri
  void set_ingred(list<ingredient>& ingred); // seteaza o noua lista de ingrediente
  void add_ingred(ingredient& ingred); // adauga inca un gredient.
  void remove_ingred(int index); // sterge ingredientul dupa index(afisat in listare)
  void remove_ingred(const string& nume); // sterge prima aparitie a ingredientului cu numele dat
  // output
  void list_ingred() const;  // listeaza ingredientele.
  virtual void afisare(ostream&) const;
  // input
  virtual void citire(istream&);
  void operator=(const Pizza&);
};
//----------------PIZZA vegetala--------------
class PizzaVegetariana:virtual public Pizza
{   // nimic special cu pizza vegetariana fata de cea normala
    // are o variabila statica
protected:
  static int numarVegetale;
  int porumb;
public:
  PizzaVegetariana(string, list<ingredient>&, float pret = 0);   // pret manopera
  PizzaVegetariana(string nume = "",float pret = 0);
  PizzaVegetariana(const PizzaVegetariana&);
  PizzaVegetariana(const Pizza&);
  ~PizzaVegetariana();
  static int numar();
  void afisare(ostream&) const;
  void citire(istream&);
  void operator=(const PizzaVegetariana&);
};
//-------------ONLINE-----------
class produsOnline: virtual public produs
{
protected:
  float distanta;
public:
  produsOnline(int dist = 0):distanta(dist){}
  // virtual float calc_pret()=0;
  float get_distance()const{return distanta;};
  void set_distance(float dist=0){distanta = dist;};
};
class PizzaOnline:virtual public Pizza, virtual public produsOnline
{
public:
  PizzaOnline(string, list<ingredient>&, float pret = 0, float dist = 0);   // pret manopera
  PizzaOnline(string nume = "",float pret = 0, float dist = 0);
  PizzaOnline(Pizza&, float dist=0);
  PizzaOnline(PizzaOnline&);
  float calc_pret() const;
  void afisare(ostream&) const;
  void citire(istream&);
  void operator=(const PizzaOnline&);
};
class PizzaVegOnline: public PizzaVegetariana,public PizzaOnline
{
public:
  PizzaVegOnline(string, list<ingredient>&, float pret = 0, float dist = 0);
  PizzaVegOnline(string nume = "",float pret = 0, float dist = 0);
  PizzaVegOnline(Pizza&, float dist=0);
  PizzaVegOnline(PizzaOnline&);
  float calc_pret() const;
  void afisare(ostream&) const;
  void citire(istream&);
  void operator=(const PizzaVegOnline&);
};
