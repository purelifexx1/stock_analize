#!/bin/bash

make
if [[ $? != 0 ]]; then
    echo "Failed to build unitTest"
    exit 1
fi
./a.out