#ifndef CIRCLE_QUEUE_H
#define CIRCLE_QUEUE_H
#include "config.h"
#include <exception>
namespace cpu {
template <typename T,int SIZE=Queue_SIZE> class CircleQueue {
public:
  CircleQueue() : head(0), tail(0), size(0) {}
  int push(T x) {
    if (size == Queue_SIZE) {
      throw std::exception();
      throw "Queue is full!";
    }
    data[tail] = x;
    int pos=tail;
    tail = (tail + 1) % SIZE;
    size++;
    return pos;
  }
  T front() {
    if (size == 0) {
      throw std::exception();
      throw "Queue is empty!";
    }
    return data[head];
  }
  void pop() {
    if (size == 0) {
      throw std::exception();
      throw "Queue is empty!";
    }
    head = (head + 1) % Queue_SIZE;
    size--;
  }
  bool empty() { return size == 0; }
  int get_size() { return size; }
  int MAX_SIZE_()
  {
    return SIZE;
  }
  bool full() { return size == Queue_SIZE; }
  void clear()
  {
    head = 0;
    tail = 0;
    size = 0;
  }
  T& operator [](int pos){
    if(pos<0||pos>=(int)size){
      throw "out of range";
    }
    return data[pos];
  }
  int get_head(){
    return head;
  }
  int get_tail(){
    return tail;
  }

private:
  T data[SIZE];
  int head, tail;
  size_t size;
};

} // namespace cpu

#endif