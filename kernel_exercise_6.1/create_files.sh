#!/bin/bash

for i in {1..9}; do
    f="/tmp/myfile$i"
    touch "$f"
    inode_info=$(ls -i "$f")
    echo "inode $inode_info"
done
