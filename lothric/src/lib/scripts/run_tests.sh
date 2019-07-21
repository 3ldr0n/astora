#!/bin/bash

BINARIES=bin/*
RED='\033[0;31m'
ERASE='\033[0m'

for bin in $BINARIES
do
    is_test=$(file $bin | grep test)
    if [ is_test != 0 ];
    then
        echo -e "\n$RED ${bin##*/} $ERASE\n"
        ./$bin
    fi
done
