#include "player_missiles.h"
#include "player_1.h"
#include "types.h"

#include <atari.h>

#include <string.h>

#pragma bss-name (push,"PLAYERMISSILE")
PlayerMissiles player_missiles;
#pragma bss-name (pop)

Player players[NUM_PLAYERS];

void init_player_missiles()
{
    byte idx;

    memset(&player_missiles, 0X00, sizeof(PlayerMissiles));

    //memcpy(&(player_missiles.player0[60]), player_1_0, sizeof(player_1_0));
    //memset(&(player_missiles.player0[60]), 0xFF, sizeof(player_missiles.player0));

    ANTIC.pmbase = ((u_short)&player_missiles) >> 8;
    OS.sdmctl = OS.sdmctl | DMACTL_PLAYFIELD_NORMAL | DMACTL_DMA_PLAYERS | DMACTL_DMA_MISSILES | DMACTL_DMA_FETCH | DMACTL_PMG_SINGLELINE;//0x2E;
    GTIA_WRITE.gractl = 0x03;
    OS.pcolr0 = GTIA_COLOR_LIGHTRED; //0x3A;  // Red
    OS.pcolr1 = 0x3A;  // Red
    OS.pcolr2 = 0x3A;  // Red
    OS.pcolr3 = 0x3A;  // Red
    GTIA_WRITE.hposp0 = 100;
    GTIA_WRITE.hposp1 = 100;
    GTIA_WRITE.hposp2 = 100;
    GTIA_WRITE.hposp3 = 100;
    OS.paddl0 = 1;             // PMs in front of all

    OS.rtclok[0] = OS.rtclok[1] = OS.rtclok[2] = 0x00;

    for(idx = 0; idx < NUM_PLAYERS; ++idx)
    {
        players[idx].dirty = 0;      // True when state changes and must be updated.
        players[idx].x = 100;
        players[idx].y = 60;
        players[idx].image_idx = 0;
        players[idx].anim_dir = 1;
    }

    // Test
    players[0].dirty = 1;
}

void set_player_position(byte idx, byte x, byte y)
{
    players[idx].x = x;
    players[idx].y = y;
    players[idx].dirty = 1;
}

void update_player_missiles()
{
    byte idx;

    for(idx = 0; idx < NUM_PLAYERS; +idx)
    {        
        if(OS.rtclok[2] > 10)
        {
            OS.rtclok[0] = OS.rtclok[1] = OS.rtclok[2] = 0x00;

            if(players[idx].image_idx == 3)
                players[idx].anim_dir = -1;

            if(players[idx].image_idx == 0)
                players[idx].anim_dir = 1;

            players[idx].image_idx  = players[idx].image_idx + players[idx].anim_dir;

            players[idx].dirty = 1;
        }

        if(players[idx].dirty)
        {
            switch(players[idx].image_idx)
            {
                case 0:
                    memcpy(&(player_missiles.player0[players[idx].y]), player_1_0, sizeof(player_1_0));
                break;
                case 1:
                    memcpy(&(player_missiles.player0[players[idx].y]), player_1_1, sizeof(player_1_1));
                break;
                case 2:
                    memcpy(&(player_missiles.player0[players[idx].y]), player_1_2, sizeof(player_1_2));
                break;
                case 3:
                    memcpy(&(player_missiles.player0[players[idx].y]), player_1_3, sizeof(player_1_3));
                break;
            }

            switch(idx)
            {
                case 0:
                    GTIA_WRITE.hposp0 = players[0].x;
                break;
                case 1:
                    GTIA_WRITE.hposp1 = players[1].x;
                break;
                case 2:
                    GTIA_WRITE.hposp2 = players[2].x;
                break;
                case 3:
                    GTIA_WRITE.hposp3 = players[3].x;
                break;
            }

            players[idx].dirty = 0;
        }
    }
}