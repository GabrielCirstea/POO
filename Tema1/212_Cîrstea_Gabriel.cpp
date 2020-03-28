/// Student Cirstea Gabriel, grupa 212
///tema 18 - clasa de filme: nume, gen, regizor rating
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

#define LUNG_SIR 256     //lungimea sirului

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
        delete[] vctor;
        vctor = buff;
        vctor[lung++] = elem;
    }
    ~myVector()
    {
        delete[] vctor;
    }

};

class film
{
private:
    char *denumire_film;
    char *gen;
    char *regizor;
    float rating;           ///rating pe imdb
public:
    ///constructor
    film();
    film(film& f);
    ///get
    char* get_denumire();
    char* get_gen();
    char* get_regizor();
    float get_rating();
    ///set
    void set_denumire(char*);
    void set_gen(char*);
    void set_regizor(char*);
    void set_rating(float);
    void citire(istream& in);          ///se vor citi denumirea,genul,regizorul si rating-ul
    void afisare(ostream&);
    friend istream& operator>>(istream &in, film &f);
    friend ostream& operator<<(ostream &out, film &f);
    int operator>(film &f);
    int operator<(film &f);
    int operator==(film &f);
    film& operator[](int index);
    film& operator=(film &f);
    ///destructor
    ~film();
};
film::film()
{
    ///initializare cu campuri necolmpletate
    this->denumire_film = new char[LUNG_SIR];
    strcpy(this->denumire_film,"-");
    this->gen = new char[LUNG_SIR];
    strcpy(this->gen,"-");
    this->regizor = new char[LUNG_SIR];
    strcpy(this->regizor,"-");
    this->rating = 0;
}

film::film(film& f)
{//constructor de copiere
    this->denumire_film = new char[LUNG_SIR];
    strcpy(this->denumire_film,f.denumire_film);
    this->gen = new char[LUNG_SIR];
    strcpy(this->gen,f.gen);
    this->regizor = new char[LUNG_SIR];
    strcpy(this->regizor,f.regizor);
    this->rating = f.rating;
}

film::~film()
{
    delete[] this->denumire_film;
    delete[] this->gen;
    delete[] this->regizor;
    this->rating = 0;
}

void film::set_denumire(char *denumire)
{
    strcpy(this->denumire_film,denumire);
}
void film::set_gen(char *gen)
{
    this->gen = new char[LUNG_SIR];
    strcpy(this->gen,gen);
}
void film::set_regizor(char *regizor)
{
    this->regizor = new char[LUNG_SIR];
    strcpy(this->regizor, regizor);
}
void film::set_rating(float rating)
{
    if(rating >= 0 && rating <= 10)
        this->rating = rating;
}

char* film::get_denumire()
{
    return this->denumire_film;
}

void film::citire(istream& in)
{
    cout<<"Denumire: ";
    in.getline(denumire_film,LUNG_SIR);
    cout<<"Genul filmului: ";
    in.getline(gen,LUNG_SIR);
    cout<<"Regizor: ";
    in.getline(regizor,LUNG_SIR);
    cout<<"Rating= ";
    in>>rating;
}

void film::afisare(ostream &out)
{
    out<<"Denumire: "<<denumire_film<<endl;
    out<<"Gen: "<<gen<<endl;
    out<<"Regizor: "<<regizor<<endl;
    out<<"Rating: "<<rating<<endl;
}

istream& operator>>(istream& in,film &f)
{
    f.citire(in);
    return in;
}

ostream& operator<<(ostream& out, film& f)
{
    f.afisare(out);
    return out;
}

film& film::operator=(film& f)
{
    this->denumire_film = new char[20];
    strcpy(this->denumire_film,f.denumire_film);
    this->gen = new char[20];
    strcpy(this->gen,f.gen);
    this->regizor = new char[20];
    strcpy(this->regizor,f.regizor);
    this->rating = f.rating;
}

int film::operator>(film &f)
{
    return this->rating > f.rating ? 1 : 0;
}

int film::operator<(film &f)
{
    return this->rating < f.rating ? 1 : 0;
}

int film::operator==(film &f)
{
    return this->rating == f.rating;
}

film& film::operator[](int index)
{
    return this[index];         ///surprinzator merge
}

///optiunea 2
int afisare_filme(myVector<film> &filme)
{
    if(!filme.get_size())
    {
        cout<<"\nNimic momentan\n";
        return 0;
    }
    for(int i=0;i<filme.get_size();i++)
    {
        cout<<i+1<<"\n"<<filme[i];
        cout<<"---\n";
    }
    return 1;
}

void comparare(myVector<film> &filme)
{///compara 2 filme dupa rating
    afisare_filme(filme);
    int nr = filme.get_size();
    if(nr < 2)
        {
            cout<<"Isuficiente filme pt comparare\n";
            return;
        }
    int index1, index2;
    cout<<"\nAlegeti indexul unui film ";
    cin>>index1;
    cout<<"\nAlegeti indexul altui film ";
    cin>>index2;
    ///mapam indexul de la 1-nr la 0-nr
    index1--;
    if(index1<0 || index1 > nr-1)
    {
        cout<<"Index incorect";
        return;
    }
    index2--;
    if(index2 < 0 || index2 > nr-1)
    {
        cout<<"Index incorect";
        return;
    }
    if(filme[index1] > filme[index2])
        cout<<"\""<<filme[index1].get_denumire()<<"\" este mai popular decat \""
                <<filme[index2].get_denumire()<<"\"\n";
    else
    {
        if(filme[index1] < filme[index2])
            cout<<"\""<<filme[index2].get_denumire()<<"\" este mai popular decat \""
                <<filme[index1].get_denumire()<<"\"\n";
        else
            cout<<"\""<<filme[index1].get_denumire()<<"\" si \""
                <<filme[index2].get_denumire()<<"\" sunt la fel de populare\n";
    }
    ///asteapta pana se apasa enter
    cin.get();
    cin.get();
}

void modificare(myVector<film> &filme)
{
    if(!afisare_filme(filme))
        return;
    cout<<"Alegeti indexul filmului dorit: ";
    int nr = filme.get_size();
    int index;
    cin>>index;
    index--;
    if(index<0 || index > nr-1)
    {
        cout<<"Index incorect";
        return;
    }
    cout<<filme[index];
    cout<<"\n++++++\n";
    cout<<"1. denumire\n";
    cout<<"2. gen\n";
    cout<<"3. regizor\n";
    cout<<"4. rating\n";
    cout<<"\n0. Back\n";
    int optiune;
    cout<<"Optiune: ";
    cin>>optiune;
    cin.get();
    switch(optiune)
    {
        case 0: return;
        case 1:
            {
                char *denumire = new char[LUNG_SIR];
                cout<<"Noua denumire: ";
                cin.getline(denumire,LUNG_SIR);
                filme[index].set_denumire(denumire);
            }break;
        case 2:
            {
                char *gen = new char[LUNG_SIR];
                cout<<"Noul gen: ";
                cin.getline(gen,LUNG_SIR);
                filme[index].set_gen(gen);
            }break;
        case 3:
            {
                char *regizor = new char[LUNG_SIR];
                cout<<"Noul regizor: ";
                cin.getline(regizor,LUNG_SIR);
                filme[index].set_regizor(regizor);
            }break;
        case 4:
            {
                int rating;
                cout<<"Rating= ";
                cin>>rating;
                filme[index].set_rating(rating);
            }break;
    } /// switch

    cout<<"\nDone!\n";
    cout<<filme[index];
    cin.get();
}

void prezentare_optiuni()
{
    cout<<"\n-Meniu-\n";
    cout<<"1. Introducere film\n";
    cout<<"2. Afisare filme\n";
    cout<<"3. Comparare filme\n";
    cout<<"4. Modificare film\n";
    cout<<"\n0. Exit\n";
}

void meniu()
{
    ///creare vector de cartii
    ///afisare vector
    ///editare carti
    ///sa comparam cartiile
    myVector<film> filme;
    //citire_fisier(filme,3);
    bool running = true;
    while(running)
    {
        prezentare_optiuni();
        int optiune;
        cout<<"Optiune: ";
        cin>>optiune;
        cin.get();
        switch(optiune)
        {
        case 0: return;
        case 1:
            {///sa mai citim filme
                film nou;
                cin>>nou;
                filme.push_back(nou);
            }break;
        case 2:
            {
                afisare_filme(filme);
            }break;
        case 3:
            {
                comparare(filme);
            }break;
        case 4:
            {
                modificare(filme);
            }break;
        }//switch
        system("pause");
        system("cls");
    }//while

}

int main()
{
    cout<<"Hello World!\n";
    meniu();
    return 0;
}
