#ifndef RESERVATION_STATION_H
#define RESERVATION_STATION_H
#include"base_unit.h"
#include"../utility/config.h"
#include "utility/container.h"
#include"Bus.h"
namespace cpu{
class Status;
struct RS_item{
  Ins ins;
  bool ready;
  int Vj,Vk;
  int A;
  int Qj,Qk;
  int dest;
  RS_item():ready(false),Vj(0),Vk(0),A(0),Qj(-1),Qk(-1),dest(-1){}
  RS_item(Ins ins):ins(ins),ready(false),Vj(0),Vk(0),A(0),Qj(-1),Qk(-1),dest(-1){}
};

class Reservation_station:public Base_unit{
public:
  Reservation_station(Bus<CD_BUS_SIZE>*cd_bus);
  void step(Status&status_cur,Status&status_next);
  void execute(Status&status_cur,Status&status_next);
  //tell the alu what to do
private:
  void update_state(Status&status_cur,Status&status_next);
  Bus<CD_BUS_SIZE>*cd_bus;
  //monitor the cd_bus
  Container<RS_item,RS_SIZE>items;
};




}
#endif // RESERVATION_STATION_H