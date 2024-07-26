#ifndef BASE_UNIT_H
#define BASE_UNIT_H
#include "../utility/config.h"
#include "../utility/util.h"
namespace cpu{

class Status;
class Base_unit{
public:
  virtual void step(Status&status) = 0;
  virtual void execute(Status&status_cur,Status&status_next) = 0;
  virtual ~Base_unit(){}
};




}

#endif