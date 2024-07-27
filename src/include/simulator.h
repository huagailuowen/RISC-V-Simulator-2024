#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "units/Base_unit.h"
#include "units/Memory.h"
#include "units/Instruction.h"
#include "utility/util.h"
#include "units/Register_file.h"
#include "units/Arithmetic_logic_unit.h"
#include "units/Bus.h"
#include "units/Load_store_buffer.h"
#include "units/Reorder_buffer.h"
#include "units/Reservation_station.h"
#include"units/Branch_predict.h"


// Your code goes here

namespace cpu{
struct RS_signal{
  Ins ins;
  int dest;
};
struct Store_Permission_signal{
  int dest;
};
struct LSB_signal{
  Ins ins;
  int dest;
};
struct ALU_signal{
  Opt op;
  int dest; 
  DataType input1,input2;

};
struct ROB_signal{
  Ins ins;
};

using std::pair;
struct Status{
  AddrType pc;
  DataType opcode;
  Ins ins;
  register_file regs;
  void init(AddrType addr,Memory* memory )
  {
    memory_=memory;
    pc=addr;
    halt=false;
    roll_back=false;
    regs.init();
    having_predicted=false;
    predict_res=false;
    alu_full=false;
    alu_signal.first=false;
    ins_stall=true;

  }
  bool halt,roll_back,ins_stall;
  
  pair<bool,ALU_signal> alu_signal;//tell ALU what to do
  pair<bool,ROB_signal> rob_signal;//tell ROB what to do
  pair<bool,LSB_signal> lsb_signal;//tell LSB what to do
  pair<bool,RS_signal> rs_signal;//tell RS what to do
  bool alu_full;
  bool rob_full;
  bool lsb_full;
  bool rs_full;
  bool having_predicted, predict_res;
  Memory* memory_;
};

class Simulator{
public:
  void run();
  void step();
  void execute();
  //Hint: the unit will first execute then step to next state
  //Hint: before the execution, the bus should be cleared, which store the data from this circle
  //state_cur.ins means the ins to be push into the queue
  //and if ins_stall == true like the case in the very first cycle, we should not execute 
  void init(AddrType start_addr);
  Base_unit* units[5];
  Memory* memory;
  Simulator();
  ~Simulator();

private:
  Status status_cur,status_next;
  Bus<CD_BUS_SIZE> cd_bus;//the cd_bus will be clear in every cycle
  Bus<MEM_BUS_SIZE> mem_bus;//the mem_bus won't be clear in every cycle, for memory is slow and need time to finish its task
  uint32_t clock_;
};






class Naive_Simulator{
public:
  int run();
  void step();
  
  void init(AddrType start_addr);
  Base_unit* memory_unit;
  Naive_Simulator();
  ~Naive_Simulator();
private:
  Status status_cur,status_next;
};  

}

#endif // SIMULATOR_H