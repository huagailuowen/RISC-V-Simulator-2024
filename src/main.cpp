#include "include/simulator.h"
#include "utility/util.h"
#include<filesystem>
#include<iostream>
#include <semaphore>
using namespace cpu;

Naive_Simulator sim;
int main()
{
    // std::cout << "Current working directory: " 
    //           << std::filesystem::current_path() << std::endl;
    // freopen("./sample/sample.data","r",stdin);
    // freopen("./testcases/superloop.data","r",stdin);
    
    sim.init(0);
    printf("%d\n", sim.run());
    return 0;
}
