#include"../include/units/Reservation_station.h"
#include"simulator.h"
namespace cpu{
Reservation_station::Reservation_station(){
  items.clear();
}
void Reservation_station::step(Status&status_cur,Status&status_next){
  update_state(status_cur,status_next);
}
void Reservation_station::update_state(Status&status_cur,Status&status_next){
  for(int i=0;i<items.MAX_SIZE_();i++){//not the size, but the capacity
    if(!items.exist(i)){
      continue;
    }
    auto &item=items[i];
    for(int j=0;j<cd_bus->MAX_SIZE_();j++){
      if(!cd_bus->exist(j)){
        continue;
      }
      auto bus_item=cd_bus->get(j);
      if(bus_item.type!=BusType::COMPUTE_FINISHED&&bus_item.type!=BusType::LOAD_FINISHED){
        continue;
      }
      if(bus_item.dest==item.Qj){
        item.Vj=bus_item.data;
        item.Qj=-1;
      }
      if(bus_item.dest==item.Qk){
        item.Vk=bus_item.data;
        item.Qk=-1;
      }
    }
    if(item.Qj==-1&&item.Qk==-1){
      item.ready=true;
    }
  }
}
  
void Reservation_station::execute(Status&status_cur,Status&status_next){
  for(int i=0;i<items.MAX_SIZE_();i++){
    if(!items.exist(i)){
      continue;
    }
    auto &item=items[i];
    if(item.ready){
      //send alu_signal
      ALU_signal signal;
      signal.op=item.ins.opt;
      signal.dest=item.dest;
      switch (item.ins.type)
      {
      case Optype::R:
        signal.input1=item.Vj;
        signal.input2=item.Vk;
        break;
      case Optype::I:
        signal.input1=item.Vj;
        signal.input2=item.ins.imm;
        break;
      default:
        throw "wrong type";
        break;
      }
      items.erase(i);
      break;
      //in a cycle, only one instruction can be executed
    }
  }
  status_next.rs_full=items.size()==items.MAX_SIZE_();
}
}