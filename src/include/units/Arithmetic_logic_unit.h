#ifndef ARITHMETIC_LOGIC_UNIT_H
#define ARITHMETIC_LOGIC_UNIT_H
#include"Base_unit.h"
#include "units/Bus.h"
#include "utility/config.h"
#include "utility/util.h"
#include"utility/container.h"

// Your code goes here
namespace cpu{

class Status;
enum class ALU_type{  
  ADD,
  MUL
};
class ALU_unit{
public:
  ALU_unit(DataType input1,DataType input2,Opt op,int dest);
  void execute();
  bool step();
  DataType output;
  int dest;
private:
  DataType input1,input2;
  Opt op;
  int latency;
};
ALU_type get_ALU_type(Opt op);
int get_latency(ALU_type type);

class Arithmetic_logic_unit:public Base_unit{
public:
  Arithmetic_logic_unit(Bus<CD_BUS_SIZE>*cd_bus);
  ~Arithmetic_logic_unit();
  void step(Status&status_cur,Status&status_next);  
  void execute(Status&status_cur,Status&status_next);
private:
  Bus<CD_BUS_SIZE> *cd_bus;
  Container<ALU_unit, 5>add;
  //I decide to mix them.
};


}


#endif // ARITHMETIC_LOGIC_UNIT_H