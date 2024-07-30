#ifndef INSTRUCTION_H
#define INSTRUCTION_H


#include "../utility/util.h"
#include "Base_unit.h"
#include "utility/circular_queue.h"
#include"Branch_predict.h"
namespace cpu{
class Status;
void decode_U(DataType input,Ins &ins);
void decode_J(DataType input,Ins &ins);
void decode_I(DataType input,Ins &ins);
void decode_S(DataType input,Ins &ins);
void decode_R(DataType input,Ins &ins);
void decode_B(DataType input,Ins &ins);
void decode(DataType input,Ins &ins);
void get_ins(Status &status,Ins &ins);

class Instruction_unit:public Base_unit{
public:

  Instruction_unit()=default;
  ~Instruction_unit();
  void step(Status&status_cur,Status&status_next);  
  void execute(Status&status_cur,Status&status_next);
  void launch(Status&status_cur,Status&status_next);
private:
  CircleQueue<Ins>ins_q;
  Branch_predict predictor;
};
}
#endif