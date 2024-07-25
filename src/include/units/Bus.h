#ifndef BUS_H
#define BUS_H

#include"../utility/config.h"

enum class BusType {
  Load,
  Store,
  INVALID,
};
class Bus{
public:
  BusType type;

};



#endif // BUS_H