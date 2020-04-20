#include <iostream>
#include <list>
#include <unordered_map>

#include "produs.h"
using namespace std;

void testIngred()
{
  ingredient a("nume",3,4);
  cout<<a<<endl;
  cout<<"Sa citim";
  cin>>a;
  cout<<a;
  ingredient b = a;
  b.set_name("carnat");
  b.set_price(2.04f);
  cout<<"----\n"<<b;
}
int main()
{
  cout<<"Salutare!\n";
  return 0;
}
