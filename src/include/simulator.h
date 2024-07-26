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
  Opt op;
  int dest; 
  DataType input1,input2;
};
struct LSB_signal{

};
struct ALU_signal{

};
struct ROB_signal{

};

using std::pair;
struct Status{
  AddrType pc;
  DataType opcode;
  Ins ins;
  register_file regs;
  void init(AddrType addr=0)
  {
    pc=addr;
    halt=false;
    roll_back=false;
    regs.init();
    having_predicted=false;
    predict_res=false;
    alu_full=false;
    rs_signal.first=false;
    ins_stall=true;
  }
  bool halt,roll_back,ins_stall;
  
  pair<bool,RS_signal> rs_signal;
  bool alu_full;
  bool having_predicted, predict_res;
};

class Simulator{
public:
  void run();
  void step();
  void execute();
  
  void init(AddrType start_addr);
  Base_unit* units[6];
  Simulator();
  ~Simulator();

private:
  Status status_cur,status_next;
  Bus<CD_BUS_SIZE> cd_bus;
  Bus<MEM_BUS_SIZE> mem_bus;
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