#ifndef BUS_H
#define BUS_H

#include"../utility/config.h"
#include "utility/container.h"
#include "utility/util.h"
namespace cpu{

enum class BusType {
  Execute,
  LoadMen,
  StoreMem,
  StoreRes,
  INVALID,
};
struct Bus_item{
  DataType data;
  AddrType addr;
  BusType type;
  Bus_item(DataType data,AddrType addr,BusType type):data(data),addr(addr),type(type){}
};
template<int BUS_CAPCITY>
class Bus{
private:
  Container<Bus_item,BUS_CAPCITY> items;
public:
  Bus(){}
  void clear()
  {
    items.clear();
  }
  void init()
  {
    items.init();
  }
  void insert(DataType data,AddrType addr,BusType type)
  {
    items.insert(Bus_item(data,addr,type));
  }
  bool exist(int pos)
  {
    return items.exist(pos);
  }
  Bus_item get(int pos)
  {
    return items.get(pos);
  }

};

}


#endif // BUS_H