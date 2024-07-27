#ifndef REORDER_BUFFER_H
#define REORDER_BUFFER_H
#include"Base_unit.h"
#include"../utility/circular_queue.h"
#include "utility/util.h"
class Status;
namespace cpu{
enum class ROB_state{
  READY,
  
  FINISHED
};
struct ROB_item{
  Ins ins;
  int dest;//pos
  DataType value;
  ROB_state state;
  ROB_item(Ins ins,int dest,ROB_state state,DataType value=0):ins(ins),dest(dest),state(state),value(value){}
};

class Reorder_buffer:public Base_unit{
public:
  Reorder_buffer();
  ~Reorder_buffer();
  void step(Status&status_cur,Status&status_next);  
  void execute(Status&status_cur,Status&status_next);
  void commit();
private:
  void update_state(Status&status_cur,Status&status_next);
  CircleQueue<ROB_item> rob;

};
}
#endif