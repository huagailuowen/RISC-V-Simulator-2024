#ifndef BRANCH_PREDICT_H
#define BRANCH_PREDICT_H

namespace cpu{
class Status;
class Branch_predict{
private:
// TO DO
public:
  Branch_predict();
  bool predict(Status &status);
};


}

#endif // BRANCH_PREDICT_H