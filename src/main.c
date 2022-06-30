// Our includes first
#include "graphics.h"
#include "playfield.h"
#include "types.h"
#include "playfield_utils.h"
#include "player_missiles.h"

// Atari specific includes next
#include <atari.h>
#include <joystick.h>
#include <conio.h>

// Standard C includes
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define USE_JOYSTICK
#define DELAY 128

extern u_short line_r, col_r;

int main()
{
    #ifdef USE_JOYSTICK
    int joy;
    #else
    u_short line_d, col_d;
    byte bounce_count = 0;
    #endif
    u_short delay;
    u_short x, y;

    cprintf("Hit Key");
    cgetc();  // Pause

    init_graphics();
    init_playfield();
    init_player_missiles();

    #ifdef USE_JOYSTICK
    y = x = 0;

    joy_install(joy_static_stddrv);

    joy = joy_read(JOY_1);
    while (!JOY_BTN_1(joy))
    {
        if (JOY_UP(joy)){
            if(y > 0)
                --y;
        }
        else if (JOY_DOWN(joy)){
            if(y < (PF_LINES - PF_LINES_PER_PAGE)-1)
                ++y;
        }

        if (JOY_LEFT(joy)) {
            if(x > 0)
                --x;
        }
        else if (JOY_RIGHT(joy)) {
            if(x < (PF_COLS - PF_COLS_PER_PAGE)-1)
                ++x;
        }

        set_player_position(0, (byte)x, (byte)y);
        update_player_missiles();
        scroll_playfield((u_short)x, (u_short)y);

        for(delay = 0; delay < DELAY; ++delay);

        joy = joy_read(JOY_1);
    }

    joy_uninstall();

    #else
    line_d = col_d = 0;

    while (bounce_count < 100) // One hundred bounces
    {
        scroll_playfield(line, col);
        //cprintf("%d %d ", line, col);
        //cprintf("%d %d\n\r", line_d, col_d);

        // Update line and col
        line += line_d;
        col  += col_d;

        // Bounce
        if(line == (PF_LINES - PF_LINES_PER_PAGE)-1) {
            line_d = -1;
            ++bounce_count;
        }
        else if(line <= 0) {
            line_d = 1;
            ++bounce_count;
        }

        if(col == (PF_COLS - PF_COLS_PER_PAGE)-1) {
            col_d = -1;
            ++bounce_count;
        }
        else if(col <= 0) {
            col_d = 1;
            ++bounce_count;
        }
        for(delay = 0; delay < DELAY; ++delay);
        //sleep(1);
    }

    #endif

    close_graphics();

    cprintf("Hit Key To Close");
    cgetc();  // Pause

    return 0;
}
