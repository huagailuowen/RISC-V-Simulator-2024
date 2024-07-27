#include"../include/units/Load_store_buffer.h"
#include"simulator.h"
#include "units/Bus.h"
#include "utility/util.h"
namespace cpu{
Load_Store_buffer::Load_Store_buffer(){
  items.clear();
}
void Load_Store_buffer::step(Status&status_cur,Status&status_next){
  update_state(status_cur,status_next);
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
      if(bus_item.type!=BusType::COMPUTE_FINISHED&&bus_item.type!=BusType::LOAD_FINISHED){
        continue;
      }
      //Warning they might read the wrong information 
      if(bus_item.addr==item.Qj){
        item.Vj=bus_item.data;
        item.Qj=-1;
      }
      if(bus_item.addr==item.Qk){
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
    for(int j=0;j<mem_bus->MAX_SIZE_();j++){
      if(!mem_bus->exist(j)){
        continue;
      }
      auto bus_item=mem_bus->get(j);
      if(bus_item.dest==item.dest){
        if(bus_item.type==BusType::STORE_FINISHED||bus_item.type==BusType::LOAD_FINISHED){
          item.finished=true;
        }
        if(bus_item.type==BusType::LOAD_FINISHED){
          item.A=bus_item.data;
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
  if(items.empty()){
    return;
  }
  bool is_store=items[items.get_head()].ins.type==Optype::S;
  for(int i=items.get_head(),j=items.get_size();j;i=(i+1)%items.MAX_SIZE_(),j--){
    auto &item=items[i];
    if(is_store!=(item.ins.type==Optype::S)){
      break;
    }
    //partly ramdom sequence
    if(item.ready){
      //send mem_signal
      if(mem_bus->full()){
        continue;
      }
      
    }
  }
  status_next.lsb_full=items.full();
}


}