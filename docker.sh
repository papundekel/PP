#!/bin/bash

cd $( cd "$(dirname "${BASH_SOURCE[0]}")"; pwd -P )

./build.sh

./build/PPtest/PPtest
