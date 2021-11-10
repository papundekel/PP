#!/bin/bash

cd $( cd "$(dirname "${BASH_SOURCE[0]}")"; pwd -P )

rm -rf ./.build/ ./build/ ./install/
