#!/bin/bash

cd /PP

pacman -S gcc cmake ninja

cmake -DCMAKE_BUILD_TYPE:STRING=Release -H. -B./build -G Ninja

cmake --build ./build --config Release --target PPtest -j 10 --
