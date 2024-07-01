@echo off 
cmake -Wno-dev -DCMAKE_CXX_COMPILER=c++ -DCMAKE_CXX_FLAGS="-static -static-libgcc -static-libstdc++" -G Ninja -S .. -B ../build && cmake --build ../build