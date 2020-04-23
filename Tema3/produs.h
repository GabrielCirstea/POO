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
  //get-eri
  const string& get_name()const{return denumire;};
  int get_cant()const{return cantitate;};
  float get_price()const{return pret;};
  //set-eri
  void set_name(string name){denumire = name;};
  void set_cant(int cant){cantitate = cant;};
  void set_price(float price){pret = price;};
  void operator=(const ingredient&);
  void afisare(ostream&);
  void citire(istream&);
  friend ostream& operator<<(ostream&, ingredient&);
  friend istream& operator>>(istream&, ingredient&);
};
//----PRODUS-----
class produs
{
 public:
  virtual float calc_pret() = 0;
};
//----PIZZA-----
class Pizza:public produs
{
 private:
  string denumire;
  // ceva ingrediente
  list<ingredient> reteta;
  float manopera;  // poate ca o putem face statica, sa fie acceasi pt toate pizza
 public:
  Pizza(string, list<ingredient>&, float pret);   // pret manopera
  Pizza(string,float);
  Pizza(Pizza&);
  //get-eri
  float get_manopera() const {return manopera;};
  const list<ingredient>& get_ingred() const {return reteta;};
  float calc_pret(); // pretul total al produsului
  //set-eri
  void set_manopera(float pret){manopera = pret;};
  void set_ingred(list<ingredient>& ingred); // seteaza o noua lista de ingrediente
  void add_ingred(ingredient& ingred); // adauga inca un gredient.
  void remove_ingred(int index); // sterge ingredientul dupa index(afisat in listare)
  void remove_ingred(const string& nume); // sterge prima aparitie a ingredientului cu numele dat
  // output
  void list_ingred();  // listeaza ingredientele.
  void afisare(ostream&);
  friend ostream& operator<<(ostream&,Pizza&);
  // input
  void citire(istream&);
  friend istream& operator>>(istream&,Pizza&);
  void operator=(Pizza&);
};
