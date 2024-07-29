#include"../include/units/Memory.h"
#include"simulator.h"
#include "utility/config.h"
#include <cstring>
#include <exception>
#include <iostream>
namespace cpu{
Memory::Memory(Bus<MEM_BUS_SIZE>*mem_bus):mem_bus(mem_bus){
  latency_time=0;
}
// RAMType Memory::fetch(int pos){
//   if(pos<0||pos>=Memory_SIZE){
//     throw std::exception();
//     throw "Memory out of bound";
//   }
//   return ram[pos];
// }
RAMType Memory::operator [](int index){
  if(index<0||index>=Memory_SIZE){
    throw std::exception();
    throw "Memory out of bound";
  }
  return ram[index];
}
DataType Memory::fetch_32(int pos){
  if(pos<0||pos+3>=Memory_SIZE){
    throw std::exception();
    throw "Memory out of bound";
  }
  return ram[pos]|(ram[pos+1]<<8)|(ram[pos+2]<<16)|(ram[pos+3]<<24);
}
DataType Memory::fetch_16(int pos){
  if(pos<0||pos+1>=Memory_SIZE){
    throw std::exception();
    throw "Memory out of bound";
  }
  return ram[pos]|(ram[pos+1]<<8);
}
DataType Memory::fetch_8(int pos){
  if(pos<0||pos>=Memory_SIZE){
    throw std::exception();
    throw "Memory out of bound";
  }
  return ram[pos];
}
void Memory::store_32(int pos,DataType data){
  if(pos<0||pos+3>=Memory_SIZE){
    throw std::exception();
    throw "Memory out of bound";
  }
  ram[pos]=data&0xff;
  ram[pos+1]=(data>>8)&0xff;
  ram[pos+2]=(data>>16)&0xff;
  ram[pos+3]=(data>>24)&0xff;
}
void Memory::store_16(int pos,DataType data){
  if(pos<0||pos+1>=Memory_SIZE){
    throw std::exception();
    throw "Memory out of bound";
  }
  ram[pos]=data&0xff;
  ram[pos+1]=(data>>8)&0xff;
}
void Memory::store_8(int pos,DataType data){
  if(pos<0||pos>=Memory_SIZE){
    throw std::exception();
    throw "Memory out of bound";
  }
  ram[pos]=data&0xff;
}
void Memory::init(){
  for(int i=0;i<Memory_SIZE;i++){
    ram[i]=0;
  }
  std::string str;
  AddrType addr;
  while(std::cin>>str){
    if(str[0]=='@'){
      if(str.size()!=9){
        throw "Invalid input";
      }
      addr=Hex_to_int(str.substr( 1, 8));
    }else{
      if(addr>=Memory_SIZE){
        throw "Memory out of bound";
      }
      if(str.size()!=2){
        throw "Invalid input";
      }
      ram[addr++]=Hex_to_int(str); 
    }
  }
}

void Memory::step(Status&status_cur,Status&status_next){
  if(status_next.roll_back){
    latency_time=0;
    return;
  }
  //the cd_bus and mem_bus should be clear in outside
}
void Memory::execute(Status&status_cur,Status&status_next){
  if(status_next.roll_back){
    return;
  }
  if(latency_time){
    latency_time--;
  }
  if(latency_time==0){
    for(int i=0;i<MEM_BUS_SIZE;i++){
      if(!mem_bus->exist(i)){
        continue;
      }
      auto &bus_item=mem_bus->fetch(i);
      if(bus_item.type==BusType::LOAD_FINISHED||bus_item.type==BusType::STORE_FINISHED){
        continue;
      }
      if(bus_item.type==BusType::LOAD_REQUEST_8){
        bus_item.data=fetch_8(bus_item.addr);
        bus_item.type=BusType::LOAD_FINISHED;
      }else if(bus_item.type==BusType::STORE_REQUEST_8){
        store_8(bus_item.addr,bus_item.data);
        bus_item.type=BusType::STORE_FINISHED;
      }else if(bus_item.type==BusType::LOAD_REQUEST_16){
        bus_item.data=fetch_16(bus_item.addr);
        bus_item.type=BusType::LOAD_FINISHED;
      }else if(bus_item.type==BusType::STORE_REQUEST_16){
        store_16(bus_item.addr,bus_item.data);
        bus_item.type=BusType::STORE_FINISHED;
      }else if(bus_item.type==BusType::LOAD_REQUEST_32){
        bus_item.data=fetch_32(bus_item.addr);
        bus_item.type=BusType::LOAD_FINISHED;
      }else if(bus_item.type==BusType::STORE_REQUEST_32){
        store_32(bus_item.addr,bus_item.data);
        bus_item.type=BusType::STORE_FINISHED;
      }else{
        throw "Invalid bus type";
      }
      break;
      //can memory serve multiple request at the same time?
      //now we assume that memory can only serve one request at a time

    }
    latency_time=MEM_LATENCY;
  }
}
}