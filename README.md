#Mayhem - Raspberry Pi 
##Martin O'Hanlon (martin@ohanlonweb.com)
##http://www.stuffaboutcode.com

##Description
A [Raspberry Pi](https://www.raspberrypi.org) port of the game [Mayhem](http://www.lemonamiga.com/games/details.php?id=2972) originally released as Public Domain / Shareware on the [Amiga](https://en.wikipedia.org/wiki/Amiga).

It was ported to the PC in 2002 by [devpack](https://github.com/devpack) and released onto github in 2011 [github.com/devpack/mayhem](https://github.com/devpack/mayhem).

I picked up it up from [code.google.com/p/mayhem](https://code.google.com/archive/p/mayhem/) ([New BSD License](https://opensource.org/licenses/BSD-3-Clause)) and ported it to the Raspberry Pi.

Myself and Lee Taylor have since extended the game with new levels and features.

If you want to play it on Windows I maintain a fork of the original version [github.com/martinohanlon/mayhem](https://github.com/devpack/mayhem) and keep it up to date with the pi version.

[Video 1](https://youtu.be/Vxozz0Ijdr0)

[Video 2 - new level](https://youtu.be/E3mho6J6OG8)

[Video of the original amiga game](https://www.youtube.com/watch?v=fs30DLGxqhs). 

[Blog post](http://www.stuffaboutcode.com/2016/04/mayhem-classic-amiga-game-ported-to.html)

![Mayhem game image](mayhem.jpg)

##Install

```
sudo apt-get install liballegro4.4 liballegro4-dev
git clone https://github.com/martinohanlon/mayhem-pi
```

##Run

```
cd mayhem-pi
./start
```

##Compile
```
cd mayhem-pi
make
```

##Keys

Player 1 - z, x, c, v, g 

Player 2 - left, right, pad del, pad 0, pad enter

Player 3 - b, n, 'comma', m, l

Player 4 - y, u, o, i, 0

##Version history
* beta - compiles, runs, ongoing mods
* 0.1 - added new levels and features
* 0.2 - seamless warping across map edges
* 0.4 - menu changes + new 'option' (powerup) changes


##Contributors
[Anthony Prieur](https://github.com/devpack)

[Martin O'Hanlon](https://github.com/martinohanlon)

Lee Taylor
