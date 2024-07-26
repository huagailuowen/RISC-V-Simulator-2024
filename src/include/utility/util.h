#ifndef UTIL_H
#define UTIL_H
#include <cstdint>
#include<string>
namespace cpu{
enum class Optype{
  R,I,S,B,U,J
};
enum class Opt {
  LUI,
  AUIPC,
  JAL,
  JALR,
  BEQ,
  BNE,
  BLT,
  BGE,
  BLTU,
  BGEU,
  LB,
  LH,
  LW,
  LBU,
  LHU,
  SB,
  SH,
  SW,
  ADDI,
  SLTI,
  SLTIU,
  XORI,
  ORI,
  ANDI,
  SLLI,
  SRLI,
  SRAI,
  ADD,
  SUB,
  SLL,
  SLT,
  SLTU,
  XOR,
  SRL,
  SRA,
  OR,
  AND
  // ... Add other instructions as needed ...
};


using DataType = uint32_t;
using AddrType = uint32_t;
using RAMType = uint8_t;
struct Ins{
  Optype type;
  Opt opt;
  DataType rd,rs1,rs2,imm;
  bool predict_res;
  AddrType pc_addr;
  Ins(Optype type,Opt opt,int rd,int rs1,int rs2,int imm,int pc_addr):
      type(type),opt(opt),rd(rd),rs1(rs1),rs2(rs2),imm(imm),pc_addr(pc_addr){}
  Ins():rd(-1),rs1(-1),rs2(-1),imm(-1){}
  //Invalid state

};
using std::string;

// std::string Opt_to_string(const Opt &opt);

uint32_t get_segment(uint32_t data,int l,int r);
//Get the segment [l,r] of data, the low bit is l and the high bit is r
uint32_t sign_ext(uint32_t data,int bit);

uint32_t Hex_to_int(std::string str);
}
#endif