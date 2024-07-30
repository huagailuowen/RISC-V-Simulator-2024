#include"include/simulator.h"
// #include"Memory.h"

#include "include/units/Instruction.h"
#include "include/utility/util.h"
#include "units/Branch_predict.h"
#include "units/Memory.h"
#include "utility/config.h"
namespace cpu{
Simulator::Simulator()
{
  clock_=0;
  memory=new Memory(&mem_bus);
  units[4] = new Instruction_unit();
  Branch_predict* branch_predict = dynamic_cast<Instruction_unit*>(units[4])->get_predictor();
  units[1] = new Arithmetic_logic_unit(&cd_bus);
  units[0] = new Load_Store_buffer(&cd_bus,&mem_bus);
  units[2] = new Reorder_buffer(&cd_bus,branch_predict);
  units[3] = new Reservation_station(&cd_bus);
  naive_simulator=new Naive_Simulator();
}
Simulator::~Simulator()
{
  delete memory;
  for(int i=0;i<5;i++){
    delete units[i];
  }
  delete naive_simulator;
}
void Simulator::init(AddrType start_addr)
{
  memory->init();
  naive_simulator->init(start_addr,memory);
  //auto init
  status_cur.init(start_addr,memory);
  status_next=status_cur;
  status_next.clear_deep();
  cd_bus.clear();
  mem_bus.clear();

}
void Simulator::onecircle()
{
  //step 1
  execute();
  step();
  status_next.regs= status_cur.regs;
  //use the same regs
  //the message in register file is always right
  status_cur = status_next;
  clock_++;
  status_next.clear_deep();
  cd_bus.clear();
  //now the next become the current
  if(status_cur.roll_back){
    mem_bus.clear();
    status_cur.rob_signal.first=false;
    status_cur.rs_signal.first=false;
    status_cur.lsb_signal.first=false;
    status_cur.sp_signal.first=false;
    status_cur.alu_signal.first=false;
    
    for(int i=0;i<Register_SIZE;i++){
      status_cur.regs.rely[i]=-1;
      status_next.regs.rely[i]=-1;
    }
    return;
  }else{
    // for(int i=0;i<MEM_BUS_SIZE;i++){
    //   if(mem_bus.exist(i)){
    //     if(mem_bus.get(i).type==BusType::LOAD_FINISHED||mem_bus.get(i).type==BusType::STORE_FINISHED){
    //       mem_bus.erase(i);
    //     }
    //   }
    // }
  }
  //step 4
}
int Simulator::run()
{
  // init(0);
  //you can't init twice
  while(!status_cur.halt){
    onecircle();
  }
  return status_cur.res&255;
}
void Simulator::step()
{
  for(int i=4;i>=0;i--){
    units[i]->step(status_cur,status_next);
  }
  memory->step(status_cur,status_next);
}
void Simulator::execute()
{
  for(int i=0;i<5;i++){
    units[i]->execute(status_cur,status_next);
  }
  memory->execute(status_cur,status_next);
}
}


//---------------------------------------------------------
// *** Naive_Simulator ***
namespace cpu{
Naive_Simulator::Naive_Simulator()
{
  memory_unit = new Memory(nullptr);
  // maybe i need a naive memory version
}
Naive_Simulator::~Naive_Simulator()
{
  Memory * memory = dynamic_cast<Memory*>(memory_unit);
  delete memory;
}
void Naive_Simulator::init(AddrType start_addr)
{
  auto memory = dynamic_cast<Memory*>(memory_unit);
  memory->init();
  status_cur.init(0,memory);
  status_cur.pc=start_addr;
}
void Naive_Simulator::init(AddrType start_addr,Memory* memory)
{
  auto memory_ = dynamic_cast<Memory*>(memory_unit);
  memory_->copy(*memory);
  status_cur.init(0,memory);
  status_next.init(0,memory);
  status_cur.pc=start_addr;
}

int Naive_Simulator::run()
{
  while(!status_cur.halt){
    step();
  }
  return status_cur.regs.reg[10] & 255;
}

void Naive_Simulator::step()
{
  round++;
  auto memory = dynamic_cast<Memory*>(memory_unit);
  status_next.init(0,memory);
  DataType opcode=memory->fetch_32(status_cur.pc);
  Ins ins;
  decode(opcode,ins);  
  ins.pc_addr=status_cur.pc;//this is extremely important
  
  status_next.pc=status_cur.pc+4;
  status_next.regs = status_cur.regs;
  if(ins.opt==Opt::ADDI && ins.rd==10 && ins.rs1==0 && ins.imm==255){
    status_next.halt=true;
    status_cur = status_next;

    return;
  }

  if(ins.type==Optype::U){
    if(ins.opt==Opt::LUI){
      status_next.regs.reg[ins.rd]=ins.imm;
    }else if(ins.opt==Opt::AUIPC){
      status_next.regs.reg[ins.rd]=ins.imm+ins.pc_addr;
    }else{
      throw std::exception();
      throw "Invalid instruction";
    }
  }else if (ins.type==Optype::J){
    if(ins.opt==Opt::JAL){
      status_next.regs.reg[ins.rd]=status_cur.pc+4;
      status_next.pc=ins.imm+status_cur.pc;
    }else{
      throw std::exception();
      throw "Invalid instruction";
    }
  }else if (ins.type==Optype::B){
    if(ins.opt==Opt::BEQ){
      if(status_cur.regs.reg[ins.rs1]==status_cur.regs.reg[ins.rs2]){
        status_next.pc=status_cur.pc+ins.imm;
      }
    }else if(ins.opt==Opt::BNE){
      if(status_cur.regs.reg[ins.rs1]!=status_cur.regs.reg[ins.rs2]){
        status_next.pc=status_cur.pc+ins.imm;
      }
    }else if(ins.opt==Opt::BLT){
      if((int)status_cur.regs.reg[ins.rs1]<(int)status_cur.regs.reg[ins.rs2]){
        status_next.pc=status_cur.pc+ins.imm;
      }
    }else if(ins.opt==Opt::BGE){
      if((int)status_cur.regs.reg[ins.rs1]>=(int)status_cur.regs.reg[ins.rs2]){
        status_next.pc=status_cur.pc+ins.imm;
      }
    }else if(ins.opt==Opt::BLTU){
      if((uint32_t)status_cur.regs.reg[ins.rs1]<(uint32_t)status_cur.regs.reg[ins.rs2]){
        status_next.pc=status_cur.pc+ins.imm;
      }
    }else if(ins.opt==Opt::BGEU){
      if((uint32_t)status_cur.regs.reg[ins.rs1]>=(uint32_t)status_cur.regs.reg[ins.rs2]){
        status_next.pc=status_cur.pc+ins.imm;
      } 
    }else{
      throw std::exception();
      throw "Invalid instruction";
    }
  
  }else if (ins.type==Optype::I){
    if(ins.opt==Opt::JALR){
      status_next.regs.reg[ins.rd]=status_cur.pc+4;
      status_next.pc=status_cur.regs.reg[ins.rs1]+ins.imm;
    }else if(ins.opt==Opt::LB){
      status_next.regs.reg[ins.rd]=memory->fetch_8(status_cur.regs.reg[ins.rs1]+ins.imm);
      status_next.regs.reg[ins.rd]=sign_ext(status_next.regs.reg[ins.rd],8);
    }else if(ins.opt==Opt::LH){
      status_next.regs.reg[ins.rd]=memory->fetch_16(status_cur.regs.reg[ins.rs1]+ins.imm);
      status_next.regs.reg[ins.rd]=sign_ext(status_next.regs.reg[ins.rd],16);
    }else if(ins.opt==Opt::LW){
      status_next.regs.reg[ins.rd]=memory->fetch_32(status_cur.regs.reg[ins.rs1]+ins.imm);
    }else if(ins.opt==Opt::LBU){
      status_next.regs.reg[ins.rd]=memory->fetch_8(status_cur.regs.reg[ins.rs1]+ins.imm);
    }else if(ins.opt==Opt::LHU){
      status_next.regs.reg[ins.rd]=memory->fetch_16(status_cur.regs.reg[ins.rs1]+ins.imm);
    }else if(ins.opt==Opt::ADDI){
      status_next.regs.reg[ins.rd]=status_cur.regs.reg[ins.rs1]+ins.imm;
    }else if(ins.opt==Opt::SLTI){
      status_next.regs.reg[ins.rd]=((int)status_cur.regs.reg[ins.rs1]<(int)ins.imm)?1:0;
    }else if(ins.opt==Opt::SLTIU){
      status_next.regs.reg[ins.rd]=((uint32_t)status_cur.regs.reg[ins.rs1]<(uint32_t)ins.imm)?1:0;
    }else if(ins.opt==Opt::XORI){
      status_next.regs.reg[ins.rd]=status_cur.regs.reg[ins.rs1]^ins.imm;
    }else if(ins.opt==Opt::ORI){
      status_next.regs.reg[ins.rd]=status_cur.regs.reg[ins.rs1]|ins.imm;
    }else if(ins.opt==Opt::ANDI){
      status_next.regs.reg[ins.rd]=status_cur.regs.reg[ins.rs1]&ins.imm;
    } 
    else if(ins.opt==Opt::SLLI){
      status_next.regs.reg[ins.rd]=status_cur.regs.reg[ins.rs1]<<ins.imm;
    }else if(ins.opt==Opt::SRLI){
      status_next.regs.reg[ins.rd]=status_cur.regs.reg[ins.rs1]>>ins.imm;
    }else if(ins.opt==Opt::SRAI){
      status_next.regs.reg[ins.rd]=((int)status_cur.regs.reg[ins.rs1])>>ins.imm;
    }else{
      throw std::exception();
      throw "Invalid instruction";
    }
  }else if (ins.type==Optype::S){
    if(ins.opt==Opt::SB){
      memory->store_8(status_cur.regs.reg[ins.rs1]+ins.imm,status_cur.regs.reg[ins.rs2]);
    }else if(ins.opt==Opt::SH){
      memory->store_16(status_cur.regs.reg[ins.rs1]+ins.imm,status_cur.regs.reg[ins.rs2]);
    }else if(ins.opt==Opt::SW){
      memory->store_32(status_cur.regs.reg[ins.rs1]+ins.imm,status_cur.regs.reg[ins.rs2]);
    }else{
      throw std::exception();
      throw "Invalid instruction";
    }
  
  }else if (ins.type==Optype::R){
    if(ins.opt==Opt::ADD){
      status_next.regs.reg[ins.rd]=status_cur.regs.reg[ins.rs1]+status_cur.regs.reg[ins.rs2];
    }else if(ins.opt==Opt::SUB){
      status_next.regs.reg[ins.rd]=status_cur.regs.reg[ins.rs1]-status_cur.regs.reg[ins.rs2];
    }else if(ins.opt==Opt::SLL){
      status_next.regs.reg[ins.rd]=status_cur.regs.reg[ins.rs1]<<status_cur.regs.reg[ins.rs2];
    }else if(ins.opt==Opt::SLT){
      status_next.regs.reg[ins.rd]=((int)status_cur.regs.reg[ins.rs1]<(int)status_cur.regs.reg[ins.rs2])?1:0;
    }else if(ins.opt==Opt::SLTU){
      status_next.regs.reg[ins.rd]=((uint32_t)status_cur.regs.reg[ins.rs1]<(uint32_t)status_cur.regs.reg[ins.rs2])?1:0;
    }else if(ins.opt==Opt::XOR){
      status_next.regs.reg[ins.rd]=status_cur.regs.reg[ins.rs1]^status_cur.regs.reg[ins.rs2];
    }else if(ins.opt==Opt::SRL){
      status_next.regs.reg[ins.rd]=status_cur.regs.reg[ins.rs1]>>status_cur.regs.reg[ins.rs2];
    }else if(ins.opt==Opt::SRA){
      status_next.regs.reg[ins.rd]=((int)status_cur.regs.reg[ins.rs1])>>status_cur.regs.reg[ins.rs2];
    }else if(ins.opt==Opt::OR){
      status_next.regs.reg[ins.rd]=status_cur.regs.reg[ins.rs1]|status_cur.regs.reg[ins.rs2];
    }else if(ins.opt==Opt::AND){
      status_next.regs.reg[ins.rd]=status_cur.regs.reg[ins.rs1]&status_cur.regs.reg[ins.rs2];
    }else{
      throw std::exception();
      throw "Invalid instruction";
    }
  
  }else{
    throw std::exception();
    throw "Invalid instruction";
  }
  status_next.regs.reg[0]=0;
  // Warning this is extremely important
  status_cur = status_next;

}
//---------------------------------------------------------




}



