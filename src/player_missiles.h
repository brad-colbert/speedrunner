#ifndef __PLAYER_MISSILES_H__
#define __PLAYER_MISSILES_H__

#include "types.h"

#define PMG_SINGLE_LINE
#ifdef PMG_SINGLE_LINE
typedef struct {
char blank[768];
char missile3210[256];
char player0[256];
char player1[256];
char player2[256];
char player3[256];
} PlayerMissiles;
#else
typedef struct {
char blank[384];
char missile3210[128];
char player0[128];
char player1[128];
char player2[128];
char player3[128];
} PlayerMissiles;
#endif

typedef struct
{
    byte dirty;
    byte x, y;
    char image_idx, anim_dir;
    byte image_time;
} Player;

#define NUM_PLAYERS 1
extern Player players[NUM_PLAYERS];

void set_player_position(byte idx, byte x, byte y);
void init_player_missiles(void);
void update_player_missiles(void);

#endif // __PLAYER_MISSILES_H__
