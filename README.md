# SpeedRunner
This is my attempt at learning a lot of things that I've always wanted to be able to do as a kid on my Atari 800... and maybe wind up with a game at the end of my efforts.

Specifically:
  * Fast fine-scrolling
  * Player missile graphics (preferable multi-color)
  * Sounds and maybe music even though I can't make music to save my life.

First, I wanted to choose a game that I think I could code up in C (cc65) for the Atari.  A game that would fit the ANTIC/GTIA capabilites well.  A game with some good action and a relatively simple goal.  A game that is multi-player, with the larger goal of taking advantage of the FujiNet for networked multi-player.

I landed on SpeedRunners (https://youtu.be/N8up3tl1_j0) which... well, watch the video.  It will give you a better idea of the gameplay than I can right now.

In this project I will try to capture an evolution of capabilities.  I will try to branch the development of each new capability so as to be an example of how to make it work and maybe what not to do as well.

## Versions

### 0.0
INITIAL(main): This is simply the initial commit with some test code that is the begining of me figuring out how to do fine scrolling.  Basically it has the rough implementation of course scrolling (with DL manipulation) as well as fine scrolling (with updates to VSCROL).

I think I'll stick with ANTIC mode 4 (4 color text) and make tiles out of a new charset that will build the playfield.  Roughly 960bytes per screen versus about 4K for GFX7, which means I should be able to keep each complete playfield in memory.  Once I work on some fast paging scheme, then I can switch to GFX7.

### 0.1
feature/scrolling and feature/vbi: Exploring and implementing the vertical blank interupt.  Most of this code exists in the assembly file *update_scroll.s*.  This actually implements both the course and fine scrolling.  The coordinates are absolute, computed on the C side (math(s) is hard in assembly... well... for me).

Since the VBI may happen in the middle of computing the scroll values, updates are coordinated with a flag that sits in 0 page.  The update will not happen as long as the **scroll_flag** is > 0.  Basically this is a simple, non blocking mutex.

### 0.2
feature/player_missiles: This implements the players and the memory structures used to manage them.  There is, currently, an example animation of P0.  Each is single line height.  Player data are stored in *player_#.h*.  The main player functions are in *player_missile.h/c*.  Basic motion mechanics are implemented in *player_missile.h/c* but I've started to move them to *mechanics.h/c* because the player positions are use to determine the location of the "viewport" of the playfield.

There is a very simple example implementation of player+playfield collision using the GTIA hardware in *player_missile.c:update_player_missiles()*.  I understand that I should consider doing this on the CPU side, but there is a good chance I can get away with using the facilities available.  As implemented it simply changes the color of the player to represent what it's collided with.
Currently, this is a bit of a mess and is a work in progress.

### 0.3
