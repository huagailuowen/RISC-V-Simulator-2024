#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "units/Base_unit.h"
#include "units/Memory.h"
#include "units/Instruction.h"
#include "utility/util.h"
#include "units/Register_file.h"
// #include "units/Arithmetic_logic_unit.h"
// #include "units/Bus.h"
// #include "units/Load_store_buffer.h"
// #include "units/Reorder_buffer.h"
// #include "units/Reservation_station.h"


// Your code goes here

namespace cpu{

struct Status{
  AddrType pc;
  DataType opcode;
  register_file regs;
  void init()
  {
    pc=0;
    halt=0;
    regs.init();
  }
  bool halt;
};

// class Simulator{
// public:
//   void run();
//   void step();
//   void execute();
  
//   void init(AddrType start_addr);
//   Base_unit* memory_unit;
//   Base_unit* instruction_unit;
//   Simulator();
//   ~Simulator();
// private:
//   Status status_cur,status_next;
// };

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