# RetroPie Install

## Desktop

Mayhem needs X to be installed. 

Install it from RetroPie Config > Update > Raspbian Tools > Install Desktop.

## Xbox controllers

The .cfg files are config files for xboxdrv to map xbox controller buttons to player 1 & 2 keys.

The Mayhem-Pi.sh script stops the xboxdrv daemon and launches it again with the new configuration and launches the game. When the game ends it restarts xboxdrv with the original config.
