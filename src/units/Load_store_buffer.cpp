#include"../include/units/Load_store_buffer.h"
#include"simulator.h"
#include "units/Bus.h"
#include "utility/util.h"
namespace cpu{
Load_Store_buffer::Load_Store_buffer(Bus<CD_BUS_SIZE>*cd_bus,Bus<MEM_BUS_SIZE>*mem_bus){
  items.clear();
  this->cd_bus=cd_bus;
  this->mem_bus=mem_bus;
}
void Load_Store_buffer::step(Status&status_cur,Status&status_next){

  update_state(status_cur,status_next);
  if(status_next.roll_back){
    items.clear();
    status_next.lsb_full=false;  
    return;
  }
}
void Load_Store_buffer::update_state(Status&status_cur,Status&status_next){
  //monitor the cd_bus
  for(int i=items.get_head(),j=items.get_size();j;i=(i+1)%items.MAX_SIZE_(),j--){//not the size, but the capacity
    auto &item=items[i];
    for(int j=0;j<cd_bus->MAX_SIZE_();j++){
    
      if(!cd_bus->exist(j)){
        continue;
      }
      auto bus_item=cd_bus->get(j);
      if(item.ins.pc_addr==4168){
        int ppp=0;
      }
      if(bus_item.type!=BusType::COMPUTE_FINISHED&&bus_item.type!=BusType::LOAD_FINISHED){
        continue;
      }
      //Warning they might read the wrong information 
      if((int)bus_item.dest==item.Qj){
        item.Vj=bus_item.data;
        item.Qj=-1;
      }
      if((int)bus_item.dest==item.Qk){
        item.Vk=bus_item.data;
        item.Qk=-1;
      }
    }
    if(item.Qj==-1&&item.Qk==-1){
      item.ready=true;
    }
  }
  //monitor the mem_bus
  for(int i=items.get_head(),j=items.get_size();j;i=(i+1)%items.MAX_SIZE_(),j--){
    auto &item=items[i];
    if(item.ins.pc_addr==4100){
            int kk=0;
          }
    for(int j=0;j<mem_bus->MAX_SIZE_();j++){
      if(!mem_bus->exist(j)){
        continue;
      }
      auto bus_item=mem_bus->get(j);
      if(bus_item.dest==item.dest){
        if(bus_item.type==BusType::STORE_FINISHED||bus_item.type==BusType::LOAD_FINISHED){
          if(item.ins.pc_addr==4100){
            int kk=0;
          }
          item.finished=true;
          mem_bus->erase(j);
        }
        if(bus_item.type==BusType::LOAD_FINISHED){
          item.A=bus_item.data;
          if(item.ins.type==Optype::I){
            if(item.ins.opt==Opt::LB){
              item.A=sign_ext(item.A,8);
            }else if(item.ins.opt==Opt::LH){
              item.A=sign_ext(item.A,16);
            }
          }
        }
        break;
      }
    }
  }
}

void Load_Store_buffer::execute(Status&status_cur,Status&status_next){
  // while(!items.empty()&&!cd_bus->full()){
  //however if it cram the bus and make other units can't use the bus, it will be a problem 
  //only allow one

  //first check the signal
  if(status_cur.lsb_signal.first){
    if(items.full()){
      throw "LSB is full";
    }
    LSB_item item(status_cur.lsb_signal.second.ins);
    item.dest=status_cur.lsb_signal.second.dest;
    
    if(item.ins.type==Optype::S){
      item.Qj=status_cur.lsb_signal.second.rely_j;
      item.Qk=status_cur.lsb_signal.second.rely_k;
      item.Vj=status_cur.lsb_signal.second.data_j;
      item.Vk=status_cur.lsb_signal.second.data_k;
      item.A=item.ins.imm;
    }else if(item.ins.type==Optype::I){
      item.Qj=status_cur.lsb_signal.second.rely_j;
      item.Vj=status_cur.lsb_signal.second.data_j;
      item.Qk=-1;
      item.A=item.ins.imm;
    }else{
      throw "wrong type";
    }
    item.ready=false;
    item.ls_begin=false;
    if(item.Qj==-1&&item.Qk==-1){
      item.ready=true;
    }
    items.push(item);
  }
  

  //Warning now we use circular queue and only allow the head to be finished
  //it is completely in order
  if(!items.empty()&&!cd_bus->full()){
    auto item=items.front();
    if(item.finished){
      BusType type;
      
      if(item.ins.type==Optype::I){
        if(item.ins.opt==Opt::LB
          ||item.ins.opt==Opt::LH
          ||item.ins.opt==Opt::LW
          ||item.ins.opt==Opt::LBU
          ||item.ins.opt==Opt::LHU){
          type=BusType::LOAD_FINISHED;
        }else{
          throw "wrong type";
        }
      }else if(item.ins.type==Optype::S){
        type=BusType::STORE_FINISHED;
      }else{
        throw "wrong type";
      }
      cd_bus->insert(item.A,0,type,item.dest);
      items.pop();
    }
  }
  if(status_cur.sp_signal.first){
    int i=1;
  }
  if(items.empty()){
    if(status_cur.sp_signal.first){
      throw "wrong signal";
    }
    return;
  }
  status_next.lsb_full=items.full();
  bool is_store=items[items.get_head()].ins.type==Optype::S;
  if(is_store){
    auto item = items[items.get_head()];
    if(item.ins.pc_addr==4168){
      int ppp=0;
    }
    if(!items[items.get_head()].ready){
      return;
    }
    if(!items[items.get_head()].ls_begin){
      items[items.get_head()].ls_begin=true;
      cd_bus->insert(0,0,BusType::TRY_TO_STORE,items[items.get_head()].dest);
      return;
    }
    if(!status_cur.sp_signal.first){
      return;
    }
    if(status_cur.sp_signal.second.dest!=items[items.get_head()].dest){
      throw "wrong dest";
    }
    if(items[items.get_head()].finished||!items[items.get_head()].ready){
      throw "wrong state";
    }
  }
  for(int i=items.get_head(),j=items.get_size();j;i=(i+1)%items.MAX_SIZE_(),j--){
    auto &item=items[i];
    if(is_store!=(item.ins.type==Optype::S)){
      break;
    }
    //partly ramdom sequence
    
    if(item.ready){
      //send mem_signal
      
      if(mem_bus->full()){
        break;
      }
      if(item.ins.type==Optype::I){
        if(item.ls_begin){
          continue;
        }else{
          item.ls_begin=true;
        }
      }
      DataType data;
      // store rs2
      AddrType addr;
      BusType status;
      int dest=item.dest;
      if(item.ins.type==Optype::I){
        if(item.ins.opt==Opt::LB
          ||item.ins.opt==Opt::LH
          ||item.ins.opt==Opt::LW
          ||item.ins.opt==Opt::LBU
          ||item.ins.opt==Opt::LHU){
          data=0;
          addr=item.Vj+item.ins.imm;
          if(item.ins.opt==Opt::LB||item.ins.opt==Opt::LBU){
            status=BusType::LOAD_REQUEST_8;
          }else if(item.ins.opt==Opt::LH||item.ins.opt==Opt::LHU){
            status=BusType::LOAD_REQUEST_16;
          }else{
            status=BusType::LOAD_REQUEST_32;
          }
        }else{
          throw "wrong type";
        }
      }else if(item.ins.type==Optype::S){
        addr=item.Vj+item.ins.imm;
        data=item.Vk;
        if(item.ins.opt==Opt::SB){
          status=BusType::STORE_REQUEST_8;
        }else if(item.ins.opt==Opt::SH){
          status=BusType::STORE_REQUEST_16;
        }else if(item.ins.opt==Opt::SW){
          status=BusType::STORE_REQUEST_32;
        }else{
          throw "wrong type";
        }

      }else{
        throw "wrong type";
      }
      mem_bus->insert(data,addr,status,dest);
    }
    if(is_store){
      break;
    }
  }
}


}