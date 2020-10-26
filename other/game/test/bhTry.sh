#!/bin/bash

g++ hello.cpp -o a.out

if [ $? -eq 0 ]; then
    mkdir $1
    if [ $? -eq 0 ]; then
        mkdir $2
        
    else
        echo "failed"
    fi
else
    echo "failed"
fi