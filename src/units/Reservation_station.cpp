#include"../include/units/Reservation_station.h"
#include"simulator.h"
#include "utility/util.h"
namespace cpu{
Reservation_station::Reservation_station(Bus<CD_BUS_SIZE>*cd_bus){
  items.clear();
  this->cd_bus=cd_bus;
}
void Reservation_station::step(Status&status_cur,Status&status_next){
  update_state(status_cur,status_next);
  if(status_next.roll_back){
    items.clear();
    status_next.rs_full=false;
    return;
  }
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
  //load the data from the rs_signal
  if(status_cur.rs_signal.first){
    if(items.full()){
      throw "RS is full";
    }
    RS_item item(status_cur.rs_signal.second.ins);
    item.dest=status_cur.rs_signal.second.dest;
    if(item.ins.type==Optype::R||item.ins.type==Optype::B||item.ins.type==Optype::J||item.ins.opt==Opt::JALR||item.ins.type==Optype::U){
      item.Qj=status_cur.rs_signal.second.rely_j;
      item.Qk=status_cur.rs_signal.second.rely_k;
      item.Vj=status_cur.rs_signal.second.data_j;
      item.Vk=status_cur.rs_signal.second.data_k;
      item.A=item.ins.imm;
    }else if(item.ins.type==Optype::I){
      item.Qj=status_cur.rs_signal.second.rely_j;
      item.Vj=status_cur.rs_signal.second.data_j;
      item.Qk=-1;
      item.A=item.ins.imm;
    }else{
      throw "wrong type";
    }
    item.ready=false;
    if(item.Qj==-1&&item.Qk==-1){
      item.ready=true;
    }
    int pos=items.insert(item);
  }
  



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
        signal.input2=(item.ins.opt==Opt::JALR)?item.Vk:item.ins.imm;
        break;
      case Optype::B:
        signal.input1=item.Vj;
        signal.input2=item.Vk;
        break;
      case Optype::U:
        signal.input1=item.Vj;
        signal.input2=item.Vk;
        break;
      case Optype::J:
        signal.input1=item.Vj;
        signal.input2=item.Vk;
        break;
      
      
      default:
        throw "wrong type";
        break;
      }
      items.erase(i);
      status_next.alu_signal.first=true;
      status_next.alu_signal.second=signal;
      break;
      //in a cycle, only one instruction can be executed
    }
  }
  status_next.rs_full=(int)items.size()==items.MAX_SIZE_();
}
}