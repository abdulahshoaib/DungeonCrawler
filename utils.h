#include <stdexcept>

template <typename T> class List {
  T *arr;
  int tail;     // index of next insert (also size)
  int capacity; // total allocated slots

  void resize(int);

public:
  List();
  ~List();

  void Append(const T &);
  void RemoveAt(int);
  T &operator[](int);

  const T &operator[](int) const;
  int Size() const;
  bool Empty() const;

  void Clear();
};
