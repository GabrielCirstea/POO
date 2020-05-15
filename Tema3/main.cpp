#include <iostream>
#include <list>
#include <unordered_map>

#include "produs.h"
#include "Meniu.h"
using namespace std;

void testIngred()
{
  ingredient a("nume",3,4);
  ingredient arpagic("arpagic",12,0.3f);
  ingredient shunca("shunca",3,2.15f);
  ingredient motzarela("motzarela",5,3.0f);
  cout<<a<<endl;
  cout<<"Sa citim";
  cin>>a;
  cout<<a;
  ingredient b = a;
  b.set_name("carnat");
  b.set_price(2.04f);
  cout<<"----\n"<<b;
}
void testPizza()
{
  Pizza p1("darve",27.2f);
  ingredient arpagic("arpagic",12,0.3f);
  ingredient shunca("shunca",3,2.15f);
  ingredient motzarela("motzarela",5,3.0f);
  list<ingredient> carne;
  carne.push_back(arpagic);
  carne.push_back(shunca);
  carne.push_back(motzarela);
  ingredient a("nume",3,4);
  p1.set_ingred(carne);
  p1.add_ingred(a);
  cout<<p1<<endl;
  p1.remove_ingred(1);
  cout<<p1<<endl;
  list<ingredient> p;
  p.push_back(a);
  p.push_back(a);
  Pizza p2("nume",p,3);
  cout<<p2;
  cout<<"Sa citim o pizza";
  cin>>p2;
  cout<<p2;
}
template<class S,class T>
void allocatorFunc(S *&trg, T &src)
{
  Pizza* p = dynamic_cast<Pizza*>(&src);
  if(p)
    {
     trg = new Pizza(*p);
    }
  PizzaOnline* po = dynamic_cast<PizzaOnline*>(&src);
  if(po)
    {
      trg = new PizzaOnline(*po);
    }
  PizzaVegetariana *pv = dynamic_cast<PizzaVegetariana*>(&src);
  if(pv)
    {
      trg = new PizzaVegetariana(*pv);
    }
  PizzaVegOnline *pov = dynamic_cast<PizzaVegOnline*>(&src);
  if(pov)
  {
    trg = new PizzaVegOnline(*pov);
  }

}
void testTemplateMeniu()
{
  Pizza p1("darve",27.2f);
  ingredient arpagic("arpagic",12,0.3f);
  ingredient shunca("shunca",3,2.15f);
  ingredient motzarela("motzarela",5,3.0f);
  list<ingredient> carne;
  carne.push_back(arpagic);
  carne.push_back(shunca);
  carne.push_back(motzarela);
  ingredient a("nume",3,4);
  p1.set_ingred(carne);
  p1.add_ingred(a);
  p1.remove_ingred(1);
  list<ingredient> p;
  p.push_back(a);
  p.push_back(a);
  // cout<<p1<<endl;
  PizzaVegOnline p2("nume",p,3);
  cout<<"alocat\n";
  p2.set_distance(29);
  cout<<"setat\n";
  cout<<p2<<endl;
  myVector<PizzaVegOnline> PVVZ;
  PVVZ.push_back(p2); // probleme la copiere cu apelarea constructorului in new
  PVVZ.push_back(p2);
  // cout<<PVVZ[1];
  Pizza *test ;
  cout<<"----Alocare:\n";
  allocatorFunc(test,p2);
  // cout<<*test;
  // delete test;
  return;
  Meniu<Pizza> M;
  // M+=p2;
  // cout<<M[0];
  PizzaVegetariana v1("nume",p,3);
  Pizza *v2;
  v2 = new PizzaVegetariana;
  cout<<"Vegetariana\n";
  cout<<v1<<endl;
  *v2 = v1;
  cout<<*v2<<endl;
  cin>>*v2;
  cout<<"Nr: "<<PizzaVegetariana::numar()<<endl;
}
int main()
{
  cout<<"Salutare!\n";
  testTemplateMeniu();
  return 0;
}
