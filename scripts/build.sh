#!/bin/bash
# TODO: Проверить на Линукс
# Отключение вывода
set +o echo
cmake -Wno-dev -DCMAKE_CXX_COMPILER=c++ -DCMAKE_CXX_FLAGS="-static -static-libgcc -static-libstdc++" -G Ninja -S .. -B ../build && cmake --build ../build
set -o echo
read -rp "Нажмите Enter, чтобы продолжить..."