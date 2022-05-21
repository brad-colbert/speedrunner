// Our includes first
#include "graphics.h"
#include "playfield.h"
#include "types.h"

// Atari specific includes next
#include <atari.h>

// Standard C includes
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define offset(pr, pc, r, c) (pr * PAGE_COLS * 24 * 40  +  pc * 40  +  r * PAGE_COLS * 40  +  c)

int main()
{
    short line, col;
    short line_d, col_d;
    byte bounce_count = 0;

    init_graphics();
    init_playfield();

    line = col = 0;
    line_d = col_d = 1;

    while (bounce_count < 100) // One hundred bounces
    {
        scroll_playfield(line, col);

        // Update line and col
        line += line_d;
        col  += col_d;

        // Bounce
        if(line >= PF_LINES) {
            line_d = -1;
            ++bounce_count;
        }
        else if(line <= 0) {
            line_d = 1;
            ++bounce_count;
        }

        if(col >= PF_COLS) {
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
