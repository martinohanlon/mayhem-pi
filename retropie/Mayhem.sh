
sudo killall xboxdrv
sudo "/opt/retropie/supplementary/xboxdrv/bin/xboxdrv" --daemon --detach --dbus disabled --detach-kernel-driver --id 0 --led 2 -c  /home/pi/RetroPie/roms/ports/mayhem-pi/retropie/mayhem_xbox_play1.cfg --silent --next-controller --id 1 --led 3 -c  /home/pi/RetroPie/roms/ports/mayhem-pi/retropie/mayhem_xbox_play2.cfg --silent 
/home/pi/RetroPie/roms/ports/mayhem-pi/start
sudo killall xboxdrv
sudo "/opt/retropie/supplementary/xboxdrv/bin/xboxdrv" --daemon --detach --dbus disabled --detach-kernel-driver --id 0 --led 2 --deadzone 4000 --silent --trigger-as-button --next-controller --id 1 --led 3 --deadzone 4000 --silent --trigger-as-button
sleep 1
