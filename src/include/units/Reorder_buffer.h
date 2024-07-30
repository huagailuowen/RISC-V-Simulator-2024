#ifndef REORDER_BUFFER_H
#define REORDER_BUFFER_H
#include"Base_unit.h"
#include"../utility/circular_queue.h"
#include "units/Branch_predict.h"
#include "utility/config.h"
#include "utility/util.h"
#include"Bus.h"
class Status;
namespace cpu{
enum class ROB_state{
  STORING,
  WAITING,
  EXCUTING,//have sent to the specific unit, waiting for the result(cd_bus feedback)
  FINISHED//only finished can be committed 
};
struct ROB_item{
  Ins ins;
  int dest;//pos
  ROB_state state;
  DataType value;
  ROB_item()=default;
  ROB_item(Ins ins,int dest,ROB_state state,DataType value=0):ins(ins),dest(dest),state(state),value(value){}
};

class Reorder_buffer:public Base_unit{
public:
  Reorder_buffer(Bus<CD_BUS_SIZE>*cd_bus,Branch_predict* branch_predict);
  ~Reorder_buffer();
  void step(Status&status_cur,Status&status_next);  
  void execute(Status&status_cur,Status&status_next);
  void commit();
private:
  void update_state(Status&status_cur,Status&status_next);
  CircleQueue<ROB_item,ROB_SIZE> rob;
  Bus<CD_BUS_SIZE>* cd_bus;
  Branch_predict* branch_predict;

};
}
#endif