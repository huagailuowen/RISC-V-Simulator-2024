#include"../include/units/Branch_predict.h"
#include"simulator.h"
namespace cpu{
  
Branch_predict::Branch_predict(){
  // TO DO
}
bool Branch_predict::predict(Status &status){
  Ins ins;
  get_ins(status,ins);
  if(ins.type!=Optype::B){
    throw "Invalid instruction";
  }
  if(status->having_predicted){
    return status->predict_res;
  }
  // TO DO
  return true;
}

}