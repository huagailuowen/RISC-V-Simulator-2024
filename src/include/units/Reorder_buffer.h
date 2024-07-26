#ifndef REORDER_BUFFER_H
#define REORDER_BUFFER_H
#include"Base_unit.h"
#include"../utility/circular_queue.h"
class Status;
namespace cpu{
enum class ROB_state{
  READY,
  EXECUTING,
  FINISHED
};
struct ROB_item{
  Ins ins;
  int dest;//pos
  ROB_state state;
  
};

class Reorder_buffer:public Base_unit{
public:
  Reorder_buffer();
  ~Reorder_buffer();
  void step(Status * status);  
  void execute();
  void commit();
private:
  CircleQueue<ROB_item> rob;

};
}
#endif