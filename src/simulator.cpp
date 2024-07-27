#include"include/simulator.h"
// #include"Memory.h"

#include "include/units/Instruction.h"
#include "include/utility/util.h"
namespace cpu{
Simulator::Simulator()
{
  clock_=0;
  memory=new Memory();
  units[1] = new Instruction_unit();
  units[2] = new Arithmetic_logic_unit();
  units[3] = new Load_store_buffer();
  units[4] = new Reorder_buffer();
  units[0] = new Reservation_station();


}
}






//---------------------------------------------------------
// *** Naive_Simulator ***
namespace cpu{
Naive_Simulator::Naive_Simulator()
{
  memory_unit = new Memory();
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
  status_cur.init();
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
  status_next.init();
  auto memory = dynamic_cast<Memory*>(memory_unit);
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


