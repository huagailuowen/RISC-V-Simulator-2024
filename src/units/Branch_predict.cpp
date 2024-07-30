#include"../include/units/Branch_predict.h"
#include"simulator.h"
#include <cstdlib>
namespace cpu{
  
Branch_predict::Branch_predict(){
  // TO DO
  items.clear();
}
bool Branch_predict::predict(Status &status){
  Ins ins=status.ins;
  if(ins.type!=Optype::B){
    throw "Invalid instruction";
  }
  if(status.having_predicted){
    return status.predict_res;
  }
  for(int i=0;i<items.MAX_SIZE_();i++){
    if(!items.exist(i)){
      continue;
    }
    if(items[i].addr==ins.pc_addr){
      if(items[i].counter<2){
        return true;
      }
      else{
        return false;
      }
    }
  }
  return true;
}
void Branch_predict::update(AddrType addr, bool result,bool is_success){
  performace[is_success]++;
  for(int i=0;i<items.MAX_SIZE_();i++){
    if(!items.exist(i)){
      continue;
    }
    if(items[i].addr==addr){
      if(!result){
        if(items[i].counter<3){
          items[i].counter++;
        }
      }
      else{
        if(items[i].counter>0){
          items[i].counter--;
        }
      }
      return;
    }
  }
  if(items.full()){
    items.erase(rand()%items.MAX_SIZE_());
  }
  predict_counter temp;
  temp.addr=addr;
  if(result){
    temp.counter=0;
  }else{
    temp.counter=3;
  }
  items.insert(temp);
  
}

}