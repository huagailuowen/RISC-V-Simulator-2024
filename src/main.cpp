#include "include/simulator.h"

#include<iostream>
using namespace cpu;
int main()
{
    Naive_Simulator sim;
    sim.init(0);
    printf("%d\n", sim.run());
    return 0;
}
