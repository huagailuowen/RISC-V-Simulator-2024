#include"../include/units/Memory.h"
#include <cstdint>
#include <cstring>
#include <exception>
#include <iostream>
namespace cpu{

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
  bool flag=false;
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

void Memory::flush(){}
void Memory::execute(){}
}