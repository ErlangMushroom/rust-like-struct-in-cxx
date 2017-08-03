#include "struct_base.hpp"
#include <iostream>

struct abc_t : public struct_base_t<abc_t> {
  abc_t(int xx, int yy)
    : x {xx}, y {yy} {
  }
  int x;
  int y;
};

struct abc_getter_t : impl<abc_t> {
  int getx()  {
    return self()->x;
  }
  int gety() {
    return self()->y;
  }
};

struct abc_setter_t : impl<abc_t> {
  void setx(int v) {
    self()->x = v;
  }
  void sety(int v) {
    self()->y = v;
  }
};

struct abc_printer_t : impl<abc_t> {
  void print() {
    std::cout << "  x:" << self()->x
              << "  y:" << self()->y << std::endl;
  }
};

int main() {
  abc_t* abc = abc_t::create(22, 33);
  abc_printer_t* printer = (abc_printer_t*)abc;
  printer->print();
  abc_setter_t* setter = (abc_setter_t*)abc;
  setter->setx(44);
  setter->sety(55);
  printer->print();
  return 0;
}