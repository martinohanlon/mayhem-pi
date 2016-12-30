#!/bin/bash

#check there is enough gpu memory to start mayhem
vcgencmd get_mem gpu > gpu_mem
source gpu_mem
#strip last char from 64M
gpu=${gpu%?}
if (( $gpu >= 96 )); then
    ./mayhem2-pi
else
    echo "Mayhem 2 needs at least 96MB of memory allocated to the GPU"
    echo "Use sudo raspi-config (Advanced Options > Memory Split) to change"
fi
rm gpu_mem
