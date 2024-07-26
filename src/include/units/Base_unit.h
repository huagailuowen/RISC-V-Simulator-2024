#ifndef BASE_UNIT_H
#define BASE_UNIT_H
#include "../utility/config.h"
#include "../utility/util.h"
namespace cpu{


class Base_unit{
public:
  virtual void flush() = 0;
  virtual void execute() = 0;
  virtual ~Base_unit(){}
};




}

#endif