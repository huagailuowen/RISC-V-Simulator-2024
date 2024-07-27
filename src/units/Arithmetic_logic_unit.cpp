#include"../include/units/Instruction.h"
#include "utility/config.h"
#include "utility/util.h"
#include"../include/units/Arithmetic_logic_unit.h"
#include"simulator.h"
#include"../include/units/Bus.h"
namespace cpu{

ALU_type get_ALU_type(Optype op){
  return ALU_type::ADD;
}
int get_latency(ALU_type type){
  if(type==ALU_type::ADD)
    return ALU_ADD_LATENCY;
  else if(type==ALU_type::MUL)
    throw("there is no mul");
  else
    throw("there is no such type");
}
ALU_unit::ALU_unit(DataType input1,DataType input2,Opt op,int dest):input1(input1),input2(input2),op(op),dest(dest){
  output=0;
  latency=get_latency(get_ALU_type(op));

}
bool ALU_unit::step(){
  if(latency>0){
    latency--;
  }
  if(latency<=0){
    execute();
    return true;
  }
  return false;
}
void ALU_unit::execute(){
  if(op==Opt::ADD) output=input1+input2;
  else if(op==Opt::SUB){
    output=input1-input2;
  }
  else if(op==Opt::AND){
    output=input1&input2;
  }
  else if(op==Opt::OR){
    output=input1|input2;
  }
  else if(op==Opt::XOR){
    output=input1^input2;
  }
  else if(op==Opt::SLL){
    output=input1<<input2;
  }
  else if(op==Opt::SRL){
    output=input1>>input2;
  }
  else if(op==Opt::SRA){
    output=(int)input1>>input2;
  }
  else if(op==Opt::SLT){
    output=(int)input1<(int)input2;
  }
  else if(op==Opt::SLTU){
    output=input1<input2;
  }
  else if(op==Opt::LUI){
    output=input1+input2;
    // throw "we will not implement this, it should be an add instruction";
  }
  else if(op==Opt::AUIPC){
    output=input1;
  }
  else if(op==Opt::BEQ){
    output=input1==input2;
  }
  else if(op==Opt::BNE){
    output=input1!=input2;
  }
  else if(op==Opt::BLT){
    output=(int)input1<(int)input2;
  }
  else if(op==Opt::BGE){
    output=(int)input1>=(int)input2;
  }
  else if(op==Opt::BLTU){
    output=input1<input2;
  }
  else if(op==Opt::BGEU){
    output=input1>=input2;
  }
  else if(op==Opt::LW){
    output=input1+input2;
  }
  else if(op==Opt::SW){
    output=input1+input2;
  }
  else if(op==Opt::ADDI){
    output=input1+input2;
  }
  else if(op==Opt::SLTI){
    output=(int)input1<(int)input2;
  } 
  else if(op==Opt::SLTIU){
    output=input1<input2;
  }
  else if(op==Opt::XORI){
    output=input1^input2;
  }
  else if(op==Opt::ORI){
    output=input1|input2;
  }
  else if(op==Opt::ANDI){
    output=input1&input2;
  }
  else if(op==Opt::SLLI){
    output=input1<<input2;
  }
  else if(op==Opt::SRLI){
    output=input1>>input2;
  }
  else if(op==Opt::SRAI){
    output=(int)input1>>input2;
  }
  else if(op==Opt::JAL){
    throw "we will not implement this.";
    output=input1+input2;
  }
  else if(op==Opt::JALR){
    throw "we will not implement this.";
    output=input1+input2;
  }
  else if(op==Opt::LB){
    output=input1+input2;
  }
  else if(op==Opt::LH){
    output=input1+input2;
  }
  else if(op==Opt::LBU){
    output=input1+input2;
  }
  else if(op==Opt::LHU){
    output=input1+input2;
  }
  else if(op==Opt::SB){
    output=input1+input2;
  }
  else if(op==Opt::SH){
    output=input1+input2;
  }

  
  else{
    throw "Invalid instruction";
  }
}

Arithmetic_logic_unit::Arithmetic_logic_unit(){
  add.clear();
}
Arithmetic_logic_unit::~Arithmetic_logic_unit(){}
void Arithmetic_logic_unit::step(Status&status_cur,Status&status_next){
  if(status_next.roll_back){
    add.clear();
    return;
  }
  if(status_next.alu_signal.first){
    ALU_type type=get_ALU_type(status_next.alu_signal.second.op);
    if(type==ALU_type::ADD){
      if(add.full()){
        throw "ALU is full";
      }
      int pos = add.insert(ALU_unit(status_next.alu_signal.second.input1,status_next.alu_signal.second.input2,status_next.alu_signal.second.op,status_next.alu_signal.second.dest));
    }else{
      throw "we will not implement this";
    }
  }
  return;
}

void Arithmetic_logic_unit::execute(Status&status_cur,Status&status_next){
  //there is only add,
  for(int i=0;i<add.MAX_SIZE_();i++){
    if(add.exist(i)){
      if(add[i].step()){
        cd_bus->insert(add[i].output,0,BusType::COMPUTE_FINISHED,add[i].dest);
        add.erase(i);
        return;
      }
    }
  }
}

} // namespace cpu
