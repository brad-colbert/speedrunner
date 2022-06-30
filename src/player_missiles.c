#include "player_missiles.h"
#include "player_1.h"
#include "types.h"

#include <atari.h>
#include <conio.h>

#include <string.h>

#pragma bss-name (push,"PLAYERMISSILE")
PlayerMissiles player_missiles;
#pragma bss-name (pop)

union __players {
    Player all[NUM_PLAYERS];
    struct {
        Player one;
        Player two;
        Player three;
        Player four;
    };
};
typedef union __players Players;

Players players;

byte idx;

void init_player_missiles()
{
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
    GTIA_WRITE.hposp0 = 0;
    GTIA_WRITE.hposp1 = 0;
    GTIA_WRITE.hposp2 = 0;
    GTIA_WRITE.hposp3 = 0;
    OS.paddl0 = 1;             // PMs in front of all

    OS.rtclok[0] = OS.rtclok[1] = OS.rtclok[2] = 0x00;

    for(idx = 0; idx < NUM_PLAYERS; ++idx)
    {
        players.all[idx].dirty = 0;      // True when state changes and must be updated.
        players.all[idx].x = 100;
        players.all[idx].y = 60;
        players.all[idx].image_idx = 0;
        players.all[idx].anim_dir = 1;
    }

    // Test
    players.one.dirty = 1;
    /*
    player1.dirty = 1;      // True when state changes and must be updated.
    player1.x = 0;
    player1.y = 0;
    player1.image_idx = 0;
    player1.anim_dir = 1;
    player2.dirty = 1;      // True when state changes and must be updated.
    player2.x = 0;
    player2.y = 0;
    player2.image_idx = 0;
    player2.anim_dir = 1;
    player3.dirty = 1;      // True when state changes and must be updated.
    player3.x = 0;
    player3.y = 0;
    player3.image_idx = 0;
    player3.anim_dir = 1;
    player4.dirty = 1;      // True when state changes and must be updated.
    player4.x = 0;
    player4.y = 0;
    player4.image_idx = 0;
    player4.anim_dir = 1;
    */
}

void set_player_position(byte num, byte x, byte y)
{
    Player* player = &players.one + sizeof(Player) * (u_short)num;

    player->x = x;
    player->y = y;
    player->dirty = 1;      // True when state changes and must be updated.

    /*
    //cprintf("%d: %d, %d\n\r", num, x, y);
    switch(num)
    {
        case 1:
            player1.x = x;
            player1.y = y;
            player1.dirty = 1;      // True when state changes and must be updated.
        break;
        case 2:
            player2.x = x;
            player2.y = y;
            player2.dirty = 1;      // True when state changes and must be updated.
        break;
        case 3:
            player3.x = x;
            player3.y = y;
            player3.dirty = 1;      // True when state changes and must be updated.
        break;
        case 4:
            player4.x = x;
            player4.y = y;
            player4.dirty = 1;      // True when state changes and must be updated.
        break;
    }
    */
    /*
    players[idx].x = x;
    players[idx].y = y;
    players[idx].dirty = 1;
    */
}

void update_player_missiles()
{
    Player* player;

    for(idx = 0; idx < NUM_PLAYERS; ++idx)
    {
        player = &players.one + sizeof(Player) * (u_short)idx;

        // Update the animation by changing the current active player sequence image
        if(OS.rtclok[2] > 10)
        {
            OS.rtclok[0] = OS.rtclok[1] = OS.rtclok[2] = 0x00;

            if(player->image_idx == 3)
                player->anim_dir = -1;

            if(player->image_idx == 0)
                player->anim_dir = 1;

            player->image_idx  = player->image_idx + player->anim_dir;

            player->dirty = 1;
        }

        if(player->dirty)
        {
            // Move in Y by updating the image in memory
            memcpy(&(player_missiles.player0[player->y]), &player_1_0[0] + sizeof(player_1_0) * player->image_idx, sizeof(player_1_0));

            // Move in X by updating the PM horizontal position
            *(&GTIA_WRITE.hposp0 + idx) = player->x;
        }

        #if 0
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

        /*
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
        */

            players[idx].dirty = 0;
        }
        #endif
    }
}