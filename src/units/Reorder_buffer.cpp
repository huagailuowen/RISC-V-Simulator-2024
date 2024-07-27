#include"../include/units/Reorder_buffer.h"
#include"simulator.h"
namespace cpu{

Reorder_buffer::Reorder_buffer(){}
Reorder_buffer::~Reorder_buffer(){}
void Reorder_buffer::step(Status&status_cur,Status&status_next){
  if(status_next.roll_back){
    rob.clear();
    return;
  }
  if(!status_cur.rob_signal.first){
    return;
  }
  if(rob.full()){
    throw "ROB is full";
  }
  int dest=rob.get_tail( );
  ROB_state state=ROB_state::READY;
  Ins ins=status_cur.rob_signal.second.ins;
  rob.push(ROB_item(ins,dest,state));
  //begin to use the cd_bus to update the status_next
  status_next.rob_full=rob.full();
  //we should change the reliance in the register_file 
  
  
  //update_state(status_cur,status_next);

}
void Reorder_buffer::execute(Status&status_cur,Status&status_next){
  //if only be stored can be commited
  for(int i=0;i<rob.MAX_SIZE_();i++){
    if(rob.exist(i)){
      if(rob[i].state==ROB_state::READY){
        if(rob[i].ins.type==Optype::B){
          if(status_cur.predict_res){
            status_next.pc=status_cur.pc+rob[i].ins.imm;
          }else{
            status_next.pc=status_cur.pc+4;
          }
          rob[i].state=ROB_state::FINISHED;
        }else if(rob[i].ins.type==Optype::J){
          status_next.pc=status_cur.pc+rob[i].ins.imm;
          rob[i].state=ROB_state::FINISHED;
        }else if(rob[i].ins.opt==Opt::JALR){
          status_next.pc=status_cur.regs.reg[rob[i].ins.rs1]+rob[i].ins.imm;
          rob[i].state=ROB_state::FINISHED;
        }else{
          status_next.pc=status_cur.pc+4;
          rob[i].state=ROB_state::FINISHED;
        }
      }
    }
  }
  status_next.rob_full=rob.full();
}


}