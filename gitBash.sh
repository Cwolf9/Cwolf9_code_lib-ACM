#!/bin/bash

git add .

if [ $? -eq 0 ]; then
    git commit -m $1
    if [ $? -eq 0 ]; then
        git push -u origin master
    else
        echo "failed"
    fi
else
    echo "failed"
fi
