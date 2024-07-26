#ifndef MEMOERY_H
#define MEMOERY_H
#include"../utility/config.h"
#include"../utility/util.h"

#include"Base_unit.h"
#include <cstdint>
namespace cpu{
class Status;
class Memory:public Base_unit{
public:
  Memory()=default;
  ~Memory()=default;
  // Warning ! you may confused with the return type of fetch_32 with fetch
  // RAMType fetch(int pos);
  // void store(int pos,DataType data);
  
  DataType fetch_32(int pos);
  DataType fetch_16(int pos);
  DataType fetch_8(int pos);
  
  
  void store_32(int pos,DataType data);
  void store_16(int pos,DataType data);
  void store_8(int pos,DataType data);
  
  void step(Status* status);
  void execute();
  void init();
#ifdef DEBUG_
public:
#endif
  RAMType operator [](int index);  
private:
  RAMType ram[Memory_SIZE];
  // RAMType cache[Cache_SIZE];

};


}


#endif
