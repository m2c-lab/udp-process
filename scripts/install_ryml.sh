#!/bin/sh

mkdir _tmp
cd _tmp
git clone --recursive https://github.com/biojppm/rapidyaml
cd rapidyaml
mkdir build
cd build
cmake ..
make
make install
cd ../../..
rm -r _tmp
