#ifndef CONFIG_H
#define CONFIG_H

namespace cpu{

const int PREDICT_COUNTER_SIZE = 32;
const int Register_SIZE = 32;
const int Memory_SIZE = 1<<20;
const int RS_SIZE = 32;
const int LSB_SIZE = 32;
const int ROB_SIZE = 32;

const int Cache_SIZE = 1<<15;

const int Queue_SIZE = 32;
const int Container_SIZE = 32;

const int CD_BUS_SIZE = 8;
const int MEM_BUS_SIZE = 4;

const int ALU_MUL_SIZE = 32;
const int ALU_ADD_SIZE = 32;

const int ALU_MUL_LATENCY = 3;
const int ALU_ADD_LATENCY = 1;
const int MEM_LATENCY = 4;

}



#endif