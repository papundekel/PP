#!/bin/bash

cmake -DCMAKE_BUILD_TYPE:STRING="$2" -B "$1" -G Ninja

cmake --build "$1" --config "$2" --target "$3" -j 10 --
