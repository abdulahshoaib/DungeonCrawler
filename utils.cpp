#include "core.h"
template class List<UIElement>;

template <typename T> void List<T>::resize(int newCap) {
  T *newArr = new T[newCap];
  for (int i = 0; i < tail; ++i)
    newArr[i] = arr[i];
  delete[] arr;
  arr = newArr;
  capacity = newCap;
}

template <typename T> List<T>::List() {
  int initialCap = 4;
  arr = new T[initialCap];
  capacity = initialCap;
  tail = 0;
}

template <typename T> List<T>::~List() { delete[] arr; }

template <typename T> void List<T>::Append(const T &obj) {
  if (tail >= capacity)
    resize(capacity * 2);
  arr[tail++] = obj;
}

template <typename T> void List<T>::RemoveAt(int index) {
  if (index < 0 || index >= tail)
    throw std::out_of_range("Invalid index");
  for (int i = index; i < tail - 1; ++i)
    arr[i] = arr[i + 1];
  tail--;
}

template <typename T> T &List<T>::operator[](int index) {
  if (index < 0 || index >= tail)
    throw std::out_of_range("Invalid index");
  return arr[index];
}

template <typename T> const T &List<T>::operator[](int index) const {
  if (index < 0 || index >= tail)
    throw std::out_of_range("Invalid index");
  return arr[index];
}

template <typename T> int List<T>::Size() const { return tail; }

template <typename T> bool List<T>::Empty() const { return tail == 0; }

template <typename T> void List<T>::Clear() { tail = 0; }
