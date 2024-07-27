#include"../include/units/Instruction.h"
#include"simulator.h"
#include "units/Branch_predict.h"
#include "units/Reorder_buffer.h"
#include "utility/util.h"

#include <cstdint>
#include <sys/types.h>

namespace cpu{


void Instruction_unit::step(Status&status_cur,Status&status_next)
{
  if(status_next.roll_back){
    ins_q.clear();
  }
  //at very first it should be empty, so ins_stall == true
  if(status_cur.ins_stall){
    return;
  }
  if(ins_q.full()){
    throw "Instruction queue is full";
  }
  ins_q.push(status_cur.ins);
}
void Instruction_unit::execute(Status&status_cur,Status&status_next)
{

  //there the ins of status_cur is decoded and put into ins_q
  //it has readly been done in the outer Simulator
  get_ins(status_cur,status_cur.ins); 

  if(status_cur.ins_stall){
    status_next.pc=status_cur.pc;
  }else{
    if(status_cur.ins.type==Optype::B){
      // the branch need to predict
      bool res=predictor.predict(status_cur);
      //we should record the result of prediction in cur!!
      status_cur.ins.predict_res=res;
      if(res){
        status_next.pc = status_cur.pc+status_cur.ins.imm;
        //there is a small add_unit to do this transition
      }else{
        status_next.pc = status_cur.pc+4;
      }
    }else if(status_cur.ins.type==Optype::J){
      status_next.pc = status_cur.pc+status_cur.ins.imm;
    }else if(status_cur.ins.opt==Opt::JALR){
      status_next.pc = status_cur.regs.reg[status_cur.ins.rs1]+status_cur.ins.imm;
    }else{
      status_next.pc=status_cur.pc+4;
    }
  }
  launch(status_cur,status_next);
}
void Instruction_unit::launch(Status&status_cur,Status&status_next)
{
  if(ins_q.empty()){
    return;
  }
  if(status_cur.rob_full){
    return;
  }
  Ins ins = ins_q.front();
  ins_q.pop();
  ROB_signal rob_signal;
  rob_signal.ins = ins;
  status_next.rob_signal.first = true;
  status_next.rob_signal.second = rob_signal;
  //TO DO
}
void get_ins(Status &status,Ins &ins)
{
  ins.pc_addr = status.pc;
  //we assume fectch the opcode is very fast
  status.opcode = status.memory_->fetch_32(status.pc);
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
    | (get_segment(input,31,31)<<20),21);
    //Warning not 20
  //ins.pc_addr is not assigned in this part
  ins.rs1 = -1;
  ins.rs2 = -1; 
}

void decode_B(DataType input, Ins &ins)
{
  uint32_t opcode = input & 0x7F;
  if(opcode!=0b1100011){
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
    | (get_segment(input,31,31)<<12),13);
    //Warning not 12  
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