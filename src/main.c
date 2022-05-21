// Our includes first
#include "graphics.h"
#include "playfield.h"
#include "types.h"

// Atari specific includes next
#include <atari.h>
#include <joystick.h>
#include <conio.h>

// Standard C includes
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define USE_JOYSTICK

int main()
{
    short line, col;
    short line_d, col_d;
    byte bounce_count = 0;
    #ifdef USE_JOYSTICK
    int joy;
    #endif

    init_graphics();
    init_playfield();

    line = col = 0;
    line_d = col_d = 1;

    #ifdef USE_JOYSTICK

    joy_install(joy_static_stddrv);

    joy = joy_read(JOY_1);
    while (!JOY_BTN_1(joy))
    {
        if (JOY_UP(joy))
        {
            //cprintf("UP\n");
            --line;
        }
        else if (JOY_DOWN(joy))
        {
            //cprintf("DOWN\n");
            ++line;
        }
        else if (JOY_LEFT(joy))
        {
            //cprintf("LEFT\n");
            --col;            
        }
        else if (JOY_RIGHT(joy))
        {
            //cprintf("RIGHT\n");
            ++col;          
        }

        // Clamp
        if (line < 0)
            line = 0;
        else if (line >= (PF_LINES-PF_LINES_PAGE))
            line = (PF_LINES-PF_LINES_PAGE);

        if (col < 0)
            col = 0;
        else if (col >= (PF_COLS-PF_COLS_PAGE))
            col = (PF_COLS-PF_COLS_PAGE);
        
        scroll_playfield(line, col);

        joy = joy_read(JOY_1);
    }

    joy_uninstall();

    #else

    while (bounce_count < 100) // One hundred bounces
    {
        scroll_playfield(line, col);

        // Update line and col
        line += line_d;
        col  += col_d;

        // Bounce
        if(line >= (PF_LINES-PF_LINES_PAGE)) {
            line_d = -1;
            ++bounce_count;
        }
        else if(line <= 0) {
            line_d = 1;
            ++bounce_count;
        }

        if(col >= (PF_COLS-PF_COLS_PAGE)) {
            col_d = -1;
            ++bounce_count;
        }
        else if(col <= 0) {
            col_d = 1;
            ++bounce_count;
        }
        //sleep(1);
    }

    #endif

    close_graphics();

    return 0;
}
