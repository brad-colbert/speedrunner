#include "player_missiles.h"
#include "player_1.h"
#include "types.h"

#include <atari.h>

#include <string.h>

#pragma bss-name (push,"PLAYERMISSILE")
PlayerMissiles player_missiles;
#pragma bss-name (pop)

int player0_image = 0;
int anim_direction = 1;
void init_player_missiles()
{
    memset(&player_missiles, 0X00, sizeof(PlayerMissiles));

    memcpy(&(player_missiles.player0[60]), player_1_0, sizeof(player_1_0));
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
}

void update_player_missiles()
{
    if(OS.rtclok[2] > 10)
    {
        OS.rtclok[0] = OS.rtclok[1] = OS.rtclok[2] = 0x00;

        player0_image = player0_image + anim_direction;
        if(player0_image > 3)
        {
            player0_image = 2;
            anim_direction = -1;
        }
        if(player0_image < 0)
        {
            player0_image = 0;
            anim_direction = 1;
        }

        switch(player0_image)
        {
            case 0:
                memcpy(&(player_missiles.player0[60]), player_1_0, sizeof(player_1_0));
            break;
            case 1:
                memcpy(&(player_missiles.player0[60]), player_1_1, sizeof(player_1_1));
            break;
            case 2:
                memcpy(&(player_missiles.player0[60]), player_1_2, sizeof(player_1_2));
            break;
            case 3:
                memcpy(&(player_missiles.player0[60]), player_1_3, sizeof(player_1_3));
            break;
        }
    }
}