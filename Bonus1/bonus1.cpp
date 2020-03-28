///student Cîrstea Gabriel, grupa 212
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

#define STR_LNG 256


template<typename T>
class myVector
{///pt a usura lucrul cu vectorii
    T* vctor;
    int lung;
public:
    myVector(int size = 0)
    {
        lung = size;
        if(size)
            vctor = new T[lung];
        else
            vctor = NULL;
    }
    int get_size()
    {
        return lung;
    }
    void poster(ostream& out)
    {///afisare
        for(int i=0;i<lung;i++)
        {
            out<<vctor[i]<<endl;
        }
    }
    T& operator[](int index)
    {
        return vctor[index];
    }
    void push_back(T& elem)
    {
        T* buff = new T[lung+1];
        for(int i=0;i<lung;i++)
        {
            buff[i] = vctor[i];
        }
        if(vctor)
            delete[] vctor;
        vctor = buff;
        vctor[lung++] = elem;
    }
    ~myVector()
    {
        delete[] vctor;
    }

};


class Produs
{
private:
    char* data;
    char *nume;
    float pret;
    //data ?
    float cantitate;
    char* masura;
    /*union{
        float greutate;
        float volum;
        int bucata;
        } Masura;*/
public:
    Produs(char*,char*,float,float,char*);
    ~Produs();

    ///get
    char* get_date(){return data;};
    char* get_nume(){return nume;};
    float get_pret(){return pret;};
    float get_cant(){return cantitate;};
    char* get_masura(){return masura;};
    ///set
    void set_nume(char*);
    void set_pret(float);
    void set_cant(float);

    void afisare(ostream& out);
    void citire(istream& in);

    friend ostream& operator<<(ostream& out, Produs& p);
    friend istream& operator>>(istream& in, Produs& p);
    Produs& operator[](int index){ return this[index];};
    Produs& operator=(Produs&);
};
Produs::Produs(char* data=(char*)"",char *nume=(char*)"",float pret = 0,float cantitate = 0,char* masura=(char*)"")
{
    if(strlen(data))
    {
        this->data= new char[strlen(data)];
        strcpy(this->data,data);
    }
    else
        this->data = NULL;
    if(strlen(nume))
    {
        this->nume = new char[strlen(nume)];
        strcpy(this->nume,nume);
    }
    else
        this->nume = NULL;
    this->pret = pret;
    this->cantitate = cantitate;
    if(strlen(masura))
    {
        this->masura = new char[strlen(masura)];
        strcpy(this->masura,masura);
    }
    else
        this->masura = NULL;
}
Produs::~Produs()
{
    delete[] nume;
}

void Produs::set_nume(char* nume)
{
    if(!strlen(nume))
        return;
    if(this->nume)
    {
        delete[] this->nume;
        this->nume = new char[strlen(nume)];
        strcpy(this->nume,nume);
    }
}
void Produs::set_pret(float pret)
{
    this->pret = pret;
}
void Produs::set_cant(float cant)
{
    cantitate = cant;
}

void Produs::afisare(ostream& out)
{
    out<<"Data: "<<data<<endl;
    out<<"Nume: "<<nume<<endl;
    out<<"Pret: "<<pret<<" per "<<masura<<endl;
    out<<"Cantitate "<<cantitate<<endl;
}
void Produs::citire(istream& in)
{
    this->data = new char[STR_LNG];
    cout<<"Data: ";
    in.getline(data,STR_LNG);
    this->nume = new char[STR_LNG];
    cout<<"nume produs: ";
    in.getline(nume,STR_LNG);
    cout<<"Pret: ";
    in>>pret;
    in.get();
    cout<<"Unitatea de masura ";
    masura = new char[STR_LNG];
    in.getline(masura,STR_LNG);
    cout<<"Cantitatea ";
    in>>cantitate;
    in.get();
}
ostream& operator<<(ostream& out, Produs& p)
{
    p.afisare(out);
    return out;
}
istream& operator>>(istream& in, Produs& p)
{
    p.citire(in);
    return in;
}
Produs& Produs::operator=(Produs& p)
{
    if(strlen(p.data))
    {
        this->data= new char[strlen(p.data)];
        strcpy(this->data,p.data);
    }
    else
        this->data = NULL;
    if(strlen(p.nume))
    {
        this->nume = new char[strlen(p.nume)];
        strcpy(this->nume,p.nume);
    }
    else
        this->nume = NULL;
    this->pret = p.pret;
    this->cantitate = p.cantitate;
    if(strlen(p.masura))
    {
        this->masura = new char[strlen(p.masura)];
        strcpy(this->masura,p.masura);
    }
    else
        this->masura = NULL;
}

class Magazin
{
private:
    char *numeMg;
    Produs *produse;
    int n;
public:
    Magazin(int);
    ~Magazin();
    int cautare(char*);
    void sterge(char*);
    void recivetAt(char*);
    void afisare(ostream& out);
    void citire(istream& in);
    void setPrice(char*,float);

    Magazin& operator=(Magazin& mg);
    friend ostream& operator<<(ostream& out, Magazin& mg);
    friend istream& operator>>(istream& in, Magazin& mg);

    int ger_nrProd(){return n;};
    char* get_numeMg(){return  numeMg;};

};
Magazin::Magazin(int n=0)
{
    this->n = n;
    if(n)
        produse = new Produs[n];
}
Magazin::~Magazin()
{
    if(n)
        delete[] produse;
}
void Magazin::afisare(ostream& out)
{
    //out<<"magazinul "<<numeMg<<endl;
    out<<"Are "<<n<<" produse\n";
    for(int i=0;i<n;i++)
        cout<<produse[i]<<endl;
}
void Magazin::citire(istream& in)
{
    cout<<"nur de produse";
    in>>n;
    in.get();
    if(n>0)
    {
        produse = new Produs[n];
        for(int i=0;i<n;i++)
        cin>>produse[i];
    }
}
ostream& operator<<(ostream& out, Magazin& mg)
{
    mg.afisare(out);
    return out;
}
istream& operator>>(istream& in, Magazin& mg)
{
    mg.citire(in);
    return in;
}
Magazin& Magazin::operator=(Magazin& mg)
{
    this->numeMg = new char[STR_LNG];
    //strcpy(this->nume,mg.nume);
    this->n = mg.n;
    if(mg.n>0)
    {
        this->produse = new Produs[mg.n];
        for(int i=0;i<mg.n;i++)
        {
            this->produse[i]=mg.produse[i];
        }
    }
}
int Magazin::cautare(char* nume)
{
    for(int i=0;i<n;i++)
    {
        if(strcmp(nume,produse[i].get_nume())==0)
            return i;
    }
    return -1;
}
void Magazin::sterge(char* numeProd)
{
    int index = cautare(numeProd);
    if(index<0)
        return;
    Produs *tmp = new Produs[n-1];
    for(int i = 0;i<index;i++)
        tmp[i] = produse[i];
    for(int i = index;i<n-1;i++)
    {
        tmp[i] = produse[i+1];
    }
    delete[] produse;
    produse = tmp;
    n--;
}
void Magazin::recivetAt(char* date)
{
    for(int i=0; i<n; i++)
    {
        if(strcmp(date,produse[i].get_date()))
            cout<<produse[i];
    }
}
void Magazin::setPrice(char* nume, float pret)
{
    int index = cautare(nume);
    if(index>-1)
    {
        produse[index].set_pret(pret);
    }
}
void meniu()
{
    myVector<Magazin> magazine;
    int optiune;
    bool running = true;
    while(running)
    {
        cout<<"optiuni:\n";
        cout<<"1. Adaugarea unui magazin\n";
        cout<<"2. Afisarea tuturor magazinelor si produselor comerciale\n";
        cout<<"3. Afisarea tuturor produselor primite la o anumita data\n";
        cout<<"4. Stergerea unui produs dintr-un magazin, dupa nume\n";
        cout<<"5. Modificarea pretului unui produs\n";
        cout<<"6. Afisarea magazinului cu cele mai multe produse\n";
        cout<<"0. iesire\n";
        cout<<"\n Optiunea dumneavoastr:";
        cin>>optiune;
        cin.get();
        switch(optiune)
        {
        case 1:
            {
                Magazin aux;
                cin>>aux;
                magazine.push_back(aux);
            }break;
        case 2:
            {
                for(int i=0;i<magazine.get_size();i++)
                {
                    cout<<"Nr: "<<i<<endl;
                    cout<<magazine[i];
                }
            }break;
        case 3:
            {
                char data[STR_LNG];
                cout<<"Introduceti data:";
                cin.getline(data,STR_LNG);
                for(int i=0;i<magazine.get_size();i++)
                {
                    magazine[i].recivetAt(data);
                }
            }break;
        case 4:
            {
                int indexMagazin;
                cout<<"Introduceti numarul magazinului ";
                cin>>indexMagazin;cin.get();
                if(indexMagazin<0 || indexMagazin > magazine.get_size())
                    cout<<"Indexul nu e bun";
                else{
                    char nume[STR_LNG];
                    cout<<"Introduceti numele produsului";
                    cin.getline(nume,STR_LNG);
                    magazine[indexMagazin].sterge(nume);

                    cout<<magazine[indexMagazin];

                }
            }break;
        case 5:
            {
                char nume[STR_LNG];
                float pret;
                cout<<"Nume produs ";
                cin.getline(nume,STR_LNG);
                cout<<"Pret ";
                cin>>pret;
                for(int i=0;i<magazine.get_size();i++)
                {
                    magazine[i].setPrice(nume,pret);
                }
            }break;
        case 6:
            {
                int mult = 0;
                for(int i =1;i<magazine.get_size();i++)
                {
                    if(magazine[i].get_numeMg() > magazine[mult].get_numeMg())
                        mult = i;
                }
                cout<<magazine[mult];
            }break;
        case 0:
            {
                running = false;
            }break;
        }// switch
        system("Pause");
        system("clear");
    }
}

int main()
{
    cout << "Hello world!" << endl;
    meniu();
    return 0;
}
