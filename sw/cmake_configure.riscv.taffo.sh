#!/bin/bash

TARGET=riscv32-unknown-elf
PULP_GCC="/opt/pulp-gcc-2.5.0"
SYSROOT="$PULP_GCC/$TARGET"

OBJDUMP="$PULP_GCC/bin/$TARGET-objdump"
OBJCOPY="$PULP_GCC/bin/$TARGET-objcopy"
RANLIB="$PULP_GCC/bin/$TARGET-ranlib"

COMPILER=taffo
COMPILER_CXX=taffo
COMPILER_ASM="$PULP_GCC/bin/$TARGET-gcc"

LINKER="$PULP_GCC/bin/$TARGET-gcc"
LINKER_CXX="$PULP_GCC/bin/$TARGET-g++"
LINKER_CMD="$LINKER <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>"
LINKER_CMD_CXX="$LINKER_CXX <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>"

VSIM=`which vsim`

TARGET_C_FLAGS="-O3  -g"
#TARGET_C_FLAGS="-O2 -g -falign-functions=16  -funroll-all-loops"

# if you want to have compressed instructions, set this to 1
RVC=0

# if you are using zero-riscy, set this to 1, otherwise it uses RISCY
USE_ZERO_RISCY=0

# set this to 1 if you are using the Floating Point extensions for riscy only
RISCY_RV32F=1

# zeroriscy with the multiplier
ZERO_RV32M=1
# zeroriscy with only 16 registers
ZERO_RV32E=0

# riscy with PULPextensions, it is assumed you use the ETH GCC Compiler
GCC_MARCH="rv32imf"
#compile arduino lib
ARDUINO_LIB=0

PULP_GIT_DIRECTORY=../../
SIM_DIRECTORY="$PULP_GIT_DIRECTORY/vsim"
#insert here your post-layout netlist if you are using IMPERIO
PL_NETLIST=""

cmake "$PULP_GIT_DIRECTORY"/sw/ \
    -DPULP_MODELSIM_DIRECTORY="$SIM_DIRECTORY" \
    -DCMAKE_C_COMPILER="$COMPILER" \
    -DCMAKE_CXX_COMPILER="$COMPILER_CXX" \
    -DCMAKE_ASM_COMPILER="$COMPILER_ASM" \
    -DVSIM="$VSIM" \
    -DRVC="$RVC" \
    -DRISCY_RV32F="$RISCY_RV32F" \
    -DUSE_ZERO_RISCY="$USE_ZERO_RISCY" \
    -DZERO_RV32M="$ZERO_RV32M" \
    -DZERO_RV32E="$ZERO_RV32E" \
    -DGCC_MARCH="$GCC_MARCH" \
    -DARDUINO_LIB="$ARDUINO_LIB" \
    -DPL_NETLIST="$PL_NETLIST" \
    -DCMAKE_C_FLAGS="$TARGET_C_FLAGS" \
    -DCMAKE_OBJCOPY="$OBJCOPY" \
    -DCMAKE_OBJDUMP="$OBJDUMP" \
    -DCMAKE_C_COMPILER_TARGET="$TARGET" \
    -DCMAKE_CXX_COMPILER_TARGET="$TARGET" \
    -DCMAKE_ASM_COMPILER_TARGET="$TARGET" \
    -DCMAKE_SYSROOT="$SYSROOT" \
    -DCMAKE_C_COMPILER_EXTERNAL_TOOLCHAIN="$PULP_GCC" \
    -DCMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN="$PULP_GCC" \
    -DCMAKE_ASM_COMPILER_EXTERNAL_TOOLCHAIN="$PULP_GCC" \
    -DCMAKE_C_LINK_EXECUTABLE="$LINKER_CMD" \
    -DCMAKE_CXX_LINK_EXECUTABLE="$LINKER_CMD_CXX"

# Add -G "Ninja" to the cmake call above to use ninja instead of make
