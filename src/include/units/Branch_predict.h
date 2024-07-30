#ifndef BRANCH_PREDICT_H
#define BRANCH_PREDICT_H
#include "utility/config.h"
#include "utility/util.h"
#include "utility/container.h"
#include<iostream>
namespace cpu{
class Status;
struct predict_counter{
  int counter;
  AddrType addr;
  predict_counter(){
    counter = 0;
  }
};
class Branch_predict{
private:
Container<predict_counter, PREDICT_COUNTER_SIZE> items;
int performace[2];
public:
  Branch_predict();
  ~Branch_predict(){
#ifdef DEBUG
    std::cerr<<"Fail:"<<performace[0]<<" "<<"Success:"<<performace[1]<<std::endl;
#endif
  }
  
  bool predict(Status &status);
  void update(AddrType addr, bool result,bool is_success);
};


}

#endif // BRANCH_PREDICT_H