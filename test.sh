#!/bin/bash

cd $( cd "$(dirname "${BASH_SOURCE[0]}")"; pwd -P )

CONF="RELEASE"
DIR="./build"

./build.sh "$DIR" "$CONF" PP-test

cd "$DIR"
ctest -C "$CONF" -T test --output-on-failure
