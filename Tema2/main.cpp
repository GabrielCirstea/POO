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

void modificare_abonat(Clienti &BD, int index)
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
      }break;
    case 0:{
      return;
      }
    }
}
void meniu()
{
  Clienti BD; //baza de date cu clienti
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
            cin>>BD;
          }break;
        case 2:
          {
            cout<<BD;
          }break;
        case 3:
          {
            cout<<"Avem "<<BD.get_nrPremium()<<" abonamente premium.\n";
          }break;
        case 4:
          {
            cout<<BD;
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
