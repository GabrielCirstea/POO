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
  ingredient(ingredient&);
  //get-eri
  const string& get_name()const{return denumire;};
  int get_cant()const{return cantitate;};
  float get_price()const{return pret;};
  //set-eri
  void set_name(string name){denumire = name;};
  void set_cant(int cant){cantitate = cant;};
  void set_price(float price){pret = price;};
  void operator=(ingredient&);
  void afisare(ostream&);
  void citire(istream&);
  friend ostream& operator<<(ostream&, ingredient&);
  friend istream& operator>>(istream&, ingredient&);
};
class produs
{
 public:
  virtual float calc_pret() = 0;
};
class Pizza:public produs
{
 private:
  // ceva ingrediente
  list<ingredient> reteta;
  float manopera;
 public:
  Pizza(list<ingredient>&, float pret);
  Pizza();
};
