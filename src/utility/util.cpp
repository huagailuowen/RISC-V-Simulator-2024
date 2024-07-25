#include "../include/utility/util.h"
#include <cstdint>
#include <sys/types.h>
namespace cpu{

uint32_t sign_ext(uint32_t x, size_t bit){
  return ((int32_t)(x<<(32-bit)))>>(32-bit);
}
uint32_t get_segment(uint32_t data, int l, int r){
  return (data>>l)&((1<<(r-l+1))-1);
}
uint32_t Hex_to_int(std::string str){
  uint32_t res=0;
  for(auto c:str){
    res<<=4;
    if(c>='0'&&c<='9'){
      res+=c-'0';
    }else if(c>='A'&&c<='F'){
      res+=c-'A'+10;
    }else{
      throw "Invalid Hex";
    }
  }
  return res;
}
}