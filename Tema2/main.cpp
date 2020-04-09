#include <iostream>
#include <stdlib.h>

#include "abonament.h"
using namespace std;

#include <iostream>
#include "abonat.h"
#include "abonament.h"
#include "clienti.h"

using namespace std;

void testAbonat()
{
	Abonat a("12",1,"darve","ceva cenp");
  cin>>a;
  Abonat b = a;
	cout<<b<<endl;
	cin>>b;
	cout<<"----\n";
	cout<<b;
  cout<<"Total de plata: "<<b.get_total()<<endl;
  cout<<"Nr abonamente normale: "<<Abonament::get_count()<<endl;
  cout<<"Nr abonamente Premium: "<<AbonamentPremium::get_count()<<endl;
  Abonament ab;   //aici se noteaza un abonament in plus
  cin>>ab;
  b.set_abonament(ab);
  cout<<"Nr abonamente normale: "<<Abonament::get_count()<<endl;
  cout<<"Nr abonamente Premium: "<<AbonamentPremium::get_count()<<endl;
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
void testClienti()
{
  Abonat a1("123",2,"Gabi","123"), a2("456",3,"Mihai","456");
  Abonament b1("Primul abonament",24.7f,23),b2("Premium",30,2);
  AbonamentPremium c1(20,b2);
  Clienti BD; //baza de date pt clienti;
  Abonat a("12",1,"darve","ceva cnp");
  a.set_abonament(b1);
  a2.set_abonament(c1);
  cout<<"A2:\n";
  cout<<a2;
  cout<<"-------\n";
  BD.insert_client(a);
  cout<<BD[0];
  BD.insert_client(a2);
  BD.afisare(cout);
  //cout<<"Icasari totale: "<<BD.get_Bill();
  cout<<"Nr tot abonamente: "<<Abonament::get_count()<<endl;
  cout<<"Nr premium: "<<AbonamentPremium::get_count()<<endl;
}
int main(){
	cout<<"Salutare lume!\n";
  testClienti();
	return 0;
}
