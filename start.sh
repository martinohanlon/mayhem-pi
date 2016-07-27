#!/bin/bash

#change to script directory
cd "$(dirname "$0")"

#is x running?
X=$( pidof X )
if [ ${#X} -gt 0 ]
then
        ./mayhem2-pi
else
        /usr/bin/startx ./mayhem2-pi
fi

