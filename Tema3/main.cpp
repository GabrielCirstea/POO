#include <iostream>
#include <list>
#include <unordered_map>

#include "produs.h"
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
int main()
{
  cout<<"Salutare!\n";
  testPizza();
  return 0;
}
