#include"../include/units/Instruction.h"
#include <cstdint>
#include <sys/types.h>

namespace cpu{




void get_ins(Status &status,Ins &ins)
{
  ins.pc_addr = status.pc;
  decode(status.opcode,ins);
}

void decode(DataType input, Ins &ins)
{
  uint32_t opcode = input & 0x7F;
  if(opcode==0b0110111 || opcode==0b0010111){
    ins.type = Optype::U;
    decode_U(input,ins);
  }else if (opcode==0b1101111){
    ins.type = Optype::J;
    decode_J(input,ins);
  }else if (opcode==0b1100011){
    ins.type = Optype::B;
    decode_B(input,ins);
  }else if (opcode==0b1100111|| opcode==0b0000011 || opcode==0b0010011){
    ins.type = Optype::I;
    decode_I(input,ins);
  }else if(opcode==0b0110011){
    ins.type = Optype::R;
    decode_R(input,ins);
  }else if(opcode==0b0100011){
    ins.type = Optype::S;
    decode_S(input,ins);
  }else{
    throw std::exception();
    throw "Invalid instruction";
  }
  return ;
}

void decode_U(DataType input, Ins &ins)
{
  uint32_t opcode = input & 0x7F;
  if(opcode==0b0110111){
    ins.opt = Opt::LUI;
  }else if(opcode==0b0010111){
    ins.opt = Opt::AUIPC;
  }else{
    throw std::exception();
    throw "Invalid instruction";
  }
  ins.rd = get_segment(input,7,11);
  ins.imm = get_segment(input,12,31)<<12;
  //ins.pc_addr is not assigned in this part
  ins.rs1 = -1;
  ins.rs2 = -1; 
}

void decode_J(DataType input, Ins &ins)
{
  uint32_t opcode = input & 0x7F;
  if(opcode==0b1101111){
    ins.opt = Opt::JAL;
  }else{
    throw std::exception();
    throw "Invalid instruction";
  }
  ins.rd=get_segment(input,7,11);
  ins.imm = sign_ext((get_segment(input,12,19)<<12) 
    | (get_segment(input,20,20)<<11) 
    | (get_segment(input,21,30)<<1)
    | (get_segment(input,31,31)<<20),8);
  //ins.pc_addr is not assigned in this part
  ins.rs1 = -1;
  ins.rs2 = -1; 
}

void decode_B(DataType input, Ins &ins)
{
  uint32_t opcode = input & 0x7F;
  if(input!=0b1100011){
    throw std::exception();
    throw "Invalid instruction";
  }
  opcode=get_segment(input,12,14);
  if(opcode==0b000){
    ins.opt = Opt::BEQ;
  }else if(opcode==0b001){
    ins.opt = Opt::BNE;
  }else if(opcode==0b100){
    ins.opt = Opt::BLT;
  }else if(opcode==0b101){
    ins.opt = Opt::BGE;
  }else if(opcode==0b110){
    ins.opt = Opt::BLTU;
  }else if(opcode==0b111){
    ins.opt = Opt::BGEU;
  }else{
    throw std::exception();
    throw "Invalid instruction";
  }
  ins.rd = -1;
  ins.imm = sign_ext((get_segment(input,8,11)<<1) 
    | (get_segment(input,25,30)<<5) 
    | (get_segment(input,7,7)<<11) 
    | (get_segment(input,31,31)<<12),12);  
  //ins.pc_addr is not assigned in this part
  ins.rs1 = get_segment(input,15,19);
  ins.rs2 = get_segment(input,20,24);

}

void decode_I(DataType input, Ins &ins)
{
  uint32_t opcode = input & 0x7F;
  if(opcode==0b1100111){
    opcode=get_segment(input,12,14);
    if(opcode==0b000){
      ins.opt = Opt::JALR;
    }else{
      throw std::exception();
      throw "Invalid instruction";
    }
  }else if(opcode==0b0000011){
    opcode=get_segment(input,12,14);
    if(opcode==0b000){
      ins.opt = Opt::LB;
    }else if(opcode==0b001){
      ins.opt = Opt::LH;
    }else if(opcode==0b010){
      ins.opt = Opt::LW;
    }else if(opcode==0b100){
      ins.opt = Opt::LBU;
    }else if(opcode==0b101){
      ins.opt = Opt::LHU;
    }else{
      throw std::exception();
      throw "Invalid instruction";
    }
  }else if(opcode==0b0010011){

    opcode=get_segment(input,12,14);
    if(opcode==0b000){
      ins.opt = Opt::ADDI;
    }else if(opcode==0b010){
      ins.opt = Opt::SLTI;
    }else if(opcode==0b011){
      ins.opt = Opt::SLTIU;
    }else if(opcode==0b100){
      ins.opt = Opt::XORI;
    }else if(opcode==0b110){
      ins.opt = Opt::ORI;
    }else if(opcode==0b111){
      ins.opt = Opt::ANDI;
    }
    else if(opcode==0b001){
      ins.opt = Opt::SLLI;
    }else if(opcode==0b101){
      if(get_segment(input,30,30)==0){
        ins.opt = Opt::SRLI;
      }else{
        ins.opt = Opt::SRAI;
      }
    }else{
      throw std::exception();
      throw "Invalid instruction";
    }
  }else{
    throw std::exception();
    throw "Invalid instruction";
  }
  ins.rd = get_segment(input,7,11);
  ins.imm = get_segment(input,20,31);
  if(ins.opt!=Opt::SLLI && ins.opt!=Opt::SRLI && ins.opt!=Opt::SRAI){
    ins.imm = sign_ext(ins.imm,12);
  }
  //ins.pc_addr is not assigned in this part
  ins.rs1 = get_segment(input,15,19);
  ins.rs2 = -1;
}

void decode_S(DataType input, Ins &ins)
{
  uint32_t opcode = input & 0x7F;
  if(opcode!=0b0100011){
    throw std::exception();
    throw "Invalid instruction";
  }
  opcode=get_segment(input,12,14);
  if(opcode==0b000){
    ins.opt = Opt::SB;
  }else if(opcode==0b001){
    ins.opt = Opt::SH;
  }else if(opcode==0b010){
    ins.opt = Opt::SW;
  }else{
    throw std::exception();
    throw "Invalid instruction";
  }
  ins.imm = sign_ext(get_segment(input,7,11) | (get_segment(input,25,31)<<5),12);
  //ins.pc_addr is not assigned in this part
  ins.rs1 = get_segment(input,15,19);
  ins.rs2 = get_segment(input,20,24);
  ins.rd = -1;

}

void decode_R(DataType input, Ins &ins){
  uint32_t opcode = input & 0x7F;
  if(opcode!=0b0110011){
    throw std::exception();
    throw "Invalid instruction";
  }
  opcode=get_segment(input,12,14);
  if(opcode==0b000){  
    if(get_segment(input,30,30)==0){
      ins.opt = Opt::ADD;
    }else{
      ins.opt = Opt::SUB;
    }
  }else if(opcode==0b001){
    ins.opt = Opt::SLL;
  }else if(opcode==0b010){
    ins.opt = Opt::SLT;
  }else if(opcode==0b011){
    ins.opt = Opt::SLTU;
  }else if(opcode==0b100){
    ins.opt = Opt::XOR;
  }else if(opcode==0b101){
    if(get_segment(input,30,30)==0){
      ins.opt = Opt::SRL;
    }else{
      ins.opt = Opt::SRA;
    }
  }else if(opcode==0b110){
    ins.opt = Opt::OR;
  }else if(opcode==0b111){
    ins.opt = Opt::AND;
  }else{
    throw std::exception();
    throw "Invalid instruction";
  }
  ins.rd = get_segment(input,7,11);
  ins.rs1 = get_segment(input,15,19);
  ins.rs2 = get_segment(input,20,24);
  ins.imm = -1;
  //ins.pc_addr is not assigned in this part

}


}