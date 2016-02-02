![IMG](http://energia.nu/img/Energia.png)

[![Stories in In Progress](https://badge.waffle.io/energia/energia.png?label=In%20Progress&title=In%20Progress)](https://waffle.io/energia/energia)<br>
[![Stories in Ready to Commit](https://badge.waffle.io/energia/energia.png?label=Ready%20to%20Commit&title=Ready%20to%20Commit)](https://waffle.io/energia/energia)


## What Is Energia?

Energia is a fork/port of Arduino for the Launchpads, or boards with MCUs from Texas Instruments.

## What Are the LaunchPads Supported?

Energia provides native support for the following LaunchPads:

* LaunchPad with MSP430G2231, MSP430G2452 or MSP430G2553 or *LaunchPad*
* Experimeter Board with MSP430FR5739 or *FraunchPad*
* LaunchPad with MSP430F5529 or *FattyPad*
* LaunchPad with MSP430FR5969
* LaunchPad with Stellaris LM4F120 or Tiva C Series TM4C123 or *StellarPad* 
* Connected LaunchPad with Tiva C Series TM4C129

## What Are the BoosterPacks Supported?

Energia includes ready-to-use libraries for the following BoosterPacks:

* Anaren Air CC110L BoosterPack
* Educational BoosterPack MKII
* LCD Sharp BoosterPack
* CC3000 SimpleLink WiFi BoosterPack

## Looking for Help?

No problem! There are a variety of resources available to get you up and running, and sprinting once you're up and running.

* [GitHub repository](http://github.com/energia/Energia) - This very page!
* [Download](http://energia.nu/download/) - Download a compiled application for Linux, Mac OS X, or Windows.
* [Website](http://energia.nu) - Full documentation including tutorials, reference, pins maps, FAQ and much more!
* [Wiki](https://github.com/energia/Energia/wiki) - Find basic information and tutorials here.
* [LaunchPad forum at 43oh](http://forum.43oh.com/forum/28-energia/) - A community around the original LaunchPad  but also the newer ones.
* [StellarPad forum at Stellaristi](http://forum.stellarisiti.com/forum/63-energia/) - A community more focused on the newer Stellaris LaunchPad.
* [Bug report](http://github.com/energia/Energia/issues) - Is something not working as it ought to? Or better yet, is there something we could make better?

## Clone instructions:

Energia consists of the main repository and a submodule called emt. The emt tree contains the sources for the Energia MT (Multi Tasking) feature that is based on TI-RTOS/SYSBIOS.
To clone Energia and the emt submodule:
```
git clone --recursive https://github.com/energia/Energia.git
```
If you already have a clone of Energia then:
```
git submodule update --init --recursive
git submodule sync
cd emt
git pull
cd ..
```
