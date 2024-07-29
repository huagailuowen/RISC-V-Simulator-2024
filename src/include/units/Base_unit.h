#ifndef BASE_UNIT_H
#define BASE_UNIT_H
namespace cpu{

class Status;
class Base_unit{
public:
  virtual void step(Status&status_cur,Status&status_next) = 0;
  virtual void execute(Status&status_cur,Status&status_next) = 0;
  virtual ~Base_unit(){}
};


}

#endif