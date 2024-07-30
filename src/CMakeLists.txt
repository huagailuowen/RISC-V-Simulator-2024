set(Unit_src
  units/Arithmetic_logic_unit.cpp
  units/Branch_predict.cpp
  units/Bus.cpp
  units/Instruction.cpp
  units/Load_store_buffer.cpp
  units/Memory.cpp
  units/Register_file.cpp
  units/Reorder_buffer.cpp
  units/Reservation_station.cpp
)
set(Utility_src 
  utility/util.cpp
)

add_library(src ${Unit_src} ${Utility_src} simulator.cpp)