#ifndef LOAD_STORE_BUFFER_H
#define LOAD_STORE_BUFFER_H
#include"base_unit.h"
#include"../utility/config.h"
#include "units/Bus.h"
#include "utility/circular_queue.h"
namespace cpu{
class Status;
struct LSB_item{
  Ins ins;
  bool ready;
  int Vj,Vk;
  int A;// can be also used as the result of loaded data
  int Qj,Qk;
  int dest;
  bool finished;
  bool store_begin;
  LSB_item():ready(false),Vj(0),Vk(0),A(0),Qj(-1),Qk(-1),dest(-1),finished(false),store_begin(false){}
  LSB_item(Ins ins):ins(ins),ready(false),Vj(0),Vk(0),A(0),Qj(-1),Qk(-1),dest(-1),finished(false),store_begin(false){}
};
class Load_Store_buffer:public Base_unit{
public:
  Load_Store_buffer(Bus<CD_BUS_SIZE>*cd_bus,Bus<MEM_BUS_SIZE>*mem_bus);
  void step(Status&status_cur,Status&status_next);
  //receive the signal from the mem_bus
  void execute(Status&status_cur,Status&status_next);
  //tell the mem what to do
  //send the signal to the mem_bus
private:
  void update_state(Status&status_cur,Status&status_next);
  Bus<CD_BUS_SIZE>* cd_bus;
  //monitor the cd_bus
  Bus<MEM_BUS_SIZE>* mem_bus;  
  CircleQueue<LSB_item,LSB_SIZE>items;
};

}

#endif