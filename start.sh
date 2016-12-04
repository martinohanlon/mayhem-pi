#!/bin/bash

#check there is enough gpu memory to start mayhem
source /boot/config.txt
if [[ !  -z  $gpu_mem  ]]; then
    if (( $gpu_mem >= 96 )); then
        ./mayhem2-pi
    else
        echo "Mayhem 2 needs at least 96MB of memory allocated to the GPU"
        echo "Use sudo raspi-config (Advanced Options > Memory Split) to change"
    fi
else
    echo "Mayhem 2 needs at least 96MB of memory allocated to the GPU"
    echo "Use sudo raspi-config (Advanced Options > Memory Split) to change"
fi

