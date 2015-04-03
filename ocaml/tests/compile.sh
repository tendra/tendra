#!/bin/bash
set -e
name=`basename $1`
# Compile source to binary capsule
tcc -Ft -o $name.t $1
# Expand all tokens in binary capsule
tnc -d  -a $name.t $name.full.t
# Generate LLVM assembler
../trans.byte $name.full.t $name.ll
# Compile and link LLVM to executable
clang $name.ll
