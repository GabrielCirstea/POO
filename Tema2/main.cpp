#include <iostream>
#include <stdlib.h>

#include "abonament.h"
using namespace std;

#include <iostream>
#include "abonat.h"
#include "abonament.h"

using namespace std;

void testAbonat()
{
	Abonat a("12",1,"darve","ceva cenp");
  Abonat b(a);
	system("clear");
	cout<<b<<endl;
	cin>>b;
	cout<<"----\n";
	cout<<b;
  cout<<"Total de plata: "<<b.get_total()<<endl;
}
void testAbonament()
{
	Abonament ab("primul abonament",24.7f,23);
	cout<<ab;
	AbonamentPremium ac(20,ab);
	cout<<ab;
	cout<<Abonament::get_count()<<endl;
	cin>>ac;
	cout<<"---\n"<<ac;
}
int main(){
	cout<<"Salutare lume!\n";
  testAbonat();
	return 0;
}
