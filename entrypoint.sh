#!/bin/bash

pacman --noconfirm -Syyy gcc cmake ninja

cd /PP

cmake -DCMAKE_BUILD_TYPE:STRING=Release -H. -B./build -G Ninja

cmake --build ./build --config Release --target PPtest -j 10 --
