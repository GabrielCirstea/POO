#include <iostream>
#include "miVectoro.h"
#include "abonat.h"

using namespace std;

class Clienti
{
 private:
  myVector<Abonat> abonati;
 public:
  //Clienti       // daca va fi cumva nevoie vor fi scrisi
  //~Clienti();   //delete abonati
  int size()const{return abonati.size();};
  int get_nrPremium(){return AbonamentPremium::get_count();};
  float get_Bill();
  Abonat& get_client(int index);
  Abonat& operator[](int index);
  void read_client(istream &in);          //citeste un client
  void insert_client(const Abonat& a);
  void afisare(ostream &out) ;

  friend istream& operator>>(istream& in, Clienti &BD);
  friend ostream& operator<<(ostream& out,Clienti &BD);
};
float Clienti::get_Bill()
{
  float suma = 0;
  for(int i=0;i<abonati.size();i++)
    {
      suma+=abonati[i].get_total();
    }
  return suma;
}
Abonat& Clienti::get_client(int index)
{
  if(index < 0)
    index = abonati.size() - index;
  return abonati[index];
}
Abonat& Clienti::operator[](int index)
{
  return this->get_client(index);
}
void Clienti::read_client(istream &in)
{
  Abonat temp;
  in>>temp;
  abonati.push_back(temp);
}
void Clienti::insert_client(const Abonat& a)
{
  abonati.push_back(a);
}
void Clienti::afisare(ostream& out)
{
  int lng = abonati.size();
  if(!lng)
    {
      out<<"Inca nu sunt clienti.\n";
      return;
    }
  for(int i=0;i<lng;i++)
    {
      out<<"---------------------\n";
      out<<"Abonat "<<i<<":"<<endl;
      out<<abonati[i];
    }
  cout<<"....................\n";
}
istream& operator>>(istream& in, Clienti &BD)
{
  BD.read_client(in);
  return in;
}
ostream& operator<<(ostream& out,Clienti &BD)
{
  BD.afisare(out);
  return out;
}
