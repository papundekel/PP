#!/bin/bash

cd $( cd "$(dirname "${BASH_SOURCE[0]}")"; pwd -P )

cmake -DCMAKE_BUILD_TYPE:STRING=Release -H. -B./build -G Ninja

cmake --build ./build --config Release --target PPtest -j 10 --
