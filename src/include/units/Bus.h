#ifndef BUS_H
#define BUS_H

#include"../utility/config.h"
#include "utility/container.h"
#include "utility/util.h"
namespace cpu{

enum class BusType {
  //cd_bus
  LOAD_FINISHED,
  STORE_FINISHED,//these two also used in mem_bus
  COMPUTE_FINISHED,
  //mem_bus
  TRY_TO_STORE,
  LOAD_REQUEST_8,
  STORE_REQUEST_8,
  LOAD_REQUEST_16,
  STORE_REQUEST_16,
  LOAD_REQUEST_32,
  STORE_REQUEST_32,
};
struct Bus_item{
  DataType data;
  AddrType addr;
  //in the mem_bus, addr means the address of the data
  //in the cd_bus, addr means the dest in the ROB
  BusType type;
  int dest;
  Bus_item(DataType data,AddrType addr,BusType type,int dest):data(data),addr(addr),type(type),dest(dest){}
};
template<int BUS_CAPCITY>
class Bus{
private:
  Container<Bus_item,BUS_CAPCITY> items;
public:
  Bus(){}
  bool full()
  {
    return items.full();
  }
  void clear()
  {
    items.clear();
  }
  void init()
  {
    items.init();
  }
  void insert(DataType data,AddrType addr,BusType type,int dest)
  {
    items.insert(Bus_item(data,addr,type,dest));
  }
  bool exist(int pos)
  {
    return items.exist(pos);
  }
  Bus_item get(int pos)
  {
    return items.get(pos);
  }
  int size()
  {
    return items.size();
  }
  int MAX_SIZE_()
  {
    return items.MAX_SIZE_();
  }
  Bus_item& fetch(int index)
  {
    return items[index];
  }

};

}


#endif // BUS_H