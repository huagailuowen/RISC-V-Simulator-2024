#include"../include/units/Reorder_buffer.h"
#include"simulator.h"
#include<iostream>
#include "utility/util.h"
namespace cpu{

Reorder_buffer::Reorder_buffer(Bus<CD_BUS_SIZE>*cd_bus)
{
  this->cd_bus=cd_bus;
}
Reorder_buffer::~Reorder_buffer(){}
void Reorder_buffer::step(Status&status_cur,Status&status_next){
  if(status_next.roll_back){
    rob.clear();
    // status_next.rob_full=false;
    status_next.rob_near_full=(rob.get_size()+1>=rob.MAX_SIZE_());
    status_next.rob_full=rob.full();
    status_next.rob_clear=true;
    return;
  }
  //begin to use the cd_bus to update the status_next
  // status_next.rob_full=rob.full();
  status_next.rob_near_full=(rob.get_size()+1>=rob.MAX_SIZE_());

  status_next.rob_clear=rob.empty();
  //we should change the ROB_state from EXCUTING to FINISHED 
  for(int i=0;i<cd_bus->MAX_SIZE_();i++){
    if(!cd_bus->exist(i)){
      continue;
    }
    auto item=cd_bus->get(i);
    int pos=item.dest;
    rob[pos].value=item.data;
    if(rob[pos].state==ROB_state::EXCUTING){
      if(rob[pos].ins.type==Optype::S){
        rob[pos].state=ROB_state::STORING;
      }else{
        rob[pos].state=ROB_state::FINISHED;
      }
      
    }else if(rob[pos].state==ROB_state::WAITING){
      if(rob[pos].ins.type==Optype::S){
        rob[pos].state=ROB_state::FINISHED;
      }else{
        throw "ROB state error";
      }
    }else{
      throw "ROB state error";
    }
  }

  if(status_next.rs_signal.first){
    auto & signal=status_next.rs_signal.second;
    if(signal.rely_j!=-1){
      //rely_j must in the rob
      if(rob[signal.rely_j].state==ROB_state::FINISHED){
        signal.data_j=rob[signal.rely_j].value;
        signal.rely_j=-1;
      }
    }
    if(signal.rely_k!=-1){
      //rely_k must in the rob
      if(rob[signal.rely_k].state==ROB_state::FINISHED){
        signal.data_k=rob[signal.rely_k].value;
        signal.rely_k=-1;
      }
    }
  }
  if(status_next.lsb_signal.first){
    auto & signal=status_next.lsb_signal.second;
    if(signal.rely_j!=-1){
      //rely_j must in the rob
      if(rob[signal.rely_j].state==ROB_state::FINISHED){
        signal.data_j=rob[signal.rely_j].value;
        signal.rely_j=-1;
      }
    }
    if(signal.rely_k!=-1){
      //rely_k must in the rob
      if(rob[signal.rely_k].state==ROB_state::FINISHED){
        signal.data_k=rob[signal.rely_k].value;
        signal.rely_k=-1;
      }
    }
  }
  

}
bool is_ls(const Ins &ins){
  auto &op=ins.opt;
  return op==Opt::LW
    ||op==Opt::SW
    ||op==Opt::LBU
    ||op==Opt::LHU
    ||op==Opt::SB
    ||op==Opt::SH
    ||op==Opt::LB
    ||op==Opt::LH;
}
bool is_rs(const Ins &ins){
  auto &op=ins.opt;
  return ins.type==Optype::R
    ||(ins.type==Optype::I&&!is_ls(ins))
    ||ins.type==Optype::B
    ||ins.type==Optype::U
    ||ins.type==Optype::J;
}

void Reorder_buffer::execute(Status&status_cur,Status&status_next){
  //we should first commit in order to tackle with those corner case(the rely instruction be commited)
  //try to commit
  //if only be stored can be commited
  //can we commit more than one ins?
  for(int i=rob.get_head(),j=rob.get_size();j;i=(i+1)%rob.MAX_SIZE_(),j--){
    if(rob[i].state==ROB_state::STORING){
      status_next.sp_signal.first=true;
      status_next.sp_signal.second.dest=rob[i].dest;
      rob[i].state=ROB_state::WAITING;
      break;
    }
    if(rob[i].state!=ROB_state::FINISHED){
      break;
    }
    auto &item=rob[i];
    if(item.ins.opt==Opt::ADDI && item.ins.rd==10 && item.ins.rs1==0 && item.ins.imm==255){
      status_next.halt=true;
      status_next.res=status_cur.regs.reg[10]&0xff;
      return;
    }
    if(item.ins.type==Optype::B){
      if(item.ins.predict_res!=item.value){
        status_next.roll_back=true;
        status_next.pc=item.ins.pc_addr;
        status_next.having_predicted=true;
        status_next.predict_res=item.value;
        return;
      }
    }else if(item.ins.type==Optype::I||item.ins.type==Optype::J||item.ins.type==Optype::U||item.ins.type==Optype::R){
      if(item.ins.rd!=0){
        status_cur.regs.reg[item.ins.rd]=item.value;
      }else{
        status_cur.regs.reg[item.ins.rd]=0;
        if(status_cur.regs.rely[item.ins.rd]!=-1){
          throw "you can't change r0";
        }
      }
      if(status_cur.regs.rely[item.ins.rd]==item.dest){
        status_cur.regs.rely[item.ins.rd]=-1;
      }
    }
    rob.pop();

    break;
    //only commit one
  }
  
  
  
  
  //try to push the ins into the rob
  if(status_cur.rob_signal.first){
    if(rob.full()){
      throw "ROB is full";
    }
    //we assume that rob's size is bigger than RS's size and LS's size
    //so we just push it without hesitation
    //otherwise we should try to push the unpushed in order
    int dest=rob.get_tail( );
    ROB_state state=ROB_state::EXCUTING;
    Ins ins=status_cur.rob_signal.second.ins;
    
    if(ins.pc_addr==4100){
      int kk=0;
    }
    std::cerr<<"pushing ins "<<ins.pc_addr<<std::endl;
    rob.push(ROB_item(ins,dest,state));
    if(is_ls(ins)){
      status_next.lsb_signal.first=true;
      status_next.lsb_signal.second.ins=ins;
      status_next.lsb_signal.second.dest=dest;
      if(ins.type==Optype::S){
        status_cur.regs.get_rely(ins.rs1,status_next.lsb_signal.second.data_j,status_next.lsb_signal.second.rely_j);
        status_cur.regs.get_rely(ins.rs2,status_next.lsb_signal.second.data_k,status_next.lsb_signal.second.rely_k);
      }else{
        status_cur.regs.get_rely(ins.rs1,status_next.lsb_signal.second.data_j,status_next.lsb_signal.second.rely_j);
        status_next.lsb_signal.second.data_k=0;
        status_next.lsb_signal.second.rely_k=-1;
      }
      

    }else if(is_rs(ins)){
      status_next.rs_signal.first=true;
      status_next.rs_signal.second.ins=ins;
      status_next.rs_signal.second.dest=dest;
      if(ins.type==Optype::R||ins.type==Optype::B){
        status_cur.regs.get_rely(ins.rs1,status_next.rs_signal.second.data_j,status_next.rs_signal.second.rely_j);
        status_cur.regs.get_rely(ins.rs2,status_next.rs_signal.second.data_k,status_next.rs_signal.second.rely_k);
      }else if(ins.opt==Opt::JALR||ins.opt==Opt::JAL){
        status_next.rs_signal.second.data_j=ins.pc_addr;
        status_next.rs_signal.second.rely_k=-1;
  
        status_next.rs_signal.second.data_k=4;
        status_next.rs_signal.second.rely_k=-1;

      }else if(ins.opt==Opt::AUIPC){
        status_next.rs_signal.second.data_j=ins.pc_addr;
        status_next.rs_signal.second.rely_k=-1;
  
        status_next.rs_signal.second.data_k=ins.imm;
        status_next.rs_signal.second.rely_k=-1;

      }else if(ins.opt==Opt::LUI){
        status_next.rs_signal.second.data_j=ins.imm;
        status_next.rs_signal.second.rely_k=-1;
  
        status_next.rs_signal.second.data_k=0;
        status_next.rs_signal.second.rely_k=-1;

      }else{
        //mainly normal I type(except for jalr)
        status_cur.regs.get_rely(ins.rs1,status_next.rs_signal.second.data_j,status_next.rs_signal.second.rely_j);
        status_next.rs_signal.second.data_k=0;
        status_next.rs_signal.second.rely_k=-1;
      }
      

    }

    if(ins.rd!=0&&ins.type!=Optype::B&&ins.type!=Optype::S){
      status_cur.regs.rely[ins.rd]=dest;
    }

  }
  status_next.rob_near_full=(rob.get_size()+1>=rob.MAX_SIZE_());
  status_next.rob_full=rob.full();
  status_next.rob_clear=rob.empty();
}


}