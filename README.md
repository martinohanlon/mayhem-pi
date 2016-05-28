#Mayhem 2 - Raspberry Pi 
##Martin O'Hanlon (martin@ohanlonweb.com)
##http://www.stuffaboutcode.com

##Description
[Mayhem](http://www.lemonamiga.com/games/details.php?id=2972) was originally released as Public Domain / Shareware on the [Amiga](https://en.wikipedia.org/wiki/Amiga). It was ported to the PC in 2002 by [devpack](https://github.com/devpack) and released onto github in 2011 [github.com/devpack/mayhem](https://github.com/devpack/mayhem). 

![Mayhem game image](mayhem.jpg)

[Video of the original amiga game](https://www.youtube.com/watch?v=fs30DLGxqhs).

I picked it up from [code.google.com/p/mayhem](https://code.google.com/archive/p/mayhem/) ([New BSD License](https://opensource.org/licenses/BSD-3-Clause)) and with the help of Lee Taylor have added new levels and features.

[Video 1](https://youtu.be/Vxozz0Ijdr0)

[Video 2 - new level](https://youtu.be/E3mho6J6OG8)

This is the [Raspberry Pi](https://www.raspberrypi.org) port of the game, you can find the Windows PC fork at [github.com/martinohanlon/mayhem](https://github.com/martinohanlon/mayhem). 

[Blog post](http://www.stuffaboutcode.com/2016/04/mayhem-classic-amiga-game-ported-to.html)

##Gameplay

Mayhem is a multiplayer (2 - 4) flight shooter with a really simple objective - destroy your opponents before they destroy you.

Your ship has limited fuel which will run down when you boost, if you run out you will be unable to control your ship, to refuel, land on any flat surface.

You can protect yourself from attack using your shields which will stop all bullets, be careful though your shields run down quickly and you wont be able to boost while your shields are on. 

Powerups are dropped (sometimes) when a player is destroyed (by either crashing or being shot) and when collected will give you a temporary boost.

###Options

Levels 1-3 are the original game levels, all other levels are new to Mayhem 2.

DCA are anti spaceship guns which will fire at the player if they get too close.

Wall collision can be turned off for new players to get used to the controls and playing the game.

##Keys

Player 1 - z, x, c, v, g 

Player 2 - left, right, pad del, pad 0, pad enter

Player 3 - b, n, 'comma', m, l

Player 4 - y, u, o, i, 0

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

##Version history
* beta - compiles, runs, ongoing mods
* 0.1 - added new levels and features
* 0.2 - seamless warping across map edges
* 0.4 - menu changes + new 'option' (powerup) changes
* 0.5 - timing and powerups are now dropped when players explode

##Contributors
[Anthony Prieur](https://github.com/devpack)

[Martin O'Hanlon](https://github.com/martinohanlon)

Lee Taylor
