#!/bin/bash

cd $( cd "$(dirname "${BASH_SOURCE[0]}")"; pwd -P )

find ./ -regex ".*\.[ch]pp" | xargs clang-format -i
