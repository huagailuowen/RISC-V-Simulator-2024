#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include "../utility/config.h"
#include "../utility/util.h"
namespace cpu{


class register_file{
public:
  /** 
  *@param reg: the unsigned value of the register
  */
  DataType reg[Register_SIZE];
  int rely[Register_SIZE];
  register_file(){
    for(int i=0;i<Register_SIZE;i++){
      reg[i]=0;
      rely[i]=-1;
    }
  }
  void init(){
    for(int i=0;i<Register_SIZE;i++){
      reg[i]=0;
      rely[i]=-1;
    }
  }
};

}
#endif