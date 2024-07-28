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
  void clear()
  {
    init();
  }
  void get_rely(int reg_index,DataType&data,int&rely_index){
    if(reg_index<0||reg_index>=Register_SIZE){
      throw "wrong register index";
    }
    data=(rely[reg_index]==-1)?reg[reg_index]:0;
    rely_index=rely[reg_index];
  }
  void set_rely(int reg_index,int rely_index){
    if(reg_index<0||reg_index>=Register_SIZE){
      throw "wrong register index";
    }
    rely[reg_index]=rely_index;
  }
};

}
#endif