#ifndef CONTAINER_H
#define CONTAINER_H
#include <exception>
#include <utility>
using std::pair;
namespace cpu{
template <typename T,size_t MAX_SIZE> class Container{
using val_type = std::pair<bool,T>;
private:
  val_type data[MAX_SIZE];
  size_t size_;
public:
  Container():size_(0){
    for(int i=0;i<(int)MAX_SIZE;i++){
      data[i].first = false;
    }
  }
  int MAX_SIZE_(){
    return (int)MAX_SIZE;
  }
  int vacant_pos(){
    if(size_>=(int)MAX_SIZE){
      return -1;
    }
    for(int i=0;i<(int)MAX_SIZE;i++){
      if(!data[i].first){
        return i;
      }
    }
    return -1;
  }
  void insert(const T &x,int pos){
    if(pos>=(int)MAX_SIZE){
      throw std::exception();
      throw "Out of bound";
    }
    if(data[pos].first){
      throw std::exception();
      throw "Position is occupied";
    }
    data[pos] = std::make_pair(true,x);
    size_++;
  }
  int insert(const T &x){
    int pos = vacant_pos();
    if(pos==-1){
      throw std::exception();
      throw "Container is full!";
    }
    insert(x,pos);
    return pos;
  }
  void erase(int pos){
    if(pos>=(int)MAX_SIZE){
      throw std::exception();
      throw "Out of bound";
    }
    if(!data[pos].first){
      throw std::exception();
      throw "Position is empty";
    }
    data[pos].first = false;
    size_--;
  }
  bool exist(int pos){
    if(pos>=(int)MAX_SIZE){
      throw std::exception();
      throw "Out of bound";
    }
    return data[pos].first;
  }
  T get(int pos){
    if(pos>=(int)MAX_SIZE){
      throw std::exception();
      throw "Out of bound";
    }
    if(!data[pos].first){
      throw std::exception();
      throw "Position is empty";
    }
    return data[pos].second;
  }
  T &operator[](int pos){
    if(pos>=(int)MAX_SIZE){
      throw std::exception();
      throw "Out of bound";
    }
    if(!data[pos].first){
      throw std::exception();
      throw "Position is empty";
    }
    return data[pos].second;
  }
  size_t size(){
    return size_;
  }
  bool empty(){
    return size_==0;
  }
  bool full(){
    return size_==MAX_SIZE;
  }
  void clear(){
    for(int i=0;i<(int)MAX_SIZE;i++){
      data[i].first = false;
    }
    size_ = 0;
  }

};
}


#endif