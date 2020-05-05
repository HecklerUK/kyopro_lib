#include <iostream>

void print() { std::cout << "\n"; }
template <class T, class... Args>
void print(const T &x, const Args &... args) {
  std::cout << x << " ";
  print(args...);
}

int main() {
  int a = 2;
  double b = 3.14;
  print(a, b);
  print(b, a);
}

