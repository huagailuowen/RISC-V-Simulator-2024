#ifndef INSTRUCTION_H
#define INSTRUCTION_H


#include "../utility/util.h"
#include "Base_unit.h"
namespace cpu{
class Status;
void decode_U(DataType input,Ins &ins);
void decode_J(DataType input,Ins &ins);
void decode_I(DataType input,Ins &ins);
void decode_S(DataType input,Ins &ins);
void decode_R(DataType input,Ins &ins);
void decode_B(DataType input,Ins &ins);
void decode(DataType input,Ins &ins);
void get_ins(Status *status,Ins &ins);
namespace cpu{
class Instruction_unit:public Base_unit{
public:

  Instruction_unit();
  ~Instruction_unit();
  void fetch();  
  void flush();
  void execute();
  
};
}
}
#endif