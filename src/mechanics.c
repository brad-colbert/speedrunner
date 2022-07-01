#include "mechanics.h"
#include "playfield.h"
#include "player_missiles.h"
#include "types.h"

#include <conio.h>

void update_playfield_using_players()
{
    #if 0
    u_short x_avg = 0;
    u_short y_avg = 0;
    byte idx;
    
    // Calculate the centroid of the position of all players
    for(idx = 0; idx < num_players; ++idx)
    {
        x_avg += players.all[idx].x;
        y_avg += players.all[idx].y;
    }

    x_avg /= num_players;
    y_avg /= num_players;
    #endif

    // Find if the player is off the visible playfield, if so, move the playfield
    u_short pf_right, pf_bottom;
    short screen_x, screen_y, pm_pf_x, pm_pf_y;
    pf_right = pf_x + PF_COLS_PER_PAGE;
    pf_bottom = pf_y + PF_LINES_PER_PAGE;
    pm_pf_x = players.one.x - PF_MIN_X;
    pm_pf_y = players.one.y - PF_MIN_Y;

    // Only draw it on the screen.
    screen_x = (short)pm_pf_x - pf_x;
    screen_y = (short)pm_pf_y - pf_y;

    //cprintf("\r%d,%d - %d,%d:%d,%d -> %d,%d      \r", players.one.x, players.one.y, pf_x, pf_y, pf_right, pf_bottom, screen_x, screen_y);
    cprintf("\rpm   %d,%d\n", players.one.x, players.one.y);
    cprintf("\rpf   %d,%d\n", pf_x, pf_y);
    cprintf("\rpf rl%d,%d\n", pf_right, pf_bottom);
    cprintf("\rpm pf%d,%d\n", pm_pf_x, pm_pf_y);
    cprintf("\rscrn %d,%d\n", screen_x, screen_y);
    gotoy(0);

    // Just do something right now
    if(screen_x < 0 | screen_y < 0)
        scroll_playfield(pm_pf_x, pm_pf_y);
    if(screen_x + PLAYER_WIDTH > pf_right)
        scroll_playfield((pm_pf_x + PLAYER_WIDTH) - PF_COLS_PER_PAGE, pf_y);
    if(screen_y + PLAYER_WIDTH > pf_bottom)                     // Should have a PIX height...
        scroll_playfield(pf_x, (pm_pf_y + PLAYER_WIDTH) - PF_LINES_PER_PAGE);
        
    /*
    u_short x = pf_x, y = pf_y;
    byte dirty = 0;
    if(players.one.x < pf_x)
    {
        x = players.one.x;
        dirty = 1;
    }
    else if(players.one.x > pf_x + PF_COLS_PER_PAGE)
    {
        x = players.one.x;
        dirty = 1;
    }
    else if(players.one.y < pf_y)
    {
        y = players.one.y;
        dirty = 1;
    }
    else if(players.one.y > pf_y + PF_LINES_PER_PAGE)
    {
        y = players.one.y;
        dirty = 1;
    }

    if(dirty)
        scroll_playfield(x, y);
    */
}
