// Our includes first
#include "graphics.h"
#include "playfield.h"
#include "types.h"
#include "playfield_utils.h"

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
    short line, col;

    cprintf("Hit Key");
    cgetc();  // Pause

    init_graphics();
    init_playfield();

    #ifndef USE_JOYSTICK
    line_d = col_d = 0;
    #endif
    line = col = 0;

    #ifdef USE_JOYSTICK

    joy_install(joy_static_stddrv);

    joy = joy_read(JOY_1);
    while (!JOY_BTN_1(joy))
    {
        if (JOY_UP(joy))
            --line;
        else if (JOY_DOWN(joy))
            ++line;

        if (JOY_LEFT(joy))
            --col;
        else if (JOY_RIGHT(joy))
            ++col;

        // Put some bounds on the coordinates
        if(line >= (PF_LINES - PF_LINES_PER_PAGE))
            line = PF_LINES - PF_LINES_PER_PAGE;
        if(line < 0)
            line = 0;

        if(col >= (PF_COLS - PF_COLS_PER_PAGE))
            col = PF_COLS - PF_COLS_PER_PAGE;
        if(col < 0)
            col = 0;
        
        scroll_playfield((u_short)line, (u_short)col);

        for(delay = 0; delay < DELAY; ++delay);

        joy = joy_read(JOY_1);
    }

    joy_uninstall();

    #else

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
