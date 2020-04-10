#include <iostream>
#include <stdlib.h>

#include "abonament.h"
using namespace std;

#include <iostream>
#include "abonat.h"
#include "abonament.h"
#include "clienti.h"
void Pause()
{
  cout<<"Apasati orice tasta pentru a va intoarce la meniu. ";
  cin.get();
  cin.get();

}
void Clear()
{
#if defined _WIN32
  system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
  system("clear");
#elif defined (__APPLE__)
  system("clear");
#endif
}
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
  Abonament b1("Primul abonament",24.7f,2),b2("Premium",30,2);
  AbonamentPremium c1(20,b2);
  Clienti BD; //baza de date pt clienti;
  Abonat a("12",1,"darve","ceva cnp");
  a2.set_abonament(c1);
  a.set_abonament(b1);
  //cout<<"A1:\n";
  //cout<<a1;
  //cout<<"-------\n";
  BD.insert_client(a);
  BD.insert_client(a2);
  BD.afisare(cout);
  cout<<"Icasari totale: "<<BD.get_Bill()<<endl;
  cout<<"Nr tot abonamente: "<<Abonament::get_count()<<endl;
  cout<<"Nr premium: "<<AbonamentPremium::get_count()<<endl;
}
void insertLaGreu(Clienti &BD)
{
  Abonat a1("123",2,"Gabi","123"), a2("456",3,"Mihai","456");
  Abonament b1("Primul abonament",24.7f,2),b2("Premium",30,2);
  AbonamentPremium c1(20,b2);
  BD.insert_client(a1);
  a1.set_abonament(b1);
  a2.set_abonament(c1);
  BD.insert_client(a1);
  BD.insert_client(a2);
}
void modificare_abonat(Clienti BD, int index)
{//se modifica abonatul index
  cout<<"1. Nume.\n";
  cout<<"2. Numar de telefon.\n";
  cout<<"3. CNP.\n";
  cout<<"4. Abonament.\n";
  cout<<"0. Inapoi\n";
  cout<<"Alegere: ";
  int alegere;cin>>alegere;
  switch(alegere)
    {
    case 1:
      {
        string nume;
        cout<<"Noul nume: ";
        cin>>nume;
        BD[index].set_nume(nume);
      }break;
    case 2:
      {
        cout<<"Noul numar de telefon: ";
        string numar;
        cin>>numar;
        BD[index].set_number(numar);
      }break;
    case 3:
      {
        cout<<"Noul CNP: ";
        string CNP;
        cin>>CNP;
        BD[index].set_CNP(CNP);
      }break;
    case 4:
      {
        cout<<"Noul abonament";
        BD[index].set_readAbon(cin);
      }
    case 0:{
      return;
    }
    }
}
void meniu()
{
  Clienti BD; //baza de date cu clienti
  insertLaGreu(BD);
  bool Running = true;
  do
    {
      int optiune;
      cout<<"Sa lucram cu abonatii:\n";
      cout<<"Optiuni curente:\n";
      cout<<"1.Introducere abonat nou.\n";
      cout<<"2.Afisare abonati inregistrati.\n";
      cout<<"3.Afisare numarului de abonati premium\n";
      cout<<"4.Modificarea unui abonat(id, nume, tel, cnp, abonament).\n";
      cout<<"5.Totalul platit de abonati.\n";
      cout<<"-----\n";
      cout<<"Optiune: ";cin>>optiune;
      switch(optiune)
        {
        case 1:
          {
            BD.read_client(cin);
          }break;
        case 2:
          {
            BD.afisare(cout);
          }break;
        case 3:
          {
            cout<<"Avem "<<BD.get_nrPremium()<<" abonamente premium.\n";
          }break;
        case 4:
          {
            BD.afisare(cout);
            cout<<"Alegeti numarul indexul abonatului: ";
            int index;
            cin>>index;
            if(index<0 || index>BD.size()-1)
              {
                cout<<"Ups..Index invalid.\n";
                break;
              }
            modificare_abonat(BD,index);
          }break;
        case 5:
          {
            cout<<"Suma totala incasata: "<<BD.get_Bill()<<endl;
          }break;
        case 0:
          Running = false;
        }
      Pause();
      Clear();
    }while(Running);
}
int main(){
	cout<<"Salutare lume!\n";
  meniu();
	return 0;
}
