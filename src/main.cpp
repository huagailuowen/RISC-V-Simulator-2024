#include "include/simulator.h"
using namespace cpu;

namespace cpu{
Simulator sim;
Naive_Simulator* naive_sim;

}
int main()
{
    // std::cout << "Current working directory: " 
    //           << std::filesystem::current_path() << std::endl;
    // freopen("./testcases/array_test2.data","r",stdin);
    // freopen("./testcases/superloop.data","r",stdin);
    
    sim.init(0);
    naive_sim = sim.naive_simulator;
    printf("%d\n", sim.run());
    return 0;
}
