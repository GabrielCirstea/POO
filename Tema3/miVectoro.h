using namespace std;
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
  int size() const
  {
    return lung;
  }
  void poster(ostream& out) const
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
  void push_back(const T& elem)
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
  void contentCopy(const myVector<T> v)
  {
    if(vctor)
      delete[] vctor;
    vctor = new T[v.size()];
    lung = v.size();
    for(int i=0;i<lung;i++)
      vctor[i] = v[i];
  }
  ~myVector()
    {
      delete[] vctor;
    }
  void operator=(const myVector<T> v)
    {
     this->contentCopy(v);
    }
};
