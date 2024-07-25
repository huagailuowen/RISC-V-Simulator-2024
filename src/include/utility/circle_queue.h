#ifndef CIRCLE_QUEUE_H
#define CIRCLE_QUEUE_H
#include "config.h"
#include <exception>
namespace cpu {
template <typename T> class CircleQueue {
public:
  CircleQueue() : head(0), tail(0), size(0) {}
  void push(T x) {
    if (size == Queue_SIZE) {
      throw std::exception();
      throw "Queue is full!";
    }
    data[tail] = x;
    tail = (tail + 1) % Queue_SIZE;
    size++;
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
  bool full() { return size == Queue_SIZE; }

private:
  T data[Queue_SIZE];
  int head, tail;
  size_t size;
};

} // namespace cpu

#endif